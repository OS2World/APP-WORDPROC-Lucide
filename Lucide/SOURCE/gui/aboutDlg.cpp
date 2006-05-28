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



