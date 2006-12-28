/* ***** BEGIN LICENSE BLOCK *****
 * Version: CDDL 1.0/LGPL 2.1
 *
 * The contents of this file are subject to the COMMON DEVELOPMENT AND
 * DISTRIBUTION LICENSE (CDDL) Version 1.0 (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at http://www.sun.com/cddl/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Initial Developer of the Original Code is
 * Eugene Romanenko, netlabs.org.
 * Portions created by the Initial Developer are Copyright (C) 2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the LGPL are applicable instead of those
 * above. If you wish to allow use of your version of this file only under the
 * terms of the LGPL, and not to allow others to use your version of this file
 * under the terms of the CDDL, indicate your decision by deleting the
 * provisions above and replace them with the notice and other provisions
 * required by the LGPL. If you do not delete the provisions above, a recipient
 * may use your version of this file under the terms of any one of the CDDL
 * or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */


#define INCL_WIN
#define INCL_GPI
#define INCL_DOS
#define INCL_DEV
#define INCL_ERRORS
#define INCL_SPL
#define INCL_SPLDOSPRINT
#include <os2.h>

#include <ludoc.xh>

#include <string.h>
#include <process.h>
#include <stdio.h>
#include <io.h>

#include "globals.h"
#include "progressDlg.h"
#include "print.h"
#include "luutils.h"
#include "messages.h"
#include "neuquant.h"


#ifndef DEVESC_ERROR
#define DEVESC_ERROR        (-1L)
#endif

#define UNITS_MULTIPLIER    100
#define STD_IMAGE_ZOOM      2.0
#define HIGH_IMAGE_ZOOM     3.0
#define PS_PRINT_BUF_SIZE   32768

void rgb_to_pal8( LuPixbuf *dst, LuPixbuf *src, int width, int height, BYTE *p_pal );


class LucidePrinting
{
    public:
        LucidePrinting( HWND hWndFrame, LuDocument *_doc,
                        const char *_title, PrintSetup *_psetup );
        ~LucidePrinting();
        void doPrint();

    private:
        bool queryCurrentForm( HAB lhab, PHCINFO pcurForm );
        void printPagePm( long page, HPS hpsPrinter, PHCINFO pcurForm, bool reduceColors );
        bool doPmPrint( HAB lhab );
        bool doPsPrint( HAB lhab );

        HWND hFrame;
        LuDocument *doc;
        char *title;
        PrintSetup *psetup;
        boolean abortPrinting;
        ProgressDlg *progressDlg;

        static void printabort( void *data );
        static void printthread( void *data );
};


void printDocument( HWND hWndFrame, LuDocument *doc, const char *title, PrintSetup *psetup )
{
    LucidePrinting *p = new LucidePrinting( hWndFrame, doc, title, psetup );
    p->doPrint();
}


LucidePrinting::LucidePrinting( HWND hWndFrame, LuDocument *_doc,
                                const char *_title, PrintSetup *_psetup )
{
    hFrame = hWndFrame;
    doc    = _doc;
    title  = newstrdup( _title );
    psetup = new PrintSetup;
    memcpy( psetup, _psetup, sizeof( PrintSetup ) );
    abortPrinting = false;
    progressDlg = new ProgressDlg( hWndFrame );
}

LucidePrinting::~LucidePrinting()
{
    delete title;
    delete psetup;
    delete progressDlg;
}

void LucidePrinting::doPrint()
{
    progressDlg->setBreakFunc( printabort, this );
    progressDlg->setText( "" );
    progressDlg->show( printthread, this );
}

