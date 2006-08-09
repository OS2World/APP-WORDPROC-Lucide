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

#include <ludoc.xh>

#include "globals.h"
#include "printDlg.h"
#include "Lucide_res.h"
#include "luutils.h"


PrintDlg::PrintDlg( HWND hWndFrame, LuDocument *_doc, long _currentpage )
{
    hFrame      = hWndFrame;
    doc         = _doc;
    scalable    = _doc->isScalable( ev );
    fixed       = _doc->isFixedImage( ev );
    currentpage = _currentpage;
    psetup      = new PrintSetup;
    memset( psetup, 0, sizeof( PrintSetup ) );
}

PrintDlg::~PrintDlg()
{
    delete psetup;
}

ULONG PrintDlg::showDialog()
{
    return WinDlgBox( HWND_DESKTOP, hFrame, printDlgProc,
                      NULLHANDLE, IDD_PRINT, this );
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
        sEntry = (SHORT)WinSendMsg( list, LM_INSERTITEM, MPFROMSHORT(LIT_END),
                                    MPFROMP( pQueueInfo[i].pszComment ) );
        WinSendMsg( list, LM_SETITEMHANDLE,
                    MPFROMSHORT(sEntry), MPFROMP( &(pQueueInfo[i]) ) );

        if ( pQueueInfo[i].fsType & PRQ3_TYPE_APPDEFAULT ) {
            setCurrentQInfo( hwnd, &( pQueueInfo[i] ) );
        }
    }
}


void PrintDlg::showJobProperties()
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
}

bool PrintDlg::isPostscriptDevice()
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

    long lTech = 0;
    HDC hdcPrinterInfo = DevOpenDC( hab, OD_INFO, "*", 3L, (PDEVOPENDATA)dos, NULLHANDLE );
    if ( hdcPrinterInfo != DEV_ERROR ) {
        DevQueryCaps( hdcPrinterInfo, CAPS_TECHNOLOGY, sizeof(long), &lTech );
        DevCloseDC( hdcPrinterInfo );
    }

    delete achDriverName;
    delete dos;
    return ( lTech == CAPS_TECH_POSTSCRIPT );
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

            return (MRESULT)FALSE;
        }

        case WM_CONTROL:
        {
            switch ( SHORT1FROMMP(mp1) )
            {
                case IDC_PNAME:
                {
                    //somPrintf( "IDC_PNAME: %d\n", SHORT2FROMMP(mp1) );

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
                    BOOL asimg = WinQueryButtonCheckstate( hwnd, IDC_TYPE_ASIMAGE );
                    WinEnableControl( hwnd, IDC_HIGHER_IMAGE_QUALITY,
                                      asimg && _this->scalable && !_this->fixed );
                }
                break;

            }
        }
        break;

        case WM_COMMAND:
            switch (SHORT1FROMMP(mp1))
            {
                case IDC_JOBPROPERTIES:
                    _this->showJobProperties();
                    return (MRESULT)FALSE;

                case DID_OK:
                    {
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
                            if ( _this->psetup->pgfrom > _this->psetup->pgto ) {
                                long tmp = _this->psetup->pgfrom;
                                _this->psetup->pgfrom = _this->psetup->pgto;
                                _this->psetup->pgto = tmp;
                            }
                        }

                        _this->psetup->ptype = TypePostScript;
                        if ( WinQueryButtonCheckstate( hwnd, IDC_TYPE_ASIMAGE ) ) {
                            _this->psetup->ptype = TypeAsImage;
                        }
                        _this->psetup->higherQuality = WinQueryButtonCheckstate( hwnd, IDC_HIGHER_IMAGE_QUALITY );

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


