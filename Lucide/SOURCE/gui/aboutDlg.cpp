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


#define INCL_DOS
#define INCL_WIN
#include <os2.h>

#include <stdio.h>

#include "lucide.h"
#include "luutils.h"
#include "lucide_res.h"

void setLinkPointer( HPOINTER hp );
void toLink( HWND hwnd );

static HWND hWndFrame = NULLHANDLE;

static MRESULT EXPENTRY AboutProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch ( msg )
    {
        case WM_INITDLG:
            {
                localizeDialog( hwnd );
                centerWindow( hWndFrame, hwnd );

                char buf[ 256 ];
                snprintf( buf, sizeof buf, "%s %s", appName, appVersion );
                WinSetDlgItemText( hwnd, IDT_LUCIDEVERSION, buf );

                HPOINTER p = WinLoadPointer( HWND_DESKTOP, NULLHANDLE, IDP_HAND );
                setLinkPointer( p );

                toLink( WinWindowFromID( hwnd, IDC_NETLABSURL ) );

                LONG cpr_clrback = SYSCLR_DIALOGBACKGROUND;
                WinSetPresParam( WinWindowFromID( hwnd, IDC_COPYRIGHTS ),
                                 PP_BACKGROUNDCOLORINDEX,
                                 sizeof( cpr_clrback ), (PVOID)&cpr_clrback );
            }
            return (MRESULT)FALSE;
    }
    return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}


void AboutBox( HWND _hWndFrame )
{
    hWndFrame = _hWndFrame;
    WinDlgBox( HWND_DESKTOP, hWndFrame, AboutProc,
               NULLHANDLE, IDD_ABOUT, NULL );
}