bool LucidePrinting::doPmPrint( HAB lhab )
{
    CHAR         achDriverName[ DRIVERNAME_LENGTH ] = "";
    CHAR         achQueueProcParams[ 8 ] = "";
    DEVOPENSTRUC dos   = { 0 };
    SIZEL        sizel = { 0 };

    HCINFO curForm = { 0 };
    if ( !queryCurrentForm( lhab, &curForm ) ) {
        return false;
    }

    // build a devopenstruct for the call to DevOpenDC
    dos.pszLogAddress      = psetup->QueueInfo.pszName;              // 1
    strcpy( achDriverName, psetup->QueueInfo.pszDriverName );
    achDriverName[ strcspn( achDriverName, "." ) ] = '\0';
    dos.pszDriverName      = achDriverName;                          // 2
    dos.pdriv              = psetup->QueueInfo.pDriverData;          // 3
    dos.pszDataType        = "PM_Q_STD";                             // 4
    dos.pszComment         = (PSZ)appName;                           // 5
    dos.pszQueueProcName   = NULL;                                   // 6
    snprintf( achQueueProcParams, sizeof( achQueueProcParams ), "COP=%d", psetup->copies );
    dos.pszQueueProcParams = achQueueProcParams;                     // 7

    HDC hdcPrinter = DevOpenDC( lhab, OD_QUEUED, "*", 7L, (PDEVOPENDATA)&dos, NULLHANDLE );
    if ( hdcPrinter == DEV_ERROR ) {
        return false;
    }

    // PS in HiMetric, 0.01 mm
    HPS hpsPrinter = GpiCreatePS( lhab, hdcPrinter, &sizel, PU_HIMETRIC | GPIA_ASSOC );
    if ( hpsPrinter == DEV_ERROR ) {
        DevCloseDC( hdcPrinter );
        return false;
    }

    // Issue STARTDOC to begin printing
    DevEscape( hdcPrinter, DEVESC_STARTDOC, strlen(title), (PBYTE)title, NULL, NULL );


    long totalpages = abs( psetup->pgto - psetup->pgfrom ) + 1;
    long pg = psetup->pgfrom;
    for ( long i = 0; i < totalpages; i++ )
    {
        char *fmt = newstrdupL( PRINT_PRINTING_PAGE_OF );
        char *buf = new char[ 255 ];
        snprintf( buf, 255, fmt, pg, i + 1, totalpages );
        progressDlg->setText( buf );
        delete fmt;
        delete buf;

        printPagePm( pg - 1, hpsPrinter, &curForm, ( totalpages > 1 ) );

        if ( pg != psetup->pgto ) {
            DevEscape( hdcPrinter, DEVESC_NEWFRAME, 0L, NULL, NULL, NULL );
        }

        if ( abortPrinting ) {
            break;
        }

        pg += ( psetup->pgfrom <= psetup->pgto ) ? 1 : -1;
    }

    // Issue DEVESC_ENDDOC, or DEVESC_ABORTDOC if printing was aborted
    DevEscape( hdcPrinter, abortPrinting ? DEVESC_ABORTDOC : DEVESC_ENDDOC,
               0L, NULL, NULL, NULL );

    // Release PS and DC
    GpiAssociate( hpsPrinter, NULLHANDLE );
    GpiDestroyPS( hpsPrinter );
    DevCloseDC( hdcPrinter );
    return true;
}


