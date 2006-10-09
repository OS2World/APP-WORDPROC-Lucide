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


#define INCL_GPI
#define INCL_WIN
#include <os2.h>

#include <process.h>
#include <stdio.h>

#include "globals.h"
#include "luutils.h"
#include "progressDlg.h"
#include "Lucide_res.h"
#include "messages.h"

#define TID_PAINT   1


ProgressDlg::ProgressDlg( HWND hWndFrame )
{
    hFrame      = hWndFrame;
    text        = newstrdup( "" );
    threadFn    = NULL;
    threadData  = NULL;
    fn          = NULL;
    data        = NULL;
    pOldBarProc = NULL;
    hpsBuffer   = NULLHANDLE;
    hdcBuffer   = NULLHANDLE;
    startPos    = 0;
}

ProgressDlg::~ProgressDlg()
{
    delete text;
}

void ProgressDlg::show( progressThreadFn _threadFn, void *_threadData )
{
    threadFn = _threadFn;
    threadData = _threadData;
    WinDlgBox( HWND_DESKTOP, hFrame, progressDlgProc,
               _hmod, IDD_PROGRESS, this );
}

void ProgressDlg::hide()
{
    if ( hDialog != NULLHANDLE ) {
        WinPostMsg( hDialog, WM_COMMAND, MPFROMSHORT( DID_OK ), (MPARAM)0 );
    }
}

void ProgressDlg::setBreakFunc( progressBrkFn _fn, void *_data )
{
    fn   = _fn;
    data = _data;
}

void ProgressDlg::setText( const char *_text )
{
    delete text;
    text = newstrdup( _text );
    if ( hDialog != NULLHANDLE ) {
        WinSetDlgItemText( hDialog, IDC_PTEXT, text );
    }
}

MRESULT EXPENTRY ProgressDlg::progressDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    // This is a static method, so we don't know which instantiation we're
    // dealing with. But we can get a pseudo-this from the parameter to
    // WM_INITDLG, which we therafter store with the window and retrieve
    // as follows:
    ProgressDlg *_this = (ProgressDlg *)WinQueryWindowULong( hwnd, QWL_USER );

    switch (msg)
    {

        // Dialog has just been created
        case WM_INITDLG:
        {
            // Save the mp2 into our user data so that subsequent calls have
            // access to the parent C++ object
            WinSetWindowULong( hwnd, QWL_USER, (ULONG)mp2 );
            _this = (ProgressDlg *)mp2;
            localizeDialog( hwnd );
            centerWindow( _this->hFrame, hwnd );

            _this->hDialog = hwnd;
            WinSetDlgItemText( hwnd, IDC_PTEXT, _this->text );
            WinEnableControl( hwnd, DID_CANCEL, _this->fn != NULL );

            _this->startPos = 0;
            HWND hBar = WinWindowFromID( hwnd, IDC_PBAR );
            HAB hBarHab = WinQueryAnchorBlock( hBar );

            if ( ( _this->hpsBuffer != NULLHANDLE ) &&
                 ( _this->hdcBuffer != NULLHANDLE ) ) {
                DestroyGraphicsBuffer( _this->hpsBuffer, _this->hdcBuffer );
                _this->hpsBuffer = _this->hdcBuffer = NULLHANDLE;
            }

            RECTL rcl;
            WinQueryWindowRect( hBar, &rcl );
            HPS hps = WinGetPS( hBar );
            CreateGraphicsBuffer( hBarHab, &rcl, hps, &_this->hpsBuffer, &_this->hdcBuffer );
            WinReleasePS( hps );

            WinSetWindowULong( hBar, QWL_USER, (ULONG)_this );
            _this->pOldBarProc = WinSubclassWindow( hBar, progressBarProc );
            WinStartTimer( hBarHab, hBar, TID_PAINT, 1 );
            
            _beginthread( _this->threadFn, NULL, 262144, _this->threadData );

            return (MRESULT)FALSE;
        }

        case WM_DESTROY:
        {
            _this->hDialog = NULLHANDLE;
            if ( ( _this->hpsBuffer != NULLHANDLE ) &&
                 ( _this->hdcBuffer != NULLHANDLE ) ) {
                DestroyGraphicsBuffer( _this->hpsBuffer, _this->hdcBuffer );
                _this->hpsBuffer = _this->hdcBuffer = NULLHANDLE;
            }
        }
        break;

        case WM_COMMAND:
            switch (SHORT1FROMMP(mp1))
            {
                case DID_OK:
                    WinDismissDlg( hwnd, DID_OK );
                    return (MRESULT)FALSE;

                case DID_CANCEL:
                    WinEnableControl( hwnd, DID_CANCEL, FALSE );
                    if ( _this->fn != NULL ) {
                        _this->fn( _this->data );
                    }
                    return (MRESULT)FALSE;
            };
            return (MRESULT)FALSE;
    }
    return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}

