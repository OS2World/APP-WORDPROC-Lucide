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

#include <stdio.h>
#include <string.h>
#include <string>

#include "tb_spl.h"

#include "lucide.h"
#include "Lucide_res.h"
#include "luutils.h"
#include "messages.h"


PFNWP pOldTbProc; // Old toolbar window proc
PFNWP pOldZeProc; // Old zoom entryfield window proc


// Toolbar window proc
static MRESULT EXPENTRY tbProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch ( msg )
    {
        case WM_CONTROL:
            {
                SHORT controlId = SHORT1FROMMP( mp1 );
                SHORT notifyCode = SHORT2FROMMP( mp1 );

                if ( ( controlId == TBID_PAGENUM ) && ( notifyCode == EN_CHANGE )
                     && !Lucide::dontSwitchPage )
                {
                        char szText[256];
                        LONG newPage = 0;
                        ULONG retLen = 0;
                        retLen = WinQueryDlgItemText( hwnd, TBID_PAGENUM, sizeof(szText),
                                            szText );

                        if ( retLen > 0) {
                                newPage = atol(szText);
                                if (newPage > 0) {
                                    Lucide::goToPage(newPage - 1);
                                }
                        }
                }

                if ( ( controlId == TBID_PAGENUM ) && ( notifyCode == EN_SETFOCUS )
                     && !Lucide::dontSwitchPage )
                {
                // highlight the text
                WinSendDlgItemMsg( hwnd, TBID_PAGENUM, EM_SETSEL,
                                      MPFROM2SHORT(0, 256), NULL);
                }

                if ( ( controlId == TBID_ZOOM ) && ( notifyCode == CBN_ENTER ) )
                {
                    bool shortValueOk = false;
                    SHORT sResult = 0;
                    if ( WinQueryDlgItemShort( hwnd, TBID_ZOOM, &sResult, FALSE ) )
                    {
                        if ( ( sResult > 0 ) && ( sResult < 1600 ) ) {
                            shortValueOk = true;
                            Lucide::focusDocview();
                            Lucide::setZoom( (double)sResult / 100.0 );
                        }
                    }

                    if ( !shortValueOk )
                    {
                        SHORT rc = SHORT1FROMMR( WinSendDlgItemMsg( hwnd, TBID_ZOOM, LM_QUERYSELECTION,
                                                                    MPFROMSHORT( LIT_CURSOR ), MPVOID ) );
                        if ( rc != LIT_NONE )
                        {
                            double z = convZoom( rc );
                            if ( z >= -2 ) {
                                Lucide::focusDocview();
                                Lucide::setZoom( z );
                            }
                        }
                    }
                }
            }
            break;
    }
    return pOldTbProc( hwnd, msg, mp1, mp2 );
}

static char savedZeText[ 255 ] = "";
// Zoom entryfield window proc
static MRESULT EXPENTRY zeProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    char tmp[ 255 ] = "";

    switch ( msg )
    {

        // clear field on click
        case WM_BUTTON1CLICK:
        {
            WinQueryWindowText( hwnd, sizeof( tmp ), tmp );
            if ( strlen( tmp ) > 0 ) {
                strcpy( savedZeText, tmp );
            }
            WinSetWindowText( hwnd, "" );
        }
        break;

        // restore text if empty when losing focus
        case WM_SETFOCUS:
        {
            if ( !SHORT1FROMMP( mp2 ) )
            {
                WinQueryWindowText( hwnd, sizeof( tmp ), tmp );
                if ( strlen( tmp ) == 0 ) {
                    WinSetWindowText( hwnd, savedZeText );
                }
            }
        }
        break;

    }
    return pOldZeProc( hwnd, msg, mp1, mp2 );
}


