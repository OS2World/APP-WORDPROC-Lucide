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
#define INCL_DEV
#define INCL_ERRORS
#define INCL_SPL
#define INCL_SPLDOSPRINT
#include <os2.h>

#include <string>

#include <ludoc.xh>

#include "globals.h"
#include "printDlg.h"
#include "Lucide_res.h"
#include "luutils.h"
#include "messages.h"


char PrintDlg::defQueue[] = { 0 };


PrintDlg::PrintDlg( HWND hWndFrame, LuDocument *_doc, const char *fname, long _currentpage )
{
    hFrame      = hWndFrame;
    doc         = _doc;
    scalable    = _doc->isScalable( ev );
    fixed       = _doc->isFixedImage( ev );
    filename    = newstrdup( fname );
    currentpage = _currentpage;
    pcurForm    = new HCINFO;
    memset( pcurForm, 0, sizeof( HCINFO ) );
    psetup      = new PrintSetup;
    memset( psetup, 0, sizeof( PrintSetup ) );
}

PrintDlg::~PrintDlg()
{
    delete filename;
    delete pcurForm;
    delete psetup;
}

ULONG PrintDlg::showDialog()
{
    return WinDlgBox( HWND_DESKTOP, hFrame, printDlgProc,
                      _hmod, IDD_PRINT, this );
}

void PrintDlg::getPrintSetup( PrintSetup *p ) {
    memcpy( p, psetup, sizeof( PrintSetup ) );
}

void PrintDlg::setCurrentQInfo( HWND hwnd, PPRQINFO3 q )
{
    memcpy( &(psetup->QueueInfo), q, sizeof( PRQINFO3 ) );
    WinSetDlgItemText( hwnd, IDC_PNAME, psetup->QueueInfo.pszComment );
    WinSetDlgItemText( hwnd, IDC_PDESCRIPTION, psetup->QueueInfo.pszDriverName );
    WinEnableControl( hwnd, IDC_JOBPROPERTIES, TRUE );
    WinEnableControl( hwnd, DID_OK, TRUE );

    // Set the print type
    if ( doc->isPostScriptExportable( ev ) && isPostscriptDevice() ) {
        WinEnableControl( hwnd, IDC_TYPE_POSTSCRIPT, TRUE );
        WinCheckButton( hwnd, IDC_TYPE_POSTSCRIPT, TRUE );
    }
    else {
        WinEnableControl( hwnd, IDC_TYPE_POSTSCRIPT, FALSE );
        WinCheckButton( hwnd, IDC_TYPE_ASIMAGE, TRUE );
    }

    WinSendMsg( hwnd, WM_CONTROL,
                MPFROM2SHORT( IDC_TYPE_POSTSCRIPT, BN_CLICKED ),
                MPFROMHWND( WinWindowFromID( hwnd, IDC_TYPE_POSTSCRIPT ) ) );

    WinCheckButton( hwnd, isPortraitOrientation() ? IDC_PORTRAIT : IDC_LANDSCAPE, TRUE );

    // removed (copies to job props)
    //WinSendDlgItemMsg( hwnd, IDC_COPIES, SPBM_SETCURRENTVALUE,
    //                   MPFROMLONG( queryCopies() ), MPVOID );

    applyForm( hwnd );
}

void PrintDlg::enumQueues( HWND hwnd )
{
    HWND list = WinWindowFromID( hwnd, IDC_PNAME );
    ULONG cReturned = 0, cTotal = 0, cbNeeded = 0;
    SPLERR se = SplEnumQueue( NULL, 3, NULL, 0L, &cReturned,
                              &cTotal, &cbNeeded, NULL );
    if ( cTotal == 0L ) {
        // TODO: 'no printers installed' message  (?)
    }

    pQueueInfo = (PPRQINFO3)malloc( cbNeeded );

    se = SplEnumQueue( NULL, 3, pQueueInfo, cbNeeded, &cReturned,
                       &cTotal, &cbNeeded, NULL );
    if ( se != NO_ERROR ) {
        // TODO: error message
        free( pQueueInfo );
        pQueueInfo = NULL;
        return;
    }

    USHORT sEntry;
    for ( ULONG i = 0; i < cReturned; i++ )
    {
        sEntry = (SHORT)WinInsertLboxItem( list, LIT_END, pQueueInfo[i].pszComment );
        WinSendMsg( list, LM_SETITEMHANDLE,
                    MPFROMSHORT(sEntry), MPFROMP( &(pQueueInfo[i]) ) );

        if ( defQueue[0] == 0 ) {
            if ( pQueueInfo[i].fsType & PRQ3_TYPE_APPDEFAULT ) {
                setCurrentQInfo( hwnd, &( pQueueInfo[i] ) );
            }
        }
        else {
            if ( strcmp( pQueueInfo[i].pszName, defQueue ) == 0 ) {
                setCurrentQInfo( hwnd, &( pQueueInfo[i] ) );
            }
        }
    }
}


