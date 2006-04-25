#define INCL_WIN
#define INCL_DOS
#define INCL_GPI
#include <os2.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "evpixbuf.xh"
#include "evdoc.xh"
#include "tb_spl.h"
#include "evince_res.h"


extern "C" LONG APIENTRY GpiDrawBits(HPS hps, PVOID pBits, PBITMAPINFO2 pbmiInfoTable,
                             LONG lCount, PPOINTL aptlPoints, LONG lRop, ULONG flOptions);

void initClipbrd();
void textToClipbrd( HAB hab, const char *text );

void DestroyGraphicsBuffer( HPS hpsBuffer, HDC hdcBuffer );
void BlitGraphicsBuffer( HPS hps, HPS hpsBuffer, PRECTL prclPaint );
BOOL CreateGraphicsBuffer( HAB hab, PRECTL prectl, HPS hps,
                           HPS *phpsBuffer, HDC *phdcBuffer );

#define ID_CNTR 10001


EvDocument * APIENTRY (*createObject)();
Environment *ev = NULL;
EvDocument *doc = NULL;
EvPixbuf *pixbuf = NULL;

int totalpages = 0;
int currentpage = 0;
int currentzoom = 100;
double coeff = 1.0;
void render_page( bool dontTouchTree = false );
double width, height;

HAB   hab;
HWND  hWndFrame;
HWND  hWndDoc;
HWND  hwndHscroll;
HWND  hwndVscroll;
HWND  hWndTree;
SHORT sHscrollMax = 0;
SHORT sVscrollMax = 0;
SHORT sHscrollPos = 0;
SHORT sVscrollPos = 0;
LONG  cxClient = 0;
LONG  cyClient = 0;
LONG  spos_x = 0;
LONG  spos_y = 0;

HPS hpsBuffer = NULLHANDLE;
HDC hdcBuffer = NULLHANDLE;


bool mousePressed = false;
short mpos_x = 0;
short mpos_y = 0;
EvRectangle r_selection = {0};
EvDocument_EvRectSequence *selrects = NULL;
EvDocument_EvRectSequence *srchrects = NULL;
EvDocument_EvLinkMapSequence *links = NULL;
HPOINTER handptr = NULLHANDLE;

PFNWP pOldSplProc;

static MRESULT EXPENTRY FInfoProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch ( msg )
    {
        case WM_INITDLG:
            {
                char buf[ 200 ];
                EvDocument_EvFontInfoSequence *fonts = doc->getFontInfo( ev );
                if ( fonts != NULL )
                {
                    for ( int i = 0; i < fonts->_length; i++ )
                    {
                        snprintf( buf, sizeof(buf), "%-24s %-16s %s",
                                  fonts->_buffer[i].name,
                                  fonts->_buffer[i].type,
                                  fonts->_buffer[i].embedded );

                        WinSendDlgItemMsg( hwnd, 101, LM_INSERTITEM,
                                           MPFROMSHORT( LIT_END ),
                                           MPFROMP( buf ) );

                    }

                    EvDocument::freeFontInfo( ev, fonts );
                }
            }
            return (MRESULT)FALSE;
    }
    return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}

static MRESULT EXPENTRY DInfoProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch ( msg )
    {
        case WM_INITDLG:
            {
                char *fmt = "%-20s: %s";
                char buf[ 500 ];
                EvDocumentInfo *info = doc->getDocumentInfo( ev );
                if ( info != NULL )
                {
                    if ( info->fields_mask & EV_DOCUMENT_INFO_TITLE ) {
                        snprintf( buf, sizeof(buf), fmt, "Title", info->title );
                        WinSendDlgItemMsg( hwnd, 101, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( buf ) );
                    }
                    if ( info->fields_mask & EV_DOCUMENT_INFO_FORMAT ) {
                        snprintf( buf, sizeof(buf), fmt, "Format", info->format );
                        WinSendDlgItemMsg( hwnd, 101, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( buf ) );
                    }
                    if ( info->fields_mask & EV_DOCUMENT_INFO_AUTHOR ) {
                        snprintf( buf, sizeof(buf), fmt, "Author", info->author );
                        WinSendDlgItemMsg( hwnd, 101, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( buf ) );
                    }
                    if ( info->fields_mask & EV_DOCUMENT_INFO_SUBJECT ) {
                        snprintf( buf, sizeof(buf), fmt, "Subject", info->subject );
                        WinSendDlgItemMsg( hwnd, 101, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( buf ) );
                    }
                    if ( info->fields_mask & EV_DOCUMENT_INFO_KEYWORDS ) {
                        snprintf( buf, sizeof(buf), fmt, "Keywords", info->keywords );
                        WinSendDlgItemMsg( hwnd, 101, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( buf ) );
                    }
                    if ( info->fields_mask & EV_DOCUMENT_INFO_CREATOR ) {
                        snprintf( buf, sizeof(buf), fmt, "Creator", info->creator );
                        WinSendDlgItemMsg( hwnd, 101, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( buf ) );
                    }
                    if ( info->fields_mask & EV_DOCUMENT_INFO_PRODUCER ) {
                        snprintf( buf, sizeof(buf), fmt, "Producer", info->producer );
                        WinSendDlgItemMsg( hwnd, 101, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( buf ) );
                    }
                    if ( info->fields_mask & EV_DOCUMENT_INFO_CREATION_DATE ) {
                        snprintf( buf, sizeof(buf), fmt, "Creation date", ctime( &info->creation_date ) );
                        WinSendDlgItemMsg( hwnd, 101, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( buf ) );
                    }
                    if ( info->fields_mask & EV_DOCUMENT_INFO_MOD_DATE ) {
                        snprintf( buf, sizeof(buf), fmt, "Modified date", ctime( &info->modified_date ) );
                        WinSendDlgItemMsg( hwnd, 101, LM_INSERTITEM, MPFROMSHORT( LIT_END ), MPFROMP( buf ) );
                    }


                    EvDocument::freeDocumentInfo( ev, info );
                }
            }
            return (MRESULT)FALSE;
    }
    return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}

