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
#define INCL_GPI
#include <os2.h>

#include <string>
#include <process.h>
#include <stdio.h>
#include <ctype.h>

#include <ludoc.xh>
#include "lucide.h"
#include "docViewer.h"
#include "progressDlg.h"
#include "pluginman.h"
#include "luutils.h"
#include "lucide_res.h"
#include "messages.h"


// OpenWatcom headers doesn't have GpiDrawBits() declaration
extern "C" {
    LONG APIENTRY GpiDrawBits(HPS hps, PVOID pBits, PBITMAPINFO2 pbmiInfoTable,
                              LONG lCount, PPOINTL aptlPoints, LONG lRop, ULONG flOptions);
}

typedef LuDocument_LuRectSequence    *PLuRectSequence;
typedef LuDocument_LuLinkMapSequence *PLuLinkMapSequence;

#define LINE_HEIGHT     16
#define BORDER_COLOR    0x909090L

// DocumentViewer constructor
DocumentViewer::DocumentViewer( HAB _hab, HWND hWndFrame )
{
    hab         = _hab;
    hMainFrame  = hWndFrame;
    sHscrollMax = 0;
    sVscrollMax = 0;
    sHscrollPos = 0;
    sVscrollPos = 0;
    sVscrollInc = 0;
    sHscrollInc = 0;
    cxClient    = 0;
    cyClient    = 0;
    hWndDoc     = NULLHANDLE;
    doc         = NULL;
    totalpages  = 0;
    currentpage = 0;
    hpsBuffer   = NULLHANDLE;
    hdcBuffer   = NULLHANDLE;
    width       = 0;
    height      = 0;
    fullwidth   = 0;
    fullheight  = 0;
    bpp         = 0;
    zoom        = 1.0;
    realzoom    = 1.0;
    rotation    = 0;
    ev          = somGetGlobalEnvironment();
    pixbuf      = NULL;
    spos_x      = 0;
    spos_y      = 0;
    progressDlg = new ProgressDlg( hWndFrame );
    drawareas   = NULL;
    drawareaIndex = 0;
    closed        = true;
    // continuous view
    continuous  = false;
    pagesizes   = NULL;
    realVscrollMax = 0;
    VScrollStep = 1;
    WinSetRectEmpty( hab, &savedRcl );
    drawPS = false;
    // fullscreen
    fullscreen = false;
    // asynch draw
    abortAsynch = false;
    termdraw    = false;
    enableAsynchDraw = false;
    DosCreateMutexSem( NULL, &todrawAccess, 0, FALSE );
    DosCreateEventSem( NULL, &haveDraw, 0, FALSE );
    // selection
    mousePressed = false;
    selectionStart.x = 0;  selectionStart.y = 0;
    selectionEnd.x = 0;  selectionEnd.y = 0;
    selection = NULL;
    selrects = NULL;
    // links
    links = NULL;
    handptr = WinLoadPointer( HWND_DESKTOP, NULLHANDLE, IDP_HAND );
    // search
    foundrects = NULL;
    searchString = NULL;
    abortSearch = false;

    // create windows
    ULONG dfFlags = FCF_VERTSCROLL | FCF_HORZSCROLL | FCF_NOBYTEALIGN;
    hWndDocFrame = WinCreateStdWindow( hWndFrame, WS_VISIBLE, &dfFlags, NULL, NULL,
                                       WS_VISIBLE, NULLHANDLE, 0, NULL );
    WinSetWindowULong( hWndDocFrame, QWL_USER, (ULONG)this );
    oldFrameProc = WinSubclassWindow( hWndDocFrame, docFrameProc );

    hWndDoc = WinCreateWindow( hWndDocFrame, "er.docview", NULL,
                               WS_VISIBLE | WS_TABSTOP, 0, 0, 0, 0, hWndDocFrame,
                               HWND_TOP, FID_CLIENT, this, NULL );

    hWndHscroll = WinWindowFromID( hWndDocFrame, FID_HORZSCROLL );
    hWndVscroll = WinWindowFromID( hWndDocFrame, FID_VERTSCROLL );

    drawThreadId = _beginthread( drawthread, NULL, 262144, this );
}

// DocumentViewer destructor
DocumentViewer::~DocumentViewer()
{
    termdraw    = true;
    abortAsynch = true;
    DosPostEventSem( haveDraw );
    DosWaitThread( &drawThreadId, DCWW_WAIT );
    DosCloseMutexSem( todrawAccess );
    DosCloseEventSem( haveDraw );

    if ( doc != NULL ) {
        freeRects( selrects );
        freeRects( foundrects );
        freeLinks();
    }

    WinDestroyPointer( handptr );

    if ( ( hpsBuffer != NULLHANDLE ) && ( hdcBuffer != NULLHANDLE ) ) {
        DestroyGraphicsBuffer( hpsBuffer, hdcBuffer );
        hpsBuffer = hdcBuffer = NULLHANDLE;
    }
    delete pixbuf;
    delete progressDlg;
    delete searchString;
    delete pagesizes;
    delete selection;
}


// static, registration of a window class
void DocumentViewer::registerClass( HAB hab )
{
    WinRegisterClass( hab, "er.docview", docViewProc, CS_SIZEREDRAW, sizeof( ULONG ) * 2 );
}

// sets the document for viewing
void DocumentViewer::setDocument( LuDocument *_doc )
{
    close();
    doc = _doc;

    if ( doc != NULL )
    {
        closed = false;

        totalpages = doc->getPageCount( ev );
        bpp = doc->getBpp( ev );
        if ( !doc->isScalable( ev ) ) {
            zoom = 1;
        }

        pagesizes = new LuSize[ totalpages ];
        countPagesizes();

        selrects = new PLuRectSequence[ totalpages ];
        memset( selrects, 0, sizeof( PLuRectSequence ) * totalpages );

        foundrects = new PLuRectSequence[ totalpages ];
        memset( foundrects, 0, sizeof( PLuRectSequence ) * totalpages );

        links = new PLuLinkMapSequence[ totalpages ];
        memset( links, 0, sizeof( PLuLinkMapSequence ) * totalpages );

        selection = new LuRectangle[ totalpages ];
        memset( selection, 0, sizeof( LuRectangle ) * totalpages );

        drawPS = doc->isRenderIntoPS( ev );
        if ( drawPS ) {
            enableAsynchDraw = false;
        }
        else {
            enableAsynchDraw = doc->isAsynchRenderingSupported( ev );
        }
        goToPage( 0 );

        if ( continuous ) {
            drawPage();
        }
    }
}

void DocumentViewer::countPagesizes()
{
    for ( long i = 0; i < totalpages; i++ )
    {
        doc->getPageSize( ev, i, &pagesizes[i].x, &pagesizes[i].y );
        if ( ( rotation == 90 ) || ( rotation == 270 ) ) {
            double tmp = pagesizes[i].x;
            pagesizes[i].x = pagesizes[i].y;
            pagesizes[i].y = tmp;
        }
        fullwidth = __max( fullwidth, pagesizes[i].x );
        fullheight += pagesizes[i].y;
    }
}

// closes the document
void DocumentViewer::close()
{
    if ( closed ) {
        return;
    }

    closed = true;
    abortAsynch = true;
    DosRequestMutexSem( todrawAccess, SEM_INDEFINITE_WAIT );

    delete drawareas;
    drawareas = NULL;

    delete pagesizes;
    pagesizes   = NULL;

    delete selection;
    selection   = NULL;

    freeRects( foundrects );
    delete foundrects;
    foundrects  = NULL;

    freeRects( selrects );
    delete selrects;
    selrects    = NULL;

    freeLinks();

    doc         = NULL;
    totalpages  = 0;
    currentpage = 0;
    fullwidth   = 0;
    fullheight  = 0;

    DosReleaseMutexSem( todrawAccess );
}

// sets the page layout
void DocumentViewer::setPageLayout( PgLayout layout )
{
    continuous = ( layout == Continuous );
    if ( doc != NULL ) {
        long pg = currentpage;
        drawPage();
        if ( continuous ) {
            goToPage( pg );
        }
    }
}

void DocumentViewer::freeRects( LuDocument_LuRectSequence **rects )
{
    if ( rects != NULL )
    {
        for ( long i = 0; i < totalpages; i++ ) {
            if ( rects[ i ] != NULL ) {
                LuDocument::freeRectangles( ev, rects[ i ] );
                rects[ i ] = NULL;
            }
        }
    }
}

