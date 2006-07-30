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
#define INCL_DEV
#define INCL_ERRORS
#define INCL_SPL
#define INCL_SPLDOSPRINT
#include <os2.h>

#include <ludoc.xh>

#include <string.h>

#include "print.h"

// OpenWatcom headers doesn't have GpiDrawBits() declaration
extern "C" {
    LONG APIENTRY GpiDrawBits(HPS hps, PVOID pBits, PBITMAPINFO2 pbmiInfoTable,
                              LONG lCount, PPOINTL aptlPoints, LONG lRop, ULONG flOptions);
}

#define UNITS_MULTIPLIER    100

#define TEST_MARGIN         10

void printPage( LuDocument *doc, long page, HPS hpsPrinter, PHCINFO pcurForm );
void queryCurrentForm( HDC hdcPrinter, PHCINFO pcurForm );

void printDocument( LuDocument *doc, void *q )
{
    PPRQINFO3    pQueueInfo = (PPRQINFO3)q;
    CHAR         achDriverName[ DRIVERNAME_LENGTH ] = "";
    SIZEL        sizel = { 0 };
    DEVOPENSTRUC dos   = { 0 };

    // build a devopenstruct for the call to DevOpenDC
    dos.pszLogAddress = pQueueInfo->pszName;
    strcpy( achDriverName, pQueueInfo->pszDriverName );
    achDriverName[ strcspn( achDriverName, "." ) ] = '\0';
    dos.pszDriverName = achDriverName;
    dos.pdriv = pQueueInfo->pDriverData;

    HDC hdcPrinter = DevOpenDC( hab, OD_QUEUED, "*", 3L, (PDEVOPENDATA)&dos, NULLHANDLE );
    if ( hdcPrinter == DEV_ERROR ) {
        somPrintf( "DevOpenDC error\n" );
        return;
    }

    // PS in HiMetric, 0.01 mm
    HPS hpsPrinter = GpiCreatePS( hab, hdcPrinter, &sizel, PU_HIMETRIC | GPIA_ASSOC );
    if ( hpsPrinter == DEV_ERROR ) {
        DevCloseDC( hdcPrinter );
        somPrintf( "GpiCreatePS error\n" );
        return;
    }

    HCINFO curForm = { 0 };
    queryCurrentForm( hdcPrinter, &curForm );
    char *psz = "test";
    // Issue STARTDOC to begin printing
    DevEscape( hdcPrinter, DEVESC_STARTDOC, (LONG)strlen(psz), (PBYTE)psz, NULL, NULL );

    somPrintf( "begin!\n" );

    printPage( doc, 0, hpsPrinter, &curForm );

    somPrintf( "end!\n" );

    DevEscape( hdcPrinter, DEVESC_ENDDOC, 0L, NULL, NULL, NULL );

    // Release PS and DC
    GpiAssociate( hpsPrinter, NULLHANDLE );
    GpiDestroyPS( hpsPrinter );
    DevCloseDC( hdcPrinter );
}


static void printPage( LuDocument *doc, long page, HPS hpsPrinter, PHCINFO pcurForm )
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

    double zoom = __min( (double)pwidth / w, (double)pheight / h );
    if ( zoom > 2.0 ) {
        zoom = 2.0;
    }

    somPrintf( "Doc pgsz: %g/%g  zoom: %g\n", w, h, zoom );
    somPrintf( "Paper %s, pgsz: %d/%d\n", pcurForm->szFormname, pcurForm->cx, pcurForm->cy );
    somPrintf( "pw/ph %d/%d\n", pwidth, pheight );
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


static void queryCurrentForm( HDC hdcPrinter, PHCINFO pcurForm )
{
    LONG lForms = DevQueryHardcopyCaps( hdcPrinter, 0, 0, NULL );
    if ( lForms == DQHC_ERROR ) {
        return;
    }

    HCINFO *forms = new HCINFO[ lForms ];
    memset( forms, 0, sizeof( HCINFO ) * lForms );
    lForms = DevQueryHardcopyCaps( hdcPrinter, 0, lForms, forms );
    if ( lForms == DQHC_ERROR ) {
        delete forms;
        return;
    }

    for ( LONG i = 0; i < lForms; i++ ) {
        if ( forms[i].flAttributes & HCAPS_CURRENT ) {
            memcpy( pcurForm, &( forms[i] ), sizeof( HCINFO ) );
            break;
        }
    }
    delete forms;
}