void page_redraw( HWND hwnd )
{
    //sHscrollPos = 0;
    sVscrollPos = 0;
    WinSendMsg( hwnd, WM_SIZE, MPFROM2SHORT( cxClient, cyClient ),
                MPFROM2SHORT( cxClient, cyClient ) );
    WinInvalidateRect( hwnd, NULL, FALSE );
}


struct TreeRecord
{
    MINIRECORDCORE miniRecordCore;
    long page;
};

static MRESULT EXPENTRY splProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch ( msg )
    {
        case WM_CONTROL:
            switch ( SHORT1FROMMP( mp1 ) )
            {
                case ID_CNTR:
                    switch ( SHORT2FROMMP( mp1 ) )
                    {
                        case CN_ENTER:
                            {
                                PNOTIFYRECORDENTER re = (PNOTIFYRECORDENTER)mp2;
                                TreeRecord *tr = (TreeRecord *)re->pRecord;
                                currentpage = tr->page;
                                render_page( true );
                                page_redraw( hWndDoc );
                            }
                            break;
                    }
                    break;
            }
            break;

        case WM_COMMAND:
        {
            switch ( SHORT1FROMMP(mp1) )
            {
                case 91:
                    {
                        FILEDLG fd;
                        memset( &fd, 0, sizeof( fd ) );
                        fd.cbSize = sizeof( fd );
                        fd.fl = FDS_CENTER | FDS_SAVEAS_DIALOG;
                        HWND hd = WinFileDlg( HWND_DESKTOP, hWndFrame, &fd );
                        if ( hd && ( fd.lReturn == DID_OK ) )
                        {
                            if ( !doc->saveAs( ev, fd.szFullFile ) )
                            {
                                WinMessageBox( hWndFrame, hWndFrame,
                                    "Save error", NULL, 1,
                                    MB_OK | MB_ERROR | MB_MOVEABLE );
                            }
                        }
                    }
                    break;

                case 92:
                    {
                        FILEDLG fd;
                        memset( &fd, 0, sizeof( fd ) );
                        fd.cbSize = sizeof( fd );
                        fd.fl = FDS_CENTER | FDS_SAVEAS_DIALOG;
                        HWND hd = WinFileDlg( HWND_DESKTOP, hWndFrame, &fd );
                        if ( hd && ( fd.lReturn == DID_OK ) )
                        {
                            doc->exportToPS( ev, fd.szFullFile, 0, totalpages-1, 576, 792, FALSE );
                        }
                    }
                    break;

                case 93:
                    {
                        //WinDlgBox( HWND_DESKTOP, hWndFrame, DInfoProc,
                        //           NULLHANDLE, ID_DOCINFO, NULL );
                    }
                    break;

                case 94:
                    {
                        //WinDlgBox( HWND_DESKTOP, hWndFrame, FInfoProc,
                        //           NULLHANDLE, ID_FONTINFO, NULL );
                    }
                    break;

                case 101:
                    {
                        if ( currentpage > 0 ) {
                            currentpage--;
                            render_page();
                            page_redraw( hWndDoc );
                        }
                    }
                    break;

                case 102:
                    {
                        if ( currentpage < (totalpages-1) ) {
                            currentpage++;
                            render_page();
                            page_redraw( hWndDoc );
                        }
                    }
                    break;

                case 201:
                    currentzoom = 50;
                    render_page();
                    page_redraw( hWndDoc );
                    break;
                case 202:
                    currentzoom = 100;
                    render_page();
                    page_redraw( hWndDoc );
                    break;
                case 203:
                    currentzoom = 125;
                    render_page();
                    page_redraw( hWndDoc );
                    break;
                case 204:
                    currentzoom = 150;
                    render_page();
                    page_redraw( hWndDoc );
                    break;
                case 205:
                    currentzoom = 200;
                    render_page();
                    page_redraw( hWndDoc );
                    break;
                case 206:
                    currentzoom = 300;
                    render_page();
                    page_redraw( hWndDoc );
                    break;
                case 207:
                    currentzoom = 400;
                    render_page();
                    page_redraw( hWndDoc );
                    break;

                case 103:
                    {
                        char *t = doc->getText( ev, currentpage, &r_selection );
                        textToClipbrd( hab, t );
                    }
                    break;

                case 104:
                    {
                        srchrects = doc->searchText( ev, currentpage, "алхимия кло" );

                        RECTL toRedraw = { 0 };
                        if ( srchrects != NULL )
                        {
                            for ( int i = 0; i < srchrects->_length; i++ )
                            {
                                RECTL r = {0};

                                r.xLeft = srchrects->_buffer[i].x1*coeff - sHscrollPos;
                                r.yBottom = cyClient - srchrects->_buffer[i].y2*coeff + sVscrollPos;
                                r.xRight = srchrects->_buffer[i].x2*coeff - sHscrollPos;
                                r.yTop = cyClient - srchrects->_buffer[i].y1*coeff + sVscrollPos;

                                WinUnionRect( hab, &toRedraw, &toRedraw, &r );
                            }

                            WinInvalidateRect( hWndDoc, &toRedraw, FALSE );
                        }
                    }
                    break;
            }

        }
        return (MRESULT)FALSE;
    }
    return pOldSplProc( hwnd, msg, mp1, mp2 );
}