void DocumentViewer::freeLinks()
{
    if ( links != NULL )
    {
        for ( long i = 0; i < totalpages; i++ ) {
            if ( links[ i ] != NULL ) {
                LuDocument::freeLinkMapping( ev, links[ i ] );
                links[ i ] = NULL;
            }
        }

        delete links;
        links = NULL;
    }
}


// switch view to specified page
void DocumentViewer::goToPage( long page )
{
    if ( ( page < 0 ) || ( page >= totalpages ) ) {
        return;
    }

    if ( continuous && ( doc != NULL ) )
    {
        bool needRedraw = ( page == currentpage );
        double pgpos = pagenumToPos( page ) / VScrollStep;
        vertScroll( hWndDoc, MPFROM2SHORT( pgpos, SB_SLIDERPOSITION ), NULLHANDLE );
        if ( needRedraw ) {
            drawPage();
        }
    }
    else
    {
        currentpage = page;
        sVscrollPos = 0;
        if ( doc != NULL ) {
            drawPage();
            Lucide::checkNavigationMenus();
        }
    }
}

// Sets the zoom level
// _zoom - actual zoom level or:
//         -1 - fit width
//         -2 - fit page
void DocumentViewer::setZoom( double _zoom )
{

    if ( doc != NULL ) {
        if ( doc->isScalable( ev ) ) {
            zoom = _zoom;
            drawPage();
        }
    }
    else {
        zoom = _zoom;
    }
}

// Sets the rotation
// rotation may be 0, 90, 180 or 270 degrees
// -90 will be changed to 270, 360 to 0
void DocumentViewer::setRotation( long _rotation )
{
    if ( _rotation == -90 ) {
        _rotation = 270;
    }
    if ( _rotation == 360 ) {
        _rotation = 0;
    }

    if ( doc != NULL )
    {
        if ( doc->isRotable( ev ) )
        {
            rotation = _rotation;
            countPagesizes();
            drawPage();
        }
    }
    else {
        rotation = _rotation;
    }
}

void DocumentViewer::setFullscreen( bool _fullscreen )
{
    fullscreen = _fullscreen;
    ULONG ulFrameStyle = WinQueryWindowULong( hWndDocFrame, QWL_STYLE );

    if ( fullscreen )
    {
        pglSave = getPageLayout();
        zoomSave = getZoom();
        setPageLayout( SinglePage );
        setZoom( -2 );
        WinSetParent( hWndHscroll, HWND_OBJECT, FALSE );
        WinSetParent( hWndVscroll, HWND_OBJECT, FALSE );
        ulFrameStyle &= ~FS_SIZEBORDER;
    }
    else
    {
        setPageLayout( pglSave );
        setZoom( zoomSave );
        WinSetParent( hWndHscroll, hWndDocFrame, FALSE );
        WinSetParent( hWndVscroll, hWndDocFrame, FALSE );
        ulFrameStyle &= ~FS_SIZEBORDER;
    }

    WinSetWindowULong( hWndDocFrame, QWL_STYLE, ulFrameStyle );
    WinSendMsg( hWndDocFrame, WM_UPDATEFRAME,
                MPFROMLONG( FCF_VERTSCROLL | FCF_HORZSCROLL | FCF_SIZEBORDER ), MPVOID );
}

// copy selected text to clipboard
void DocumentViewer::copyToClipbrd()
{
    if ( continuous )
    {
        std::string txt = "";
        for ( long i = 0; i < totalpages; i++ ) {
            if ( selrects[ i ] != NULL ) {
                txt += doc->getText( ev, i, &(selection[ i ]) );
            }
        }
        textToClipbrd( hab, txt.c_str() );
    }
    else {
        char *t = doc->getText( ev, currentpage, &(selection[ currentpage ]) );
        textToClipbrd( hab, t );
    }
}

// select all text (continuous view) or current page (single page view)
void DocumentViewer::selectAll()
{
    if ( continuous )
    {
        for ( long i = 0; i < totalpages; i++ )
        {
            selection[ i ].x1 = 0;
            selection[ i ].y1 = 0;
            selection[ i ].x2 = pagesizes[ i ].x;
            selection[ i ].y2 = pagesizes[ i ].y;
            LuDocument::freeRectangles( ev, selrects[ i ] );
            selrects[ i ] = doc->getSelectionRectangles( ev, i, &(selection[i]) );
        }
    }
    else
    {
        selection[ currentpage ].x1 = 0;
        selection[ currentpage ].y1 = 0;
        selection[ currentpage ].x2 = pagesizes[ currentpage ].x;
        selection[ currentpage ].y2 = pagesizes[ currentpage ].y;
        LuDocument::freeRectangles( ev, selrects[ currentpage ] );
        selrects[ currentpage ] = doc->getSelectionRectangles( ev, currentpage, &(selection[currentpage]) );
    }

    Lucide::enableCopy( true );
    WinInvalidateRect( hWndDoc, NULL, FALSE );
}

// perform search in document
void DocumentViewer::searchDocument( const char *_searchString, bool _caseSensitive,
                                     bool _continueSearch )
{
    abortSearch = false;
    if ( !continueSearch ) {
        freeRects( foundrects );
    }

    delete searchString;
    searchString = newstrdup( _searchString );
    caseSensitive = _caseSensitive;
    continueSearch = _continueSearch;

    progressDlg->setBreakFunc( searchabort, this );
    progressDlg->setText( "" );
    progressDlg->show( searchthread, this );
}

// static method, cancels asynch rendering if abortAsynch is true
void DocumentViewer::searchabort( void *data )
{
    ((DocumentViewer *)data)->abortSearch = true;
}

