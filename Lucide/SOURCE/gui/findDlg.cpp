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
#include <os2.h>

#include <stdio.h>

#include "globals.h"
#include "findDlg.h"
#include "Lucide_res.h"
#include "luutils.h"
#include "messages.h"

#define MAXSEARCHLENGTH 100

FindDlg::FindDlg( HWND hWndFrame )
{
    hFrame        = hWndFrame;
    searchString  = newstrdup( "" );
    caseSensitive = false;
}

FindDlg::~FindDlg()
{
    delete searchString;
}

ULONG FindDlg::showDialog()
{
    return WinDlgBox( HWND_DESKTOP, hFrame, findDlgProc,
                      _hmod, IDD_FIND, this );
}



MRESULT EXPENTRY FindDlg::findDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    // This is a static method, so we don't know which instantiation we're
    // dealing with. But we can get a pseudo-this from the parameter to
    // WM_INITDLG, which we therafter store with the window and retrieve
    // as follows:
    FindDlg *_this = (FindDlg *)WinQueryWindowULong( hwnd, QWL_USER );

    switch (msg)
    {

        // Dialog has just been created
        case WM_INITDLG:
        {
            // Save the mp2 into our user data so that subsequent calls have
            // access to the parent C++ object
            WinSetWindowULong( hwnd, QWL_USER, (ULONG)mp2 );
            _this = (FindDlg *)mp2;
            localizeDialog( hwnd );
            centerWindow( _this->hFrame, hwnd );

            WinSendDlgItemMsg( hwnd, IDC_FINDFIELD, EM_SETTEXTLIMIT,
                               MPFROMSHORT( MAXSEARCHLENGTH ), MPVOID );
            WinSetDlgItemText( hwnd, IDC_FINDFIELD, _this->searchString );
            WinSendDlgItemMsg( hwnd, IDC_FINDFIELD, EM_SETSEL, MPFROM2SHORT( 0, MAXSEARCHLENGTH ), MPVOID );
            WinCheckButton( hwnd, IDC_FINDMATCHCASE, _this->caseSensitive );

            return (MRESULT)FALSE;
        }

        case WM_COMMAND:
            switch (SHORT1FROMMP(mp1))
            {
                case DID_OK:
                    {
                        char buf[ MAXSEARCHLENGTH + 1 ];
                        WinQueryDlgItemText( hwnd, IDC_FINDFIELD, sizeof( buf ), buf );
                        delete _this->searchString;
                        _this->searchString = newstrdup( buf );
                        _this->caseSensitive = WinQueryButtonCheckstate( hwnd, IDC_FINDMATCHCASE );
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


//
// ------------------ GotoDlg ---------------------
//

GotoDlg::GotoDlg( HWND hWndFrame, long _pages, long _curpage )
{
    hFrame  = hWndFrame;
    page    = -1;
    pages   = _pages;
    curpage = _curpage;
}

GotoDlg::~GotoDlg()
{
}

ULONG GotoDlg::showDialog()
{
    return WinDlgBox( HWND_DESKTOP, hFrame, gotoDlgProc,
                      _hmod, IDD_GOTOPAGE, this );
}



MRESULT EXPENTRY GotoDlg::gotoDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    // This is a static method, so we don't know which instantiation we're
    // dealing with. But we can get a pseudo-this from the parameter to
    // WM_INITDLG, which we therafter store with the window and retrieve
    // as follows:
    GotoDlg *_this = (GotoDlg *)WinQueryWindowULong( hwnd, QWL_USER );

    switch (msg)
    {

        // Dialog has just been created
        case WM_INITDLG:
        {
            // Save the mp2 into our user data so that subsequent calls have
            // access to the parent C++ object
            WinSetWindowULong( hwnd, QWL_USER, (ULONG)mp2 );
            _this = (GotoDlg *)mp2;
            localizeDialog( hwnd );
            centerWindow( _this->hFrame, hwnd );

            WinSendDlgItemMsg( hwnd, IDC_PAGE, SPBM_SETLIMITS,
                               MPFROMLONG( _this->pages ), MPFROMLONG( 1 ) );
            WinSendDlgItemMsg( hwnd, IDC_PAGE, SPBM_SETCURRENTVALUE,
                               MPFROMLONG( _this->curpage ), MPVOID );
            char *pgfrm = newstrdupL( GTP_OF );
            char pgnum[ 32 ];
            snprintf( pgnum, sizeof( pgnum ), pgfrm, _this->pages );
            delete pgfrm;
            WinSetDlgItemText( hwnd, IDC_PAGES, pgnum );
            return (MRESULT)FALSE;
        }

        case WM_COMMAND:
            switch (SHORT1FROMMP(mp1))
            {
                case DID_OK:
                    {
                        LONG spbmValue = 0;
                        BOOL rc = (BOOL)WinSendDlgItemMsg( hwnd, IDC_PAGE, SPBM_QUERYVALUE,
                                            MPFROMP( &spbmValue ),
                                            MPFROM2SHORT( 0, SPBQ_UPDATEIFVALID ) );

                        if ( rc && ( spbmValue > 0 ) ) {
                            _this->page = spbmValue;
                        }
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