void PrintDlg::showJobProperties( HWND hwnd )
{
    if ( psetup->QueueInfo.pszName[0] == 0 ) {
        return;
    }

    char achDriverName[ DRIVERNAME_LENGTH ];
    char achDeviceName[ DEVICENAME_LENGTH ];

    // The pszDriverName is of the form DRIVER.DEVICE (e.g.,
    // LASERJET.HP LaserJet IID) so we need to separate it at the dot
    int i = strcspn( psetup->QueueInfo.pszDriverName, "." );
    if ( i > 0 ) {
        strncpy( achDriverName, psetup->QueueInfo.pszDriverName, i );
        achDriverName[ i ] = '\0';
        strcpy( achDeviceName, &( psetup->QueueInfo.pszDriverName[ i + 1 ] ) );
    }
    else {
        strcpy( achDriverName, psetup->QueueInfo.pszDriverName );
        *achDeviceName = '\0';
    }

    // There may be more than one printer assigned to this print queue
    // We will use the first in the comma separated list.  We would
    // need an expanded dialog for the user to be more specific.
    char *pszTemp = strchr( psetup->QueueInfo.pszPrinters, ',' );
    if ( pszTemp != NULL ) {
        // Strip off comma and trailing printer names
        *pszTemp = '\0';
    }

    // Post the job properties dialog for the printer to allow the
    // user to modify the options
    DevPostDeviceModes( hab, psetup->QueueInfo.pDriverData, achDriverName,
                        achDeviceName, psetup->QueueInfo.pszPrinters, DPDM_POSTJOBPROP );

    WinCheckButton( hwnd, isPortraitOrientation() ? IDC_PORTRAIT : IDC_LANDSCAPE, TRUE );

    // removed (copies to job props)
    //WinSendDlgItemMsg( hwnd, IDC_COPIES, SPBM_SETCURRENTVALUE,
    //                   MPFROMLONG( queryCopies() ), MPVOID );

    applyForm( hwnd );
}

HDC PrintDlg::getInfoDC()
{
    char *achDriverName = new char[ DRIVERNAME_LENGTH ];
    // build a devopenstruct for the call to DevOpenDC
    DEVOPENSTRUC *dos   = new DEVOPENSTRUC;
    memset( dos, 0, sizeof( DEVOPENSTRUC ) );
    dos->pszLogAddress = psetup->QueueInfo.pszName;              // 1
    strcpy( achDriverName, psetup->QueueInfo.pszDriverName );
    achDriverName[ strcspn( achDriverName, "." ) ] = '\0';
    dos->pszDriverName = achDriverName;                          // 2
    dos->pdriv = psetup->QueueInfo.pDriverData;                  // 3

    HDC hdcPrinterInfo = DevOpenDC( hab, OD_INFO, "*", 3L, (PDEVOPENDATA)dos, NULLHANDLE );

    delete achDriverName;
    delete dos;

    return hdcPrinterInfo;
}

bool PrintDlg::isPostscriptDevice()
{
    long lTech = 0;
    HDC hdcPrinterInfo = getInfoDC();
    if ( hdcPrinterInfo != DEV_ERROR ) {
        DevQueryCaps( hdcPrinterInfo, CAPS_TECHNOLOGY, sizeof(long), &lTech );
        DevCloseDC( hdcPrinterInfo );
    }
    return ( lTech == CAPS_TECH_POSTSCRIPT );
}