static MRESULT VertScroll( HWND hwnd, MPARAM mp2 )
{
    LONG sVscrollInc = 0;

    switch ( SHORT2FROMMP( mp2 ) )
    {
        case SB_LINEUP:
            sVscrollInc = -1;
            break ;
        case SB_LINEDOWN:
            sVscrollInc = 1;
            break;
        case SB_PAGEUP:
            sVscrollInc = __min( -1, -cyClient );
            break;
        case SB_PAGEDOWN:
            sVscrollInc = __max( 1, cyClient );
            break;
        case SB_SLIDERTRACK:
            sVscrollInc = SHORT1FROMMP( mp2 ) - sVscrollPos;
            break;
    }

    sVscrollInc = __max( -sVscrollPos, __min( sVscrollInc, sVscrollMax - sVscrollPos ) );

    if ( sVscrollInc != 0 )
    {
        sVscrollPos += (SHORT)sVscrollInc;
        WinScrollWindow( hwnd, 0, sVscrollInc,
                         NULL, NULL, NULLHANDLE, NULL, SW_INVALIDATERGN );
        WinSendMsg( hwndVscroll, SBM_SETPOS, MPFROMSHORT( sVscrollPos ), MPVOID );
        WinUpdateWindow( hwnd );
    }

    //printf( "sVscrollPos: %d\n", sVscrollPos );

    return ( MRFROMLONG( 0 ) );
}

static MRESULT HorizScroll( HWND hwnd, MPARAM mp2 )
{
    LONG sHscrollInc = 0;

    switch ( SHORT2FROMMP( mp2 ) )
    {
        case SB_LINELEFT:
            sHscrollInc = -1;
            break;
        case SB_LINERIGHT:
            sHscrollInc = 1;
            break;
        case SB_PAGELEFT:
            sHscrollInc = __min( -1, -cxClient );
            break;
        case SB_PAGERIGHT:
            sHscrollInc = __max( 1, cxClient );
            break;
        case SB_SLIDERTRACK:
            sHscrollInc = SHORT1FROMMP( mp2 ) - sHscrollPos;
            break;
    }

    sHscrollInc = __max( -sHscrollPos, __min( sHscrollInc, sHscrollMax - sHscrollPos ) );

    if ( sHscrollInc != 0 )
    {
        sHscrollPos += (SHORT)sHscrollInc;
        WinScrollWindow( hwnd, -sHscrollInc, 0, NULL, NULL,
                         NULLHANDLE, NULL, SW_INVALIDATERGN );
        WinSendMsg( hwndHscroll, SBM_SETPOS, MPFROMSHORT( sHscrollPos ), MPVOID );
        WinUpdateWindow( hwnd );
    }
    //printf( "sHscrollPos: %d\n", sHscrollPos );
    return ( MRFROMLONG( 0 ) );
}

void check_menu()
{
    HWND hmenu = WinWindowFromID( hWndFrame, FID_MENU );
    WinEnableMenuItem( hmenu, 91, doc->isSaveable( ev ) );
    WinEnableMenuItem( hmenu, 92, doc->isPSExportable( ev ) );
    WinEnableMenuItem( hmenu, 94, doc->isHaveFontInfo( ev ) );
    WinEnableMenuItem( hmenu, 101, ( currentpage > 0 ) );
    WinEnableMenuItem( hmenu, 102, ( currentpage < (totalpages-1) ) );
    WinEnableMenuItem( hmenu, 200, doc->isScalable( ev ) );
    WinEnableMenuItem( hmenu, 103, ( selrects != NULL ) );
}


