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
#include <string.h>
#include <malloc.h>

#include "globals.h"
#include "luutils.h"
#include "lucide_res.h"

void setLinkPointer( HPOINTER hp );
void toLink( HWND hwnd );
BOOL DrawTransparentBitmap( HAB hab, HPS hpsDraw, PPOINTL drawptl, HBITMAP hbmp );

typedef struct
{
    PFNWP oldLogoProc;
    HBITMAP image;
} logoData;

#define IMAGE_X 52
#define IMAGE_Y 52

static MRESULT EXPENTRY LogoProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    logoData *ld = (logoData *)WinQueryWindowULong( hwnd, QWL_USER );
    switch ( msg )
    {
        case WM_PAINT:
            {
                HPS hps;
                RECTL rect;
                WinQueryWindowRect( hwnd, &rect );
                hps = WinBeginPaint( hwnd, 0L, 0L );
                if ( ld->image != NULLHANDLE )
                {
                    LONG xPos = ( rect.xRight - IMAGE_X ) / 2;
                    LONG yPos = ( rect.yTop - IMAGE_Y ) / 2;
                    POINTL ptl = { xPos, yPos };
                    DrawTransparentBitmap( hab, hps, &ptl, ld->image );
                    //WinDrawBitmap( hps, ld->image, NULL, &ptl, 0, 0, DBM_NORMAL );
                }
                WinEndPaint( hps );
            }
            return (MRESULT)FALSE;

        case WM_DESTROY:
            ld->oldLogoProc( hwnd, msg, mp1, mp2 );
            if ( ld->image != NULLHANDLE ) {
                GpiDeleteBitmap( ld->image );
            }
            free( ld );
            return (MRESULT)FALSE;
    }
    return ld->oldLogoProc( hwnd, msg, mp1, mp2 );
}

void logoImageCreate( HWND hwnd )
{
    logoData *ld;
    ld = (logoData *)malloc( sizeof( logoData ) );
    memset( ld, 0, sizeof( logoData ) );
    ld->oldLogoProc = WinSubclassWindow( hwnd, LogoProc );
    WinSetWindowULong( hwnd, QWL_USER, (ULONG)ld );
    HPS hps = WinGetPS( hwnd );
    ld->image = GpiLoadBitmap( hps, NULLHANDLE, IDB_LOGO, 0, 0 );
    WinReleasePS( hps );
    WinInvalidateRect( hwnd, NULL, FALSE );
}


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

                logoImageCreate( WinWindowFromID( hwnd, IDC_LOGO ) );
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