// **************************************************
// OpenWatcom headers doesn't have these declarations
// **************************************************
#ifndef DJP_SJ_ORIENTATION
typedef struct _djpItem
{
    ULONG       cb;
    ULONG       ulProperty;
    LONG        lType;
    ULONG       ulNumReturned;
    ULONG       ulValue;
} DJP_ITEM, *PDJP_ITEM;

#define DJP_ALL                 1L
#define DJP_CURRENT             2L
#define DJP_NONE                0L
#define DJP_SJ_ORIENTATION      1L
#define DJP_SJ_COPIES           16L

#define DJP_ORI_PORTRAIT        1L
#define DJP_ORI_LANDSCAPE       2L
#define DJP_ORI_REV_PORTRAIT    3L
#define DJP_ORI_REV_LANDSCAPE   4L
#endif
// **************************************************

bool PrintDlg::isPortraitOrientation()
{
    bool rVal = true;

    HDC hdcPrinterInfo = getInfoDC();
    if ( hdcPrinterInfo != DEV_ERROR )
    {
        DJP_ITEM djp[ 2 ] = { { 0 } };

        // Get Orientation from Job Properties
        djp[0].cb = sizeof( DJP_ITEM );
        djp[0].ulProperty = DJP_SJ_ORIENTATION;
        djp[0].lType = DJP_CURRENT;
        djp[0].ulNumReturned = 1;
        djp[0].ulValue = 1;

        djp[1].cb = sizeof( DJP_ITEM );
        djp[1].ulProperty = 0;
        djp[1].lType = DJP_NONE;
        djp[1].ulNumReturned = 1;
        djp[1].ulValue = 0;

        LONG outSz = psetup->QueueInfo.pDriverData->cb;
        LONG rc = DevEscape( hdcPrinterInfo, DEVESC_QUERYJOBPROPERTIES,
                             sizeof( DJP_ITEM ) * 2, (PBYTE)djp,
                             &outSz, (PBYTE)psetup->QueueInfo.pDriverData );

        if ( ( rc == DEV_OK ) || ( rc == DEV_WARNING ) )
        {
            if ( ( djp[0].lType != DJP_NONE ) &&
                 ( djp[0].ulProperty == DJP_SJ_ORIENTATION ) &&
                 ( djp[0].lType > 0 ) )
            {
                if ( ( djp[0].ulValue == DJP_ORI_LANDSCAPE ) ||
                     ( djp[0].ulValue == DJP_ORI_REV_LANDSCAPE ) ) {
                    rVal = false;
                }
            }
        }

        DevCloseDC( hdcPrinterInfo );
    }

    return rVal;
}

void PrintDlg::setPortraitOrientation( bool portrait, HWND hwnd )
{
    HDC hdcPrinterInfo = getInfoDC();
    if ( hdcPrinterInfo != DEV_ERROR )
    {
        DJP_ITEM djp[ 2 ] = { { 0 } };

        // Set Orientation
        djp[0].cb = sizeof( DJP_ITEM );
        djp[0].ulProperty = DJP_SJ_ORIENTATION;
        djp[0].lType = DJP_CURRENT;
        djp[0].ulNumReturned = 1;
        djp[0].ulValue = portrait ? DJP_ORI_PORTRAIT : DJP_ORI_LANDSCAPE;

        djp[1].cb = sizeof( DJP_ITEM );
        djp[1].ulProperty = 0;
        djp[1].lType = DJP_NONE;
        djp[1].ulNumReturned = 1;
        djp[1].ulValue = 0;

        LONG outSz = psetup->QueueInfo.pDriverData->cb;
        DevEscape( hdcPrinterInfo, DEVESC_SETJOBPROPERTIES,
                   sizeof( DJP_ITEM ) * 2, (PBYTE)djp,
                   &outSz, (PBYTE)psetup->QueueInfo.pDriverData );

        DevCloseDC( hdcPrinterInfo );

        applyForm( hwnd );
    }
}

