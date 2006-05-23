/*
 *
 *  Copyrights? Public domain, nah!
 *
 */

#define INCL_WIN
#define INCL_GPI
#include <os2.h>

#include "tb_spl.h"


#define SPLITTER_WIDTH  5

static LONG lColor[ SPLITTER_WIDTH ] =
{
    CLR_PALEGRAY, CLR_WHITE,    CLR_PALEGRAY,
    CLR_PALEGRAY, CLR_DARKGRAY
};

struct splitterWndStruct
{
    SHORT splitterPos;
    SHORT splitterWidth;
    SHORT fixedSize;
    ULONG style;
    HWND  firstWindow;
    HWND  secondWindow;
    HPOINTER ptrWE;
    HPOINTER ptrNS;
};


static VOID setWindSize( HWND splitWnd, splitterWndStruct *sws )
{
    if ( !WinIsWindowVisible( splitWnd ) ) {
        return;
    }

    if ( sws->firstWindow && sws->secondWindow )
    {
        if ( !( WinIsWindowVisible( sws->firstWindow ) &&
             WinIsWindowVisible( sws->secondWindow ) ) ) {
            return;
        }

        SWP swp;
        WinQueryWindowPos( splitWnd, &swp );

        SHORT x, y, cx, cy;
        if ( sws->style & SBS_VSPLIT )
        {
            if ( sws->style & SBS_FIRSTFIXED ) {
                sws->splitterPos = sws->fixedSize;
            } else if ( sws->style & SBS_SECONDFIXED ) {
                sws->splitterPos = swp.cx - sws->fixedSize;
            }

            if ( sws->splitterPos > ( ( swp.cx - sws->splitterWidth ) - 1 ) ) {
                sws->splitterPos = ( swp.cx - sws->splitterWidth ) - 1;
            }

            sws->splitterPos = sws->splitterPos < 0 ? 0 : sws->splitterPos;
            x = swp.x;
            y = swp.y;
            cx = sws->splitterPos;
            cy = swp.cy;
            WinSetWindowPos( sws->firstWindow, HWND_TOP,
                x, y, cx, cy, SWP_ZORDER | SWP_SIZE | SWP_MOVE );
            x = swp.x + sws->splitterPos + sws->splitterWidth;
            y = swp.y;
            cx = ( ( swp.cx - sws->splitterPos ) - sws->splitterWidth );
            cx = cx < 0 ? 0 : cx;
            cy = swp.cy;
            WinSetWindowPos( sws->secondWindow, HWND_TOP,
                x, y, cx, cy, SWP_ZORDER | SWP_SIZE | SWP_MOVE  );
        }
        else if ( sws->style & SBS_HSPLIT )
        {
            if ( sws->style & SBS_FIRSTFIXED ) {
                sws->splitterPos = sws->fixedSize;
            } else if ( sws->style & SBS_SECONDFIXED ) {
                sws->splitterPos = swp.cy - sws->fixedSize;
            }

            if ( sws->splitterPos > ( ( swp.cy - sws->splitterWidth ) - 1 ) ) {
                sws->splitterPos = ( swp.cy - sws->splitterWidth ) - 1;
            }

            sws->splitterPos = sws->splitterPos < 0 ? 0 : sws->splitterPos;
            x = swp.x;
            y = swp.y;
            cx = swp.cx;
            cy = sws->splitterPos;
            WinSetWindowPos( sws->firstWindow, HWND_TOP,
                x, y, cx, cy, SWP_ZORDER | SWP_SIZE | SWP_MOVE  );
            x = swp.x;
            y = swp.y + sws->splitterPos + sws->splitterWidth;
            cx = swp.cx;
            cy = ( ( swp.cy - sws->splitterPos ) - sws->splitterWidth );
            WinSetWindowPos( sws->secondWindow, HWND_TOP,
                x, y, cx, cy, SWP_ZORDER | SWP_SIZE | SWP_MOVE  );
        }
        WinInvalidateRect( splitWnd, NULL, FALSE );
        WinInvalidateRect( sws->firstWindow, NULL, TRUE );
        WinInvalidateRect( sws->secondWindow, NULL, TRUE );
    }
}