void LucidePrinting::printPagePm( long page, HPS hpsPrinter,
                                  PHCINFO pcurForm, bool reduceColors )
{
    long bpp = doc->getBpp( ev );
    double w = 0, h = 0;
    doc->getPageSize( ev, page, &w, &h );

    // Magrins
    LONG mLeft   = __max( psetup->margin_left, pcurForm->xLeftClip );
    LONG mBottom = __max( psetup->margin_bottom, pcurForm->yBottomClip );
    LONG mRight  = __max( psetup->margin_right, pcurForm->cx - pcurForm->xRightClip );
    LONG mTop    = __max( psetup->margin_top, pcurForm->cy - pcurForm->yTopClip );

    // Count paper page size in hi-metric
    LONG pwidth = ( pcurForm->cx - mLeft - mRight ) * UNITS_MULTIPLIER;
    LONG pheight = ( pcurForm->cy - mTop - mBottom ) * UNITS_MULTIPLIER;

    double zoom = 1.0;
    if ( doc->isScalable( ev ) && !doc->isFixedImage( ev ) )
    {
        double maxcoeff = psetup->higherQuality ? HIGH_IMAGE_ZOOM : STD_IMAGE_ZOOM;
        zoom = __min( (double)pwidth / w, (double)pheight / h );
        if ( zoom > maxcoeff ) {
            zoom = maxcoeff;
        }
    }

    //somPrintf( "Doc pgsz: %g/%g  zoom: %g\n", w, h, zoom );
    //somPrintf( "Paper %s, pgsz: %d/%d\n", pcurForm->szFormname, pcurForm->cx, pcurForm->cy );
    //somPrintf( "pw/ph %d/%d\n", pwidth, pheight );

    w *= zoom;
    h *= zoom;
    double pgzoom = __min( (double)pwidth / w, (double)pheight / h );

    // Printed size
    LONG prwidth = w * pgzoom;
    LONG prheight = h * pgzoom;
    LONG yPos = 0;
    if ( prheight < pheight ) {
        yPos = pheight - prheight;
    }
    RECTL rclDraw = { mLeft*UNITS_MULTIPLIER, (mBottom*UNITS_MULTIPLIER)+yPos,
                      prwidth, prheight+yPos };

    LONG rclx = w;
    LONG rcly = h;

    if ( doc->isRenderIntoPS( ev ) )
    {
        doc->renderPageToPS( ev, page, 0, 0, rclx, rcly, zoom, 0, hpsPrinter, &rclDraw,
                             NULL, NULL );
    }
    else
    {
        LuPixbuf *pixbuf = new LuPixbuf( ev, rclx, rcly, bpp );
        POINTL aptlPoints[4]={ rclDraw.xLeft, rclDraw.yBottom,
                               rclDraw.xRight-1, rclDraw.yTop-1,
                               0, 0, rclx, rcly };

        doc->renderPageToPixbuf( ev, page, 0, 0, rclx, rcly, zoom, 0, pixbuf,
                                 NULL, NULL );

        LONG lRop = ROP_SRCCOPY;
        if ( reduceColors )
        {
            LONG bhsz = sizeof( BITMAPINFOHEADER2 ) + ( sizeof( RGB2 ) * 256 );
            BITMAPINFO2 *pbmi = (BITMAPINFO2 *)malloc( bhsz );
            memset( pbmi, 0, bhsz );
            pbmi->cbFix = sizeof( BITMAPINFOHEADER2 );
            pbmi->cx = rclx;
            pbmi->cy = rcly;
            pbmi->cPlanes = 1;
            pbmi->cBitCount = 8;
            pbmi->ulCompression = BCA_UNCOMP;
            pbmi->cbImage = 0;
            pbmi->cxResolution = 0;
            pbmi->cyResolution = 0;
            pbmi->cclrUsed = 0;
            pbmi->cclrImportant = 0;
            pbmi->usUnits = BRU_METRIC;
            pbmi->usReserved = 0;
            pbmi->usRecording = BRA_BOTTOMUP;
            pbmi->usRendering = BRH_NOTHALFTONED;
            pbmi->cSize1 = 0;
            pbmi->cSize2 = 0;
            pbmi->ulColorEncoding = BCE_RGB;
            pbmi->ulIdentifier = 0;

            PBYTE pal = ((PBYTE)pbmi) + sizeof( BITMAPINFOHEADER2 );
            LuPixbuf *p = new LuPixbuf( ev, rclx, rcly, 1 );

            rgb_to_pal8( p, pixbuf, rclx, rcly, pal );

            GpiDrawBits( hpsPrinter, p->getDataPtr( ev ), pbmi, 4L,
                         aptlPoints, lRop, BBO_IGNORE );
            delete p;
            free( pbmi );
        }
        else
        {
            BITMAPINFO2 pbmi;
            pbmi.cbFix = 16L;
            pbmi.cx = rclx;
            pbmi.cy = rcly;
            pbmi.cPlanes = 1;
            pbmi.cBitCount = bpp * 8;
            GpiDrawBits( hpsPrinter, pixbuf->getDataPtr( ev ), &pbmi, 4L,
                         aptlPoints, lRop, BBO_IGNORE );
        }
        delete pixbuf;
    }
}