static MRESULT EXPENTRY wndProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch ( msg )
    {
        case WM_SIZE:
            {
                cxClient = SHORT1FROMMP( mp2 );
                cyClient = SHORT2FROMMP( mp2 );

                if ( ( hpsBuffer != NULLHANDLE ) && ( hdcBuffer != NULLHANDLE ) ) {
                    DestroyGraphicsBuffer( hpsBuffer, hdcBuffer );
                    hpsBuffer = hdcBuffer = NULLHANDLE;
                }

                HPS hps = WinGetPS( hwnd );
                RECTL rectl = { 0, 0, cxClient, cyClient };
                CreateGraphicsBuffer( hab, &rectl, hps, &hpsBuffer, &hdcBuffer );
                WinReleasePS( hps );

                sHscrollMax = (SHORT)__max( 0, width - cxClient );
                sHscrollPos = __min( sHscrollPos, sHscrollMax );

                WinSendMsg( hwndHscroll, SBM_SETSCROLLBAR,
                            MPFROMSHORT(sHscrollPos), MPFROM2SHORT(0, sHscrollMax) );
                WinSendMsg( hwndHscroll, SBM_SETTHUMBSIZE,
                            MPFROM2SHORT( cxClient, width ), MPVOID );
                WinEnableWindow( hwndHscroll, (BOOL)( sHscrollMax != 0 ) );

                sVscrollMax = (SHORT)__max( 0, height - cyClient );
                sVscrollPos = __min( sVscrollPos, sVscrollMax );

                WinSendMsg( hwndVscroll, SBM_SETSCROLLBAR,
                            MPFROMSHORT(sVscrollPos), MPFROM2SHORT(0, sVscrollMax) );
                WinSendMsg( hwndVscroll, SBM_SETTHUMBSIZE,
                            MPFROM2SHORT( cyClient, height ), MPVOID );
                WinEnableWindow( hwndVscroll, (BOOL)( sVscrollMax != 0 ) );
            }
            return (MRESULT)FALSE;

        case WM_HSCROLL:
            HorizScroll( hwnd, mp2 );
            break;

        case WM_VSCROLL:
            VertScroll( hwnd, mp2 );
            break;

        case WM_ERASEBACKGROUND:
            return (MRESULT)TRUE;

        case WM_PAINT:
            {
                RECTL rcl;
                HPS hps = WinBeginPaint( hwnd, 0L, &rcl );
                //WinQueryWindowRect( hwnd, &rcl );

                GpiErase( hpsBuffer );

                BITMAPINFO2 pbmi;
                pbmi.cbFix = 16L;
                pbmi.cx = pixbuf->getWidth( ev );
                pbmi.cy = pixbuf->getHeight( ev );
                pbmi.cPlanes = 1;
                pbmi.cBitCount = 24;

                RECTL rclPage = { 0, 0, pbmi.cx, pbmi.cy };
                if ( pbmi.cy < cyClient )
                {
                    rclPage.yBottom = cyClient - pbmi.cy;
                    rclPage.yTop = cyClient;
                }
                RECTL rclDraw = { 0, 0, 0, 0 };

                if ( WinIntersectRect( hab, &rclDraw, &rcl, &rclPage ) )
                {

                    spos_x = sHscrollPos + rclDraw.xLeft;
                    spos_y = 0;
                    if ( pbmi.cy > cyClient ) {
                        spos_y = ( (pbmi.cy - cyClient) - sVscrollPos ) + rclDraw.yBottom;
                    } else {
                        spos_y = rclDraw.yBottom - rclPage.yBottom;
                    }

                    LONG rclx = rclDraw.xRight - rclDraw.xLeft;
                    LONG rcly = rclDraw.yTop - rclDraw.yBottom;
                    //printf( "cyClient %d  sVscrollPos %d\n", cyClient, sVscrollPos );
                    //printf( "xLeft %d, yBottom %d, xRight %d, yTop %d, spos_x %d, spos_y %d, spos_x+rclx %d, spos_y+rcly %d\n",
                    //        rclDraw.xLeft, rclDraw.yBottom, rclDraw.xRight, rclDraw.yTop, spos_x, spos_y, spos_x+rclx, spos_y+rcly );

                    POINTL aptlPoints[4]={ rclDraw.xLeft, rclDraw.yBottom,
                                           rclDraw.xRight, rclDraw.yTop,
                                           spos_x, spos_y,
                                           spos_x+rclx+1, spos_y+rcly+1 };

                    LONG lRop = ROP_SRCCOPY;

                    GpiDrawBits( hpsBuffer, pixbuf->getDataPtr( ev ), &pbmi, 4L,
                                 aptlPoints, lRop, BBO_IGNORE );


                    if ( selrects != NULL )
                    {
                        for ( int i = 0; i < selrects->_length; i++ )
                        {
                            RECTL r = {0};

                            r.xLeft = selrects->_buffer[i].x1 - sHscrollPos;
                            r.yBottom = cyClient - selrects->_buffer[i].y2 + sVscrollPos;
                            r.xRight = selrects->_buffer[i].x2 - sHscrollPos;
                            r.yTop = cyClient - selrects->_buffer[i].y1 + sVscrollPos;

                            WinDrawBorder( hpsBuffer, &r, 1, 1, CLR_RED, CLR_GREEN, 0 );
                        }
                    }
                    if ( srchrects != NULL )
                    {
                        for ( int i = 0; i < srchrects->_length; i++ )
                        {
                            RECTL r = {0};

                            r.xLeft = srchrects->_buffer[i].x1*coeff - sHscrollPos;
                            r.yBottom = cyClient - srchrects->_buffer[i].y2*coeff + sVscrollPos;
                            r.xRight = srchrects->_buffer[i].x2*coeff - sHscrollPos;
                            r.yTop = cyClient - srchrects->_buffer[i].y1*coeff + sVscrollPos;

                            WinDrawBorder( hpsBuffer, &r, 1, 1, CLR_DARKGREEN, CLR_GREEN, 0 );
                        }
                    }

                    if ( links != NULL )
                    {
                        for ( int i = 0; i < links->_length; i++ )
                        {
                            RECTL r = {0};

                            r.xLeft = (links->_buffer[i].area.x1*coeff) - sHscrollPos;
                            r.yBottom = cyClient - (links->_buffer[i].area.y2*coeff) + sVscrollPos;
                            r.xRight = (links->_buffer[i].area.x2*coeff) - sHscrollPos;
                            r.yTop = cyClient - (links->_buffer[i].area.y1*coeff) + sVscrollPos;

                            WinDrawBorder( hpsBuffer, &r, 1, 1, CLR_BLUE, CLR_GREEN, 0 );
                        }
                    }

                    if ( ( rcl.xLeft == 0 ) && ( rcl.yBottom == 0 ) &&
                         ( rcl.xRight == cxClient ) && ( rcl.yTop == cyClient ) )
                    {
                        short w = 0, h = 0;
                        if ( doc->getThumbnailSize( ev, currentpage, 76, &w, &h ) )
                        {
                            EvPixbuf *pb = doc->getThumbnail( ev, currentpage, 76 );
                            if ( pb != NULL )
                            {
                                SHORT px = cxClient - ( w + 3 );
                                SHORT py = cyClient - ( h + 3 );

                                RECTL rcl = { px, py, px + w + 3, py + h + 3 };
                                WinDrawBorder( hpsBuffer, &rcl, 1, 1, CLR_RED, CLR_GREEN, 0 );

                                BITMAPINFO2 pbmi;
                                pbmi.cbFix = 16L;
                                pbmi.cx = pb->getWidth( ev );
                                pbmi.cy = pb->getHeight( ev );
                                pbmi.cPlanes = 1;
                                pbmi.cBitCount = 24;

                                POINTL aptlPoints[4]={ px+1, py+1, px+w+2, py+h+2,
                                                       0, 0, w+1, h+1 };
                                GpiDrawBits( hpsBuffer, pb->getDataPtr( ev ), &pbmi, 4L,
                                             aptlPoints, ROP_SRCCOPY, BBO_IGNORE );

                                delete pb;
                            }
                        }
                    }

                    BlitGraphicsBuffer( hps, hpsBuffer, &rcl );
                }

                //WinDrawBorder( hps, &rcl, 1,1, CLR_RED, CLR_GREEN, 0 );


                WinEndPaint( hps );
            }
            break;

        case WM_BUTTON1DOWN:
            {
                mousePressed = true;
                mpos_x = SHORT1FROMMP(mp1);
                mpos_y = SHORT2FROMMP(mp1);
            }
            break;

        case WM_BUTTON1UP:
            {
                mousePressed = false;
                WinEnableMenuItem( WinWindowFromID( hWndFrame, FID_MENU ),
                                   103, ( selrects != NULL ) );
            }
            break;

        case WM_BUTTON1CLICK:
            {
                SHORT xcurpos = SHORT1FROMMP(mp1);
                SHORT ycurpos = SHORT2FROMMP(mp1);

                if ( links != NULL )
                {
                    for ( int i = 0; i < links->_length; i++ )
                    {
                        RECTL r = {0};

                        r.xLeft = (links->_buffer[i].area.x1*coeff) - sHscrollPos;
                        r.yBottom = cyClient - (links->_buffer[i].area.y2*coeff) + sVscrollPos;
                        r.xRight = (links->_buffer[i].area.x2*coeff) - sHscrollPos;
                        r.yTop = cyClient - (links->_buffer[i].area.y1*coeff) + sVscrollPos;

                        POINTL ptl = { xcurpos, ycurpos };
                        if ( WinPtInRect( hab, &r, &ptl ) )
                        {
                            if ( links->_buffer[i].link.type == EV_LINK_TYPE_EXTERNAL_URI )
                            {
                                WinMessageBox( hWndFrame, hWndFrame,
                                    links->_buffer[i].link.uri, "URI", 1,
                                    MB_OK | MB_INFORMATION | MB_MOVEABLE );
                            }
                            else if ( links->_buffer[i].link.type == EV_LINK_TYPE_TITLE )
                            {
                                char *title = links->_buffer[i].link.title;
                                if ( title == NULL ) {
                                    title = "???";
                                }
                                WinMessageBox( hWndFrame, hWndFrame,
                                    title, "?", 1,
                                    MB_OK | MB_INFORMATION | MB_MOVEABLE );
                            }
                            else if ( links->_buffer[i].link.type == EV_LINK_TYPE_PAGE )
                            {
                                currentpage = links->_buffer[i].link.page;
                                render_page();
                                page_redraw( hwnd );
                            }

                            return (MRESULT)FALSE;
                        }
                    }
                }
            }
            break;

        case WM_MOUSEMOVE:
            {
                SHORT xcurpos = SHORT1FROMMP(mp1);
                SHORT ycurpos = SHORT2FROMMP(mp1);

                if ( mousePressed )
                {
                    r_selection.x1 = (mpos_x+sHscrollPos)/coeff;
                    r_selection.y1 = ((cyClient-mpos_y)+sVscrollPos)/coeff;
                    r_selection.x2 = (xcurpos+sHscrollPos)/coeff;
                    r_selection.y2 = ((cyClient-ycurpos)+sVscrollPos)/coeff;

                    RECTL toRedraw = { 0 };

                    if ( selrects != NULL )
                    {
                        for ( int i = 0; i < selrects->_length; i++ )
                        {
                            RECTL r = {0};

                            r.xLeft = selrects->_buffer[i].x1 - sHscrollPos;
                            r.yBottom = cyClient - selrects->_buffer[i].y2 + sVscrollPos;
                            r.xRight = selrects->_buffer[i].x2 - sHscrollPos;
                            r.yTop = cyClient - selrects->_buffer[i].y1 + sVscrollPos;

                            WinUnionRect( hab, &toRedraw, &toRedraw, &r );
                        }
                    }


                    EvDocument::freeRectangles( ev, selrects );
                    selrects = doc->getSelectionRectangles( ev, currentpage, coeff, &r_selection );

                    if ( selrects != NULL )
                    {
                        for ( int i = 0; i < selrects->_length; i++ )
                        {
                            RECTL r = {0};

                            r.xLeft = selrects->_buffer[i].x1 - sHscrollPos;
                            r.yBottom = cyClient - selrects->_buffer[i].y2 + sVscrollPos;
                            r.xRight = selrects->_buffer[i].x2 - sHscrollPos;
                            r.yTop = cyClient - selrects->_buffer[i].y1 + sVscrollPos;

                            WinUnionRect( hab, &toRedraw, &toRedraw, &r );
                        }
                    }

                    WinInvalidateRect( hwnd, &toRedraw, FALSE );
                }
                else
                {
                    if ( links != NULL )
                    {
                        for ( int i = 0; i < links->_length; i++ )
                        {
                            RECTL r = {0};

                            r.xLeft = (links->_buffer[i].area.x1*coeff) - sHscrollPos;
                            r.yBottom = cyClient - (links->_buffer[i].area.y2*coeff) + sVscrollPos;
                            r.xRight = (links->_buffer[i].area.x2*coeff) - sHscrollPos;
                            r.yTop = cyClient - (links->_buffer[i].area.y1*coeff) + sVscrollPos;

                            POINTL ptl = { xcurpos, ycurpos };
                            if ( WinPtInRect( hab, &r, &ptl ) )
                            {
                                WinSetPointer( HWND_DESKTOP, handptr );
                                return (MRESULT)FALSE;
                            }
                        }
                    }
                }
            }
            break;
    }
    return WinDefWindowProc( hwnd, msg, mp1, mp2 );
}

