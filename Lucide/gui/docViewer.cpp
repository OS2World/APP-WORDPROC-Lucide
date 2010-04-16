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
#include <algorithm>
#include <process.h>
#include <stdio.h>
#include <ctype.h>

#include <ludoc.xh>
#include <luibutton.xh>
#include <luitext.xh>
#include "lucide.h"
#include "docViewer.h"
#include "progressDlg.h"
#include "pluginman.h"
#include "luutils.h"
#include "lucide_res.h"
#include "messages.h"
#include "cpconv.h"


// ASYNCH_RENDER_ENABLE, normally must be defined
#define ASYNCH_RENDER_ENABLE

typedef LuDocument_LuRectSequence    *PLuRectSequence;
typedef LuDocument_LuLinkMapSequence *PLuLinkMapSequence;

#define LINE_HEIGHT     16
#define BORDER_COLOR    0x909090L
#define PAGEBACK_COLOR  0xFFFFFFL
#define VERT_SPACE      2
#define NO_MOUSE_TIMER  1
#define NO_MOUSE_TIME   3000 // ms
#define SB_PAGEDRAG     100

#define DOC_ID_ENTRY    0
#define DOC_ID_MLE      1

void PageInputFields::fillCache( int i )
{
    LuInputField *field = fields->_buffer[ i ];
    Cache &entry = cache[ i ];
    entry.rect = field->getRectangle( ev );
    entry.type = field->getType( ev );
    entry.supported = false;
    entry.modified = false;

    switch( entry.type ) {
        case LuInputField_Button: {
            LuInputButton *button = static_cast<LuInputButton *>( field );
            if ( button->getButtonType( ev ) != LuInputButton_Check )
                break;
            // so far, only check boxes are supported
            entry.supported = true;
            break;
        }
        case LuInputField_Text: {
            LuInputText *text = static_cast<LuInputText *>( field );
            if ( text->isReadOnly( ev ) )
                break;
            entry.supported = true;
            break;
        }
        case LuInputField_Choice:
        case LuInputField_Signature:
        default:
            // these are currently not supported
            break;
    }
}

// DocumentViewer constructor
DocumentViewer::DocumentViewer( HWND hWndFrame )
{
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
    hWndEntry   = NULLHANDLE;
    hWndMLE     = NULLHANDLE;
    textField   = NULL;
    textFieldPage = 0;
    textFieldIndex = 0;
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
    zoomMode    = false;
    rotation    = 0;
    pixbuf      = NULL;
    spos_x      = 0;
    spos_y      = 0;
    progressDlg = new ProgressDlg( hWndFrame );
    drawareas   = NULL;
    drawareaIndex = 0;
    closed        = true;
    layout        = SinglePage;
    // continuous view
    pagesizes   = NULL;
    realVscrollMax = 0;
    VScrollStep = 1;
    WinSetRectEmpty( hab, &savedRcl );
    drawPS = false;
    // mouse drag using right button
    docDraggingStarted = false;
    docDraggingStart.x = 0;  docDraggingStart.y = 0;
    docDraggingEnd.x = 0;  docDraggingEnd.y = 0;
    // fullscreen
    fullscreen     = false;
    mouseHidden    = false;
    inFocus        = false;
    xLastPos       = 0;
    yLastPos       = 0;
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
    handPtr = WinLoadPointer( HWND_DESKTOP, _hmod, IDP_HAND );
    handClosedPtr = WinLoadPointer( HWND_DESKTOP, _hmod, IDP_HAND_CLOSED );
    zoomInPtr = WinLoadPointer( HWND_DESKTOP, _hmod, IDP_ZOOM_IN );
    zoomOutPtr = WinLoadPointer( HWND_DESKTOP, _hmod, IDP_ZOOM_OUT );
    textPtr = WinQuerySysPointer( HWND_DESKTOP, SPTR_TEXT, FALSE );
    // input fields
    inputFields = NULL;
    // search
    foundrects = NULL;
    searchString = NULL;
    abortSearch = false;

    // create windows
    ULONG dfFlags = FCF_VERTSCROLL | FCF_HORZSCROLL | FCF_NOBYTEALIGN;
    hWndDocFrame = WinCreateStdWindow( hWndFrame, WS_VISIBLE, &dfFlags, NULL, NULL,
                                       WS_VISIBLE, _hmod, 0, NULL );
    WinSetWindowULong( hWndDocFrame, QWL_USER, (ULONG)this );
    oldFrameProc = WinSubclassWindow( hWndDocFrame, docFrameProc );

    hWndDoc = WinCreateWindow( hWndDocFrame, "er.docview", NULL,
                               WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN,
                               0, 0, 0, 0, hWndDocFrame,
                               HWND_TOP, FID_CLIENT, this, NULL );

    hWndEntry = WinCreateWindow( hWndDoc, WC_ENTRYFIELD, NULL,
                                 ES_AUTOSCROLL | ES_MARGIN,
                                 0, 0, 0, 0, hWndDoc,
                                 HWND_TOP, DOC_ID_ENTRY, NULL, NULL );

    hWndMLE = WinCreateWindow( hWndDoc, WC_MLE, NULL,
                               MLS_BORDER,
                               0, 0, 0, 0, hWndDoc,
                               HWND_TOP, DOC_ID_MLE, NULL, NULL );

    char *mleFont = "10.Helvetica Bold";
    WinSetPresParam( hWndMLE, PP_FONTNAMESIZE, strlen( mleFont ) + 1, mleFont );

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
        freeInputFields();
    }

    WinDestroyPointer( handPtr );
    WinDestroyPointer( handClosedPtr );
    WinDestroyPointer( zoomInPtr );
    WinDestroyPointer( zoomOutPtr );

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
void DocumentViewer::registerClass()
{
    WinRegisterClass( hab, "er.docview", docViewProc, CS_SIZEREDRAW, sizeof( ULONG ) * 2 );
}