HWND createToolbar( HWND hwnd )
{
    HWND hToolBar = WinCreateWindow( hwnd, WC_ER_TOOLBAR, "",
                                WS_VISIBLE, 0, 0, 0, 0, hwnd, HWND_TOP,
                                0, NULL, NULL );
    pOldTbProc = WinSubclassWindow( hToolBar, tbProc );

    // used for different purposes
    char pgnum[ 32 ];
    HPS hps;

    AddBtnStruct bs;

    bs.cmd = CM_OPEN;
    bs.bubbleText = newstrdupL( TBHINT_OPEN );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_OPEN;
    bs.pictHmod = _hmod;
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
    bs.pictHmod = _hmod;
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
    bs.pictHmod = _hmod;
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
    bs.pictHmod = _hmod;
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
    bs.pictHmod = _hmod;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    // pages text
    AddCtrlStruct cs;
    cs.ctrlHandle = WinCreateWindow( hToolBar, WC_ENTRYFIELD, NULL,
                                     WS_VISIBLE|ES_CENTER|ES_MARGIN|ES_AUTOSCROLL,
                                     0,0,0,0, hToolBar, HWND_TOP, TBID_PAGENUM, NULL, NULL );
    WinSetPresParam( cs.ctrlHandle, PP_FONTNAMESIZE, deffontlen, deffont );
    // calculate the width
    snprintf( pgnum, sizeof( pgnum ), "%d", 99999 );
    hps = WinGetPS( cs.ctrlHandle );
    cs.cx = getStringPixSize( hps, pgnum ) + 4;
    WinReleasePS( hps );

    cs.cy = 2;
    cs.bubbleText = NULL;
    WinSendMsg( hToolBar, TBM_ADDCONTROL, (MPARAM)&cs, MPVOID );

    cs.ctrlHandle = WinCreateWindow( hToolBar, WC_STATIC, NULL,
                                     WS_VISIBLE | SS_TEXT | DT_CENTER | DT_VCENTER,
                                     0,0,0,0, hToolBar, HWND_TOP, TBID_OFPAGES, NULL, NULL );
    WinSetPresParam( cs.ctrlHandle, PP_FONTNAMESIZE, deffontlen, deffont );
    ULONG syscmenu = SYSCLR_MENU;
    WinSetPresParam( cs.ctrlHandle, PP_BACKGROUNDCOLORINDEX, sizeof( ULONG ), &syscmenu );
    char *pgfrm = newstrdupL( TB_PAGENUM );
    snprintf( pgnum, sizeof( pgnum ), pgfrm, 99999 );
    delete pgfrm;
    hps = WinGetPS( cs.ctrlHandle );
    cs.cx = getStringPixSize( hps, pgnum );
    WinReleasePS( hps );
    cs.cy = 0;
    cs.bubbleText = NULL;
    WinSendMsg( hToolBar, TBM_ADDCONTROL, (MPARAM)&cs, MPVOID );

    bs.cmd = CM_NEXTPAGE;
    bs.bubbleText = newstrdupL( TBHINT_NEXT_PAGE );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_NEXTPAGE;
    bs.pictHmod = _hmod;
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
    bs.pictHmod = _hmod;
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
    bs.pictHmod = _hmod;
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
    bs.pictHmod = _hmod;
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
    bs.pictHmod = _hmod;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    cs.ctrlHandle = WinCreateWindow( hToolBar, WC_COMBOBOX, NULL,
                                     WS_VISIBLE | CBS_DROPDOWN,
                                     0,0,0,0, hToolBar, HWND_TOP, TBID_ZOOM, NULL, NULL );
    WinSetPresParam( cs.ctrlHandle, PP_FONTNAMESIZE, deffontlen, deffont );
    std::string actsizetext = getLocalizedString( TBHINT_ACTUAL_SIZE );
    cs.cx = setZoomValues( cs.ctrlHandle ) +
                ( WinQuerySysValue( HWND_DESKTOP, SV_CXVSCROLL ) * 2 );
    cs.cy = -200;
    cs.bubbleText = NULL;
    pOldZeProc = WinSubclassWindow( WinWindowFromID( cs.ctrlHandle, CBID_EDIT ), zeProc );
    WinSendMsg( hToolBar, TBM_ADDCONTROL, (MPARAM)&cs, MPVOID );

    WinSendMsg( hToolBar, TBM_ADDSEPARATOR, MPVOID, MPVOID );

    bs.cmd = CM_FIND;
    bs.bubbleText = newstrdupL( TBHINT_FIND );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_FIND;
    bs.pictHmod = _hmod;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    bs.cmd = CM_FINDAGAIN;
    bs.bubbleText = newstrdupL( TBHINT_FINDAGAIN );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_FINDAGAIN;
    bs.pictHmod = _hmod;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    WinSendMsg( hToolBar, TBM_ADDSEPARATOR, MPVOID, MPVOID );

    bs.cmd = CM_ZOOM_IN_OUT;
    bs.bubbleText = newstrdupL( TBHINT_ZOOM_IN_OUT );
    bs.bubbleRes = 0;
    bs.bubbleHmod = NULLHANDLE;
    bs.pictRes = IDB_MGLASS;
    bs.pictHmod = _hmod;
    bs.menuRes = 0;
    bs.menuHmod = NULLHANDLE;
    bs.checked = FALSE;
    bs.enabled = TRUE;
    WinSendMsg( hToolBar, TBM_ADDBUTTON, (MPARAM)&bs, MPVOID );

    return hToolBar;
}