int PrintDlg::queryCopies() // currently unused
{
    int rVal = 1;

    HDC hdcPrinterInfo = getInfoDC();
    if ( hdcPrinterInfo != DEV_ERROR )
    {
        DJP_ITEM djp[ 2 ] = { { 0 } };

        // Get number of copies from Job Properties
        djp[0].cb = sizeof( DJP_ITEM );
        djp[0].ulProperty = DJP_SJ_COPIES;
        djp[0].lType = DJP_CURRENT;
        djp[0].ulNumReturned = 1;
        djp[0].ulValue = 1;

        djp[1].cb = sizeof( DJP_ITEM );
        djp[1].ulProperty = 0;
        djp[1].lType = DJP_NONE;
        djp[1].ulNumReturned = 1;
        djp[1].ulValue = 0;

        LONG outSz = psetup->QueueInfo.pDriverData->cb;
        LONG rc = DevEscape( hdcPrinterInfo, DEVESC_QUERYJOBPROPERTIES,
                             sizeof( DJP_ITEM ) * 2, (PBYTE)djp,
                             &outSz, (PBYTE)psetup->QueueInfo.pDriverData );

        if ( ( rc == DEV_OK ) || ( rc == DEV_WARNING ) ) {
            rVal = djp[0].ulValue;
        }

        DevCloseDC( hdcPrinterInfo );
    }

    return rVal;
}

void PrintDlg::setCopies( int copies )  // currently unused
{
    HDC hdcPrinterInfo = getInfoDC();
    if ( hdcPrinterInfo != DEV_ERROR )
    {
        DJP_ITEM djp[ 2 ] = { { 0 } };

        // Set number of copies
        djp[0].cb = sizeof( DJP_ITEM );
        djp[0].ulProperty = DJP_SJ_COPIES;
        djp[0].lType = DJP_CURRENT;
        djp[0].ulNumReturned = 1;
        djp[0].ulValue = copies;

        djp[1].cb = sizeof( DJP_ITEM );
        djp[1].ulProperty = 0;
        djp[1].lType = DJP_NONE;
        djp[1].ulNumReturned = 1;
        djp[1].ulValue = 0;

        LONG outSz = psetup->QueueInfo.pDriverData->cb;
        DevEscape( hdcPrinterInfo, DEVESC_SETJOBPROPERTIES,
                   sizeof( DJP_ITEM ) * 2, (PBYTE)djp,
                   &outSz, (PBYTE)psetup->QueueInfo.pDriverData );

        DevCloseDC( hdcPrinterInfo );
    }
}

