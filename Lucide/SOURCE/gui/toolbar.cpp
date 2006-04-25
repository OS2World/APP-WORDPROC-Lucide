#define INCL_WIN
#include <os2.h>

#include <stdio.h>
#include <string>

#include <tb_spl.h>

#include "lucide.h"
#include "Lucide_res.h"
#include "luutils.h"
#include "messages.h"


PFNWP pOldTbProc;


static MRESULT EXPENTRY tbProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch ( msg )
    {
        case WM_CONTROL:
            {
                SHORT controlId = SHORT1FROMMP( mp1 );
                SHORT notifyCode = SHORT2FROMMP( mp1 );

                if ( ( controlId == TBID_PAGENUM ) && ( notifyCode == SPBN_CHANGE )
                     && !Lucide::dontSwitchPage )
                {
                    LONG spbmValue = 0;
                    BOOL rc = (BOOL)WinSendDlgItemMsg( hwnd, TBID_PAGENUM, SPBM_QUERYVALUE,
                                       MPFROMP( &spbmValue ),
                                       MPFROM2SHORT( 0, SPBQ_UPDATEIFVALID ) );

                    if ( rc && ( spbmValue > 0 ) ) {
                        Lucide::goToPage( spbmValue - 1 );
                    }
                }

                if ( ( controlId == TBID_ZOOM ) && ( notifyCode == CBN_ENTER ) )
                {
                    SHORT rc = (SHORT)WinSendDlgItemMsg( hwnd, TBID_ZOOM, LM_QUERYSELECTION,
                                            MPFROMSHORT( LIT_CURSOR ), MPVOID );
                    if ( rc != LIT_NONE )
                    {
                        switch ( rc )
                        {
                            case 0:   Lucide::setZoom( 1 );      break;
                            case 1:   Lucide::setZoom( -2 );     break;
                            case 2:   Lucide::setZoom( -1 );     break;
                            case 3:   Lucide::setZoom( 0.125 );  break;
                            case 4:   Lucide::setZoom( 0.25 );   break;
                            case 5:   Lucide::setZoom( 0.5 );    break;
                            case 6:   Lucide::setZoom( 1 );      break;
                            case 7:   Lucide::setZoom( 1.25 );   break;
                            case 8:   Lucide::setZoom( 1.5 );    break;
                            case 9:   Lucide::setZoom( 2 );      break;
                            case 10:  Lucide::setZoom( 3 );      break;
                            case 11:  Lucide::setZoom( 4 );      break;
                            case 12:  Lucide::setZoom( 8 );      break;
                            case 13:  Lucide::setZoom( 16 );     break;
                        }
                    }
                }
            }
            break;
    }
    return pOldTbProc( hwnd, msg, mp1, mp2 );
}