bool LucidePrinting::doPsPrint( HAB lhab )
{
    CHAR         achDriverName[ DRIVERNAME_LENGTH ] = "";
    CHAR         achQueueProcParams[ 8 ] = "";
    DEVOPENSTRUC dos   = { 0 };
    SIZEL        sizel = { 0 };

    HCINFO curForm = { 0 };
    if ( !queryCurrentForm( lhab, &curForm ) ) {
        return false;
    }

    char *generating_ps = newstrdupL( PRINT_GENERATING_POSTSCRIPT );
    progressDlg->setText( generating_ps );
    delete generating_ps;

    // Magrins
    LONG mLeft   = __max( psetup->margin_left, curForm.xLeftClip );
    LONG mBottom = __max( psetup->margin_bottom, curForm.yBottomClip );
    LONG mRight  = __max( psetup->margin_right, curForm.cx - curForm.xRightClip );
    LONG mTop    = __max( psetup->margin_top, curForm.cy - curForm.yTopClip );

    // Count paper page size in 1/72 inches
    double pwidth = ( (double)( curForm.cx - mLeft - mRight ) / 25.4 ) * 72.0;
    double pheight = ( (double)( curForm.cy - mTop - mBottom ) / 25.4 ) * 72.0;

    char tmpps[ CCHMAXPATH ] = "";
    if ( psetup->psToFile ) {
        strcpy( tmpps, psetup->psFile );
    }
    else {
        getTmpDir( tmpps );
        strcat( tmpps, "TMPLUCID.PS" );
    }

    boolean rcexp = doc->exportToPostScript( ev, tmpps, psetup->pgfrom-1, psetup->pgto-1,
                                             pwidth, pheight, &abortPrinting );

    if ( abortPrinting ) {
        unlink( tmpps );
        return true;
    }
    if ( !rcexp ) {
        unlink( tmpps );
        return false;
    }

    if ( !psetup->psToFile )
    {
        char *spooling_ps = newstrdupL( PRINT_SPOOLING_POSTSCRIPT );
        progressDlg->setText( spooling_ps );
        delete spooling_ps;

        // build a devopenstruct for the call to DevOpenDC
        dos.pszLogAddress      = psetup->QueueInfo.pszName;              // 1
        strcpy( achDriverName, psetup->QueueInfo.pszDriverName );
        achDriverName[ strcspn( achDriverName, "." ) ] = '\0';
        dos.pszDriverName      = achDriverName;                          // 2
        dos.pdriv              = psetup->QueueInfo.pDriverData;          // 3
        dos.pszDataType        = "PM_Q_RAW";                             // 4
        dos.pszComment         = (PSZ)appName;                           // 5
        dos.pszQueueProcName   = NULL;                                   // 6
        snprintf( achQueueProcParams, sizeof( achQueueProcParams ), "COP=%d", psetup->copies );
        dos.pszQueueProcParams = achQueueProcParams;                     // 7

        HDC hdcPrinter = DevOpenDC( lhab, OD_QUEUED, "*", 7L, (PDEVOPENDATA)&dos, NULLHANDLE );
        if ( hdcPrinter == DEV_ERROR ) {
            unlink( tmpps );
            return false;
        }

        // Issue STARTDOC to begin printing
        LONG rc = DevEscape( hdcPrinter, DEVESC_STARTDOC, strlen(title), (PBYTE)title, NULL, NULL );
        if ( rc == DEVESC_ERROR ) {
            DevCloseDC( hdcPrinter );
            unlink( tmpps );
            return false;
        }

        FILE *f = fopen( tmpps, "rb" );
        if ( f == NULL ) {
            DevEscape( hdcPrinter, DEVESC_ABORTDOC, 0L, NULL, NULL, NULL );
            DevCloseDC( hdcPrinter );
            unlink( tmpps );
            return false;
        }

        bool splerr = false;
        void *buf = malloc( PS_PRINT_BUF_SIZE );
        int rd = 0;
        while ( ( rc != DEVESC_ERROR ) && ( rd = fread( buf, 1, PS_PRINT_BUF_SIZE, f ) ) != 0 )
        {
            rc = DevEscape( hdcPrinter, DEVESC_RAWDATA, rd, (char *)buf, NULL, NULL );
            if ( ( rc == DEVESC_ERROR ) || abortPrinting ) {
                splerr = true;
                break;
            }
        }
        free( buf );
        fclose( f );
        unlink( tmpps );

        DevEscape( hdcPrinter, splerr ? DEVESC_ABORTDOC : DEVESC_ENDDOC,
                   0L, NULL, NULL, NULL );
        DevCloseDC( hdcPrinter );

        if ( splerr && !abortPrinting ) {
            return false;
        }
    }

    return true;
}