bool PrintDlg::queryCurrentForm()
{
    HDC hdcPrinterInfo = getInfoDC();
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

void PrintDlg::applyForm( HWND hwnd )
{
    if ( queryCurrentForm() )
    {
        WinSetDlgItemText( hwnd, IDC_SELECTED_FORM, pcurForm->szFormname );

        long margin_top_min    = pcurForm->cy - pcurForm->yTopClip;
        long margin_left_min   = pcurForm->xLeftClip;
        long margin_bottom_min = pcurForm->yBottomClip;
        long margin_right_min  = pcurForm->cx - pcurForm->xRightClip;

        if ( WinQueryButtonCheckstate( hwnd, IDC_IGNMARGINS ) ) {
            margin_top_min = margin_left_min = margin_bottom_min = margin_right_min = 0;
        }

        long margin_top_max    = pcurForm->cy - margin_bottom_min;
        long margin_left_max   = pcurForm->cx - margin_right_min;
        long margin_bottom_max = pcurForm->cy - margin_top_min;
        long margin_right_max  = pcurForm->cx - margin_left_min;

        WinSendDlgItemMsg( hwnd, IDC_MTOP, SPBM_SETLIMITS,
                           MPFROMLONG( margin_top_max ), MPFROMLONG( margin_top_min ) );
        WinSendDlgItemMsg( hwnd, IDC_MTOP, SPBM_SETCURRENTVALUE,
                           MPFROMLONG( margin_top_min ), MPVOID );
        WinSendDlgItemMsg( hwnd, IDC_MLEFT, SPBM_SETLIMITS,
                           MPFROMLONG( margin_left_max ), MPFROMLONG( margin_left_min ) );
        WinSendDlgItemMsg( hwnd, IDC_MLEFT, SPBM_SETCURRENTVALUE,
                           MPFROMLONG( margin_left_min ), MPVOID );
        WinSendDlgItemMsg( hwnd, IDC_MBOTTOM, SPBM_SETLIMITS,
                           MPFROMLONG( margin_bottom_max ), MPFROMLONG( margin_bottom_min ) );
        WinSendDlgItemMsg( hwnd, IDC_MBOTTOM, SPBM_SETCURRENTVALUE,
                           MPFROMLONG( margin_bottom_min ), MPVOID );
        WinSendDlgItemMsg( hwnd, IDC_MRIGHT, SPBM_SETLIMITS,
                           MPFROMLONG( margin_right_max ), MPFROMLONG( margin_right_min ) );
        WinSendDlgItemMsg( hwnd, IDC_MRIGHT, SPBM_SETCURRENTVALUE,
                           MPFROMLONG( margin_right_min ), MPVOID );

        //somPrintf( "cx %d, cy %d, xLeftClip %d, yBottomClip %d, xRightClip %d, yTopClip %d\n",
        //           pcurForm->cx, pcurForm->cy, pcurForm->xLeftClip, pcurForm->yBottomClip,
        //           pcurForm->xRightClip, pcurForm->yTopClip );

    }
    else {
        WinSetDlgItemText( hwnd, IDC_SELECTED_FORM, "" );
    }
}


// do not allow round-trip on spins
static MRESULT EXPENTRY spinProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    PFNWP oldSpinProc = (PFNWP)WinQueryWindowULong( hwnd, QWL_USER );

    if ( msg == SPBM_SPINDOWN )
    {
        LONG upLimit = 0, lowLimit = 0, curVal = 0;
        WinSendMsg( hwnd, SPBM_QUERYLIMITS, MPFROMP( &upLimit ), MPFROMP( &lowLimit ) );
        WinSendMsg( hwnd, SPBM_QUERYVALUE, MPFROMP( &curVal ), MPFROM2SHORT( 0, SPBQ_DONOTUPDATE ) );
        if ( curVal <= lowLimit ) {
            return (MRESULT)TRUE;
        }
    }
    else if ( msg == SPBM_SPINUP )
    {
        LONG upLimit = 0, lowLimit = 0, curVal = 0;
        WinSendMsg( hwnd, SPBM_QUERYLIMITS, MPFROMP( &upLimit ), MPFROMP( &lowLimit ) );
        WinSendMsg( hwnd, SPBM_QUERYVALUE, MPFROMP( &curVal ), MPFROM2SHORT( 0, SPBQ_DONOTUPDATE ) );
        if ( curVal >= upLimit ) {
            return (MRESULT)TRUE;
        }
    }

    return oldSpinProc( hwnd, msg, mp1, mp2 );
}

