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

// OpenWatcom headers doesn't have GpiDrawBits() declaration
extern "C" {
    LONG APIENTRY GpiDrawBits(HPS hps, PVOID pBits, PBITMAPINFO2 pbmiInfoTable,
                              LONG lCount, PPOINTL aptlPoints, LONG lRop, ULONG flOptions);
}

#define UNITS_MULTIPLIER    100
#define STD_IMAGE_ZOOM      2.0
#define HIGH_IMAGE_ZOOM     3.0
#define PS_PRINT_BUF_SIZE   32768
#define TEST_MARGIN         10


class LucidePrinting
{
    public:
        LucidePrinting( HWND hWndFrame, LuDocument *_doc,
                        const char *_title, PrintSetup *_psetup );
        ~LucidePrinting();
        void doPrint();

    private:
        bool queryCurrentForm( HAB lhab, PHCINFO pcurForm );
        void printPagePm( long page, HPS hpsPrinter, PHCINFO pcurForm );
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
    DEVOPENSTRUC dos   = { 0 };
    SIZEL        sizel = { 0 };

    HCINFO curForm = { 0 };
    if ( !queryCurrentForm( lhab, &curForm ) ) {
        return false;
    }

    // build a devopenstruct for the call to DevOpenDC
    dos.pszLogAddress = psetup->QueueInfo.pszName;              // 1
    strcpy( achDriverName, psetup->QueueInfo.pszDriverName );
    achDriverName[ strcspn( achDriverName, "." ) ] = '\0';
    dos.pszDriverName = achDriverName;                          // 2
    dos.pdriv         = psetup->QueueInfo.pDriverData;          // 3
    dos.pszDataType   = "PM_Q_STD";                             // 4

    HDC hdcPrinter = DevOpenDC( lhab, OD_QUEUED, "*", 4L, (PDEVOPENDATA)&dos, NULLHANDLE );
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