static VOID getSplitterSize( HWND splitWnd, splitterWndStruct *sws, PRECTL rcl )
{
    RECTL rcl1;
    WinQueryWindowRect( splitWnd, &rcl1 );
    if ( sws->style & SBS_VSPLIT )
    {
        rcl->xLeft   = sws->splitterPos;
        rcl->yBottom = 0;
        rcl->xRight  = sws->splitterPos + sws->splitterWidth;
        rcl->yTop    = ( rcl1.yTop - rcl1.yBottom );
    }
    else
    {
        rcl->xLeft   = 0;
        rcl->yBottom = sws->splitterPos;
        rcl->xRight  = ( rcl1.xRight - rcl1.xLeft );
        rcl->yTop    = sws->splitterPos + sws->splitterWidth;
    }
}

static MRESULT EXPENTRY splitterProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    splitterWndStruct *sws = (splitterWndStruct *)WinQueryWindowULong( hwnd, sizeof( ULONG ) );
    if ( sws == NULL )
    {
        sws = new splitterWndStruct;
        sws->splitterPos = 0;
        sws->style = WinQueryWindowULong( hwnd, QWL_STYLE );
        sws->splitterWidth = sws->style & SBS_FIXED ? 0 : SPLITTER_WIDTH;
        sws->firstWindow = NULLHANDLE;
        sws->secondWindow = NULLHANDLE;
        sws->ptrWE = NULLHANDLE;
        sws->ptrNS = NULLHANDLE;
        WinSetWindowULong( hwnd, sizeof( ULONG ), (ULONG)sws );
    }

    switch ( msg )
    {
        case SBM_SETWINDOWS:
            sws->firstWindow = HWNDFROMMP( mp1 );
            sws->secondWindow = HWNDFROMMP( mp2 );
            setWindSize( hwnd, sws );
            return (MRESULT)(TRUE);

        case SBM_SETSPLITTERPOS:
            sws->splitterPos = sws->fixedSize = SHORT1FROMMP( mp1 );
            setWindSize( hwnd, sws );
            return (MRESULT)(TRUE);

        case SBM_GETSPLITTERPOS:
            return MRFROMSHORT( sws->splitterPos );

        case SBM_SETPOINTERS:
            sws->ptrWE = (HPOINTER)mp1;
            sws->ptrNS = (HPOINTER)mp2;
            return (MRESULT)(TRUE);

        case SBM_SETFIXEDSIZE:
            sws->fixedSize = SHORT1FROMMP( mp1 );
            setWindSize( hwnd, sws );
            return (MRESULT)(TRUE);

        case WM_DESTROY:
            delete sws;
            break;

        case WM_WINDOWPOSCHANGED:
        case WM_SHOW:
            setWindSize( hwnd, sws );
            break;

        case WM_PAINT:
            {
                RECTL rcl;
                POINTL ptl;
                WinQueryWindowRect( hwnd, &rcl );
                HPS hps = WinBeginPaint( hwnd, 0L, 0L );

                if ( !( sws->style & SBS_FIXED ) )
                {
                    if ( sws->style & SBS_VSPLIT )
                    {
                        ptl.x = sws->splitterPos;
                        for ( int i = 0; i < sws->splitterWidth; i++ )
                        {
                            ptl.y = 0;
                            GpiMove( hps, &ptl );
                            ptl.y = ( rcl.yTop - rcl.yBottom );
                            GpiSetColor( hps, lColor[ i ] );
                            GpiLine( hps, &ptl );
                            ptl.x++;
                        }
                    }
                    else if ( sws->style & SBS_HSPLIT )
                    {
                        ptl.y = sws->splitterPos;
                        for ( int i = sws->splitterWidth; i > 0; i-- )
                        {
                            ptl.x = 0;
                            GpiMove( hps, &ptl );
                            ptl.x = ( rcl.xRight - rcl.xLeft );
                            GpiSetColor( hps, lColor[ i ] );
                            GpiLine( hps, &ptl );
                            ptl.y++;
                        }
                    }
                }
                WinEndPaint( hps );
            }
            return (MRESULT)(FALSE);

        case WM_MOUSEMOVE:
            {
                if ( sws->style & SBS_FIXED ) {
                    return (MRESULT)(FALSE);
                }

                POINTL ptl = { SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ) };
                RECTL rcl;
                getSplitterSize( hwnd, sws, &rcl );

                if ( WinPtInRect( WinQueryAnchorBlock( hwnd ), &rcl, &ptl ) )
                {
                    if ( sws->style & SBS_VSPLIT )
                    {
                        if ( sws->ptrWE == NULLHANDLE )
                        {
                            WinSetPointer( HWND_DESKTOP,
                                WinQuerySysPointer( HWND_DESKTOP,
                                        SPTR_SIZEWE, FALSE ) );
                        }
                        else {
                            WinSetPointer( HWND_DESKTOP, sws->ptrWE );
                        }
                    }
                    else
                    {
                        if ( sws->ptrNS == NULLHANDLE )
                        {
                            WinSetPointer( HWND_DESKTOP,
                                WinQuerySysPointer( HWND_DESKTOP,
                                        SPTR_SIZENS, FALSE ) );
                        }
                        else {
                            WinSetPointer( HWND_DESKTOP, sws->ptrNS );
                        }
                    }
                }
                else
                {
                    WinSetPointer( HWND_DESKTOP,
                            WinQuerySysPointer( HWND_DESKTOP,
                                    SPTR_ARROW, FALSE ) );
                }
            }
            return (MRESULT)(FALSE);

        case WM_BUTTON1DOWN:
            {
                if ( sws->style & SBS_FIXED ) {
                    return (MRESULT)(FALSE);
                }

                SHORT oldpos = sws->splitterPos;

                POINTL ptl = { SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ) };
                TRACKINFO track;

                track.cxBorder = 2;
                track.cyBorder = 2;
                track.cxGrid   = 1;
                track.cyGrid   = 1;
                track.cxKeyboard = 8;
                track.cyKeyboard = 8;
                WinQueryWindowRect( hwnd, &track.rclBoundary );
                getSplitterSize( hwnd, sws, &track.rclTrack );

                if ( !WinPtInRect( WinQueryAnchorBlock( hwnd ), &track.rclTrack, &ptl ) ) {
                    return (MRESULT)FALSE;
                }

                track.ptlMinTrackSize.x = track.rclTrack.xRight
                                        - track.rclTrack.xLeft;
                track.ptlMinTrackSize.y = track.rclTrack.yTop
                                        - track.rclTrack.yBottom;
                track.ptlMaxTrackSize.x = track.rclTrack.xRight
                                        - track.rclTrack.xLeft;
                track.ptlMaxTrackSize.y = track.rclTrack.yTop
                                        - track.rclTrack.yBottom;

                track.fs = TF_MOVE | TF_ALLINBOUNDARY;

                if ( WinTrackRect( hwnd, 0, &track ) )
                {
                    if ( sws->style & SBS_VSPLIT ) {
                        sws->splitterPos = track.rclTrack.xLeft;
                    } else {
                        sws->splitterPos = track.rclTrack.yBottom;
                    }

                    setWindSize( hwnd, sws );

                    // notify owner
                    WinSendMsg( WinQueryWindow( hwnd, QW_OWNER ), WM_CONTROL,
                                MPFROM2SHORT( WinQueryWindowUShort( hwnd, QWS_ID ),
                                              SBN_POSITIONCHANGED ),
                                MPFROM2SHORT( sws->splitterPos, oldpos ) );
                }
            }
            return (MRESULT)(FALSE);

        case WM_ERASEBACKGROUND:
            return (MRESULT)(FALSE);
    }
    return WinDefWindowProc( hwnd, msg, mp1, mp2 );
}


BOOL InitPMSplitterClass( HAB hab )
{
    return WinRegisterClass( hab, WC_ER_SPLITTER, splitterProc,
                             0, sizeof( ULONG ) * 2 );
}