// sets the document for viewing
void DocumentViewer::setDocument( LuDocument *_doc )
{
    close( true );
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
        adjustSize();

        selrects = new PLuRectSequence[ totalpages ];
        memset( selrects, 0, sizeof( PLuRectSequence ) * totalpages );

        foundrects = new PLuRectSequence[ totalpages ];
        memset( foundrects, 0, sizeof( PLuRectSequence ) * totalpages );

        if ( doc->isHaveLinks( ev ) ) {
            links = new PLuLinkMapSequence[ totalpages ];
            memset( links, 0, sizeof( PLuLinkMapSequence ) * totalpages );
        }

        if ( doc->isHaveInputFields( ev ) ) {
            inputFields = new PageInputFields[ totalpages ];
            memset( inputFields, 0, sizeof( PageInputFields ) * totalpages );
        }

        selection = new LuRectangle[ totalpages ];
        memset( selection, 0, sizeof( LuRectangle ) * totalpages );

        drawPS = doc->isRenderIntoPS( ev );
        if ( drawPS ) {
            enableAsynchDraw = false;
        }
        else {
#ifdef ASYNCH_RENDER_ENABLE
            enableAsynchDraw = doc->isAsynchRenderingSupported( ev );
#else
            enableAsynchDraw = false;
#endif
        }
        goToPage( 0 );
    }
}

void DocumentViewer::countPagesizes()
{
    for ( long i = 0; i < totalpages; i++ )
    {
        doc->getPageSize( ev, i, &pagesizes[i].x, &pagesizes[i].y );
        if ( isRotated() ) {
            double tmp = pagesizes[i].x;
            pagesizes[i].x = pagesizes[i].y;
            pagesizes[i].y = tmp;
        }
        fullwidth = std::max( fullwidth, pagesizes[i].x );
        fullheight += ( pagesizes[i].y + VERT_SPACE );
    }
}

// closes the document
bool DocumentViewer::close( bool force )
{
    if ( closed ) {
        return true;
    }

    if ( !force ) {
        // check if the document was modified
        bool modified = false;
        if ( inputFields != NULL ) {
            for ( long pg = 0; pg < totalpages; ++pg ) {
                if ( inputFields[ pg ].fields == NULL )
                    continue;
                for ( unsigned long i = 0; i < inputFields[ pg ].fields->_length; ++i ) {
                    if ( inputFields[ pg ].cache[ i ].modified ) {
                        modified = true;
                        break;
                    }
                }
            }
        }

        if ( modified ) {
            // ask for the confirmation to close the modified document
            char *t = newstrdupL( MSGS_WARNING );
            char *m = newstrdupL( MSGS_CLOSE_MODIFIED_DOCUMENT );
            ULONG response = WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, m, t,
                                            0, MB_YESNOCANCEL | MB_WARNING | MB_MOVEABLE );
            delete m;
            delete t;
            if ( response == MBID_CANCEL ) {
                return false;
            }
            if ( response == MBID_YES ) {
                if ( !Lucide::saveDocumentAs() )
                    return false;
            }
        }
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

    freeInputFields();

    doc             = NULL;
    totalpages      = 0;
    currentpage     = 0;
    fullwidth       = 0;
    fullheight      = 0;

    DosReleaseMutexSem( todrawAccess );

    WinInvalidateRect( hWndDocFrame, NULL, TRUE );

    return true;
}