    long totalpages = psetup->pgto - psetup->pgfrom + 1;
    for ( long pg = psetup->pgfrom; pg <= psetup->pgto; pg++ )
    {
        char *fmt = newstrdupL( PRINT_PRINTING_PAGE_OF );
        char *buf = new char[ 255 ];
        snprintf( buf, 255, fmt, pg, totalpages );
        progressDlg->setText( buf );
        delete fmt;
        delete buf;

        printPagePm( pg - 1, hpsPrinter, &curForm );

        if ( pg != psetup->pgto ) {
            DevEscape( hdcPrinter, DEVESC_NEWFRAME, 0L, NULL, NULL, NULL );
        }

        if ( abortPrinting ) {
            break;
        }
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


void LucidePrinting::printPagePm( long page, HPS hpsPrinter, PHCINFO pcurForm )
{
    long bpp = doc->getBpp( ev );
    double w = 0, h = 0;
    doc->getPageSize( ev, page, &w, &h );

    // Magrins
    LONG mLeft   = __max( TEST_MARGIN, pcurForm->xLeftClip );
    LONG mBottom = __max( TEST_MARGIN, pcurForm->yBottomClip );
    LONG mRight  = __max( TEST_MARGIN, pcurForm->cx - pcurForm->xRightClip );
    LONG mTop    = __max( TEST_MARGIN, pcurForm->cy - pcurForm->yTopClip );

    // Count paper page size in hi-metric
    LONG pwidth = ( pcurForm->cx - mLeft - mRight ) * UNITS_MULTIPLIER;
    LONG pheight = ( pcurForm->cy - mTop - mBottom ) * UNITS_MULTIPLIER;

    double zoom = 1.0;
    if ( doc->isScalable( ev ) )
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
        doc->renderPageToPS( ev, page, 0, 0, rclx, rcly, zoom, 0, hpsPrinter, &rclDraw );
    }
    else
    {
        LuPixbuf *pixbuf = new LuPixbuf( ev, rclx, rcly, bpp );
        POINTL aptlPoints[4]={ rclDraw.xLeft, rclDraw.yBottom,
                               rclDraw.xRight-1, rclDraw.yTop-1,
                               0, 0, rclx, rcly };

        doc->renderPageToPixbuf( ev, page, 0, 0, rclx, rcly, zoom, 0, pixbuf );

        LONG lRop = ROP_SRCCOPY;
        BITMAPINFO2 pbmi;
        pbmi.cbFix = 16L;
        pbmi.cx = rclx;
        pbmi.cy = rcly;
        pbmi.cPlanes = 1;
        pbmi.cBitCount = bpp * 8;
        GpiDrawBits( hpsPrinter, pixbuf->getDataPtr( ev ), &pbmi, 4L,
                     aptlPoints, lRop, BBO_IGNORE );
        delete pixbuf;
    }
}



bool LucidePrinting::doPsPrint( HAB lhab )
{
    CHAR         achDriverName[ DRIVERNAME_LENGTH ] = "";
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
    LONG mLeft   = __max( TEST_MARGIN, curForm.xLeftClip );
    LONG mBottom = __max( TEST_MARGIN, curForm.yBottomClip );
    LONG mRight  = __max( TEST_MARGIN, curForm.cx - curForm.xRightClip );
    LONG mTop    = __max( TEST_MARGIN, curForm.cy - curForm.yTopClip );

    // Count paper page size in 1/72 inches
    double pwidth = ( (double)( curForm.cx - mLeft - mRight ) / 25.4 ) * 72.0;
    double pheight = ( (double)( curForm.cy - mTop - mBottom ) / 25.4 ) * 72.0;

    char tmpps[ CCHMAXPATHCOMP ] = "";
    char *tmpenv = getenv( "TMP" );
    strcpy( tmpps, ( tmpenv == NULL ) ? ".\\" : tmpenv );
    if ( tmpps[ strlen( tmpps ) - 1 ] != '\\' ) {
        strcat( tmpps, "\\" );
    }
    strcat( tmpps, "TMPLUCID.PS" );

    BOOL rc = doc->exportToPostScript( ev, tmpps, psetup->pgfrom-1, psetup->pgto-1,
                                       pwidth, pheight, false, &abortPrinting );

    if ( abortPrinting ) {
        unlink( tmpps );
        return true;
    }
    if ( !rc ) {
        unlink( tmpps );
        return false;
    }

    char *spooling_ps = newstrdupL( PRINT_SPOOLING_POSTSCRIPT );
    progressDlg->setText( spooling_ps );
    delete spooling_ps;

    // build a devopenstruct for the call to SplQmOpen
    dos.pszLogAddress = psetup->QueueInfo.pszName;              // 1
    strcpy( achDriverName, psetup->QueueInfo.pszDriverName );
    achDriverName[ strcspn( achDriverName, "." ) ] = '\0';
    dos.pszDriverName = achDriverName;                          // 2
    dos.pdriv         = psetup->QueueInfo.pDriverData;          // 3
    dos.pszDataType   = "PM_Q_RAW";                             // 4

    HSPL hspl = SplQmOpen( "*", 4L, (PQMOPENDATA)&dos );
    if ( hspl == SPL_ERROR ) {
        unlink( tmpps );
        return false;
    }

    rc = SplQmStartDoc( hspl, title );
    if ( !rc ) {
        SplQmAbort( hspl );
        unlink( tmpps );
        return false;
    }

    FILE *f = fopen( tmpps, "rb" );
    if ( f == NULL ) {
        SplQmAbort( hspl );
        unlink( tmpps );
        return false;
    }

    bool splerr = false;
    char *pcl_prolog = "\x1b%-12345X@PJL JOB\n@PJL ENTER LANGUAGE = POSTSCRIPT \n";
    char *pcl_epilog = "\x1b%-12345X@PJL EOJ\n";

    if ( !( rc = SplQmWrite( hspl, strlen( pcl_prolog ), pcl_prolog ) ) ) {
        splerr = true;
    }

    void *buf = malloc( PS_PRINT_BUF_SIZE );
    int rd = 0;
    while ( rc && ( rd = fread( buf, 1, PS_PRINT_BUF_SIZE, f ) ) != 0 ) {
        rc = SplQmWrite( hspl, rd, buf );
        if ( !rc || abortPrinting ) {
            splerr = true;
            break;
        }
    }
    free( buf );
    fclose( f );
    unlink( tmpps );

    if ( !splerr ) {
        if ( !( rc = SplQmWrite( hspl, strlen( pcl_epilog ), pcl_epilog ) ) ) {
            splerr = true;
        }
    }

    if ( splerr ) {
        SplQmAbort( hspl );
        if ( !abortPrinting ) {
            return false;
        }
    }
    else {
        SplQmEndDoc( hspl );
        SplQmClose( hspl );
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

    //long lTech = 0;
    //DevQueryCaps( hdcPrinterInfo, CAPS_TECHNOLOGY, sizeof(long), &lTech );
    //somPrintf( "lTech: 0x%x\n", lTech );

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