HWND createToolbar( HWND hwnd )
{
    HWND hToolBar = WinCreateWindow( hwnd, WC_ER_TOOLBAR, "",
                                WS_VISIBLE, 0, 0, 0, 0, hwnd, HWND_TOP,
                                0, NULL, NULL );
    pOldTbProc = WinSubclassWindow( hToolBar, tbProc );

    AddBtnStruct bs;

    bs.cmd = CM_OPEN;
    bs.bubbleText = newstrdupL( TBHINT_OPEN );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_OPEN;
    bs.pictHmod = NULLHANDLE;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    bs.cmd = CM_PRINT;
    bs.bubbleText = newstrdupL( TBHINT_PRINT );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_PRINT;
    bs.pictHmod = NULLHANDLE;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    WinSendMsg( hToolBar, TBM_ADDSEPARATOR, MPVOID, MPVOID );

    bs.cmd = CM_NAVPANE;
    bs.bubbleText = newstrdupL( TBHINT_SHOW_NAV_PANE );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_NAVPANE;
    bs.pictHmod = NULLHANDLE;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    WinSendMsg( hToolBar, TBM_ADDSEPARATOR, MPVOID, MPVOID );

    bs.cmd = CM_FIRSTPAGE;
    bs.bubbleText = newstrdupL( TBHINT_FIRST_PAGE );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_FIRSTPAGE;
    bs.pictHmod = NULLHANDLE;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    bs.cmd = CM_PREVPAGE;
    bs.bubbleText = newstrdupL( TBHINT_PREV_PAGE );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_PREVPAGE;
    bs.pictHmod = NULLHANDLE;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    // pages spin
    AddCtrlStruct cs;
    cs.ctrlHandle = WinCreateWindow( hToolBar, WC_SPINBUTTON, NULL,
                                     WS_VISIBLE|SPBS_MASTER|SPBS_NUMERICONLY|SPBS_JUSTCENTER,
                                     0,0,0,0, hToolBar, HWND_TOP, TBID_PAGENUM, NULL, NULL );
    WinSendMsg( cs.ctrlHandle, SPBM_SETLIMITS, (MPARAM)0, (MPARAM)0 );
    WinSetPresParam( cs.ctrlHandle, PP_FONTNAMESIZE, deffontlen, deffont );
    cs.cx = 50;
    cs.cy = 0;
    cs.bubbleText = NULL;
    WinSendMsg( hToolBar, TBM_ADDCONTROL, (MPARAM)&cs, MPVOID );

    cs.ctrlHandle = WinCreateWindow( hToolBar, WC_STATIC, NULL,
                                     WS_VISIBLE | SS_TEXT | DT_CENTER | DT_VCENTER,
                                     0,0,0,0, hToolBar, HWND_TOP, TBID_OFPAGES, NULL, NULL );
    WinSetPresParam( cs.ctrlHandle, PP_FONTNAMESIZE, deffontlen, deffont );
    ULONG syscmenu = SYSCLR_MENU;
    WinSetPresParam( cs.ctrlHandle, PP_BACKGROUNDCOLORINDEX, sizeof( ULONG ), &syscmenu );
    char *pgfrm = newstrdupL( TB_PAGENUM );
    char pgnum[ 32 ];
    snprintf( pgnum, sizeof( pgnum ), pgfrm, 9999 );
    delete pgfrm;
    HPS hps = WinGetPS( cs.ctrlHandle );
    cs.cx = getStringPixSize( hps, pgnum ) + 4;
    WinReleasePS( hps );
    cs.cy = 0;
    cs.bubbleText = NULL;
    WinSendMsg( hToolBar, TBM_ADDCONTROL, (MPARAM)&cs, MPVOID );

    bs.cmd = CM_NEXTPAGE;
    bs.bubbleText = newstrdupL( TBHINT_NEXT_PAGE );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_NEXTPAGE;
    bs.pictHmod = NULLHANDLE;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    bs.cmd = CM_LASTPAGE;
    bs.bubbleText = newstrdupL( TBHINT_LAST_PAGE );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_LASTPAGE;
    bs.pictHmod = NULLHANDLE;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    WinSendMsg( hToolBar, TBM_ADDSEPARATOR, MPVOID, MPVOID );

    bs.cmd = CM_ACTSIZE;
    bs.bubbleText = newstrdupL( TBHINT_ACTUAL_SIZE );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_100PERC;
    bs.pictHmod = NULLHANDLE;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    bs.cmd = CM_FITWINDOW;
    bs.bubbleText = newstrdupL( TBHINT_FIT_WINDOW );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_FITPAGE;
    bs.pictHmod = NULLHANDLE;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    bs.cmd = CM_FITWIDTH;
    bs.bubbleText = newstrdupL( TBHINT_FIT_WIDTH );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_FITWIDTH;
    bs.pictHmod = NULLHANDLE;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    cs.ctrlHandle = WinCreateWindow( hToolBar, WC_COMBOBOX, NULL,
                                     WS_VISIBLE | CBS_DROPDOWNLIST,
                                     0,0,0,0, hToolBar, HWND_TOP, TBID_ZOOM, NULL, NULL );
    WinSetPresParam( cs.ctrlHandle, PP_FONTNAMESIZE, deffontlen, deffont );
    std::string actsizetext = getLocalizedString( TBHINT_ACTUAL_SIZE );
    WinSetWindowText( cs.ctrlHandle, actsizetext.c_str() );
    WinSendMsg( cs.ctrlHandle, LM_INSERTITEM, MPFROMSHORT(LIT_END),
                MPFROMP( actsizetext.c_str() ) );
    WinSendMsg( cs.ctrlHandle, LM_INSERTITEM, MPFROMSHORT(LIT_END),
                MPFROMP( getLocalizedString( TBHINT_FIT_WINDOW ).c_str() ) );
    WinSendMsg( cs.ctrlHandle, LM_INSERTITEM, MPFROMSHORT(LIT_END),
                MPFROMP( getLocalizedString( TBHINT_FIT_WIDTH ).c_str() ) );
    WinSendMsg( cs.ctrlHandle, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP( "12.5%" ) );
    WinSendMsg( cs.ctrlHandle, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP( "25%" ) );
    WinSendMsg( cs.ctrlHandle, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP( "50%" ) );
    WinSendMsg( cs.ctrlHandle, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP( "100%" ) );
    WinSendMsg( cs.ctrlHandle, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP( "125%" ) );
    WinSendMsg( cs.ctrlHandle, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP( "150%" ) );
    WinSendMsg( cs.ctrlHandle, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP( "200%" ) );
    WinSendMsg( cs.ctrlHandle, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP( "300%" ) );
    WinSendMsg( cs.ctrlHandle, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP( "400%" ) );
    WinSendMsg( cs.ctrlHandle, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP( "800%" ) );
    WinSendMsg( cs.ctrlHandle, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP( "1600%" ) );
    cs.cx = 80;
    cs.cy = -100;
    cs.bubbleText = NULL;
    WinSendMsg( hToolBar, TBM_ADDCONTROL, (MPARAM)&cs, MPVOID );

    WinSendMsg( hToolBar, TBM_ADDSEPARATOR, MPVOID, MPVOID );

    bs.cmd = CM_FIND;
    bs.bubbleText = newstrdupL( TBHINT_FIND );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_FIND;
    bs.pictHmod = NULLHANDLE;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    return hToolBar;
}