bool loadDll( const char *fn )
{
    char *dllname = "EVDOC";
    char ext[ _MAX_EXT ];
    _splitpath( fn, NULL, NULL, NULL, ext );

    if ( stricmp( ext, ".JPG" ) == 0 ) {
        dllname = "EVJPEG";
    } else if ( stricmp( ext, ".PDF" ) == 0 ) {
        dllname = "EVPPLR";
    } else if ( stricmp( ext, ".DJVU" ) == 0 ) {
        dllname = "EVDJVU";
    }

    HMODULE h = NULLHANDLE;
    if ( DosLoadModule( NULL, 0, dllname, &h ) == 0 ) {
        DosQueryProcAddr( h, 0, "createObject", (PFN *)&createObject );
        return true;
    }

    printf( "Can't load module '%s'\n", dllname );
    return false;
}

bool treeToPage( TreeRecord *parent, long page )
{
    SHORT atr = ( parent == NULL ) ? CMA_FIRST : CMA_FIRSTCHILD;
    TreeRecord *pr = (TreeRecord *)WinSendMsg( hWndTree, CM_QUERYRECORD,
                            MPFROMP( parent ), MPFROM2SHORT( atr, CMA_ITEMORDER ) );
    while ( ( pr != NULL ) && ( (int)pr != -1 ) )
    {
        if ( pr->page == page )
        {
            if ( parent != NULL ) {
                WinSendMsg( hWndTree, CM_EXPANDTREE, MPFROMP( parent ), MPVOID );
            }
            WinSendMsg( hWndTree, CM_SETRECORDEMPHASIS, MPFROMP( pr ),
                        MPFROM2SHORT( TRUE, CRA_SELECTED | CRA_CURSORED ) );
            return true;
        }

        if ( treeToPage( pr, page ) ) {
            return true;
        }

        pr = (TreeRecord *)WinSendMsg( hWndTree, CM_QUERYRECORD,
                            MPFROMP( pr ), MPFROM2SHORT( CMA_NEXT, CMA_ITEMORDER ) );
    }
    return false;
}