bool LucidePrinting::queryCurrentForm( HAB lhab, PHCINFO pcurForm )
{
    CHAR         achDriverName[ DRIVERNAME_LENGTH ] = "";
    DEVOPENSTRUC dos   = { 0 };
    // build a devopenstruct for the call to DevOpenDC
    dos.pszLogAddress = psetup->QueueInfo.pszName;              // 1
    strcpy( achDriverName, psetup->QueueInfo.pszDriverName );
    achDriverName[ strcspn( achDriverName, "." ) ] = '\0';
    dos.pszDriverName = achDriverName;                          // 2
    dos.pdriv = psetup->QueueInfo.pDriverData;                  // 3

    HDC hdcPrinterInfo = DevOpenDC( lhab, OD_INFO, "*", 3L, (PDEVOPENDATA)&dos, NULLHANDLE );
    if ( hdcPrinterInfo == DEV_ERROR ) {
        return false;
    }

    LONG lForms = DevQueryHardcopyCaps( hdcPrinterInfo, 0, 0, NULL );
    if ( lForms == DQHC_ERROR ) {
        DevCloseDC( hdcPrinterInfo );
        return false;
    }

    HCINFO *forms = new HCINFO[ lForms ];
    memset( forms, 0, sizeof( HCINFO ) * lForms );
    lForms = DevQueryHardcopyCaps( hdcPrinterInfo, 0, lForms, forms );
    if ( lForms == DQHC_ERROR ) {
        delete forms;
        DevCloseDC( hdcPrinterInfo );
        return false;
    }

    for ( LONG i = 0; i < lForms; i++ ) {
        if ( forms[i].flAttributes & HCAPS_CURRENT ) {
            memcpy( pcurForm, &( forms[i] ), sizeof( HCINFO ) );
            break;
        }
    }

    delete forms;
    DevCloseDC( hdcPrinterInfo );
    return true;
}

// static method
void LucidePrinting::printabort( void *data )
{
    ((LucidePrinting *)data)->abortPrinting = true;
}

// static method, thread for asynchronous printing
void LucidePrinting::printthread( void *p )
{
    DosSetPriority( PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_MAXIMUM, 0 );
    LucidePrinting *_this = (LucidePrinting *)p;

    HAB thab = WinInitialize( 0 );
    HMQ thmq = WinCreateMsgQueue( thab, 0 );

    bool printOk = false;
    if ( _this->psetup->ptype == TypePostScript ) {
        printOk = _this->doPsPrint( thab );
    }
    else {
        printOk = _this->doPmPrint( thab );
    }
    _this->progressDlg->hide();

    if ( !printOk )
    {
        char *printfailed = newstrdupL( PRINT_FAILED );
        WinMessageBox( HWND_DESKTOP, _this->hFrame, printfailed, NULL,
                       1, MB_OK | MB_ERROR | MB_MOVEABLE );
        delete printfailed;
    }

    WinDestroyMsgQueue( thmq );
    WinTerminate( thab );
    _endthread();

    delete _this;
}


// Convert RGB 24/32 bit pixbuf into 8 bit palettized
static void rgb_to_pal8( LuPixbuf *dst, LuPixbuf *src, int width, int height, BYTE *p_pal )
{
    NeuQuantizer *nq = new NeuQuantizer( src, 256 );

    nq->initnet();
    nq->learn( 10 );
    nq->unbiasnet();

    int *palette = (int *)nq->getNetwork();
    for ( int i = 0; i < ( 256 * 4 ); i++ ) {
        p_pal[ i ] = palette[ i ];
    }
    nq->inxbuild();

    unsigned char *p_src = (unsigned char *)src->getDataPtr( ev );
    unsigned char *p_dst = (unsigned char *)dst->getDataPtr( ev );
    long rowsize_src = src->getRowSize( ev );
    long rowsize_dst = dst->getRowSize( ev );
    long x = src->getWidth( ev );
    long y = src->getHeight( ev );
    long bpp = src->getBpp( ev );

    for ( long py = 0; py < y; py++ )
    {
        BYTE *row_src = p_src + ( rowsize_src * py );
        long row_dst = rowsize_dst * py;
        for ( long px = 0; px < x; px++ )
        {
            BYTE *pix = row_src + ( px * bpp );
            p_dst[ row_dst + px ] = nq->inxsearch( pix[0], pix[1], pix[2] );
        }
    }

    delete nq;
}

