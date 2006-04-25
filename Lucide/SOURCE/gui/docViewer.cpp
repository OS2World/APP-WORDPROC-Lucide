#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>

#include <process.h>
#include <stdio.h>

#include <ludoc.xh>
#include "lucide.h"
#include "docViewer.h"
#include "progressDlg.h"
#include "luutils.h"
#include "lucide_res.h"
#include "messages.h"


// OpenWatcom 1.4 headers doesn't have GpiDrawBits() declaration
extern "C" {
    LONG APIENTRY GpiDrawBits(HPS hps, PVOID pBits, PBITMAPINFO2 pbmiInfoTable,
                              LONG lCount, PPOINTL aptlPoints, LONG lRop, ULONG flOptions);
}

typedef LuDocument_LuRectSequence *PLuRectSequence;

#define LINE_HEIGHT     16

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
    zoom        = 1.0;
    realzoom    = 1.0;
    ev          = somGetGlobalEnvironment();
    pixbuf      = NULL;
    spos_x      = 0;
    spos_y      = 0;
    progressDlg = new ProgressDlg( hWndFrame );
    // continuous view
    continuous  = true;
    pagesizes   = NULL;
    realVscrollMax = 0;
    VScrollStep = 0;
    drawareas   = NULL;
    // asynch draw
    abortAsynch = false;
    termdraw    = false;
    enableAsynchDraw = false;
    WinSetRectEmpty( hab, &drawRect );
    DosCreateMutexSem( NULL, &todrawAccess, 0, FALSE );
    DosCreateEventSem( NULL, &haveDraw, 0, FALSE );
    // selection
    mousePressed = false;
    selectionStart.x = 0;  selectionStart.y = 0;
    selectionEnd.x = 0;  selectionEnd.y = 0;
    selection.x1 = 0;  selection.y1 = 0;  selection.x2 = 0;  selection.y2 = 0;
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

    hWndDoc = WinCreateWindow( hWndDocFrame, "er.docview", NULL,
                               WS_VISIBLE | WS_TABSTOP, 0, 0, 0, 0, hWndDocFrame,
                               HWND_TOP, FID_CLIENT, this, NULL );

    hWndHscroll = WinWindowFromID( hWndDocFrame, FID_HORZSCROLL );
    hWndVscroll = WinWindowFromID( hWndDocFrame, FID_VERTSCROLL );

    drawThreadId = _beginthread( drawthread, NULL, 65536, this );
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
        LuDocument::freeRectangles( ev, selrects );
        LuDocument::freeLinkMapping( ev, links );
        freeFoundrects();
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
}


// static, registration of a window class
void DocumentViewer::registerClass( HAB hab )
{
    WinRegisterClass( hab, "er.docview", docViewProc, CS_SIZEREDRAW, sizeof( ULONG ) * 2 );
}

// sets the document for viewing
void DocumentViewer::setDocument( LuDocument *_doc )
{
    doc         = _doc;
    zoom        = 1;
    currentpage = 0;
    fullwidth   = 0;
    fullheight  = 0;
    delete pagesizes;
    pagesizes   = NULL;
    delete foundrects;
    foundrects  = NULL;

    if ( doc != NULL )
    {
        totalpages = doc->getPageCount( ev );

        pagesizes = new LuSize[ totalpages ];
        for ( long i = 0; i < totalpages; i++ ) {
            doc->getPageSize( ev, i, &pagesizes[i].x, &pagesizes[i].y );
            fullwidth = __max( fullwidth, pagesizes[i].x );
            fullheight += pagesizes[i].y;
        }

        foundrects = new PLuRectSequence[ totalpages ];
        memset( foundrects, 0, sizeof( PLuRectSequence ) * totalpages );
        enableAsynchDraw = false; //doc->isAsynchRenderingSupported( ev );
        drawPage();
    }
}

void DocumentViewer::freeFoundrects()
{
    if ( foundrects != NULL ) {
        for ( long i = 0; i < totalpages; i++ ) {
            LuDocument::freeRectangles( ev, foundrects[ i ] );
        }
    }
}