// static method, thread for asynchronous searching
void DocumentViewer::searchthread( void *p )
{
    DosSetPriority( PRTYS_THREAD, PRTYC_REGULAR, PRTYD_MINIMUM, 0 );
    DocumentViewer *_this = (DocumentViewer *)p;

    HAB thab = WinInitialize( 0 );
    HMQ thmq = WinCreateMsgQueue( thab, 0 );

    long i = _this->currentpage;
    if ( _this->continueSearch && ( _this->currentpage < ( _this->totalpages - 1 ) ) ) {
        i = _this->currentpage + 1;
    }

    bool found = false;
    for ( ; i < _this->totalpages; i++ )
    {
        char *fmt = newstrdupL( FIND_SEARCH_PAGE_OF );
        char *buf = new char[ 255 ];
        snprintf( buf, 255, fmt, i + 1, _this->totalpages );
        _this->progressDlg->setText( buf );
        delete fmt;
        delete buf;

        _this->foundrects[ i ] = _this->doc->searchText( _this->ev, i,
                                        (char *)_this->searchString, _this->caseSensitive );
        if ( _this->foundrects[ i ] != NULL )
        {
            found = true;
            _this->progressDlg->hide();
            _this->goToPage( i );
            if ( _this->foundrects[i]->_length > 0 ) {
                RECTL r;
                _this->docPosToWinPos( i, &(_this->foundrects[i]->_buffer[0]), &r );
                _this->scrollToPos( _this->hWndDoc, NULLHANDLE, r.xLeft, r.yBottom, false );
            }
            break;
        }

        if ( _this->abortSearch ) {
            break;
        }
    }
    _this->progressDlg->hide();

    if ( !found && !_this->abortSearch )
    {
        char *notfound = newstrdupL( FIND_NOT_FOUND );
        WinMessageBox( HWND_DESKTOP, _this->hMainFrame, notfound, NULL,
                       1, MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
        delete notfound;
    }

    WinDestroyMsgQueue( thmq );
    WinTerminate( thab );
    _endthread();
}

// count real zoom level based on specified
void DocumentViewer::adjustSize()
{
    if ( doc != NULL )
    {
        width  = pagesizes[ currentpage ].x;
        height = pagesizes[ currentpage ].y;

        fullwidth = 0;
        fullheight = 0;
        for ( long i = 0; i < totalpages; i++ ) {
            fullwidth = __max( fullwidth, pagesizes[i].x );
            fullheight += pagesizes[i].y;
        }

        if ( zoom == -1 ) { // fit width
            realzoom = (double)cxClient / ( continuous ? fullwidth : width );
        }
        else if ( zoom == -2 ) { // fit page
            realzoom = __min( (double)cxClient / width, (double)cyClient / height );
        }
        else {
            realzoom = zoom;
        }
        width *= realzoom;
        height *= realzoom;
        fullwidth *= realzoom;
        fullheight *= realzoom;
    }
}

// page redraw
void DocumentViewer::drawPage()
{
    if ( !continuous )
    {
        LuDocument::freeRectangles( ev, selrects[ currentpage ] );
        selrects[ currentpage ] = NULL;

        if ( links != NULL ) {
            if ( links[ currentpage ] == NULL ) {
                links[ currentpage ] = doc->getLinkMapping( ev, currentpage );
            }
        }

        Lucide::enableCopy( false );
    }
    WinSendMsg( hWndDoc, WM_SIZE, MPFROM2SHORT( cxClient, cyClient ),
                MPFROM2SHORT( cxClient, cyClient ) );
    WinInvalidateRect( hWndDoc, NULL, FALSE );
}


// handles vertical scrolling
MRESULT DocumentViewer::vertScroll( HWND hwnd, MPARAM mp2, HRGN hrgn )
{
    if ( fullscreen ) {
        return ( MRFROMLONG( 0 ) );
    }

    sVscrollInc = 0;

    switch ( SHORT2FROMMP( mp2 ) )
    {
        case SB_LINEUP:
            sVscrollInc = -(__max( LINE_HEIGHT, VScrollStep ));
            break ;
        case SB_LINEDOWN:
            sVscrollInc = __max( LINE_HEIGHT, VScrollStep );
            break;
        case SB_PAGEUP:
            sVscrollInc = __min( -1, -( cyClient - LINE_HEIGHT ) );
            break;
        case SB_PAGEDOWN:
            sVscrollInc = __max( 1, cyClient - LINE_HEIGHT );
            break;
        case SB_SLIDERTRACK:
        case SB_SLIDERPOSITION:
            sVscrollInc = ( SHORT1FROMMP( mp2 ) - sVscrollPos ) * VScrollStep;
            break;
    }

    sVscrollInc = __max( -sVscrollPos * VScrollStep, __min( sVscrollInc,
                              ( sVscrollMax - sVscrollPos ) * VScrollStep ) );

    if ( sVscrollInc != 0 )
    {
        sVscrollPos += (SHORT)( sVscrollInc / VScrollStep );
        WinScrollWindow( hwnd, 0, sVscrollInc, NULL, NULL, hrgn, NULL, SW_INVALIDATERGN );
        WinSendMsg( hWndVscroll, SBM_SETPOS, MPFROMSHORT( sVscrollPos ), MPVOID );
        WinUpdateWindow( hwnd );
        sVscrollInc = 0;
    }
    return ( MRFROMLONG( 0 ) );
}

// handles horizontal scrolling
MRESULT DocumentViewer::horizScroll( HWND hwnd, MPARAM mp2, HRGN hrgn )
{
    if ( fullscreen ) {
        return ( MRFROMLONG( 0 ) );
    }

    sHscrollInc = 0;

    switch ( SHORT2FROMMP( mp2 ) )
    {
        case SB_LINELEFT:
            sHscrollInc = -LINE_HEIGHT;
            break;
        case SB_LINERIGHT:
            sHscrollInc = LINE_HEIGHT;
            break;
        case SB_PAGELEFT:
            sHscrollInc = __min( -1, -( cxClient - LINE_HEIGHT ) );
            break;
        case SB_PAGERIGHT:
            sHscrollInc = __max( 1, cxClient - LINE_HEIGHT );
            break;
        case SB_SLIDERTRACK:
        case SB_SLIDERPOSITION:
            sHscrollInc = SHORT1FROMMP( mp2 ) - sHscrollPos;
            break;
    }

    sHscrollInc = __max( -sHscrollPos, __min( sHscrollInc, sHscrollMax - sHscrollPos ) );

    if ( sHscrollInc != 0 )
    {
        sHscrollPos += (SHORT)sHscrollInc;
        WinScrollWindow( hwnd, -sHscrollInc, 0, NULL, NULL, hrgn, NULL, SW_INVALIDATERGN );
        WinSendMsg( hWndHscroll, SBM_SETPOS, MPFROMSHORT( sHscrollPos ), MPVOID );
        WinUpdateWindow( hwnd );
        sHscrollInc = 0;
    }
    return ( MRFROMLONG( 0 ) );
}


// handles WM_SIZE message
// creates appropriate hps buffer, sets scrollbars limits
void DocumentViewer::wmSize( HWND hwnd, MPARAM mp2 )
{
    if ( !WinIsWindowShowing( hwnd ) ) {
        return;
    }

    cxClient = SHORT1FROMMP( mp2 );
    cyClient = SHORT2FROMMP( mp2 );

    double relativeScrollPos = ( sVscrollMax == 0 ) ? 0 :
                                    (double)sVscrollPos / (double)sVscrollMax;

    adjustSize();

    if ( ( hpsBuffer != NULLHANDLE ) && ( hdcBuffer != NULLHANDLE ) ) {
        DestroyGraphicsBuffer( hpsBuffer, hdcBuffer );
        hpsBuffer = hdcBuffer = NULLHANDLE;
    }

    HPS hps = WinGetPS( hwnd );
    RECTL rectl = { 0, 0, cxClient, cyClient };
    CreateGraphicsBuffer( hab, &rectl, hps, &hpsBuffer, &hdcBuffer );
    WinReleasePS( hps );

    if ( fullscreen )
    {
        sHscrollMax = 0;
        sHscrollPos = 0;
        realVscrollMax = 0;
        VScrollStep = 1;
        sVscrollPos = 0;
    }
    else
    {
        sHscrollMax = (SHORT)__max( 0, ( continuous ? fullwidth : width ) - cxClient );
        sHscrollPos = __min( sHscrollPos, sHscrollMax );

        WinSendMsg( hWndHscroll, SBM_SETSCROLLBAR,
                    MPFROMSHORT(sHscrollPos), MPFROM2SHORT(0, sHscrollMax) );
        WinSendMsg( hWndHscroll, SBM_SETTHUMBSIZE,
                    MPFROM2SHORT( cxClient, width ), MPVOID );
        WinEnableWindow( hWndHscroll, (BOOL)( sHscrollMax != 0 ) );

        if ( continuous )
        {
            realVscrollMax = __max( 0, fullheight - cyClient );
            VScrollStep = LINE_HEIGHT;
            ULONG ssize = realVscrollMax / VScrollStep;
            while ( ssize > 32000 ) {
                VScrollStep += LINE_HEIGHT;
                ssize = realVscrollMax / VScrollStep;
            }

            sVscrollMax = (SHORT)ssize;
        }
        else {
            realVscrollMax = sVscrollMax = (SHORT)__max( 0, height - cyClient );
            VScrollStep = 1;
        }
        sVscrollPos = __min( sVscrollPos, sVscrollMax );

        WinSendMsg( hWndVscroll, SBM_SETSCROLLBAR,
                    MPFROMSHORT(sVscrollPos), MPFROM2SHORT(0, sVscrollMax) );
        if ( continuous ) {
            WinSendMsg( hWndVscroll, SBM_SETTHUMBSIZE,
                        MPFROM2SHORT( cyClient/VScrollStep, fullheight/VScrollStep ), MPVOID );
        }
        else {
            WinSendMsg( hWndVscroll, SBM_SETTHUMBSIZE,
                        MPFROM2SHORT( cyClient, height ), MPVOID );
        }
        WinEnableWindow( hWndVscroll, (BOOL)( sVscrollMax != 0 ) );

        SHORT realScrollPos = (SHORT)(sVscrollMax * relativeScrollPos);
        vertScroll( hWndDoc, MPFROM2SHORT( realScrollPos, SB_SLIDERPOSITION ), NULLHANDLE );
    }
}

// returns true if subrect inside rect
inline bool isSubrect( PRECTL rect, PRECTL subrect )
{
    return ( ( subrect->xLeft >= rect->xLeft ) &&
             ( subrect->yBottom >= rect->yBottom ) &&
             ( subrect->xRight <= rect->xRight ) &&
             ( subrect->yTop <= rect->yTop ) );
}

// static method, cancels asynch rendering if abortAsynch is true
long _System DocumentViewer::asynchCallbackFnAbort( void *data )
{
    return (long)(((DocumentViewer *)data)->abortAsynch);
}

// static method, draws area during asynch rendering
long _System DocumentViewer::asynchCallbackFnDraw( void *data )
{
    DocumentViewer *_this = (DocumentViewer *)data;
    HPS hps = WinGetPS( _this->hWndDoc );
    if ( hps != NULLHANDLE )
    {
        PRECTL drawRect = &((*_this->drawareas)[_this->drawareaIndex].drawrect);
        LONG rclx = drawRect->xRight - drawRect->xLeft;
        LONG rcly = drawRect->yTop - drawRect->yBottom;

        POINTL aptlPoints[4]={ drawRect->xLeft, drawRect->yBottom,
                               drawRect->xRight-1, drawRect->yTop-1,
                               0, 0, rclx, rcly };

        LONG lRop = ROP_SRCCOPY;
        BITMAPINFO2 pbmi;
        pbmi.cbFix = 16L;
        pbmi.cx = rclx;
        pbmi.cy = rcly;
        pbmi.cPlanes = 1;
        pbmi.cBitCount = _this->bpp * 8;
        GpiDrawBits( hps, _this->pixbuf->getDataPtr( _this->ev ), &pbmi, 4L,
                     aptlPoints, lRop, BBO_IGNORE );

        WinReleasePS( hps );
    }
    return 0;
}

// static method, thread for asynchronous rendering
void DocumentViewer::drawthread( void *p )
{
    DosSetPriority( PRTYS_THREAD, PRTYC_REGULAR, PRTYD_MINIMUM, 0 );
    DocumentViewer *_this = (DocumentViewer *)p;

    HAB thab = WinInitialize( 0 );
    HMQ thmq = WinCreateMsgQueue( thab, 0 );

    ULONG postCnt;
    while ( !_this->termdraw )
    {
        DosWaitEventSem( _this->haveDraw, SEM_INDEFINITE_WAIT );
        DosResetEventSem( _this->haveDraw, &postCnt );
        _this->abortAsynch = false;

        if ( ( _this->drawareas != NULL ) && ( _this->doc != NULL ) )
        {
            DosRequestMutexSem( _this->todrawAccess, SEM_INDEFINITE_WAIT );

            for ( _this->drawareaIndex = 0;
                  _this->drawareaIndex < _this->drawareas->size();
                  _this->drawareaIndex++ )
            {
                PageDrawArea *pda = &(*_this->drawareas)[ _this->drawareaIndex ];

                LONG rclx = pda->drawrect.xRight - pda->drawrect.xLeft;
                LONG rcly = pda->drawrect.yTop - pda->drawrect.yBottom;
                _this->pixbuf = new LuPixbuf( _this->ev, rclx, rcly, _this->bpp );
                _this->doc->renderPageToPixbufAsynch( _this->ev, pda->pagenum,
                       pda->startpos.x, pda->startpos.y, rclx, rcly, _this->realzoom,
                       _this->rotation, _this->pixbuf,
                       asynchCallbackFnDraw, asynchCallbackFnAbort, p );
                delete _this->pixbuf;
                _this->pixbuf = NULL;

                if ( _this->abortAsynch ) {
                    break;  // TODO: remove completed areas from drawareas
                }
            }

            if ( !_this->abortAsynch )
            {
                HPS hps = WinGetPS( _this->hWndDoc );
                if ( hps != NULLHANDLE ) {
                    for ( int i = 0; i < _this->drawareas->size(); i++ )
                    {
                        PageDrawArea *pda = &(*_this->drawareas)[ i ];

                        _this->drawSelection( pda->pagenum, hps, &pda->drawrect );
                        _this->drawFound( pda->pagenum, hps, &pda->drawrect );
                    }
                    WinReleasePS( hps );
                }
                WinSetRectEmpty( _this->hab, &_this->savedRcl );
                delete _this->drawareas;
                _this->drawareas = NULL;
            }

            DosReleaseMutexSem( _this->todrawAccess );
        }
    }
    WinDestroyMsgQueue( thmq );
    WinTerminate( thab );
    _endthread();
}

// handles WM_PAINT if singlepage asynchronous rendering used
// posts events to drawthread
void DocumentViewer::wmPaintAsynch( HWND hwnd )
{
    RECTL rcl;
    HPS hps = WinBeginPaint( hwnd, 0L, &rcl );
    GpiCreateLogColorTable( hpsBuffer, 0, LCOLF_RGB, 0, 0, NULL );
    WinFillRect( hpsBuffer, &rcl, BORDER_COLOR );
    BlitGraphicsBuffer( hps, hpsBuffer, &rcl );
    WinEndPaint( hps );

    if ( doc != NULL )
    {
        LONG xPos = 0, yPos = 0;
        if ( width < cxClient ) {
            xPos = ( cxClient - width ) / 2;
        }
        if ( height < cyClient ) {
            yPos = ( cyClient - height ) / 2;
        }

        RECTL rclPage = { xPos, yPos, width + xPos, height + yPos };
        RECTL rclDraw = { 0 };
        if ( WinIntersectRect( hab, &rclDraw, &rcl, &rclPage ) )
        {
            if ( ( drawareas != NULL ) && ( drawareas->size() > 0 ) ) {
                if ( isSubrect( &((*drawareas)[0].drawrect), &rclDraw ) &&
                     ( sVscrollInc == 0 ) && ( sHscrollInc == 0 ) ) {
                    return;
                }
            }

            abortAsynch = true;
            DosRequestMutexSem( todrawAccess, SEM_INDEFINITE_WAIT );

            if ( drawareas == NULL ) {
                drawareas = new DrawAreas;
            }
            if ( drawareas->size() == 0 ) {
                PageDrawArea pda;
                memset( &pda, 0, sizeof( pda ) );
                pda.pagenum = currentpage;
                drawareas->push_back( pda );
            }

            PageDrawArea *ppda = &((*drawareas)[0]);

            if ( !WinIsRectEmpty( hab, &ppda->drawrect ) )
            {
                if ( sVscrollInc > 0 ) {
                    ppda->drawrect.yTop    += sVscrollInc;
                } else if ( sVscrollInc < 0 ) {
                    ppda->drawrect.yBottom += sVscrollInc;
                }
                if ( sHscrollInc > 0 ) {
                    ppda->drawrect.xLeft  -= sHscrollInc;
                } else if ( sHscrollInc < 0 ) {
                    ppda->drawrect.xRight -= sHscrollInc;
                }
            }
            WinUnionRect( hab, &ppda->drawrect, &ppda->drawrect, &rclDraw );
            ppda->startpos.x = sHscrollPos + ppda->drawrect.xLeft - xPos;
            ppda->startpos.y = ( yPos > 0 ) ? rclPage.yTop - ppda->drawrect.yTop :
                    ( cyClient - ppda->drawrect.yTop ) + sVscrollPos;

            DosReleaseMutexSem( todrawAccess );
            DosPostEventSem( haveDraw );
        }
    }
}


// handles WM_PAINT if continuous asynchronous rendering used
void DocumentViewer::wmPaintContAsynch( HWND hwnd )
{
    RECTL rcl, rclWin, rclDraw = { 0 };
    HPS hps = WinBeginPaint( hwnd, 0L, &rcl );
    GpiCreateLogColorTable( hpsBuffer, 0, LCOLF_RGB, 0, 0, NULL );
    WinFillRect( hpsBuffer, &rcl, BORDER_COLOR );
    BlitGraphicsBuffer( hps, hpsBuffer, &rcl );
    WinEndPaint( hps );

    if ( doc != NULL )
    {
        if ( isSubrect( &savedRcl, &rcl ) && ( sVscrollInc == 0 ) && ( sHscrollInc == 0 ) ) {
            return;
        }

        abortAsynch = true;
        DosRequestMutexSem( todrawAccess, SEM_INDEFINITE_WAIT );

        WinQueryWindowRect( hwnd, &rclWin );
        WinUnionRect( hab, &rcl, &rcl, &savedRcl );

        if ( sVscrollInc > 0 ) {
            rcl.yTop    += sVscrollInc;
        } else if ( sVscrollInc < 0 ) {
            rcl.yBottom += sVscrollInc;
        }
        if ( sHscrollInc > 0 ) {
            rcl.xLeft  -= sHscrollInc;
        } else if ( sHscrollInc < 0 ) {
            rcl.xRight -= sHscrollInc;
        }

        WinIntersectRect( hab, &rclDraw, &rcl, &rclWin );
        WinCopyRect( hab, &rcl, &rclDraw );
        WinCopyRect( hab, &savedRcl, &rcl );

        delete drawareas;
        drawareas = findDrawAreas( &rcl );

        for ( int i = 0; i < drawareas->size(); i++ )
        {
            PageDrawArea *pda = &(*drawareas)[ i ];

            // load links for page if not loaded before
            if ( links[ pda->pagenum ] == NULL ) {
                links[ pda->pagenum ] = doc->getLinkMapping( ev, pda->pagenum );
            }
        }
        DosReleaseMutexSem( todrawAccess );
        DosPostEventSem( haveDraw );

        determineCurrentPage();
    }
}


// handles WM_PAINT if single-page synchronous rendering used
void DocumentViewer::wmPaint( HWND hwnd )
{
    RECTL rcl;
    HPS hps = WinBeginPaint( hwnd, 0L, &rcl );
    GpiCreateLogColorTable( hpsBuffer, 0, LCOLF_RGB, 0, 0, NULL );
    WinFillRect( hpsBuffer, &rcl, BORDER_COLOR );

    if ( doc != NULL )
    {
        LONG xPos = 0, yPos = 0;
        if ( width < cxClient ) {
            xPos = ( cxClient - width ) / 2;
        }
        if ( height < cyClient ) {
            yPos = ( cyClient - height ) / 2;
        }

        RECTL rclPage = { xPos, yPos, width + xPos, height + yPos };
        RECTL rclDraw = { 0 };
        if ( WinIntersectRect( hab, &rclDraw, &rcl, &rclPage ) )
        {
            spos_x = sHscrollPos + rclDraw.xLeft - xPos;
            spos_y = ( yPos > 0 ) ? rclPage.yTop - rclDraw.yTop : (cyClient - rclDraw.yTop) + sVscrollPos;
            LONG rclx = rclDraw.xRight - rclDraw.xLeft;
            LONG rcly = rclDraw.yTop - rclDraw.yBottom;

            if ( drawPS )
            {
                doc->renderPageToPS( ev, currentpage, spos_x, spos_y, rclx, rcly,
                                     realzoom, rotation, hpsBuffer, &rclDraw );
            }
            else
            {
                pixbuf = new LuPixbuf( ev, rclx, rcly, bpp );
                POINTL aptlPoints[4]={ rclDraw.xLeft, rclDraw.yBottom,
                                       rclDraw.xRight-1, rclDraw.yTop-1,
                                       0, 0, rclx, rcly };

                doc->renderPageToPixbuf( ev, currentpage, spos_x, spos_y,
                                         rclx, rcly, realzoom, rotation, pixbuf );
                LONG lRop = ROP_SRCCOPY;
                BITMAPINFO2 pbmi;
                pbmi.cbFix = 16L;
                pbmi.cx = rclx;
                pbmi.cy = rcly;
                pbmi.cPlanes = 1;
                pbmi.cBitCount = bpp * 8;
                GpiDrawBits( hpsBuffer, pixbuf->getDataPtr( ev ), &pbmi, 4L,
                             aptlPoints, lRop, BBO_IGNORE );
                delete pixbuf;
                pixbuf = NULL;
            }

            drawSelection( currentpage, hpsBuffer, &rclDraw );
            drawFound( currentpage, hpsBuffer, &rclDraw );

            BlitGraphicsBuffer( hps, hpsBuffer, &rcl );
        }
    }
    else {
        BlitGraphicsBuffer( hps, hpsBuffer, &rcl );
    }
    WinEndPaint( hps );
}


// founds number of page at specified vertical position
// for continuous view only
long DocumentViewer::posToPagenum( LONG yPosWin, double *pageRest )
{
    double yPos = ( cyClient - yPosWin ) + ( sVscrollPos * VScrollStep );
    double pgend = 0;
    for ( long i = 0; i < totalpages; i++ )
    {
        pgend += ( pagesizes[ i ].y * realzoom );
        if ( yPos < pgend ) {
            *pageRest = pgend - yPos;
            return i;
        }
    }
    return 0;
}

// founds vertical position of specified
// for continuous view only
double DocumentViewer::pagenumToPos( long pagenum )
{
    double ypos = 0;
    for ( long i = 0; i < pagenum; i++ ) {
        ypos += pagesizes[ i ].y;
    }
    return ypos * realzoom;
}

// founds pages and it's areas to draw
// for continuous view only
DrawAreas *DocumentViewer::findDrawAreas( PRECTL r )
{
    DrawAreas *areas = new DrawAreas;
    if ( doc != NULL )
    {
        long foundpage = -1;
        double pageRest;
        for ( LONG i = r->yTop; i >= r->yBottom; i-- )
        {
            pageRest = 0;
            long pg = posToPagenum( i, &pageRest );
            if ( pg != foundpage )
            {
                double w = pagesizes[ pg ].x * realzoom;

                PageDrawArea pda;
                pda.pagenum = pg;

                LONG xPos = 0;
                if ( w < cxClient ) {
                    xPos = ( cxClient - w ) / 2;
                }
                RECTL rclPage = { xPos, 0, width + xPos, height };
                RECTL rclDraw = { 0 };
                if ( WinIntersectRect( hab, &rclDraw, r, &rclPage ) )
                {
                    pda.drawrect.xLeft   = __min( w + xPos, rclDraw.xLeft );
                    pda.drawrect.yBottom = __max( i - pageRest, rclDraw.yBottom );
                    pda.drawrect.xRight  = __min( w + xPos, rclDraw.xRight );
                    pda.drawrect.yTop    = i;

                    pda.startpos.x = sHscrollPos + pda.drawrect.xLeft - xPos;
                    pda.startpos.y = ( pagesizes[ pg ].y * realzoom ) - pageRest;

                    areas->push_back( pda );
                }
                foundpage = pg;
                i -= pageRest;
            }
        }
    }

    return areas;
}


// found current page in continuous view mode.
// it's a page which occupes a most larger area in the window.
void DocumentViewer::determineCurrentPage()
{
    RECTL rcl = { 0 };
    WinQueryWindowRect( hWndDoc, &rcl );
    DrawAreas *areas = findDrawAreas( &rcl );
    long pg = 0;
    long sz = 0;
    for ( int i = 0; i < areas->size(); i++ )
    {
        PageDrawArea *pda = &(*areas)[ i ];
        long pgsz = pda->drawrect.yTop - pda->drawrect.yBottom;
        if ( pgsz > sz ) {
            pg = pda->pagenum;
            sz = pgsz;
        }
    }
    delete areas;

    if ( pg != currentpage ) {
        currentpage = pg;
        Lucide::checkNavigationMenus();
    }
}


// handles WM_PAINT if continuous synchronous rendering used
void DocumentViewer::wmPaintCont( HWND hwnd )
{
    RECTL rcl;
    HPS hps = WinBeginPaint( hwnd, 0L, &rcl );
    GpiCreateLogColorTable( hpsBuffer, 0, LCOLF_RGB, 0, 0, NULL );
    WinFillRect( hpsBuffer, &rcl, BORDER_COLOR );

    if ( doc != NULL )
    {
        delete drawareas;
        drawareas = findDrawAreas( &rcl );

        for ( int i = 0; i < drawareas->size(); i++ )
        {
            PageDrawArea *pda = &(*drawareas)[ i ];

            // load links for page if not loaded before
            if ( links[ pda->pagenum ] == NULL ) {
                links[ pda->pagenum ] = doc->getLinkMapping( ev, pda->pagenum );
            }

            spos_x = pda->startpos.x;
            spos_y = pda->startpos.y;
            LONG rclx = pda->drawrect.xRight - pda->drawrect.xLeft;
            LONG rcly = pda->drawrect.yTop - pda->drawrect.yBottom;

            if ( drawPS )
            {
                doc->renderPageToPS( ev, pda->pagenum, spos_x, spos_y, rclx, rcly,
                                     realzoom, rotation, hpsBuffer, &(pda->drawrect) );
            }
            else
            {
                pixbuf = new LuPixbuf( ev, rclx, rcly, bpp );
                POINTL aptlPoints[4]={ pda->drawrect.xLeft, pda->drawrect.yBottom,
                                       pda->drawrect.xRight-1, pda->drawrect.yTop-1,
                                       0, 0, rclx, rcly };
                doc->renderPageToPixbuf( ev, pda->pagenum, spos_x, spos_y,
                                         rclx, rcly, realzoom, rotation, pixbuf );
                LONG lRop = ROP_SRCCOPY;
                BITMAPINFO2 pbmi;
                pbmi.cbFix = 16L;
                pbmi.cx = rclx;
                pbmi.cy = rcly;
                pbmi.cPlanes = 1;
                pbmi.cBitCount = bpp * 8;
                GpiDrawBits( hpsBuffer, pixbuf->getDataPtr( ev ), &pbmi, 4L,
                             aptlPoints, lRop, BBO_IGNORE );
                delete pixbuf;
                pixbuf = NULL;
            }

            drawSelection( pda->pagenum, hpsBuffer, &pda->drawrect );
            drawFound( pda->pagenum, hpsBuffer, &pda->drawrect );
        }
        delete drawareas;
        drawareas = NULL;
    }
    BlitGraphicsBuffer( hps, hpsBuffer, &rcl );
    WinEndPaint( hps );

    if ( doc != NULL ) {
        determineCurrentPage();
    }
}


// Rotates document rectangle
void DocumentViewer::rotateRectangle( long pagenum, LuRectangle *r )
{
    double tmp_x1 = r->x1;
    double tmp_y1 = r->y1;
    double tmp_x2 = r->x2;
    double tmp_y2 = r->y2;

    double w = pagesizes[ pagenum ].x;
    double h = pagesizes[ pagenum ].y;

    if ( rotation == 90 ) {
        r->x1 = tmp_y1;
        r->y1 = w - tmp_x1;
        r->x2 = tmp_y2;
        r->y2 = w - tmp_x2;
    }
    else if ( rotation == 180 )
    {
        r->x1 = w - tmp_x2;
        r->y1 = h - tmp_y2;
        r->x2 = w - tmp_x1;
        r->y2 = h - tmp_y1;
    }
    else if ( rotation == 270 )
    {
        r->x1 = h - tmp_y1;
        r->y1 = tmp_x1;
        r->x2 = h - tmp_y2;
        r->y2 = tmp_x2;
    }

    if ( r->x1 > r->x2 ) {
        double tmp = r->x1;
        r->x1 = r->x2;
        r->x2 = tmp;
    }

    if ( r->y1 > r->y2 ) {
        double tmp = r->y1;
        r->y1 = r->y2;
        r->y2 = tmp;
    }
}

// converts window position to document position
// single page mode only
void DocumentViewer::winPosToDocPos( PPOINTL startpoint, PPOINTL endpoint, LuRectangle *r )
{
    LONG sx = startpoint->x;
    LONG sy = startpoint->y;
    LONG ex = endpoint->x;
    LONG ey = endpoint->y;
    if ( width < cxClient ) {
        LONG xPos = ( cxClient - width ) / 2;
        sx -= xPos;
        ex -= xPos;
    }
    if ( height < cyClient ) {
        LONG yPos = ( cyClient - height ) / 2;
        sy += yPos;
        ey += yPos;
    }

    r->x1 = ( sx + sHscrollPos ) / realzoom;
    r->y1 = ( ( cyClient - sy ) + sVscrollPos ) / realzoom;
    r->x2 = ( ex + sHscrollPos ) / realzoom;
    r->y2 = ( ( cyClient - ey ) + sVscrollPos ) / realzoom;

    rotateRectangle( currentpage, r );
}

// converts window position to document position
// continuous view mode only
void DocumentViewer::winPosToDocPos( PageDrawArea *pda, LuRectangle *r )
{
    LONG sx = pda->drawrect.xLeft;
    LONG ex = pda->drawrect.xRight;
    double w = pagesizes[ pda->pagenum ].x * realzoom;
    if ( w < cxClient ) {
        LONG xPos = ( cxClient - w ) / 2;
        sx -= xPos;
        ex -= xPos;
    }

    r->x1 = ( sHscrollPos + sx ) / realzoom;;
    r->y1 = pda->startpos.y / realzoom;
    r->x2 = ( ( ex - sx ) / realzoom ) + r->x1;
    r->y2 = ( ( pda->drawrect.yTop - pda->drawrect.yBottom ) / realzoom ) + r->y1;

    rotateRectangle( pda->pagenum, r );
}

// converts document position to window position
void DocumentViewer::docPosToWinPos( long pagenum, LuRectangle *r, PRECTL rcl )
{
    double yplus = continuous ? pagenumToPos( pagenum ) : 0;
    double w = pagesizes[ pagenum ].x;
    double h = pagesizes[ pagenum ].y;

    double tmp_x1 = r->x1;
    double tmp_y1 = r->y1;
    double tmp_x2 = r->x2;
    double tmp_y2 = r->y2;

    if ( rotation == 90 )
    {
        tmp_x1 = w - r->y2;
        tmp_y1 = r->x1;
        tmp_x2 = w - r->y1;
        tmp_y2 = r->x2;
    }
    else if ( rotation == 180 )
    {
        tmp_x1 = w - r->x2;
        tmp_y1 = h - r->y2;
        tmp_x2 = w - r->x1;
        tmp_y2 = h - r->y1;
    }
    else if ( rotation == 270 )
    {
        tmp_x1 = r->y1;
        tmp_y1 = h - r->x2;
        tmp_x2 = r->y2;
        tmp_y2 = h - r->x1;
    }

    rcl->xLeft   = ( tmp_x1 * realzoom ) - sHscrollPos;
    rcl->yBottom = cyClient - ( yplus + ( tmp_y2 * realzoom ) ) + ( sVscrollPos * VScrollStep );
    rcl->xRight  = ( tmp_x2 * realzoom ) - sHscrollPos;
    rcl->yTop    = cyClient - ( yplus + ( tmp_y1 * realzoom ) ) + ( sVscrollPos * VScrollStep );

    LONG pw = w * realzoom;
    if ( pw < cxClient ) {
        LONG xPos = ( cxClient - pw ) / 2;
        rcl->xLeft  += xPos;
        rcl->xRight += xPos;
    }
    if ( !continuous )
    {
        LONG ph = h * realzoom;
        if ( ph < cyClient ) {
            LONG yPos = ( cyClient - ph ) / 2;
            rcl->yBottom -= yPos;
            rcl->yTop    -= yPos;
        }
    }
}

// creates region from sequence of rectangles
HRGN DocumentViewer::rectsToRegion( long pagenum, HPS hps, LuDocument_LuRectSequence *rects )
{
    HRGN hrgn = GpiCreateRegion( hps, 0, NULL );
    if ( rects != NULL )
    {
        RECTL r = {0};
        for ( int i = 0; i < rects->_length; i++ )
        {
            docPosToWinPos( pagenum, &(rects->_buffer[i]), &r );
            HRGN tmprgn = GpiCreateRegion( hps, 1, &r );
            GpiCombineRegion( hps, hrgn, hrgn, tmprgn, CRGN_OR );
            GpiDestroyRegion( hps, tmprgn );
        }
    }
    return hrgn;
}

// draws selected area in window, using XOR mix
// drawing area may be restricted by r rectangle
void DocumentViewer::drawSelection( long pagenum, HPS hps, PRECTL r )
{
    GpiSetMix( hps, FM_XOR );
    GpiSetColor( hps, CLR_YELLOW );
    HRGN selectRegion = rectsToRegion( pagenum, hps, selrects[ pagenum ] );
    if ( r != NULL )
    {
        HRGN tmprgn = GpiCreateRegion( hps, 1, r );
        GpiCombineRegion( hps, selectRegion, selectRegion, tmprgn, CRGN_AND );
        GpiDestroyRegion( hps, tmprgn );
    }
    GpiPaintRegion( hps, selectRegion );
    GpiDestroyRegion( hps, selectRegion );
}

void DocumentViewer::drawFound( long pagenum, HPS hps, PRECTL r )
{
    GpiSetMix( hps, FM_XOR );
    GpiSetColor( hps, CLR_CYAN );
    HRGN selectRegion = rectsToRegion( pagenum, hps, foundrects[ pagenum ] );
    if ( r != NULL )
    {
        HRGN tmprgn = GpiCreateRegion( hps, 1, r );
        GpiCombineRegion( hps, selectRegion, selectRegion, tmprgn, CRGN_AND );
        GpiDestroyRegion( hps, tmprgn );
    }
    GpiPaintRegion( hps, selectRegion );
    GpiDestroyRegion( hps, selectRegion );
}

// scrolls window to specified pos (optionally with text selection)
void DocumentViewer::scrollToPos( HWND hwnd, HRGN hrgn, LONG xpos, LONG ypos,
                                  bool withSelection )
{
    SHORT xinc = 0;
    SHORT yinc = 0;

    if ( ( xpos < 0 ) && ( sHscrollPos > 0 ) ) {
        xinc = __max( sHscrollPos * -1, xpos );
    } else if ( ( xpos > cxClient ) && ( sHscrollPos < sHscrollMax ) ) {
        xinc = __min( sHscrollMax - sHscrollPos, xpos - cxClient );
    }
    if ( ( ypos < 0 ) && ( sVscrollPos < sVscrollMax ) ) {
        yinc = __min( ( sVscrollMax - sVscrollPos ) * VScrollStep, ypos * -1 );
    }
    else if ( ( ypos > cyClient ) && ( sVscrollPos > 0 ) ) {
        yinc = __max( ( sVscrollPos * -1 ) * VScrollStep, cyClient - ypos );
    }

    if ( xinc != 0 ) {
        horizScroll( hwnd, MPFROM2SHORT( sHscrollPos + xinc, SB_SLIDERPOSITION ), hrgn );
        if ( withSelection ) {
            selectionStart.x -= xinc;
        }
    }

    if ( yinc != 0 )
    {
        SHORT remainder = yinc % VScrollStep;
        if ( remainder != 0 ) {
            SHORT add = VScrollStep - remainder;
            yinc += ( ( yinc > 0 ) ? add : -add );
        }

        vertScroll( hwnd, MPFROM2SHORT( ( ( sVscrollPos * VScrollStep ) + yinc ) / VScrollStep,
                                        SB_SLIDERPOSITION ), hrgn );
        if ( withSelection ) {
            selectionStart.y += yinc;
        }
    }
}

// handles WM_MOUSEMOVE
// performs text selection if mouse button pressed
// changes mouse ptr to 'hand' if it moves over link area
BOOL DocumentViewer::wmMouseMove( HWND hwnd, SHORT xpos, SHORT ypos )
{
    if ( mousePressed && ( doc != NULL ) )
    {
        selectionEnd.x = xpos;
        selectionEnd.y = ypos;

        if ( continuous )
        {
            scrollToPos( hwnd, NULLHANDLE, xpos, ypos, true );

            RECTL selRect = {
                selectionStart.x < selectionEnd.x ? selectionStart.x : selectionEnd.x,
                selectionStart.y < selectionEnd.y ? selectionStart.y : selectionEnd.y,
                selectionStart.x < selectionEnd.x ? selectionEnd.x : selectionStart.x,
                selectionStart.y < selectionEnd.y ? selectionEnd.y : selectionStart.y
            };

            DrawAreas *areas = findDrawAreas( &selRect );

            HPS hps = WinGetPS( hwnd );
            GpiSetMix( hps, FM_XOR );
            GpiSetColor( hps, CLR_YELLOW );

            for ( int i = 0; i < areas->size(); i++ )
            {
                PageDrawArea *pda = &(*areas)[ i ];

                winPosToDocPos( pda, &(selection[pda->pagenum]) );

                HRGN clearRegion = rectsToRegion( pda->pagenum, hps, selrects[ pda->pagenum ] );
                LuDocument::freeRectangles( ev, selrects[ pda->pagenum ] );
                selrects[ pda->pagenum ] = doc->getSelectionRectangles( ev, pda->pagenum, &(selection[pda->pagenum]) );
                HRGN selectRegion = rectsToRegion( pda->pagenum, hps, selrects[ pda->pagenum ] );
                GpiCombineRegion( hps, selectRegion, selectRegion, clearRegion, CRGN_XOR );
                GpiPaintRegion( hps, selectRegion );
                GpiDestroyRegion( hps, clearRegion );
                GpiDestroyRegion( hps, selectRegion );
            }

            WinReleasePS( hps );
            delete areas;
        }
        else
        {
            winPosToDocPos( &selectionStart, &selectionEnd, &(selection[currentpage]) );

            HPS hps = WinGetPS( hwnd );
            HRGN scrolledRegion = NULLHANDLE; //GpiCreateRegion( hps, 0, NULL );

            scrollToPos( hwnd, scrolledRegion, xpos, ypos, true );

            // 127/191/255
            //LONG lclr = ( 127 << 16 ) | ( 191 << 8 ) | 255;
            //LONG lclr = ( 128 << 16 ) | ( 64 << 8 );
            //LONG ltabl[ 1 ] = { lclr };
            //GpiCreateLogColorTable( hps, 0, LCOLF_CONSECRGB, 100, 1, ltabl );

            GpiSetMix( hps, FM_XOR );
            GpiSetColor( hps, CLR_YELLOW );
            //GpiSetColor( hps, 100 );

            HRGN clearRegion = rectsToRegion( currentpage, hps, selrects[ currentpage ] );
            LuDocument::freeRectangles( ev, selrects[ currentpage ] );
            if ( ( selectionStart.x == selectionEnd.x ) &&
                 ( selectionStart.y == selectionEnd.y ) ) {
                selrects[ currentpage ] = NULL;
                memset( &(selection[ currentpage ]), 0, sizeof( LuRectangle ) );
            }
            else {
                selrects[ currentpage ] = doc->getSelectionRectangles( ev, currentpage, &(selection[currentpage]) );
            }
            HRGN selectRegion = rectsToRegion( currentpage, hps, selrects[ currentpage ] );
            GpiCombineRegion( hps, selectRegion, selectRegion, clearRegion, CRGN_XOR );
            //GpiCombineRegion( hps, selectRegion, selectRegion, scrolledRegion, CRGN_DIFF );
            GpiPaintRegion( hps, selectRegion );
            GpiDestroyRegion( hps, clearRegion );
            GpiDestroyRegion( hps, selectRegion );
            //GpiDestroyRegion( hps, scrolledRegion );

            WinReleasePS( hps );
        }
    }
    else if ( links != NULL )
    {
        long pg = currentpage;
        if ( continuous ) {
            double tmp;
            pg = posToPagenum( ypos, &tmp );
        }

        if ( links[ pg ] != NULL )
        {
            for ( int i = 0; i < links[ pg ]->_length; i++ )
            {
                RECTL r = {0};
                docPosToWinPos( pg, &(links[ pg ]->_buffer[i].area), &r );

                POINTL ptl = { xpos, ypos };
                if ( WinPtInRect( hab, &r, &ptl ) ) {
                    WinSetPointer( HWND_DESKTOP, handptr );
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

// handles WM_BUTTON1CLICK
BOOL DocumentViewer::wmClick( HWND hwnd, SHORT xpos, SHORT ypos )
{
    if ( links == NULL ) {
        return FALSE;
    }

    long pg = currentpage;
    if ( continuous ) {
        double tmp;
        pg = posToPagenum( ypos, &tmp );
    }

    if ( links[ pg ] != NULL )
    {
        for ( int i = 0; i < links[ pg ]->_length; i++ )
        {
            RECTL r = {0};
            docPosToWinPos( pg, &(links[ pg ]->_buffer[i].area), &r );

            POINTL ptl = { xpos, ypos };
            if ( WinPtInRect( hab, &r, &ptl ) )
            {
                if ( links[ pg ]->_buffer[i].link.type == LU_LINK_TYPE_EXTERNAL_URI )
                {
                    WinMessageBox( HWND_DESKTOP, hMainFrame,
                        links[ pg ]->_buffer[i].link.uri, "URI", 1,
                        MB_OK | MB_INFORMATION | MB_MOVEABLE );
                }
                else if ( links[ pg ]->_buffer[i].link.type == LU_LINK_TYPE_TITLE )
                {
                    char *title = links[ pg ]->_buffer[i].link.title;
                    if ( title == NULL ) {
                        title = "???";
                    }
                    WinMessageBox( HWND_DESKTOP, hMainFrame,
                        title, "?", 1, MB_OK | MB_INFORMATION | MB_MOVEABLE );
                }
                else if ( links[ pg ]->_buffer[i].link.type == LU_LINK_TYPE_PAGE )
                {
                    goToPage( links[ pg ]->_buffer[i].link.page );
                }

                return TRUE;
            }
        }
    }

    return FALSE;
}


BOOL DocumentViewer::wmChar( HWND hwnd, MPARAM mp1, MPARAM mp2 )
{
    USHORT fsflags = SHORT1FROMMP( mp1 );
    USHORT usch = SHORT1FROMMP( mp2 );
    USHORT usvk = SHORT2FROMMP( mp2 );

    if ( ( fsflags & KC_VIRTUALKEY ) && !( fsflags & KC_KEYUP ) )
    {
        switch ( usvk )
        {
            case VK_UP:
                WinSendMsg( hwnd, WM_VSCROLL, MPVOID, MPFROM2SHORT( 0, SB_LINEUP ) );
                return TRUE;

            case VK_DOWN:
                WinSendMsg( hwnd, WM_VSCROLL, MPVOID, MPFROM2SHORT( 0, SB_LINEDOWN ) );
                return TRUE;

            case VK_PAGEUP:
                if ( fsflags & KC_CTRL )
                {
                    if ( fullscreen ) {
                        goToPage( 0 );
                    } else {
                        vertScroll( hwnd, MPFROM2SHORT( 0, SB_SLIDERPOSITION ), NULLHANDLE );
                    }
                }
                else
                {
                    if ( fullscreen ) {
                        goToPage( currentpage - 1 );
                    } else {
                        WinSendMsg( hwnd, WM_VSCROLL, MPVOID, MPFROM2SHORT( 0, SB_PAGEUP ) );
                    }
                }
                return TRUE;

            case VK_PAGEDOWN:
                if ( fsflags & KC_CTRL )
                {
                    if ( fullscreen ) {
                        goToPage( totalpages - 1 );
                    } else {
                        vertScroll( hwnd, MPFROM2SHORT( sVscrollMax, SB_SLIDERPOSITION ), NULLHANDLE );
                    }
                }
                else
                {
                    if ( fullscreen ) {
                        goToPage( currentpage + 1 );
                    } else {
                        WinSendMsg( hwnd, WM_VSCROLL, MPVOID, MPFROM2SHORT( 0, SB_PAGEDOWN ) );
                    }
                }
                return TRUE;

            case VK_LEFT:
                WinSendMsg( hwnd, WM_HSCROLL, MPVOID, MPFROM2SHORT( 0, SB_LINELEFT ) );
                return TRUE;

            case VK_RIGHT:
                WinSendMsg( hwnd, WM_HSCROLL, MPVOID, MPFROM2SHORT( 0, SB_LINERIGHT ) );
                return TRUE;

            case VK_HOME:
                horizScroll( hwnd, MPFROM2SHORT( 0, SB_SLIDERPOSITION ), NULLHANDLE );
                return TRUE;

            case VK_END:
                horizScroll( hwnd, MPFROM2SHORT( sHscrollMax, SB_SLIDERPOSITION ), NULLHANDLE );
                return TRUE;
        }
    }

    // Ctrl+L
    if ( ( fsflags & KC_CTRL ) && !( fsflags & KC_KEYUP ) && ( toupper( usch ) == 'L' ) )
    {
        Lucide::toggleFullscreen();
        return TRUE;
    }

    // +
    if ( ( fsflags & KC_CHAR ) && !( fsflags & KC_KEYUP ) && ( usch == '+' ) ) {
        goToPage( currentpage + 1 );
        return TRUE;
    }
    // -
    if ( ( fsflags & KC_CHAR ) && !( fsflags & KC_KEYUP ) && ( usch == '-' ) ) {
        goToPage( currentpage - 1 );
        return TRUE;
    }

    return FALSE;
}

// handles WM_BUTTON1DOWN
void DocumentViewer::wmButton1Down( HWND hwnd, SHORT xpos, SHORT ypos )
{
    if ( continuous && ( doc != NULL ) )
    {
        // clear selection
        RECTL rcl = { 0 };
        WinQueryWindowRect( hwnd, &rcl );
        DrawAreas *areas = findDrawAreas( &rcl );

        HPS hps = WinGetPS( hwnd );
        GpiSetMix( hps, FM_XOR );
        GpiSetColor( hps, CLR_YELLOW );

        for ( int i = 0; i < areas->size(); i++ )
        {
            PageDrawArea *pda = &(*areas)[ i ];

            HRGN clearRegion = rectsToRegion( pda->pagenum, hps, selrects[ pda->pagenum ] );
            GpiPaintRegion( hps, clearRegion );
            GpiDestroyRegion( hps, clearRegion );
        }
        WinReleasePS( hps );
        delete areas;

        freeRects( selrects );

        memset( selection, 0, sizeof( LuRectangle ) * totalpages );
    }

    WinSetCapture( HWND_DESKTOP, hwnd );
    mousePressed = true;
    selectionStart.x = xpos;
    selectionStart.y = ypos;
}

// handles WM_BUTTON1UP
void DocumentViewer::wmButton1Up()
{
    WinSetCapture( HWND_DESKTOP, NULLHANDLE );
    mousePressed = false;

    bool haveSelection = false;
    for ( long i = 0; i < totalpages; i++ ) {
        if ( selrects[ i ] != NULL ) {
            haveSelection = true;
            break;
        }
    }

    Lucide::enableCopy( haveSelection );
}


// handles DM_DRAGOVER
MRESULT DocumentViewer::wmDragOver( PDRAGINFO dragInfo )
{
    PDRAGITEM dragItem;
    USHORT    usOp, usIndicator;

    usOp = 0;
    usIndicator = DOR_NODROPOP;

    DrgAccessDraginfo( dragInfo );

    if ( dragInfo->usOperation == DO_DEFAULT )
    {
        dragItem = DrgQueryDragitemPtr( dragInfo, 0 );
        if ( DrgQueryDragitemCount( dragInfo ) == 1 )
        {
            if ( DrgVerifyRMF( dragItem, "DRM_OS2FILE", NULL ) &&
                 ( dragItem->hstrContainerName != NULLHANDLE ) &&
                 ( dragItem->hstrSourceName != NULLHANDLE ) )
            {
                char fname[ CCHMAXPATHCOMP ] = "";
                DrgQueryStrName( dragItem->hstrSourceName, CCHMAXPATHCOMP, fname );
                char *ext = strrchr( fname, '.' );
                if ( ext != NULL ) {
                    if ( pluginMan->createDocumentForExt( ext + 1, true ) != NULL ) {
                        usIndicator = DOR_DROP;
                        usOp = DO_UNKNOWN;
                    }
                }
            }
        }
    }

    DrgFreeDraginfo( dragInfo );
    return MRFROM2SHORT( usIndicator, usOp );
}


// handles DM_DROP
void DocumentViewer::wmDrop( PDRAGINFO dragInfo )
{
    PDRAGITEM dragItem;

    DrgAccessDraginfo( dragInfo );
    dragItem = DrgQueryDragitemPtr( dragInfo, 0 );

    char fname[ CCHMAXPATHCOMP ] = "";
    char fpath[ CCHMAXPATH ] = "";
    DrgQueryStrName( dragItem->hstrSourceName, CCHMAXPATHCOMP, fname );
    DrgQueryStrName( dragItem->hstrContainerName, CCHMAXPATH, fpath );
    DrgFreeDraginfo( dragInfo );

    strcat( fpath, fname );
    Lucide::loadDocument( fpath );
}


// static, window procedure
MRESULT EXPENTRY DocumentViewer::docViewProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    DocumentViewer *_this = (DocumentViewer *)WinQueryWindowULong( hwnd, QWL_USER );

    switch ( msg )
    {
        case WM_CREATE:
        {
            // Save the mp1 into our user data so that subsequent calls have
            // access to the parent C++ object
            WinSetWindowULong( hwnd, QWL_USER, (ULONG)mp1 );
            _this = (DocumentViewer *)mp1;
            return (MRESULT)FALSE;
        }

        case DM_DRAGOVER:
            return _this->wmDragOver( (PDRAGINFO)mp1 );

        case DM_DROP:
            _this->wmDrop( (PDRAGINFO)mp1 );
            return (MRESULT)FALSE;

        case WM_ERASEBACKGROUND:
            return (MRESULT)TRUE;

        case WM_SIZE:
            _this->wmSize( hwnd, mp2 );
            return (MRESULT)FALSE;

        case WM_HSCROLL:
            _this->horizScroll( hwnd, mp2, NULLHANDLE );
            break;

        case WM_VSCROLL:
            _this->vertScroll( hwnd, mp2, NULLHANDLE );
            break;

        case WM_PAINT:
            if ( _this->enableAsynchDraw ) {
                if ( _this->continuous ) {
                    _this->wmPaintContAsynch( hwnd );
                } else {
                    _this->wmPaintAsynch( hwnd );
                }
            } else {
                if ( _this->continuous ) {
                    _this->wmPaintCont( hwnd );
                } else {
                    _this->wmPaint( hwnd );
                }
            }
            return (MRESULT)FALSE;

        case WM_BUTTON1DOWN:
            _this->wmButton1Down( hwnd, SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ) );
            break;

        case WM_BUTTON1UP:
            _this->wmButton1Up();
            break;

        case WM_MOUSEMOVE:
            if ( _this->wmMouseMove( hwnd, SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ) ) ) {
                return (MRESULT)TRUE;
            }
            break;

        case WM_BUTTON1CLICK:
            if ( _this->wmClick( hwnd, SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ) ) ) {
                return (MRESULT)TRUE;
            }
            break;

        case WM_CHAR:
            if ( _this->wmChar( hwnd, mp1, mp2 ) ) {
                return (MRESULT)TRUE;
            }
            break;
    }

    return WinDefWindowProc( hwnd, msg, mp1, mp2 );
}


// static, window procedure
MRESULT EXPENTRY DocumentViewer::docFrameProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    DocumentViewer *_this = (DocumentViewer *)WinQueryWindowULong( hwnd, QWL_USER );

    switch ( msg )
    {
        case WM_SYSCOMMAND:
            // Send WM_SYSCOMMAND messages to main frame
            WinSendMsg( _this->hMainFrame, WM_SYSCOMMAND, mp1, mp2 );
            return (MRESULT)FALSE;
    }

    return _this->oldFrameProc( hwnd, msg, mp1, mp2 );
}