MRESULT EXPENTRY PrintDlg::printDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    // This is a static method, so we don't know which instantiation we're
    // dealing with. But we can get a pseudo-this from the parameter to
    // WM_INITDLG, which we therafter store with the window and retrieve
    // as follows:
    PrintDlg *_this = (PrintDlg *)WinQueryWindowULong( hwnd, QWL_USER );

    switch (msg)
    {

        // Dialog has just been created
        case WM_INITDLG:
        {
            // Save the mp2 into our user data so that subsequent calls have
            // access to the parent C++ object
            WinSetWindowULong( hwnd, QWL_USER, (ULONG)mp2 );
            _this = (PrintDlg *)mp2;
            localizeDialog( hwnd );
            centerWindow( _this->hFrame, hwnd );

            // Print range
            WinCheckButton( hwnd, IDC_RANGEALL, TRUE );

            // Set the print range spins
            long pages = _this->doc->getPageCount( ev );
            WinSendDlgItemMsg( hwnd, IDC_PGFROM, SPBM_SETLIMITS,
                               MPFROMLONG( pages ), MPFROMLONG( 1 ) );
            WinSendDlgItemMsg( hwnd, IDC_PGFROM, SPBM_SETCURRENTVALUE,
                               MPFROMLONG( 1 ), MPVOID );
            WinSendDlgItemMsg( hwnd, IDC_PGTO, SPBM_SETLIMITS,
                               MPFROMLONG( pages ), MPFROMLONG( 1 ) );
            WinSendDlgItemMsg( hwnd, IDC_PGTO, SPBM_SETCURRENTVALUE,
                               MPFROMLONG( pages ), MPVOID );

            // Enum printer queues
            _this->enumQueues( hwnd );

            // Number of copies
            WinSendDlgItemMsg( hwnd, IDC_COPIES, SPBM_SETLIMITS,
                               MPFROMLONG( 999 ), MPFROMLONG( 1 ) );
            WinSendDlgItemMsg( hwnd, IDC_COPIES, SPBM_SETCURRENTVALUE,
                               MPFROMLONG( 1 ), MPVOID );

            USHORT sEntry;
            HWND reo = WinWindowFromID( hwnd, IDC_RANGE_EVEN_ODD );
            WinSetWindowText( reo, getLocalizedString( PD_RANGE_EVEN_ODD ).c_str() );
            sEntry = (SHORT)WinInsertLboxItem( reo, LIT_END, getLocalizedString( PD_RANGE_EVEN_ODD ).c_str() );
            WinSendMsg( reo, LM_SETITEMHANDLE, MPFROMSHORT(sEntry), MPFROMLONG( OEOddEven ) );
            sEntry = (SHORT)WinInsertLboxItem( reo, LIT_END, getLocalizedString( PD_RANGE_ODD ).c_str() );
            WinSendMsg( reo, LM_SETITEMHANDLE, MPFROMSHORT(sEntry), MPFROMLONG( OEOdd ) );
            sEntry = (SHORT)WinInsertLboxItem( reo, LIT_END, getLocalizedString( PD_RANGE_EVEN ).c_str() );
            WinSendMsg( reo, LM_SETITEMHANDLE, MPFROMSHORT(sEntry), MPFROMLONG( OEEven ) );

            HWND spin = WinWindowFromID( hwnd, IDC_MLEFT );
            PFNWP proc = WinSubclassWindow( spin, spinProc );
            WinSetWindowULong( spin, QWL_USER, (ULONG)proc );
            spin = WinWindowFromID( hwnd, IDC_MRIGHT );
            proc = WinSubclassWindow( spin, spinProc );
            WinSetWindowULong( spin, QWL_USER, (ULONG)proc );
            spin = WinWindowFromID( hwnd, IDC_MTOP );
            proc = WinSubclassWindow( spin, spinProc );
            WinSetWindowULong( spin, QWL_USER, (ULONG)proc );
            spin = WinWindowFromID( hwnd, IDC_MBOTTOM );
            proc = WinSubclassWindow( spin, spinProc );
            WinSetWindowULong( spin, QWL_USER, (ULONG)proc );

            return (MRESULT)FALSE;
        }

        case WM_CONTROL:
        {
            switch ( SHORT1FROMMP(mp1) )
            {
                case IDC_PNAME:
                {
                    if ( SHORT2FROMMP(mp1) == CBN_LBSELECT )
                    {
                        SHORT rc = (SHORT)WinSendDlgItemMsg( hwnd, IDC_PNAME, LM_QUERYSELECTION,
                                                             MPFROMSHORT( LIT_CURSOR ), MPVOID );
                        if ( rc != LIT_NONE ) {
                            MRESULT r = WinSendDlgItemMsg( hwnd, IDC_PNAME, LM_QUERYITEMHANDLE,
                                                           MPFROMSHORT( rc ), MPVOID );
                            _this->setCurrentQInfo( hwnd, (PPRQINFO3)r );
                        }
                    }
                }
                break;

                case IDC_RANGEALL:
                case IDC_RANGECURRENT:
                case IDC_RANGEPAGES:
                {
                    BOOL en = WinQueryButtonCheckstate( hwnd, IDC_RANGEPAGES );
                    WinEnableControl( hwnd, IDC_LABELFROM, en );
                    WinEnableControl( hwnd, IDC_PGFROM, en );
                    WinEnableControl( hwnd, IDC_LABELTO, en );
                    WinEnableControl( hwnd, IDC_PGTO, en );
                }
                break;

                case IDC_TYPE_POSTSCRIPT:
                case IDC_TYPE_ASIMAGE:
                {
                    BOOL aspsc = WinQueryButtonCheckstate( hwnd, IDC_TYPE_POSTSCRIPT );
                    BOOL asimg = WinQueryButtonCheckstate( hwnd, IDC_TYPE_ASIMAGE );
                    WinEnableControl( hwnd, IDC_PRINT_TO_FILE, aspsc );
                    WinEnableControl( hwnd, IDC_HIGHER_IMAGE_QUALITY,
                                      asimg && _this->scalable && !_this->fixed );
                    WinEnableControl( hwnd, IDC_RANGE_EVEN_ODD_LABEL, asimg );
                    WinEnableControl( hwnd, IDC_RANGE_EVEN_ODD, asimg );
                }
                break;

                case IDC_PORTRAIT:
                case IDC_LANDSCAPE:
                {
                    bool portrait = WinQueryButtonCheckstate( hwnd, IDC_PORTRAIT );
                    _this->setPortraitOrientation( portrait, hwnd );
                }
                break;

                case IDC_IGNMARGINS:
                {
                    if ( ( SHORT2FROMMP(mp1) == BN_CLICKED ) ||
                         ( SHORT2FROMMP(mp1) == BN_DBLCLICKED ) )
                    {
                        _this->applyForm( hwnd );
                    }
                }
                break;

                // removed (copies to job props)
                //case IDC_COPIES:
                //{
                //    if ( SHORT2FROMMP(mp1) == SPBN_CHANGE )
                //    {
                //        LONG cp = 0;
                //        WinSendDlgItemMsg( hwnd, IDC_COPIES, SPBM_QUERYVALUE,
                //                           MPFROMP( &cp ), MPFROM2SHORT( 0, SPBQ_UPDATEIFVALID ) );
                //        _this->setCopies( cp );
                //    }
                //}
                //break;
            }
        }
        break;

        case WM_COMMAND:
            switch (SHORT1FROMMP(mp1))
            {
                case IDC_JOBPROPERTIES:
                    _this->showJobProperties( hwnd );
                    return (MRESULT)FALSE;

                case DID_OK:
                    {
                        long ml = 0, mr = 0, mt = 0, mb = 0;
                        WinSendDlgItemMsg( hwnd, IDC_MLEFT, SPBM_QUERYVALUE, MPFROMP( &ml ), MPFROM2SHORT( 0, SPBQ_UPDATEIFVALID ) );
                        WinSendDlgItemMsg( hwnd, IDC_MRIGHT, SPBM_QUERYVALUE, MPFROMP( &mr ), MPFROM2SHORT( 0, SPBQ_UPDATEIFVALID ) );
                        WinSendDlgItemMsg( hwnd, IDC_MTOP, SPBM_QUERYVALUE, MPFROMP( &mt ), MPFROM2SHORT( 0, SPBQ_UPDATEIFVALID ) );
                        WinSendDlgItemMsg( hwnd, IDC_MBOTTOM, SPBM_QUERYVALUE, MPFROMP( &mb ), MPFROM2SHORT( 0, SPBQ_UPDATEIFVALID ) );

                        if ( ( _this->pcurForm->cx < ( ml + mr ) ) ||
                             ( _this->pcurForm->cy < ( mt + mb ) ) )
                        {
                            char *wrongmargins = newstrdupL( PD_WRONG_MARGINS );
                            WinMessageBox( HWND_DESKTOP, _this->hFrame, wrongmargins, NULL,
                                           1, MB_OK | MB_ERROR | MB_MOVEABLE );
                            delete wrongmargins;
                            return (MRESULT)FALSE;  // Return, don't leave dialog
                        }

                        _this->psetup->margin_left   = ml;
                        _this->psetup->margin_right  = mr;
                        _this->psetup->margin_top    = mt;
                        _this->psetup->margin_bottom = mb;

                        LONG cp = 0;
                        WinSendDlgItemMsg( hwnd, IDC_COPIES, SPBM_QUERYVALUE, MPFROMP( &cp ), MPFROM2SHORT( 0, SPBQ_UPDATEIFVALID ) );
                        _this->psetup->copies = cp;

                        _this->psetup->range = RangeAll;
                        _this->psetup->pgfrom = 1;
                        _this->psetup->pgto = _this->doc->getPageCount( ev );

                        if ( WinQueryButtonCheckstate( hwnd, IDC_RANGECURRENT ) ) {
                            _this->psetup->range = RangeCurrent;
                            _this->psetup->pgfrom = _this->currentpage;
                            _this->psetup->pgto = _this->currentpage;
                        }

                        if ( WinQueryButtonCheckstate( hwnd, IDC_RANGEPAGES ) )
                        {
                            _this->psetup->range = RangePages;
                            LONG tmpVal = 0;
                            BOOL rc = (BOOL)WinSendDlgItemMsg( hwnd, IDC_PGFROM, SPBM_QUERYVALUE, MPFROMP( &tmpVal ), MPFROM2SHORT( 0, SPBQ_UPDATEIFVALID ) );
                            if ( rc && ( tmpVal > 0 ) ) {
                                _this->psetup->pgfrom = tmpVal;
                            }
                            rc = (BOOL)WinSendDlgItemMsg( hwnd, IDC_PGTO, SPBM_QUERYVALUE, MPFROMP( &tmpVal ), MPFROM2SHORT( 0, SPBQ_UPDATEIFVALID ) );
                            if ( rc && ( tmpVal > 0 ) ) {
                                _this->psetup->pgto = tmpVal;
                            }
                        }

                        _this->psetup->ptype = TypePostScript;
                        if ( WinQueryButtonCheckstate( hwnd, IDC_TYPE_ASIMAGE ) ) {
                            _this->psetup->ptype = TypeAsImage;
                        }
                        _this->psetup->higherQuality = WinQueryButtonCheckstate( hwnd, IDC_HIGHER_IMAGE_QUALITY );

                        _this->psetup->oddeven = OEOddEven;
                        if ( _this->psetup->ptype == TypeAsImage )
                        {
                            SHORT rc = (SHORT)WinSendDlgItemMsg( hwnd, IDC_RANGE_EVEN_ODD, LM_QUERYSELECTION,
                                                             MPFROMSHORT( LIT_CURSOR ), MPVOID );
                            if ( rc != LIT_NONE ) {
                                MRESULT r = WinSendDlgItemMsg( hwnd, IDC_RANGE_EVEN_ODD, LM_QUERYITEMHANDLE,
                                                           MPFROMSHORT( rc ), MPVOID );
                                _this->psetup->oddeven = (PrintOddEven)(int)r;
                            }
                        }

                        _this->psetup->psToFile = WinQueryButtonCheckstate( hwnd, IDC_PRINT_TO_FILE );

                        if ( ( _this->psetup->ptype == TypePostScript ) &&
                             _this->psetup->psToFile )
                        {
                            strcpy( _this->psetup->psFile, _this->filename );
                            char *pointpos = strrchr( _this->psetup->psFile, '.' );
                            if ( pointpos != NULL ) {
                                *pointpos = 0;
                            }
                            strcat( _this->psetup->psFile, ".ps" );

                            PFILEDLG fd = new FILEDLG;
                            memset( fd, 0, sizeof( FILEDLG ) );
                            fd->cbSize = sizeof( FILEDLG );
                            fd->fl = FDS_CENTER | FDS_SAVEAS_DIALOG;
                            strcpy( fd->szFullFile, _this->psetup->psFile );
                            WinFileDlg( HWND_DESKTOP, hwnd, fd );
                            if ( fd->lReturn == DID_OK ) {
                                strcpy( _this->psetup->psFile, fd->szFullFile );
                                delete fd;
                            }
                            else {
                                delete fd;
                                WinDismissDlg( hwnd, DID_CANCEL );
                                return (MRESULT)FALSE;
                            }
                        }

                        // save name of selected queue to make it default for session
                        strcpy( defQueue, _this->psetup->QueueInfo.pszName );

                        WinDismissDlg( hwnd, DID_OK );
                    }
                    return (MRESULT)FALSE;

                case DID_CANCEL:
                    WinDismissDlg( hwnd, DID_CANCEL );
                    return (MRESULT)FALSE;
            };
            return (MRESULT)FALSE;
    }
    return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}