void render_page( bool dontTouchTree )
{
    check_menu();
    delete pixbuf;

    EvDocument::freeLinkMapping( ev, links );
    links = doc->getLinkMapping( ev, currentpage );

    EvDocument::freeRectangles( ev, selrects );
    EvDocument::freeRectangles( ev, srchrects );
    selrects = NULL;
    srchrects = NULL;

    doc->getPageSize( ev, currentpage, &width, &height );
    coeff = (double)currentzoom / 100.0;
    width *= coeff;
    height *= coeff;
    //printf( "width: %d   height: %d\n", (int)width, (int)height );
    if ( !dontTouchTree ) {
        treeToPage( NULL, currentpage );
    }
    pixbuf = new EvPixbuf( ev, width, height );
    doc->renderPageToPixbuf( ev, currentpage, 0, 0, width, height, coeff, 0, pixbuf );
}


static char *newstrdup( const char *s )
{
    if ( s == NULL ) {
        return NULL;
    }
    char *temp = new char[ strlen( s ) + 1 ];
    strcpy( temp, s );
    return temp;
}

/*static char *newstrFromUTF8( const char *s )
{
    if ( s == NULL ) {
        return NULL;
    }

    unsigned blen = strlen( s ) + 1;
    char *b = new char[ blen ];
    memset( b, 0, blen );
    char *bsav = b;
    const char *from = s;
    unsigned flen = strlen( s );
    cnvUTF8ToSys( &from, &flen, &b, &blen );
    return bsav;
}*/

