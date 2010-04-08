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

#include <string>

#include "settingsDlg.h"
#include "lusettings.h"
#include "luutils.h"
#include "Lucide_res.h"
#include "messages.h"


SettingsDlg::SettingsDlg( HWND hWndFrame, LuSettings *s )
{
    hFrame = hWndFrame;
    settings = s;
}

SettingsDlg::~SettingsDlg()
{
}

void SettingsDlg::doDialog()
{
    WinDlgBox( HWND_DESKTOP, hFrame, settingsDlgProc,
               _hmod, IDD_SETTINGS, this );
    delete this;
}

static void setZoomCombo( HWND combo, SHORT cbind, double zoom )
{
    if ( cbind != -1 ) {
        char buf[ 255 ] = "";
        WinQueryLboxItemText( combo, cbind, buf, sizeof( buf ) );
        WinSetWindowText( combo, buf );
    }

    if ( zoom != 0 ) {
        std::string z = str( zoom * 100.0 ) + "%";
        WinSetWindowText( combo, z.c_str() );
    }
}

MRESULT EXPENTRY SettingsDlg::settingsDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    // This is a static method, so we don't know which instantiation we're
    // dealing with. But we can get a pseudo-this from the parameter to
    // WM_INITDLG, which we therafter store with the window and retrieve
    // as follows:
    SettingsDlg *_this = (SettingsDlg *)WinQueryWindowULong( hwnd, QWL_USER );

    switch (msg)
    {

        // Dialog has just been created
        case WM_INITDLG:
        {
            // Save the mp2 into our user data so that subsequent calls have
            // access to the parent C++ object
            WinSetWindowULong( hwnd, QWL_USER, (ULONG)mp2 );
            _this = (SettingsDlg *)mp2;
            localizeDialog( hwnd );
            centerWindow( _this->hFrame, hwnd );

            // init

            // layout
            HWND hLayout = WinWindowFromID( hwnd, IDC_DEFPGLAYOUT );
            std::string spage = getLocalizedString( SD_SINGLE_PAGE );
            std::string cont = getLocalizedString( SD_CONTINUOUS );
            WinInsertLboxItem( hLayout, LIT_END, spage.c_str() );
            WinInsertLboxItem( hLayout, LIT_END, cont.c_str() );
            if ( _this->settings->layout == SinglePage ) {
                WinSetWindowText( hLayout, spage.c_str() );
            } else if ( _this->settings->layout = Continuous ) {
                WinSetWindowText( hLayout, cont.c_str() );
            }

            // zoom
            HWND zoomCombo = WinWindowFromID( hwnd, IDC_DEFZOOM );
            setZoomValues( zoomCombo );
            if ( _this->settings->zoom == -2 ) {
                setZoomCombo( zoomCombo, 1, 0 );
            } else if ( _this->settings->zoom == -1 ) {
                setZoomCombo( zoomCombo, 2, 0 );
            } else if ( _this->settings->zoom == 1 ) {
                setZoomCombo( zoomCombo, 0, 0 );
            } else {
                setZoomCombo( zoomCombo, -1, _this->settings->zoom );
            }

            return (MRESULT)FALSE;
        }

        case WM_COMMAND:
            switch (SHORT1FROMMP(mp1))
            {
                case DID_OK:
                    {
                        SHORT rc = SHORT1FROMMR( WinSendDlgItemMsg( hwnd, IDC_DEFPGLAYOUT, LM_QUERYSELECTION,
                                                                    MPFROMSHORT( LIT_CURSOR ), MPVOID ) );
                        if ( rc != LIT_NONE )
                        {
                            if ( rc == 0 ) {
                                _this->settings->layout = SinglePage;
                            } else if ( rc == 1 ) {
                                _this->settings->layout = Continuous;
                            }
                        }

                        rc = SHORT1FROMMR( WinSendDlgItemMsg( hwnd, IDC_DEFZOOM, LM_QUERYSELECTION,
                                                              MPFROMSHORT( LIT_CURSOR ), MPVOID ) );
                        if ( rc != LIT_NONE )
                        {
                            double z = convZoom( rc );
                            if ( z >= -2 ) {
                                _this->settings->zoom = z;
                            }
                        }

                        _this->settings->save();

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


