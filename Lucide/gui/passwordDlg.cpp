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


#include "os2all.h"

#include "globals.h"
#include "passwordDlg.h"
#include "Lucide_res.h"
#include "luutils.h"
#include "Lucide.h"

#define MAXPASSWORDLENGTH 100


PasswordDlg::PasswordDlg( HWND hWndFrame )
{
    hFrame   = hWndFrame;
    password = newstrdup( "" );
}

PasswordDlg::~PasswordDlg()
{
    delete password;
}

ULONG PasswordDlg::showDialog()
{
    return WinDlgBox( HWND_DESKTOP, hFrame, passwordDlgProc,
                      _hmod, IDD_PASSWORD, this );
}


MRESULT EXPENTRY PasswordDlg::passwordDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    // This is a static method, so we don't know which instantiation we're
    // dealing with. But we can get a pseudo-this from the parameter to
    // WM_INITDLG, which we therafter store with the window and retrieve
    // as follows:
    PasswordDlg *_this = (PasswordDlg *)WinQueryWindowULong( hwnd, QWL_USER );

    switch (msg)
    {

        // Dialog has just been created
        case WM_INITDLG:
        {
            // Save the mp2 into our user data so that subsequent calls have
            // access to the parent C++ object
            WinSetWindowULong( hwnd, QWL_USER, (ULONG)mp2 );
            _this = (PasswordDlg *)mp2;
            localizeDialog( hwnd );
            centerWindow( _this->hFrame, hwnd );

            // setup the accelerators
            WinSetAccelTable( hab, WinLoadAccelTable( hab, _hmod, IDA_ADDHELPACCEL ), hwnd );

            WinSendDlgItemMsg( hwnd, IDC_PASSWORD, EM_SETTEXTLIMIT,
                               MPFROMSHORT( MAXPASSWORDLENGTH ), MPVOID );
            return (MRESULT)FALSE;
        }

        case WM_COMMAND:
            switch (SHORT1FROMMP(mp1))
            {
                case DID_OK:
                    {
                        char buf[ MAXPASSWORDLENGTH + 1 ];
                        WinQueryDlgItemText( hwnd, IDC_PASSWORD, sizeof( buf ), buf );
                        delete _this->password;
                        _this->password = newstrdup( buf );
                        WinDismissDlg( hwnd, DID_OK );
                    }
                    return (MRESULT)FALSE;

                case DID_CANCEL:
                    WinDismissDlg( hwnd, DID_CANCEL );
                    return (MRESULT)FALSE;

                case CM_HELP:
                  if (Lucide::hwndHelp)
                      WinSendMsg(Lucide::hwndHelp,HM_DISPLAY_HELP,
                                 MPFROM2SHORT(118, 0), MPFROMSHORT(HM_RESOURCEID));
                  return (MRESULT)FALSE;
            };
            return (MRESULT)FALSE;
    }
    return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}