/*static void viewTree( int level, EvIndexNode *n )
{
    if ( n == NULL ) {
        return;
    }

    somLPrintf( level, "title: %s\n", n->getLink(ev)->title );

    EvIndexNode *cn = n->getFirstChild( ev );
    while ( cn != NULL )
    {
        viewTree( level+1, cn );
        cn = n->getNextChild( ev );
    }
}  */

void addNodes( HWND hwnd, TreeRecord *parent, EvIndexNode *n )
{
    if ( n == NULL ) {
        return;
    }

    EvLink *link = n->getLink(ev);

    RECORDINSERT ri;
    TreeRecord *pr = (TreeRecord *)WinSendMsg( hwnd, CM_ALLOCRECORD,
       MPFROMLONG( sizeof( TreeRecord ) - sizeof( MINIRECORDCORE ) ), MPFROMSHORT( 1 ) );

    pr->miniRecordCore.cb = sizeof( MINIRECORDCORE );
    pr->miniRecordCore.flRecordAttr = 0;
    pr->miniRecordCore.ptlIcon.x = 0;
    pr->miniRecordCore.ptlIcon.y = 0;
    pr->miniRecordCore.pszIcon = newstrdup( link->title );
    pr->miniRecordCore.hptrIcon = NULLHANDLE;
    pr->page = link->page;

    ri.cb = sizeof( RECORDINSERT );
    ri.pRecordParent = (PRECORDCORE)parent;
    ri.pRecordOrder = (PRECORDCORE)CMA_END;
    ri.zOrder = (USHORT)CMA_TOP;
    ri.cRecordsInsert = 1;
    ri.fInvalidateRecord = TRUE;
    WinSendMsg( hwnd, CM_INSERTRECORD, MPFROMP( pr ), MPFROMP( &ri ) );

    EvIndexNode *cn = n->getFirstChild( ev );
    while ( cn != NULL )
    {
        addNodes( hwnd, pr, cn );
        cn = n->getNextChild( ev );
    }
}

void fill_tree( HWND hwnd )
{
    if ( doc->isHaveIndex( ev ) )
    {
        CNRINFO ci;
        ci.cb = sizeof( CNRINFO );
        WinSendMsg( hwnd, CM_QUERYCNRINFO, MPFROMP( &ci ), MPFROMSHORT( ci.cb ) );
        ci.flWindowAttr &= ~( CV_NAME | CV_FLOW | CV_TEXT | CV_ICON | CV_TREE );
        ci.flWindowAttr |= ( CV_TREE | CV_TEXT | CV_MINI | CA_TREELINE );
        WinSendMsg( hwnd, CM_SETCNRINFO, MPFROMP( &ci ), MPFROMLONG( CMA_FLWINDOWATTR ) );

        EvIndexNode *n = doc->getIndex( ev );
        EvIndexNode *cn = n->getFirstChild( ev );
        while ( cn != NULL )
        {
            addNodes( hwnd, NULL, cn );
            cn = n->getNextChild( ev );
        }
        delete n;
    }
    else
    {
        CNRINFO ci;
        ci.cb = sizeof( CNRINFO );
        WinSendMsg( hwnd, CM_QUERYCNRINFO, MPFROMP( &ci ), MPFROMSHORT( ci.cb ) );
        ci.flWindowAttr &= ~( CV_NAME | CV_FLOW | CV_TEXT | CV_ICON | CV_TREE );
        ci.flWindowAttr |= ( CV_TEXT | CV_MINI );
        WinSendMsg( hwnd, CM_SETCNRINFO, MPFROMP( &ci ), MPFROMLONG( CMA_FLWINDOWATTR ) );

        char pgbuf[ 20 ];
        for ( int i = 0; i < totalpages; i++ )
        {
            snprintf( pgbuf, sizeof(pgbuf), "Page %d", i + 1 );
            RECORDINSERT ri;
            TreeRecord *pr = (TreeRecord *)WinSendMsg( hwnd, CM_ALLOCRECORD,
               MPFROMLONG( sizeof( TreeRecord ) - sizeof( MINIRECORDCORE ) ), MPFROMSHORT( 1 ) );

            pr->miniRecordCore.cb = sizeof( MINIRECORDCORE );
            pr->miniRecordCore.flRecordAttr = 0;
            pr->miniRecordCore.ptlIcon.x = 0;
            pr->miniRecordCore.ptlIcon.y = 0;
            pr->miniRecordCore.pszIcon = newstrdup( pgbuf );
            pr->miniRecordCore.hptrIcon = NULLHANDLE;
            pr->page = i;

            ri.cb = sizeof( RECORDINSERT );
            ri.pRecordParent = (PRECORDCORE)NULL;
            ri.pRecordOrder = (PRECORDCORE)CMA_END;
            ri.zOrder = (USHORT)CMA_TOP;
            ri.cRecordsInsert = 1;
            ri.fInvalidateRecord = TRUE;
            WinSendMsg( hwnd, CM_INSERTRECORD, MPFROMP( pr ), MPFROMP( &ri ) );
        }
    }
}