// switch view to specified page
void DocumentViewer::goToPage( long page )
{
    currentpage = page;
    if ( doc != NULL ) {
        drawPage();
        Lucide::checkNavigationMenus();
    }
}

// Sets the zoom level
// _zoom - actual zoom level or:
//         -1 - fit width
//         -2 - fit page
void DocumentViewer::setZoom( double _zoom )
{
    zoom = _zoom;
    if ( doc != NULL ) {
        drawPage();
    }
}

// copy selected text to clipboard
void DocumentViewer::copyToClipbrd()
{
    char *t = doc->getText( ev, currentpage, &selection );
    textToClipbrd( hab, t );
}

// perform search in document
void DocumentViewer::searchDocument( const char *_searchString, bool _caseSensitive,
                                     bool _continueSearch )
{
    abortSearch = false;
    if ( !continueSearch ) {
        freeFoundrects();
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
            if ( _this->foundrects[i]->_length > 0 )
            {
                RECTL r;
                _this->docPosToWinPos( &(_this->foundrects[i]->_buffer[0]), &r );
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
        doc->getPageSize( ev, currentpage, &width, &height );

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
    if ( continuous )
    {

    }
    else
    {
        LuDocument::freeRectangles( ev, selrects );
        selrects = NULL;
        LuDocument::freeLinkMapping( ev, links );
        links = doc->getLinkMapping( ev, currentpage );
        Lucide::enableCopy( false );
        adjustSize();
        sVscrollPos = 0;
        WinSendMsg( hWndDoc, WM_SIZE, MPFROM2SHORT( cxClient, cyClient ),
                    MPFROM2SHORT( cxClient, cyClient ) );
        WinInvalidateRect( hWndDoc, NULL, FALSE );
    }
}


// handles vertical scrolling
MRESULT DocumentViewer::vertScroll( HWND hwnd, MPARAM mp2, HRGN hrgn )
{
    sVscrollInc = 0;

    switch ( SHORT2FROMMP( mp2 ) )
    {
        case SB_LINEUP:
            sVscrollInc = -LINE_HEIGHT;
            break ;
        case SB_LINEDOWN:
            sVscrollInc = LINE_HEIGHT;
            break;
        case SB_PAGEUP:
            sVscrollInc = __min( -1, -( cyClient - LINE_HEIGHT ) );
            break;
        case SB_PAGEDOWN:
            sVscrollInc = __max( 1, cyClient + LINE_HEIGHT );
            break;
        case SB_SLIDERTRACK:
        case SB_SLIDERPOSITION:
            sVscrollInc = ( SHORT1FROMMP( mp2 ) - sVscrollPos ) *
                                    ( continuous ? VScrollStep : 1 );
            break;
    }

    if ( continuous ) {
        sVscrollInc = __max( -sVscrollPos * VScrollStep, __min( sVscrollInc,
                                  ( sVscrollMax - sVscrollPos ) * VScrollStep ) );
    } else {
        sVscrollInc = __max( -sVscrollPos, __min( sVscrollInc, sVscrollMax - sVscrollPos ) );
    }

    if ( sVscrollInc != 0 )
    {
        sVscrollPos += (SHORT)( continuous ? ( sVscrollInc / VScrollStep ) : sVscrollInc );
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
    cxClient = SHORT1FROMMP( mp2 );
    cyClient = SHORT2FROMMP( mp2 );

    adjustSize();

    if ( ( hpsBuffer != NULLHANDLE ) && ( hdcBuffer != NULLHANDLE ) ) {
        DestroyGraphicsBuffer( hpsBuffer, hdcBuffer );
        hpsBuffer = hdcBuffer = NULLHANDLE;
    }

    HPS hps = WinGetPS( hwnd );
    RECTL rectl = { 0, 0, cxClient, cyClient };
    CreateGraphicsBuffer( hab, &rectl, hps, &hpsBuffer, &hdcBuffer );
    WinReleasePS( hps );

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
    DocumentViewer *d = (DocumentViewer *)data;
    HPS hps = WinGetPS( d->hWndDoc );
    if ( hps != NULLHANDLE )
    {
        LONG rclx = d->drawRect.xRight - d->drawRect.xLeft;
        LONG rcly = d->drawRect.yTop - d->drawRect.yBottom;

        POINTL aptlPoints[4]={ d->drawRect.xLeft, d->drawRect.yBottom,
                               d->drawRect.xRight-1, d->drawRect.yTop-1,
                               0, 0, rclx, rcly };

        LONG lRop = ROP_SRCCOPY;
        BITMAPINFO2 pbmi;
        pbmi.cbFix = 16L;
        pbmi.cx = rclx;
        pbmi.cy = rcly;
        pbmi.cPlanes = 1;
        pbmi.cBitCount = 24;
        GpiDrawBits( hps, d->pixbuf->getDataPtr( d->ev ), &pbmi, 4L,
                     aptlPoints, lRop, BBO_IGNORE );

        WinReleasePS( hps );
    }
    return 0;
}

// static method, thread for asynchronous rendering
void DocumentViewer::drawthread( void *p )
{
    DosSetPriority( PRTYS_THREAD, PRTYC_REGULAR, PRTYD_MINIMUM, 0 );
    DocumentViewer *d = (DocumentViewer *)p;

    HAB thab = WinInitialize( 0 );
    HMQ thmq = WinCreateMsgQueue( thab, 0 );

    ULONG postCnt;
    while ( !d->termdraw )
    {
        DosWaitEventSem( d->haveDraw, SEM_INDEFINITE_WAIT );
        DosResetEventSem( d->haveDraw, &postCnt );
        d->abortAsynch = false;

        if ( !WinIsRectEmpty( thab, &d->drawRect) )
        {
            if ( d->doc != NULL )
            {
                DosRequestMutexSem( d->todrawAccess, SEM_INDEFINITE_WAIT );
                LONG rclx = d->drawRect.xRight - d->drawRect.xLeft;
                LONG rcly = d->drawRect.yTop - d->drawRect.yBottom;
                d->pixbuf = new LuPixbuf( d->ev, rclx, rcly );
                d->doc->renderPageToPixbufAsynch( d->ev, d->currentpage,
                           d->spos_x, d->spos_y, rclx, rcly, d->realzoom, 0, d->pixbuf,
                           asynchCallbackFnDraw, asynchCallbackFnAbort, p );
                if ( !d->abortAsynch )
                {
                    HPS hps = WinGetPS( d->hWndDoc );
                    if ( hps != NULLHANDLE ) {
                        d->drawSelection( hps, &d->drawRect );
                        d->drawFound( hps, &d->drawRect );
                        WinReleasePS( hps );
                    }
                    WinSetRectEmpty( thab, &d->drawRect );
                }
                delete d->pixbuf;
                d->pixbuf = NULL;
                DosReleaseMutexSem( d->todrawAccess );
            }
        }
    }

    WinDestroyMsgQueue( thmq );
    WinTerminate( thab );
    _endthread();
}

// handles WM_PAINT if document supports asynch rendering.
// posts events to drawthread
void DocumentViewer::wmPaintAsynch( HWND hwnd )
{
    RECTL rcl;
    HPS hps = WinBeginPaint( hwnd, 0L, &rcl );
    if ( hps != NULLHANDLE )
    {
        RECTL rclWin = { 0 };
        WinQueryWindowRect( hwnd, &rclWin );
        if ( WinEqualRect( hab, &rcl, &rclWin ) ) {
            GpiErase( hps );
        }
        WinEndPaint( hps );
    }

    RECTL rclPage = { 0, 0, width, height };
    if ( height < cyClient )
    {
        rclPage.yBottom = cyClient - height;
        rclPage.yTop = cyClient;
    }
    RECTL rclDraw = { 0, 0, 0, 0 };
    if ( WinIntersectRect( hab, &rclDraw, &rcl, &rclPage ) )
    {
        if ( isSubrect( &drawRect, &rclDraw ) &&
             ( sVscrollInc == 0 ) && ( sHscrollInc == 0 ) ) {
            return;
        }

        abortAsynch = true;
        DosRequestMutexSem( todrawAccess, SEM_INDEFINITE_WAIT );
        if ( !WinIsRectEmpty( hab, &drawRect ) )
        {
            if ( sVscrollInc > 0 ) {
                drawRect.yTop    += sVscrollInc;
            } else if ( sVscrollInc < 0 ) {
                drawRect.yBottom += sVscrollInc;
            }
            if ( sHscrollInc > 0 ) {
                drawRect.xLeft  -= sHscrollInc;
            } else if ( sHscrollInc < 0 ) {
                drawRect.xRight -= sHscrollInc;
            }
        }
        WinUnionRect( hab, &drawRect, &drawRect, &rclDraw );
        spos_x = sHscrollPos + drawRect.xLeft;
        spos_y = (cyClient - drawRect.yTop) + sVscrollPos;

        // workaround ?
        drawRect.xRight++;
        drawRect.yTop++;

        DosReleaseMutexSem( todrawAccess );
        DosPostEventSem( haveDraw );
    }
}


// handles WM_PAINT if single-page synchronous rendering used
void DocumentViewer::wmPaint( HWND hwnd )
{
    RECTL rcl;
    HPS hps = WinBeginPaint( hwnd, 0L, &rcl );
    GpiErase( hpsBuffer );

    RECTL rclPage = { 0, 0, width, height };
    if ( height < cyClient )
    {
        rclPage.yBottom = cyClient - height;
        rclPage.yTop = cyClient;
    }
    RECTL rclDraw = { 0, 0, 0, 0 };
    if ( WinIntersectRect( hab, &rclDraw, &rcl, &rclPage ) )
    {
        spos_x = sHscrollPos + rclDraw.xLeft;
        spos_y = (cyClient - rclDraw.yTop) + sVscrollPos;
        LONG rclx = rclDraw.xRight - rclDraw.xLeft;
        LONG rcly = rclDraw.yTop - rclDraw.yBottom;

        pixbuf = new LuPixbuf( ev, rclx, rcly );
        POINTL aptlPoints[4]={ rclDraw.xLeft, rclDraw.yBottom,
                               rclDraw.xRight-1, rclDraw.yTop-1,
                               0, 0, rclx, rcly };

        doc->renderPageToPixbuf( ev, currentpage, spos_x, spos_y,
                                 rclx, rcly, realzoom, 0, pixbuf );
        LONG lRop = ROP_SRCCOPY;
        BITMAPINFO2 pbmi;
        pbmi.cbFix = 16L;
        pbmi.cx = rclx;
        pbmi.cy = rcly;
        pbmi.cPlanes = 1;
        pbmi.cBitCount = 24;
        GpiDrawBits( hpsBuffer, pixbuf->getDataPtr( ev ), &pbmi, 4L,
                     aptlPoints, lRop, BBO_IGNORE );

        drawSelection( hpsBuffer, &rclDraw );
        drawFound( hpsBuffer, &rclDraw );

        BlitGraphicsBuffer( hps, hpsBuffer, &rcl );
        delete pixbuf;
        pixbuf = NULL;
    }

    WinEndPaint( hps );
}


// founds number of page at specified vertical position
long DocumentViewer::posToPagenum( double yPos, double *pageRest )
{
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

// founds pages and it's areas to draw
DrawAreas *DocumentViewer::foundDrawAreas( PRECTL r )
{
    DrawAreas *areas = new DrawAreas;
    if ( doc != NULL )
    {
        long foundpage = -1;
        double docPos, pageRest;
        for ( LONG i = r->yTop; i >= r->yBottom; i-- )
        {
            pageRest = 0;
            docPos = ( cyClient - i ) + ( sVscrollPos * VScrollStep );
            long pg = posToPagenum( docPos, &pageRest );
            if ( pg != foundpage )
            {
                PageDrawArea pda;
                pda.pagenum = pg;
                pda.drawrect.xLeft   = r->xLeft;
                pda.drawrect.yBottom = __max( i - pageRest, r->yBottom );
                pda.drawrect.xRight  = r->xRight;
                pda.drawrect.yTop    = i;

                pda.startpos.x = 0;
                pda.startpos.y = ( pagesizes[ pg ].y * realzoom ) - pageRest;

                areas->push_back( pda );
                foundpage = pg;
                i -= pageRest;
                //somPrintf( "PGSIZE: %f, (yBottom: %d, yTop: %d)  PG: %d/%f  STPOS: %f\n",
                //  pagesizes[ pg ].y, pda.drawrect.yBottom, pda.drawrect.yTop,
                //         pg, pageRest, pda.startpos.y );
            }
        }
    }

    return areas;
}


// found current page in continuous view mode.
// it's a page which occupes a most larger area in the window.
void DocumentViewer::foundCurrentPage()
{
    RECTL rcl = { 0 };
    WinQueryWindowRect( hWndDoc, &rcl );
    DrawAreas *areas = foundDrawAreas( &rcl );
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
    GpiErase( hpsBuffer );

    delete drawareas;
    drawareas = foundDrawAreas( &rcl );

    for ( int i = 0; i < drawareas->size(); i++ )
    {
        PageDrawArea *pda = &(*drawareas)[ i ];

        RECTL rclDraw = { __min( pagesizes[ pda->pagenum ].x * realzoom,
                                 pda->drawrect.xLeft ),
                          pda->drawrect.yBottom,
                          __min( pagesizes[ pda->pagenum ].x * realzoom,
                                 pda->drawrect.xRight ),
                          pda->drawrect.yTop };

        spos_x = sHscrollPos + rclDraw.xLeft;
        //spos_y = ( cyClient - rclDraw.yTop ) + ( sVscrollPos * VScrollStep );
        spos_y = pda->startpos.y;
        LONG rclx = rclDraw.xRight - rclDraw.xLeft;
        LONG rcly = rclDraw.yTop - rclDraw.yBottom;

        pixbuf = new LuPixbuf( ev, rclx, rcly );
        POINTL aptlPoints[4]={ rclDraw.xLeft, rclDraw.yBottom,
                               rclDraw.xRight-1, rclDraw.yTop-1,
                               0, 0, rclx, rcly };

        doc->renderPageToPixbuf( ev, pda->pagenum, spos_x, spos_y,
                                 rclx, rcly, realzoom, 0, pixbuf );
        LONG lRop = ROP_SRCCOPY;
        BITMAPINFO2 pbmi;
        pbmi.cbFix = 16L;
        pbmi.cx = rclx;
        pbmi.cy = rcly;
        pbmi.cPlanes = 1;
        pbmi.cBitCount = 24;
        GpiDrawBits( hpsBuffer, pixbuf->getDataPtr( ev ), &pbmi, 4L,
                     aptlPoints, lRop, BBO_IGNORE );

        //drawSelection( hpsBuffer, &rclDraw );
        //drawFound( hpsBuffer, &rclDraw );

        delete pixbuf;
        pixbuf = NULL;
    }
    delete drawareas;
    drawareas = NULL;
    BlitGraphicsBuffer( hps, hpsBuffer, &rcl );
    WinEndPaint( hps );

    foundCurrentPage();
}


// converts window position to document position
void DocumentViewer::winPosToDocPos( PPOINTL startpoint, PPOINTL endpoint, LuRectangle *r )
{
    r->x1 = ( startpoint->x + sHscrollPos ) / realzoom;
    r->y1 = ( ( cyClient - startpoint->y ) + sVscrollPos ) / realzoom;
    r->x2 = ( endpoint->x + sHscrollPos ) / realzoom;
    r->y2 = ( ( cyClient - endpoint->y ) + sVscrollPos ) / realzoom;
}

// converts document position to window position
void DocumentViewer::docPosToWinPos( LuRectangle *r, PRECTL rcl )
{
    rcl->xLeft   = ( r->x1 * realzoom ) - sHscrollPos;
    rcl->yBottom = cyClient - ( r->y2 * realzoom ) + sVscrollPos;
    rcl->xRight  = ( r->x2 * realzoom ) - sHscrollPos;
    rcl->yTop    = cyClient - ( r->y1 * realzoom ) + sVscrollPos;
}

// creates region from sequence of rectangles
HRGN DocumentViewer::rectsToRegion( HPS hps, LuDocument_LuRectSequence *rects, bool useScale )
{
    HRGN hrgn = GpiCreateRegion( hps, 0, NULL );
    if ( rects != NULL )
    {
        RECTL r = {0};
        for ( int i = 0; i < rects->_length; i++ )
        {
            if ( useScale ) {
                docPosToWinPos( &(rects->_buffer[i]), &r );
            }
            else
            {
                r.xLeft = rects->_buffer[i].x1 - sHscrollPos;
                r.yBottom = cyClient - rects->_buffer[i].y2 + sVscrollPos;
                r.xRight = rects->_buffer[i].x2 - sHscrollPos;
                r.yTop = cyClient - rects->_buffer[i].y1 + sVscrollPos;
            }
            HRGN tmprgn = GpiCreateRegion( hps, 1, &r );
            GpiCombineRegion( hps, hrgn, hrgn, tmprgn, CRGN_OR );
            GpiDestroyRegion( hps, tmprgn );
        }
    }
    return hrgn;
}

// draws selected area in window, using XOR mix
// drawing area may be restricted by r rectangle
void DocumentViewer::drawSelection( HPS hps, PRECTL r )
{
    GpiSetMix( hps, FM_XOR );
    GpiSetColor( hps, CLR_YELLOW );
    HRGN selectRegion = rectsToRegion( hps, selrects, false );
    if ( r != NULL )
    {
        HRGN tmprgn = GpiCreateRegion( hps, 1, r );
        GpiCombineRegion( hps, selectRegion, selectRegion, tmprgn, CRGN_AND );
        GpiDestroyRegion( hps, tmprgn );
    }
    GpiPaintRegion( hps, selectRegion );
    GpiDestroyRegion( hps, selectRegion );
}

void DocumentViewer::drawFound( HPS hps, PRECTL r )
{
    GpiSetMix( hps, FM_XOR );
    GpiSetColor( hps, CLR_CYAN );
    HRGN selectRegion = rectsToRegion( hps, foundrects[ currentpage ], true );
    if ( r != NULL )
    {
        HRGN tmprgn = GpiCreateRegion( hps, 1, r );
        GpiCombineRegion( hps, selectRegion, selectRegion, tmprgn, CRGN_AND );
        GpiDestroyRegion( hps, tmprgn );
    }
    GpiPaintRegion( hps, selectRegion );
    GpiDestroyRegion( hps, selectRegion );
}

// scrolls window during text selection
void DocumentViewer::scrollToPos( HWND hwnd, HRGN hrgn, SHORT xpos, SHORT ypos,
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
        yinc = __min( sVscrollMax - sVscrollPos, ypos * -1 );
    }
    else if ( ( ypos > cyClient ) && ( sVscrollPos > 0 ) ) {
        yinc = __max( sVscrollPos * -1, cyClient - ypos );
    }

    if ( xinc != 0 ) {
        horizScroll( hwnd, MPFROM2SHORT( sHscrollPos + xinc, SB_SLIDERPOSITION ), hrgn );
        if ( withSelection ) {
            selectionStart.x -= xinc;
        }
    }
    if ( yinc != 0 ) {
        vertScroll( hwnd, MPFROM2SHORT( sVscrollPos + yinc, SB_SLIDERPOSITION ), hrgn );
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

        winPosToDocPos( &selectionStart, &selectionEnd, &selection );

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

        HRGN clearRegion = rectsToRegion( hps, selrects, false );
        LuDocument::freeRectangles( ev, selrects );
        if ( ( selectionStart.x == selectionEnd.x ) &&
             ( selectionStart.y == selectionEnd.y ) ) {
            selrects = NULL;
        }
        else {
            selrects = doc->getSelectionRectangles( ev, currentpage, realzoom, &selection );
        }
        HRGN selectRegion = rectsToRegion( hps, selrects, false );
        GpiCombineRegion( hps, selectRegion, selectRegion, clearRegion, CRGN_XOR );
        //GpiCombineRegion( hps, selectRegion, selectRegion, scrolledRegion, CRGN_DIFF );
        GpiPaintRegion( hps, selectRegion );
        GpiDestroyRegion( hps, clearRegion );
        GpiDestroyRegion( hps, selectRegion );
        //GpiDestroyRegion( hps, scrolledRegion );

        WinReleasePS( hps );
    }
    else if ( links != NULL )
    {
        for ( int i = 0; i < links->_length; i++ )
        {
            RECTL r = {0};
            docPosToWinPos( &(links->_buffer[i].area), &r );

            POINTL ptl = { xpos, ypos };
            if ( WinPtInRect( hab, &r, &ptl ) ) {
                WinSetPointer( HWND_DESKTOP, handptr );
                return TRUE;
            }
        }
    }

    return FALSE;
}

// handles WM_BUTTON1CLICK
BOOL DocumentViewer::wmClick( HWND hwnd, SHORT xpos, SHORT ypos )
{
    if ( links != NULL )
    {
        for ( int i = 0; i < links->_length; i++ )
        {
            RECTL r = {0};
            docPosToWinPos( &(links->_buffer[i].area), &r );

            POINTL ptl = { xpos, ypos };
            if ( WinPtInRect( hab, &r, &ptl ) )
            {
                if ( links->_buffer[i].link.type == LU_LINK_TYPE_EXTERNAL_URI )
                {
                    WinMessageBox( HWND_DESKTOP, hMainFrame,
                        links->_buffer[i].link.uri, "URI", 1,
                        MB_OK | MB_INFORMATION | MB_MOVEABLE );
                }
                else if ( links->_buffer[i].link.type == LU_LINK_TYPE_TITLE )
                {
                    char *title = links->_buffer[i].link.title;
                    if ( title == NULL ) {
                        title = "???";
                    }
                    WinMessageBox( HWND_DESKTOP, hMainFrame,
                        title, "?", 1, MB_OK | MB_INFORMATION | MB_MOVEABLE );
                }
                else if ( links->_buffer[i].link.type == LU_LINK_TYPE_PAGE )
                {
                    goToPage( links->_buffer[i].link.page );
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
                WinSendMsg( hwnd, WM_VSCROLL, MPVOID, MPFROM2SHORT( 0, SB_PAGEUP ) );
                return TRUE;

            case VK_PAGEDOWN:
                WinSendMsg( hwnd, WM_VSCROLL, MPVOID, MPFROM2SHORT( 0, SB_PAGEDOWN ) );
                return TRUE;

            case VK_LEFT:
                WinSendMsg( hwnd, WM_HSCROLL, MPVOID, MPFROM2SHORT( 0, SB_LINELEFT ) );
                return TRUE;

            case VK_RIGHT:
                WinSendMsg( hwnd, WM_HSCROLL, MPVOID, MPFROM2SHORT( 0, SB_LINERIGHT ) );
                return TRUE;
        }
    }

    return FALSE;
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
                _this->wmPaintAsynch( hwnd );
            } else {
                if ( _this->continuous ) {
                    _this->wmPaintCont( hwnd );
                } else {
                    _this->wmPaint( hwnd );
                }
            }
            return (MRESULT)FALSE;

        case WM_BUTTON1DOWN:
            {
                WinSetCapture( HWND_DESKTOP, hwnd );
                _this->mousePressed = true;
                _this->selectionStart.x = SHORT1FROMMP( mp1 );
                _this->selectionStart.y = SHORT2FROMMP( mp1 );
            }
            break;

        case WM_BUTTON1UP:
            {
                WinSetCapture( HWND_DESKTOP, NULLHANDLE );
                _this->mousePressed = false;
                Lucide::enableCopy( _this->selrects != NULL );
            }
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