#define SHAPE_LEN   30

MRESULT EXPENTRY ProgressDlg::progressBarProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    ProgressDlg *_this = (ProgressDlg *)WinQueryWindowULong( hwnd, QWL_USER );

    switch ( msg )
    {
        case WM_PAINT:
            _this->wmPaintBar( hwnd );
            return (MRESULT)FALSE;

        case WM_TIMER:
            if ( SHORT1FROMMP( mp1 ) == TID_PAINT )
            {
                WinInvalidateRect( hwnd, NULL, FALSE );
                _this->startPos += 3;
                if ( _this->startPos > ( ( SHAPE_LEN * 2 ) - 1 ) ) {
                    _this->startPos = 0;
                }
            }
            break;
    }
    return _this->pOldBarProc( hwnd, msg, mp1, mp2 );
}

void ProgressDlg::drawShape( HPS hps, PRECTL r )
{
    POINTL ptlStart, ptlEnd;
    ptlStart.x = r->xLeft;      // x coordinate, lower-left corner of box
    ptlStart.y = r->yBottom;    // y coordinate, lower-left corner of box
    ptlEnd.x   = r->xRight;     // x coordinate, upper-right corner of box
    ptlEnd.y   = r->yTop;       // y coordinate, upper-right corner of box
    GpiMove( hps, &ptlStart );
    GpiBox( hps, DRO_FILL, &ptlEnd, 0, 0 ); // Draw sheared box
}

void ProgressDlg::wmPaintBar( HWND hwnd )
{
    RECTL rcl;
    HPS hps = WinBeginPaint( hwnd, 0, NULL );
    WinQueryWindowRect( hwnd, &rcl );

    // 161,192,224
    LONG lclr1 = ( 161 << 16 ) | ( 192 << 8 ) | 224;
    LONG lclr2 = ( 121 << 16 ) | ( 144 << 8 ) | 168;
    LONG ltabl[ 2 ] = { lclr1, lclr2 };
    GpiCreateLogColorTable( hpsBuffer, 0, LCOLF_CONSECRGB, 100, 2, ltabl );
    WinFillRect( hpsBuffer, &rcl, 100 );
    GpiSetColor( hpsBuffer, 101 );

    MATRIXLF matlfTransform;
    matlfTransform.fxM11 = MAKEFIXED( 1, 0 );
    matlfTransform.fxM12 = MAKEFIXED( 0, 0 );
    matlfTransform.lM13  = 0;
    matlfTransform.fxM21 = MAKEFIXED( 0, 65536 / 2 );  // Shear factor .5
    matlfTransform.fxM22 = MAKEFIXED( 1, 0 );
    matlfTransform.lM23  = 0;
    matlfTransform.lM31  = 0;               // Translate 0 units right
    matlfTransform.lM32  = 0;
    matlfTransform.lM33  = 1;
    GpiSetDefaultViewMatrix( hpsBuffer, 9, &matlfTransform, TRANSFORM_REPLACE );

    LONG xPos = startPos - ( SHAPE_LEN * 2 );
    for ( ; xPos < rcl.xRight; xPos += ( SHAPE_LEN * 2 ) )
    {
        RECTL r = { xPos, rcl.yBottom, xPos + SHAPE_LEN, rcl.yTop - 1 };
        drawShape( hpsBuffer, &r );
    }

    BlitGraphicsBuffer( hps, hpsBuffer, &rcl );
    WinEndPaint( hps );
}