char deffont[] = "9.WarpSans";

int main( int argc, char **argv )
{
    PPIB pib;
    PTIB tib;
    DosGetInfoBlocks(&tib, &pib);
    pib->pib_ultype = 3;

    if ( argc < 2 )
    {
        printf("No file name given!\n");
        return 1;
    }

    ev = somGetGlobalEnvironment();

    if ( !loadDll( argv[1] ) ) {
        return 1;
    }

    doc = createObject();
    int res = doc->loadFile( ev, argv[1], NULL, NULL );
    if (!res) {
        printf("Error loading document!\n");
        return 1;
    }

    totalpages = doc->getPageCount( ev );

    HMQ   hmq;
    QMSG  qmsg;
    hab = WinInitialize( 0 );
    hmq = WinCreateMsgQueue( hab, 0 );
    //WinSetCp( hmq, 1208 );

    initClipbrd();
    handptr = WinLoadPointer( HWND_DESKTOP, NULLHANDLE, 500 );

    ULONG ulFrameFlags = FCF_TITLEBAR | FCF_SIZEBORDER | FCF_SYSMENU |
                         FCF_MINMAX | FCF_TASKLIST | FCF_NOBYTEALIGN | FCF_MENU;
    hWndFrame = WinCreateStdWindow( HWND_DESKTOP, 0, &ulFrameFlags, NULL, "test",
                                    WS_SYNCPAINT|WS_VISIBLE, NULLHANDLE, 100, NULL );
    // сплиттер
    InitPMSplitterClass( hab );
    HWND hSplitter = WinCreateWindow( hWndFrame, WC_ER_SPLITTER, "",
                                      WS_VISIBLE | SBS_VSPLIT,
                                      0, 0, 0, 0, hWndFrame, HWND_TOP,
                                      FID_CLIENT, NULL, NULL );
    pOldSplProc = WinSubclassWindow( hSplitter, splProc );

    hWndTree = WinCreateWindow( hWndFrame, WC_CONTAINER, "",
                                WS_VISIBLE|CCS_MINIRECORDCORE|CCS_READONLY|CCS_MINIICONS, 0, 0, 0, 0, hWndFrame,
                                HWND_TOP, ID_CNTR, NULL, NULL );
    WinSetPresParam( hWndTree, PP_FONTNAMESIZE, sizeof(deffont), deffont );
    fill_tree( hWndTree );

    WinRegisterClass( hab, "my.test", wndProc, CS_SIZEREDRAW, sizeof( ULONG ) * 2 );
    ULONG dfFlags = FCF_VERTSCROLL | FCF_HORZSCROLL | FCF_NOBYTEALIGN;
    HWND hwndDocFrame = WinCreateStdWindow( hWndFrame,
                            WS_VISIBLE, &dfFlags, "my.test", NULL,
                            WS_VISIBLE, NULLHANDLE, 0, &hWndDoc );
    hwndHscroll = WinWindowFromID( hwndDocFrame, FID_HORZSCROLL );
    hwndVscroll = WinWindowFromID( hwndDocFrame, FID_VERTSCROLL );

    //hWndDoc = WinCreateWindow( hWndFrame, "my.test", "",
    //                              WS_SYNCPAINT|WS_VISIBLE, 0, 0, 0, 0, hWndFrame,
    //                              HWND_TOP, 2, NULL, NULL );

    WinSendMsg( hSplitter, SBM_SETWINDOWS,
                MPFROMHWND( hWndTree ), MPFROMHWND( hwndDocFrame ) );
    WinSendMsg( hSplitter, SBM_SETSPLITTERPOS, MPFROMSHORT( 80 ), MPVOID );

    render_page();

    // Показать окно программы
    WinSetWindowPos( hWndFrame, HWND_TOP, 100, 100, 630, 400,
                     SWP_SIZE | SWP_MOVE | SWP_SHOW | SWP_ACTIVATE );


    // Messsage loop
    while ( WinGetMsg( hab, &qmsg, 0, 0, 0 ) ) {
        WinDispatchMsg( hab, &qmsg );
    }

    WinDestroyWindow( hWndFrame );
    WinDestroyMsgQueue( hmq );
    WinTerminate( hab );

    delete doc;
    return 0;
}

