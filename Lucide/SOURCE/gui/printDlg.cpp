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

#include "printDlg.h"
#include "Lucide_res.h"
#include "luutils.h"

extern HAB hab;

#define DEVICENAME_LENGTH   32
#define DRIVERNAME_LENGTH   128

struct PrintDlgInternalData
{
    PPRQINFO3 pQueueInfo;
    PPRQINFO3 pCurQueue;
};


PrintDlg::PrintDlg( HWND hWndFrame, LuDocument *_doc )
{
    hFrame = hWndFrame;
    doc    = _doc;
    data   = new PrintDlgInternalData;
    memset( data, 0, sizeof( PrintDlgInternalData ) );
}

PrintDlg::~PrintDlg()
{
    if ( data->pQueueInfo != NULL ) {
        free( data->pQueueInfo );
    }
    delete data;
}

ULONG PrintDlg::showDialog()
{
    return WinDlgBox( HWND_DESKTOP, hFrame, printDlgProc,
                      NULLHANDLE, IDD_PRINT, this );
}


void PrintDlg::setCurrentQInfo( HWND hwnd, void *i )
{
    data->pCurQueue = (PPRQINFO3)i;
    WinSetDlgItemText( hwnd, IDC_PNAME, data->pCurQueue->pszComment );
    WinSetDlgItemText( hwnd, IDC_PDESCRIPTION, data->pCurQueue->pszDriverName );
    WinEnableControl( hwnd, IDC_JOBPROPERTIES, TRUE );
    WinEnableControl( hwnd, DID_OK, TRUE );
}

void PrintDlg::enumQueues( HWND hwnd )
{
    HWND list = WinWindowFromID( hwnd, IDC_PNAME );
    ULONG cReturned = 0, cTotal = 0, cbNeeded = 0;
    SPLERR se = SplEnumQueue( NULL, 3, NULL, 0L, &cReturned,
                              &cTotal, &cbNeeded, NULL );
    if ( cTotal == 0L ) {
        // TODO: 'no printers installed' message
    }

    data->pQueueInfo = (PPRQINFO3)malloc( cbNeeded );

    se = SplEnumQueue( NULL, 3, data->pQueueInfo, cbNeeded, &cReturned,
                       &cTotal, &cbNeeded, NULL );
    if ( se != NO_ERROR ) {
        // TODO: error message
        free( data->pQueueInfo );
        data->pQueueInfo = NULL;
        return;
    }

    USHORT sEntry;
    for ( ULONG i = 0; i < cReturned; i++ )
    {
        sEntry = (SHORT)WinSendMsg( list, LM_INSERTITEM, MPFROMSHORT(LIT_END),
                                    MPFROMP( data->pQueueInfo[i].pszComment ) );
        WinSendMsg( list, LM_SETITEMHANDLE,
                    MPFROMSHORT(sEntry), MPFROMP( &(data->pQueueInfo[i]) ) );

        if ( data->pQueueInfo[i].fsType & PRQ3_TYPE_APPDEFAULT ) {
            setCurrentQInfo( hwnd, &( data->pQueueInfo[i] ) );
        }
    }
}


void PrintDlg::showJobProperties()
{
    if ( data->pCurQueue == NULL ) {
        return;
    }

    char achDriverName[ DRIVERNAME_LENGTH ];
    char achDeviceName[ DEVICENAME_LENGTH ];

    // The pszDriverName is of the form DRIVER.DEVICE (e.g.,
    // LASERJET.HP LaserJet IID) so we need to separate it at the dot
    int i = strcspn( data->pCurQueue->pszDriverName, "." );
    if ( i > 0 ) {
        strncpy( achDriverName, data->pCurQueue->pszDriverName, i );
        achDriverName[ i ] = '\0';
        strcpy( achDeviceName, &( data->pCurQueue->pszDriverName[ i + 1 ] ) );
    }
    else {
        strcpy( achDriverName, data->pCurQueue->pszDriverName );
        *achDeviceName = '\0';
    }

    // There may be more than one printer assigned to this print queue
    // We will use the first in the comma separated list.  We would
    // need an expanded dialog for the user to be more specific.
    char *pszTemp = strchr( data->pCurQueue->pszPrinters, ',' );
    if ( pszTemp != NULL ) {
        // Strip off comma and trailing printer names
        *pszTemp = '\0' ;
    }

    // Post the job properties dialog for the printer to allow the
    // user to modify the options
    DevPostDeviceModes( hab, data->pCurQueue->pDriverData, achDriverName,
                        achDeviceName, data->pCurQueue->pszPrinters, DPDM_POSTJOBPROP );
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
            _this->enumQueues( hwnd );
            return (MRESULT)FALSE;
        }

        case WM_CONTROL:
        {
            if ( (SHORT1FROMMP(mp1) == IDC_PNAME) && (SHORT2FROMMP(mp1) == CBN_ENTER) )
            {
                SHORT rc = (SHORT)WinSendDlgItemMsg( hwnd, IDC_PNAME, LM_QUERYSELECTION,
                                                     MPFROMSHORT( LIT_CURSOR ), MPVOID );
                if ( rc != LIT_NONE ) {
                    MRESULT r = WinSendDlgItemMsg( hwnd, IDC_PNAME, LM_QUERYITEMHANDLE,
                                                   MPFROMSHORT( rc ), MPVOID );
                    _this->setCurrentQInfo( hwnd, r );
                }
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
                        // do
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