// sets the page layout
void DocumentViewer::setPageLayout( PgLayout _layout )
{
    layout = _layout;
    if ( doc != NULL ) {
        long pg = currentpage;
        drawPage();
        if ( isContinuous() ) {
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

void DocumentViewer::freeInputFields()
{
    if ( inputFields != NULL )
    {
        for ( long i = 0; i < totalpages; i++ ) {
            if ( inputFields[ i ].fields != NULL ) {
                LuDocument::freeInputFields( ev, inputFields[ i ].fields );
                inputFields[ i ].fields = NULL;
            }
            if ( inputFields[ i ].cache != NULL ) {
                delete[] inputFields[ i ].cache;
                inputFields[ i ].cache = NULL;
            }
        }

        delete inputFields;
        inputFields = NULL;
    }
}

// switch view to specified page
void DocumentViewer::goToPage( long page )
{
    if ( ( page < 0 ) || ( page >= totalpages ) ) {
        return;
    }

    if ( isContinuous() && ( doc != NULL ) )
    {
        bool needRedraw = ( page == currentpage );
        double pgpos = pagenumToPos( page ) / VScrollStep;
        vertScroll( hWndDoc, MPFROM2SHORT( pgpos, SB_SLIDERPOSITION ) );
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
    if ( ( _zoom == 0 ) || ( _zoom < -2 ) || ( ( _zoom > 0 ) && ( _zoom < 0.05 ) ) ) {
        return;
    }

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

    // make sure partial repaints from the async thread are discarded while we
    // change the document window's size and position several times below
    WinLockWindowUpdate( HWND_DESKTOP, hWndDocFrame );

    if ( fullscreen )
    {
        pglSave = getPageLayout();
        zoomSave = getZoom();
        setPageLayout( SinglePage );
        setZoom( -2 );
        WinSetParent( hWndHscroll, HWND_OBJECT, FALSE );
        WinSetParent( hWndVscroll, HWND_OBJECT, FALSE );
    }
    else
    {
        setPageLayout( pglSave );
        setZoom( zoomSave );
        WinSetParent( hWndHscroll, hWndDocFrame, FALSE );
        WinSetParent( hWndVscroll, hWndDocFrame, FALSE );
    }

    WinLockWindowUpdate( HWND_DESKTOP, NULLHANDLE );

    WinSendMsg( hWndDocFrame, WM_UPDATEFRAME, MPVOID, MPVOID );

    unhideMouse();
}

void DocumentViewer::unhideMouse()
{
    if ( mouseHidden ) {
        WinShowPointer( HWND_DESKTOP, TRUE );
        mouseHidden = false;
    }

    if ( fullscreen && inFocus ) {
        WinStartTimer( hab, hWndDoc, NO_MOUSE_TIMER, NO_MOUSE_TIME );
    }
}

// copy selected text to clipboard
void DocumentViewer::copyToClipbrd()
{
    if ( isContinuous() )
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
    if ( isContinuous() )
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

        _this->foundrects[ i ] = _this->doc->searchText( ev, i,
                                        (char *)_this->searchString, _this->caseSensitive );
        if ( _this->foundrects[ i ] != NULL )
        {
            found = true;
            _this->progressDlg->hide();
            _this->goToPage( i );
            if ( _this->foundrects[i]->_length > 0 ) {
                RECTL r;
                _this->docPosToWinPos( i, &(_this->foundrects[i]->_buffer[0]), &r );
                _this->scrollToPos( _this->hWndDoc, r.xLeft, r.yBottom, false );
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
            fullwidth = std::max( fullwidth, pagesizes[i].x );
            fullheight += pagesizes[i].y;
        }

        if ( zoom == -1 ) { // fit width
            realzoom = (double)cxClient / ( isContinuous() ? fullwidth : width );
        }
        else if ( zoom == -2 ) { // fit page
            realzoom = std::min( (double)cxClient / width, (double)cyClient / height );
        }
        else {
            realzoom = zoom;
        }
        width *= realzoom;
        height *= realzoom;
        fullwidth *= realzoom;
        fullheight *= realzoom;
        fullheight += ( VERT_SPACE * totalpages );
    }
}

// page redraw
void DocumentViewer::drawPage()
{
    if ( !isContinuous() )
    {
        LuDocument::freeRectangles( ev, selrects[ currentpage ] );
        selrects[ currentpage ] = NULL;

        if ( links != NULL ) {
            if ( links[ currentpage ] == NULL ) {
                links[ currentpage ] = doc->getLinkMapping( ev, currentpage );
            }
        }

        if ( inputFields != NULL ) {
            if ( inputFields[ currentpage ].fields == NULL ) {
                inputFields[ currentpage ].fields = doc->getInputFields( ev, currentpage );
                unsigned long len = inputFields[ currentpage ].fields->_length;
                inputFields[ currentpage ].cache = new PageInputFields::Cache[ len ];
                memset( inputFields[ currentpage ].cache, 0, sizeof( PageInputFields::Cache ) * len );
            }
        }

        Lucide::enableCopy( false );
    }
    WinSendMsg( hWndDoc, WM_SIZE, MPFROM2SHORT( cxClient, cyClient ),
                MPFROM2SHORT( cxClient, cyClient ) );
    WinInvalidateRect( hWndDoc, NULL, FALSE );
}


// handles vertical scrolling
MRESULT DocumentViewer::vertScroll( HWND hwnd, MPARAM mp2 )
{
    sVscrollInc = 0;

    switch ( SHORT2FROMMP( mp2 ) )
    {
        case SB_LINEUP:
            sVscrollInc = -(std::max( LINE_HEIGHT, (int)VScrollStep ));
            break ;
        case SB_LINEDOWN:
            sVscrollInc = std::max( LINE_HEIGHT, (int)VScrollStep );
            break;
        case SB_PAGEUP:
            sVscrollInc = std::min( -1, -( (int)cyClient - LINE_HEIGHT ) );
            break;
        case SB_PAGEDOWN:
            sVscrollInc = std::max( 1, (int)cyClient - LINE_HEIGHT );
            break;
        case SB_SLIDERTRACK:
        case SB_SLIDERPOSITION:
            sVscrollInc = ( SHORT1FROMMP( mp2 ) - sVscrollPos ) * VScrollStep;
            break;
        case SB_PAGEDRAG:
            sVscrollInc = (SHORT)SHORT1FROMMP( mp2 );
            break;
    }

    sVscrollInc =
        std::max( -sVscrollPos * (LONG)VScrollStep,
                  std::min( sVscrollInc,
                            ( sVscrollMax - sVscrollPos ) * (LONG)VScrollStep ) );
    sVscrollInc = ( sVscrollInc / VScrollStep ) * VScrollStep;

    if ( sVscrollInc != 0 )
    {
        sVscrollPos += (SHORT)( sVscrollInc / VScrollStep );
        WinScrollWindow( hwnd, 0, sVscrollInc, NULL, NULL, NULLHANDLE, NULL,
                         SW_INVALIDATERGN | SW_SCROLLCHILDREN );
        WinSendMsg( hWndVscroll, SBM_SETPOS, MPFROMSHORT( sVscrollPos ), MPVOID );
        WinUpdateWindow( hwnd );
        sVscrollInc = 0;
    }
    return ( MRFROMLONG( 0 ) );
}

// handles horizontal scrolling
MRESULT DocumentViewer::horizScroll( HWND hwnd, MPARAM mp2 )
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
            sHscrollInc = std::min( -1, -( (int)cxClient - LINE_HEIGHT ) );
            break;
        case SB_PAGERIGHT:
            sHscrollInc = std::max( 1, (int)cxClient - LINE_HEIGHT );
            break;
        case SB_SLIDERTRACK:
        case SB_SLIDERPOSITION:
            sHscrollInc = SHORT1FROMMP( mp2 ) - sHscrollPos;
            break;
        case SB_PAGEDRAG:
            sHscrollInc = (SHORT)SHORT1FROMMP( mp2 );
            break;
    }

    sHscrollInc =
        std::max( -(LONG)sHscrollPos,
                  std::min( sHscrollInc, (LONG)(sHscrollMax - sHscrollPos) ) );

    if ( sHscrollInc != 0 )
    {
        sHscrollPos += (SHORT)sHscrollInc;
        WinScrollWindow( hwnd, -sHscrollInc, 0, NULL, NULL, NULLHANDLE, NULL,
                         SW_INVALIDATERGN | SW_SCROLLCHILDREN );
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

    sHscrollMax = (SHORT)std::max( 0., ( isContinuous() ? fullwidth : width ) - cxClient );
    sHscrollPos = std::min( sHscrollPos, sHscrollMax );

    WinSendMsg( hWndHscroll, SBM_SETSCROLLBAR,
                MPFROMSHORT(sHscrollPos), MPFROM2SHORT(0, sHscrollMax) );
    WinSendMsg( hWndHscroll, SBM_SETTHUMBSIZE,
                MPFROM2SHORT( cxClient, width ), MPVOID );
    WinEnableWindow( hWndHscroll, (BOOL)( sHscrollMax != 0 ) );

    VScrollStep = 1;
    if ( isContinuous() )
    {
        realVscrollMax = std::max( 0., fullheight - cyClient );
        ULONG ssize = realVscrollMax / VScrollStep;
        while ( ssize > 32000 ) {
            VScrollStep += LINE_HEIGHT;
            ssize = realVscrollMax / VScrollStep;
        }

        sVscrollMax = (SHORT)ssize;
        if ( realVscrollMax > ( sVscrollMax * VScrollStep ) ) {
            sVscrollMax += 1;
        }
    }
    else {
        realVscrollMax = sVscrollMax = (SHORT)std::max( 0., height - cyClient );
    }
    sVscrollPos = std::min( sVscrollPos, sVscrollMax );

    WinSendMsg( hWndVscroll, SBM_SETSCROLLBAR,
                MPFROMSHORT(sVscrollPos), MPFROM2SHORT(0, sVscrollMax) );
    if ( isContinuous() ) {
        WinSendMsg( hWndVscroll, SBM_SETTHUMBSIZE,
                    MPFROM2SHORT( cyClient/VScrollStep, fullheight/VScrollStep ), MPVOID );
    }
    else {
        WinSendMsg( hWndVscroll, SBM_SETTHUMBSIZE,
                    MPFROM2SHORT( cyClient, height ), MPVOID );
    }
    WinEnableWindow( hWndVscroll, (BOOL)( sVscrollMax != 0 ) );

    SHORT realScrollPos = (SHORT)(sVscrollMax * relativeScrollPos);
    vertScroll( hWndDoc, MPFROM2SHORT( realScrollPos, SB_SLIDERPOSITION ) );

    positionTextField();
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
        GpiDrawBits( hps, _this->pixbuf->getDataPtr( ev ), &pbmi, 4L,
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
                long renderErrorCode = LU_RERR_NO_ERROR;
                char *renderError = NULL;

                PageDrawArea *pda = &(*_this->drawareas)[ _this->drawareaIndex ];

                LONG rclx = pda->drawrect.xRight - pda->drawrect.xLeft;
                LONG rcly = pda->drawrect.yTop - pda->drawrect.yBottom;
                _this->pixbuf = new LuPixbuf( ev, rclx, rcly, _this->bpp );
                _this->doc->renderPageToPixbufAsynch( ev, pda->pagenum,
                       pda->startpos.x, pda->startpos.y, rclx, rcly, _this->realzoom,
                       _this->rotation, _this->pixbuf,
                       (LuDocument_asynchCallbackFn)asynchCallbackFnDraw,
                       (LuDocument_asynchCallbackFn)asynchCallbackFnAbort, p,
                       &renderErrorCode, &renderError );
                delete _this->pixbuf;
                _this->pixbuf = NULL;

                if ( renderErrorCode != LU_RERR_NO_ERROR )
                {
                    // TODO: display error/warning (renderErrorCode, renderError)

                    // ...

                    if ( renderError != NULL ) {
                        SOMFree( renderError );
                    }
                }

                if ( _this->abortAsynch ) {
                    break;  // TODO: remove completed areas from drawareas (?)
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
                WinSetRectEmpty( thab, &_this->savedRcl );
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

// handles WM_PAINT if single-page asynchronous rendering used
// posts events to drawthread
void DocumentViewer::wmPaintAsynch( HWND hwnd )
{
    LONG xPos = 0, yPos = 0;
    RECTL rclPage = { 0 };
    RECTL rcl;
    HPS hps = WinBeginPaint( hwnd, 0L, &rcl );
    GpiCreateLogColorTable( hpsBuffer, 0, LCOLF_RGB, 0, 0, NULL );
    WinFillRect( hpsBuffer, &rcl, BORDER_COLOR );
    if ( doc != NULL )
    {
        if ( width < cxClient ) {
            xPos = ( cxClient - width ) / 2;
        }
        if ( height < cyClient ) {
            yPos = ( cyClient - height ) / 2;
        }

        rclPage.xLeft   = xPos;
        rclPage.yBottom = yPos;
        rclPage.xRight  = width + xPos;
        rclPage.yTop    = height + yPos;
        WinFillRect( hpsBuffer, &rclPage, PAGEBACK_COLOR );
    }
    BlitGraphicsBuffer( hps, hpsBuffer, &rcl );
    WinEndPaint( hps );

    if ( doc != NULL )
    {
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

    if ( doc != NULL )
    {
        long foundpage = -1;
        double pageRest;
        for ( LONG i = rcl.yTop; i >= rcl.yBottom; i-- )
        {
            pageRest = 0;
            long pg = posToPagenum( i, &pageRest );
            if ( ( pg != foundpage ) && ( pg != -1 ) )
            {
                RECTL rclPage = { 0 };
                LuRectangle lr = { 0, 0,
                    isRotated() ? (pagesizes[ pg ].y - 1) : (pagesizes[ pg ].x - 1),
                    isRotated() ? (pagesizes[ pg ].x - 1) : (pagesizes[ pg ].y - 1) };
                docPosToWinPos( pg, &lr, &rclPage );
                WinFillRect( hpsBuffer, &rclPage, PAGEBACK_COLOR );
                foundpage = pg;
                i -= pageRest;
            }
        }
    }

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
            if ( links != NULL ) {
                if ( links[ pda->pagenum ] == NULL ) {
                    links[ pda->pagenum ] = doc->getLinkMapping( ev, pda->pagenum );
                }
            }

            // load input fields for page if not loaded before
            if ( inputFields != NULL ) {
                if ( inputFields[ pda->pagenum ].fields == NULL ) {
                    inputFields[ pda->pagenum ].fields = doc->getInputFields( ev, pda->pagenum );
                    unsigned long len = inputFields[ pda->pagenum ].fields->_length;
                    inputFields[ pda->pagenum ].cache = new PageInputFields::Cache[ len ];
                    memset( inputFields[ pda->pagenum ].cache, 0, sizeof( PageInputFields::Cache ) * len );
                }
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
            spos_y = ( height < cyClient ) ? rclPage.yTop - rclDraw.yTop : (cyClient - rclDraw.yTop) + sVscrollPos;
            LONG rclx = rclDraw.xRight - rclDraw.xLeft;
            LONG rcly = rclDraw.yTop - rclDraw.yBottom;

            long renderErrorCode = LU_RERR_NO_ERROR;
            char *renderError = NULL;

            if ( drawPS )
            {
                doc->renderPageToPS( ev, currentpage, spos_x, spos_y, rclx, rcly,
                                     realzoom, rotation, hpsBuffer, &rclDraw,
                                     &renderErrorCode, &renderError );
            }
            else
            {
                pixbuf = new LuPixbuf( ev, rclx, rcly, bpp );
                POINTL aptlPoints[4]={ rclDraw.xLeft, rclDraw.yBottom,
                                       rclDraw.xRight-1, rclDraw.yTop-1,
                                       0, 0, rclx, rcly };

                doc->renderPageToPixbuf( ev, currentpage, spos_x, spos_y,
                                         rclx, rcly, realzoom, rotation, pixbuf,
                                         &renderErrorCode, &renderError );
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

            if ( renderErrorCode != LU_RERR_NO_ERROR )
            {
                // TODO: display error/warning (renderErrorCode, renderError)

                // ...

                if ( renderError != NULL ) {
                    SOMFree( renderError );
                }
            }

            drawSelection( currentpage, hpsBuffer, &rclDraw );
            drawFound( currentpage, hpsBuffer, &rclDraw );
        }
    }
    BlitGraphicsBuffer( hps, hpsBuffer, &rcl );
    WinEndPaint( hps );
}


// founds number of page at specified vertical position
// for continuous view only
long DocumentViewer::posToPagenum( LONG yPosWin, double *pageRest )
{
    double yPos = ( cyClient - yPosWin ) + ( sVscrollPos * VScrollStep );
    double pgstart = 0;
    double pgend = 0;
    for ( long i = 0; i < totalpages; i++ )
    {
        pgend = pgstart + ( pagesizes[ i ].y * realzoom );
        if ( ( yPos >= pgstart ) && ( yPos < pgend ) ) {
            *pageRest = pgend - yPos;
            return i;
        }
        pgstart = ( pgend + VERT_SPACE );
    }
    return -1;
}

// founds vertical position of specified
// for continuous view only
double DocumentViewer::pagenumToPos( long pagenum )
{
    double ypos = 0;
    for ( long i = 0; i < pagenum; i++ ) {
        ypos += pagesizes[ i ].y;
    }
    return ( ( ypos * realzoom ) + ( pagenum * VERT_SPACE ) );
}

void DocumentViewer::showTextField( long page, long index, PRECTL r )
{
    // save the previous changes if any
    if ( textField != NULL )
        hideTextField();

    textField =
        static_cast<LuInputText *>( inputFields[ page ].fields->_buffer[ index ] );
    textFieldPage = page;
    textFieldIndex = index;

    positionTextField( r );

    HWND hwnd;
    if ( textField->isMultiLine( ev ) ) {
        hwnd = hWndMLE;
        WinSendMsg( hwnd, MLM_SETTEXTLIMIT, MPFROMLONG( 65520 ), NULL );
    } else {
        hwnd = hWndEntry;
        // @todo uncomment this once it returns anything useful
        // int maxLen = textField->getMaximumLength( ev );
        WinSendMsg( hwnd, EM_SETTEXTLIMIT, MPFROMLONG( 65520 ), NULL );
    }

    const char *contents = textField->getContents( ev );
    char *str = uniUtf8ToSys( contents, NULL, NULL );
    WinSetWindowText( hwnd, str );
    delete[] str;

    WinShowWindow( hwnd, TRUE );
    WinSetFocus( HWND_DESKTOP, hwnd );
}

void DocumentViewer::positionTextField( PRECTL r )
{
    if ( textField == NULL )
        return;

    RECTL r2;
    if ( r == NULL ) {
        LuRectangle *rect = textField->getRectangle( ev );
        docPosToWinPos( textFieldPage, rect, &r2 );
    } else {
        r2 = *r;
    }

    static LONG ulDpi = 0;
    if ( ulDpi == 0 ) {
        // DPI is constant beteen reboots
        HPS hps = WinGetScreenPS( HWND_DESKTOP );
        DevQueryCaps( GpiQueryDevice( hps ), CAPS_HORIZONTAL_FONT_RES,
                      1, &ulDpi );
        WinReleasePS( hps );
    }

    LONG points = -1;
    HWND hwnd;
    if ( textField->isMultiLine( ev ) ) {
        hwnd = hWndMLE;
        // the font size for multi-line text does not change
    } else {
        hwnd = hWndEntry;
        // reduce the rectangle to compensate for the border
        r2.xLeft += 3;
        r2.yBottom += 3;
        r2.xRight -= 3;
        r2.yTop -= 3;
        // set the font size to match the field height
        points = ( r2.yTop - r2.yBottom ) * 72 / 120 - 2;
        if ( points < 1 )
            points = 1;
    }

    if (points >= 0 ) {
        char font[ 32 ];
        sprintf( font, "%d.Helvetica Bold", points );
        WinSetPresParam( hWndEntry, PP_FONTNAMESIZE, strlen( font ) + 1, font );
    }

    WinSetWindowPos( hwnd, HWND_TOP,
                     r2.xLeft, r2.yBottom,
                     r2.xRight - r2.xLeft,
                     r2.yTop - r2.yBottom,
                     SWP_MOVE | SWP_SIZE | SWP_ZORDER );
}

void DocumentViewer::hideTextField( bool apply, PPOINTL ptl )
{
    if ( textField != NULL ) {
        HWND hwnd = textField->isMultiLine( ev ) ? hWndMLE : hWndEntry;
        SWP swp;
        WinQueryWindowPos( hwnd, &swp );
        RECTL r = { swp.x, swp.y, swp.x + swp.cx, swp.y + swp.cy };
        if ( ptl && WinPtInRect( hab, &r, ptl ) ) {
            // don't hide if the point is inside the field
            return;
        }
        if ( apply ) {
            LONG len = WinQueryWindowTextLength( hwnd );
            char *str = new char [ len + 1 ];
            *str = 0;
            WinQueryWindowText( hwnd, len + 1, str );
            str[ len ] = 0;
            char *contents = uniSysToUtf8( str, NULL, NULL );
            char *oldContents = textField->getContents( ev );
            if ( (oldContents == NULL && contents != NULL) ||
                 (oldContents != NULL && contents == NULL) ||
                 strcmp( textField->getContents( ev ), contents ) ) {
                // only modify the field if it differs
                textField->setContents( ev, contents );
                inputFields[ textFieldPage ].cache[ textFieldIndex ].modified = true;
            }
            delete[] contents;
            delete[] str;
        }
        textField = NULL;
        WinShowWindow( hwnd, FALSE );
        // repaint little bit more (rounding errors)
        r.xLeft -= 1; r.yBottom -= 1;
        r.xRight += 1; r.yTop += 1;
        WinInvalidateRect( hWndDoc, &r, TRUE );
        // remove the focus from the window we hid
        WinSetFocus( HWND_DESKTOP, hWndDoc );
    }
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
            if ( ( pg != foundpage ) && ( pg != -1 ) )
            {
                double w = pagesizes[ pg ].x * realzoom;

                PageDrawArea pda = {0};
                pda.pagenum = pg;

                LONG xPos = 0;
                if ( w < cxClient ) {
                    xPos = ( cxClient - w ) / 2;
                }
                RECTL rclPage = { 0 };
                LuRectangle lr = { 0, 0,
                    isRotated() ? (pagesizes[ pg ].y - 1) : (pagesizes[ pg ].x - 1),
                    isRotated() ? (pagesizes[ pg ].x - 1) : (pagesizes[ pg ].y - 1) };
                docPosToWinPos( pg, &lr, &rclPage );
                if ( WinIntersectRect( hab, &pda.drawrect, r, &rclPage ) )
                {
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
            if ( links != NULL ) {
                if ( links[ pda->pagenum ] == NULL ) {
                    links[ pda->pagenum ] = doc->getLinkMapping( ev, pda->pagenum );
                }
            }

            // load input fields for page if not loaded before
            if ( inputFields != NULL ) {
                if ( inputFields[ pda->pagenum ].fields == NULL ) {
                    inputFields[ pda->pagenum ].fields = doc->getInputFields( ev, pda->pagenum );
                    unsigned long len = inputFields[ pda->pagenum ].fields->_length;
                    inputFields[ pda->pagenum ].cache = new PageInputFields::Cache[ len ];
                    memset( inputFields[ pda->pagenum ].cache, 0, sizeof( PageInputFields::Cache ) * len );
                }
            }

            spos_x = pda->startpos.x;
            spos_y = pda->startpos.y;
            LONG rclx = pda->drawrect.xRight - pda->drawrect.xLeft;
            LONG rcly = pda->drawrect.yTop - pda->drawrect.yBottom;

            long renderErrorCode = LU_RERR_NO_ERROR;
            char *renderError = NULL;

            if ( drawPS )
            {
                doc->renderPageToPS( ev, pda->pagenum, spos_x, spos_y, rclx, rcly,
                                     realzoom, rotation, hpsBuffer, &(pda->drawrect),
                                     &renderErrorCode, &renderError );
            }
            else
            {
                pixbuf = new LuPixbuf( ev, rclx, rcly, bpp );
                POINTL aptlPoints[4]={ pda->drawrect.xLeft, pda->drawrect.yBottom,
                                       pda->drawrect.xRight-1, pda->drawrect.yTop-1,
                                       0, 0, rclx, rcly };
                doc->renderPageToPixbuf( ev, pda->pagenum, spos_x, spos_y,
                                         rclx, rcly, realzoom, rotation, pixbuf,
                                         &renderErrorCode, &renderError );
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

            if ( renderErrorCode != LU_RERR_NO_ERROR )
            {
                // TODO: display error/warning (renderErrorCode, renderError)

                // ...

                if ( renderError != NULL ) {
                    SOMFree( renderError );
                }
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
    double yplus = isContinuous() ? pagenumToPos( pagenum ) : 0;
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
    if ( !isContinuous() )
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
void DocumentViewer::scrollToPos( HWND hwnd, LONG xpos, LONG ypos,
                                  bool withSelection )
{
    SHORT xinc = 0;
    SHORT yinc = 0;

    if ( ( xpos < 0 ) && ( sHscrollPos > 0 ) ) {
        xinc = std::max( (SHORT)( -sHscrollPos ), (SHORT)xpos );
    } else if ( ( xpos > cxClient ) && ( sHscrollPos < sHscrollMax ) ) {
        xinc = std::min( (SHORT)( sHscrollMax - sHscrollPos ), (SHORT)( xpos - cxClient ) );
    }
    if ( ( ypos < 0 ) && ( sVscrollPos < sVscrollMax ) ) {
        yinc = std::min( (SHORT)( ( sVscrollMax - sVscrollPos ) * VScrollStep ), (SHORT)( -ypos ) );
    }
    else if ( ( ypos > cyClient ) && ( sVscrollPos > 0 ) ) {
        yinc = std::max( (SHORT)( ( -sVscrollPos ) * VScrollStep ), (SHORT)( cyClient - ypos ) );
    }

    if ( xinc != 0 ) {
        horizScroll( hwnd, MPFROM2SHORT( sHscrollPos + xinc, SB_SLIDERPOSITION ) );
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
                                        SB_SLIDERPOSITION ) );
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
    if ( ( xpos != xLastPos ) || ( ypos != yLastPos ) ) // only if mouse really moved
    {
        unhideMouse();
    }
    xLastPos = xpos;
    yLastPos = ypos;

    if ( zoomMode )
    {
        HPOINTER ptr = zoomInPtr;
        if ( WinGetPhysKeyState( HWND_DESKTOP, 0x1d ) & 0x8000 ) {
            ptr = zoomOutPtr;
        }
        WinSetPointer( HWND_DESKTOP, ptr );
        return TRUE;
    }
    else
    {
        if ( mousePressed && ( doc != NULL ) )
        {
            selectionEnd.x = xpos;
            selectionEnd.y = ypos;

            if ( isContinuous() )
            {
                scrollToPos( hwnd, xpos, ypos, true );

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

                scrollToPos( hwnd, xpos, ypos, true );

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
                GpiPaintRegion( hps, selectRegion );
                GpiDestroyRegion( hps, clearRegion );
                GpiDestroyRegion( hps, selectRegion );

                WinReleasePS( hps );
            }
        }
        else if ( docDraggingStarted && ( doc != NULL ) )
        {
            WinSetPointer( HWND_DESKTOP, handClosedPtr );
            docDraggingEnd.x = xpos;
            docDraggingEnd.y = ypos;

            SHORT hMove = -( docDraggingEnd.x - docDraggingStart.x );
            if ( abs( hMove ) > 5 )
            {
                horizScroll( hwnd, MPFROM2SHORT( hMove, SB_PAGEDRAG ) );
                docDraggingStart.x = xpos;
            }

            SHORT vMove = docDraggingEnd.y - docDraggingStart.y;
            if ( abs( vMove ) > 5 )
            {
                vertScroll( hwnd, MPFROM2SHORT( vMove, SB_PAGEDRAG ) );
                docDraggingStart.y = ypos;
            }
            return TRUE;
        }
        else if ( links != NULL || inputFields != NULL )
        {
            long pg = currentpage;
            if ( isContinuous() ) {
                double tmp;
                pg = posToPagenum( ypos, &tmp );
            }

            if ( links != NULL )
            {
                if ( ( pg != -1 ) && ( links[ pg ] != NULL ) )
                {
                    for ( int i = 0; i < links[ pg ]->_length; i++ )
                    {
                        RECTL r = {0};
                        docPosToWinPos( pg, &(links[ pg ]->_buffer[i].area), &r );

                        POINTL ptl = { xpos, ypos };
                        if ( WinPtInRect( hab, &r, &ptl ) ) {
                            WinSetPointer( HWND_DESKTOP, handPtr );
                            return TRUE;
                        }
                    }
                }
            }

            if ( inputFields != NULL )
            {
                if ( ( pg != -1 ) && ( inputFields[ pg ].fields != NULL ) )
                {
                    for ( int i = 0; i < inputFields[ pg ].fields->_length; i++ )
                    {
                        PageInputFields::Cache &entry = inputFields[ pg ].cache[ i ];
                        if ( entry.rect == NULL )
                            inputFields[ pg ].fillCache( i );

                        if ( entry.supported ) {
                            RECTL r = {0};
                            docPosToWinPos( pg, entry.rect, &r );

                            POINTL ptl = { xpos, ypos };
                            if ( WinPtInRect( hab, &r, &ptl ) ) {
                                WinSetPointer( HWND_DESKTOP,
                                               entry.type == LuInputField_Text ?
                                               textPtr : handPtr );
                                return TRUE;
                            }
                        }
                    }
                }
            }
        }
    }
    return FALSE;
}

void DocumentViewer::zoomInOut( bool zoomIn )
{
    if ( ( doc != NULL ) && doc->isScalable( ev ) )
    {
        double z = getRealZoom() / 4;
        double zval = 0;
        if ( zoomIn ) {
            zval = getRealZoom() + z;
        } else {
            zval = getRealZoom() - z;
        }
        zval = (long)( zval * 20.0 ) / 20.0;   // Round to 0.05 (5%)
        if ( zval == getRealZoom() ) {
            zval += ( zoomIn ? 0.01 : -0.01 );
        }
        if ( zval > 0.1 ) {
            Lucide::setZoom( zval );
        }
    }
}

void DocumentViewer::resetModifiedState()
{
    if ( inputFields != NULL ) {
        for ( long pg = 0; pg < totalpages; ++pg ) {
            if ( inputFields[ pg ].fields == NULL )
                continue;
            for ( unsigned long i = 0; i < inputFields[ pg ].fields->_length; ++i ) {
                inputFields[ pg ].cache[ i ].modified = false;
            }
        }
    }
}

// handles WM_BUTTON1CLICK
BOOL DocumentViewer::wmClick( HWND hwnd, SHORT xpos, SHORT ypos )
{
    if ( zoomMode )
    {
        zoomInOut( ( WinGetPhysKeyState( HWND_DESKTOP, 0x1d ) & 0x8000 ) == 0 );
        return TRUE;
    }
    else
    {
        if ( links == NULL && inputFields == NULL ) {
            return FALSE;
        }

        long pg = currentpage;
        if ( isContinuous() ) {
            double tmp;
            pg = posToPagenum( ypos, &tmp );
        }

        if ( links != NULL )
        {
            if ( ( pg != -1 ) && ( links[ pg ] != NULL ) )
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
                            if ( !startBrowser( links[ pg ]->_buffer[i].link.uri ) )
                            {
                                char *m = newstrdupL( MSGS_ERROR_STARTING_BROWSER );
                                WinMessageBox( HWND_DESKTOP, hMainFrame, m,
                                           NULL, 0, MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
                                delete m;
                            }
                        }
                        else if ( links[ pg ]->_buffer[i].link.type == LU_LINK_TYPE_EXTERNAL_FILE )
                        {
                            char *uri = links[ pg ]->_buffer[i].link.uri;
                            if ( uri != NULL ) {
                                Lucide::newWindow( uri, true );
                            }
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
        }

        if ( inputFields != NULL )
        {
            if ( ( pg != -1 ) && ( inputFields[ pg ].fields != NULL ) )
            {
                for ( int i = 0; i < inputFields[ pg ].fields->_length; i++ )
                {
                    PageInputFields::Cache &entry = inputFields[ pg ].cache[ i ];
                    if ( entry.rect == NULL )
                        inputFields[ pg ].fillCache( i );

                    if ( entry.supported ) {
                        RECTL r = {0};
                        docPosToWinPos( pg, entry.rect, &r );

                        POINTL ptl = { xpos, ypos };
                        if ( WinPtInRect( hab, &r, &ptl ) )
                        {
                            LuInputField *field = inputFields[ pg ].fields->_buffer[ i ];

                            switch ( entry.type )
                            {
                                case LuInputField_Button:
                                {
                                    LuInputButton *button = static_cast<LuInputButton *>( field );
                                    LuInputButton_ButtonType type = button->getButtonType( ev );
                                    if ( type == LuInputButton_Check || type == LuInputButton_Radio ) {
                                        boolean state = button->getState( ev );
                                        button->setState( ev, !state );
                                        WinInvalidateRect( hwnd, &r, FALSE );
                                        entry.modified = true;
                                    }
                                    break;
                                }
                                case LuInputField_Text:
                                {
                                    showTextField( pg, i, &r );
                                    break;
                                }
                                default:
                                    break;
                            }

                            return TRUE;
                        }
                    }
                }
            }
        }
    }
    return FALSE;
}

// handles WM_BUTTON2CLICK
BOOL DocumentViewer::wmRightClick( HWND hwnd, SHORT xpos, SHORT ypos )
{
    if ( zoomMode )
    {
        zoomInOut( false );
        return TRUE;
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
                        vertScroll( hwnd, MPFROM2SHORT( 0, SB_SLIDERPOSITION ) );
                    }
                }
                else
                {
                    bool dojump = ( !isContinuous() && ( sVscrollPos == 0 )
                                        && ( currentpage > 0 ) );

                    if ( fullscreen || dojump ) {
                        goToPage( currentpage - 1 );
                        if ( dojump ) {
                            vertScroll( hwnd, MPFROM2SHORT( sVscrollMax, SB_SLIDERPOSITION ) );
                        }
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
                        vertScroll( hwnd, MPFROM2SHORT( sVscrollMax, SB_SLIDERPOSITION ) );
                    }
                }
                else
                {
                    bool dojump = ( !isContinuous() && ( sVscrollPos == sVscrollMax ) );

                    if ( fullscreen || dojump ) {
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
                horizScroll( hwnd, MPFROM2SHORT( 0, SB_SLIDERPOSITION ) );
                return TRUE;

            case VK_END:
                horizScroll( hwnd, MPFROM2SHORT( sHscrollMax, SB_SLIDERPOSITION ) );
                return TRUE;

            case VK_ESC:
                if ( textField != NULL ) {
                    hideTextField( false );
                    return TRUE;
                }
                break;

            case VK_ENTER:
            case VK_NEWLINE:
                if ( textField != NULL ) {
                    hideTextField();
                    return TRUE;
                }
                break;
        }
    }

    // Special case for Esc in fullscreen
    if ( fullscreen && !( fsflags & KC_KEYUP ) && ( fsflags & KC_VIRTUALKEY ) && ( usvk == VK_ESC ) ) {
        Lucide::toggleFullscreen();
        return TRUE;
    }

    // Ctrl && zoomMode
    if ( ( fsflags & KC_VIRTUALKEY ) && ( usvk == VK_CTRL ) && zoomMode ) {
        wmMouseMove( hwnd, 0, 0 ); // to switch mouse pointer if in zoomMode
    }

    return FALSE;
}

// handles WM_BUTTON1DOWN
void DocumentViewer::wmButton1Down( HWND hwnd, SHORT xpos, SHORT ypos )
{
    if ( isContinuous() && ( doc != NULL ) )
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

    POINTL ptl = { xpos, ypos };
    hideTextField( true, &ptl );

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


// handles WM_BUTTON2DOWN
void DocumentViewer::wmButton2Down( HWND hwnd, SHORT xpos, SHORT ypos )
{
    if ( doc != NULL )
    {
        WinSetCapture( HWND_DESKTOP, hwnd );
        docDraggingStarted = true;
        docDraggingStart.x = xpos;
        docDraggingStart.y = ypos;
    }
}


// handles WM_BUTTON2UP
void DocumentViewer::wmButton2Up()
{
    if ( docDraggingStarted )
    {
        WinSetCapture( HWND_DESKTOP, NULLHANDLE );
        docDraggingStarted = false;
    }
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

// handles WM_TIMER
void DocumentViewer::wmTimer( USHORT idTimer )
{
    if ( idTimer == NO_MOUSE_TIMER )
    {
        if ( fullscreen && !mouseHidden && inFocus )
        {
            WinShowPointer( HWND_DESKTOP, FALSE );
            mouseHidden = true;
            WinStopTimer( hab, hWndDoc, NO_MOUSE_TIMER );
        }
    }
}

// handles WM_CONTROL
void DocumentViewer::wmControl( USHORT idControl, USHORT notifyCode, HWND hwndControl )
{
    if ( ( idControl == DOC_ID_ENTRY && notifyCode == EN_KILLFOCUS &&
           textField != NULL && !textField->isMultiLine( ev ) ) ||
         ( idControl == DOC_ID_MLE && notifyCode == MLN_KILLFOCUS &&
           textField != NULL && textField->isMultiLine( ev ) ) )
        hideTextField();
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

        case WM_SETFOCUS:
            _this->inFocus = SHORT1FROMMP( mp2 ) == TRUE;
            _this->unhideMouse();
            break;

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
            _this->horizScroll( hwnd, mp2 );
            break;

        case WM_VSCROLL:
            _this->vertScroll( hwnd, mp2 );
            break;

        case WM_PAINT:
            if ( _this->enableAsynchDraw ) {
                if ( _this->isContinuous() ) {
                    _this->wmPaintContAsynch( hwnd );
                } else {
                    _this->wmPaintAsynch( hwnd );
                }
            } else {
                if ( _this->isContinuous() ) {
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

        case WM_BUTTON2DOWN:
            _this->wmButton2Down( hwnd, SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ) );
            break;

        case WM_BUTTON2UP:
            _this->wmButton2Up();
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

        case WM_BUTTON2CLICK:
            if ( _this->wmRightClick( hwnd, SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ) ) ) {
                return (MRESULT)TRUE;
            }
            break;

        case WM_CHAR:
            if ( _this->wmChar( hwnd, mp1, mp2 ) ) {
                return (MRESULT)TRUE;
            }
            break;

        case WM_FOCUSCHANGE:
            if ( SHORT1FROMMP( mp2 ) ) {
                Lucide::activeWindow = AwView;
            }
            break;

        case WM_TIMER:
            _this->wmTimer( SHORT1FROMMP( mp1 ) );
            break;

        case WM_CONTROL:
            _this->wmControl( SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ), HWNDFROMMP( mp2 ) );
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
            // Send WM_SYSCOMMAND messages to the main frame so that the main
            // system menu works when the document frame (which doesn't actually
            // have a system menu) is in focus
            WinSendMsg( _this->hMainFrame, WM_SYSCOMMAND, mp1, mp2 );
            return (MRESULT)FALSE;
    }

    return _this->oldFrameProc( hwnd, msg, mp1, mp2 );
}

