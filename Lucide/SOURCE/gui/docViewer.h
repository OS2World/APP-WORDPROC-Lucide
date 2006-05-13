#ifndef __DOCVIEWER_H
#define __DOCVIEWER_H

#include <vector>

#include <ludoc.xh>
#include "lucide.h"

class ProgressDlg;

struct LuSize  { double x, y; };

struct PageDrawArea
{
    long   pagenum;
    LuSize startpos;
    RECTL  drawrect;
};

typedef std::vector<PageDrawArea> DrawAreas;

class DocumentViewer
{
    public:
        DocumentViewer( HAB _hab, HWND hWndFrame );
        virtual ~DocumentViewer();

        void setViewMode( ViewMode mode );

        HWND getHWND() { return hWndDocFrame; }

        void setDocument( LuDocument *_doc );
        void goToPage( long page );
        long getCurrentPage() { return currentpage; }
        void setZoom( double _zoom );
        double getZoom() { return zoom; }
        double getRealZoom() { return realzoom; }
        void copyToClipbrd();
        void searchDocument( const char *_searchString, bool _caseSensitive,
                             bool _continueSearch );

        static void registerClass( HAB hab );

        // Internal stuffs
    private:

        void drawPage();
        void adjustSize();

        MRESULT vertScroll( HWND hwnd, MPARAM mp2, HRGN hrgn );
        MRESULT horizScroll( HWND hwnd, MPARAM mp2, HRGN hrgn );
        void wmSize( HWND hwnd, MPARAM mp2 );
        void wmPaint( HWND hwnd );
        void wmPaintCont( HWND hwnd );
        void wmPaintAsynch( HWND hwnd );
        void wmPaintContAsynch( HWND hwnd );
        void wmButton1Down( HWND hwnd, SHORT xpos, SHORT ypos );
        BOOL wmMouseMove( HWND hwnd, SHORT xpos, SHORT ypos );
        BOOL wmClick( HWND hwnd, SHORT xpos, SHORT ypos );
        BOOL wmChar( HWND hwnd, MPARAM mp1, MPARAM mp2 );
        void winPosToDocPos( PPOINTL startpoint, PPOINTL endpoint, LuRectangle *r );
        void winPosToDocPos( PageDrawArea *pda, LuRectangle *r );
        void docPosToWinPos( long pagenum, LuRectangle *r, PRECTL rcl, bool useZoom = true );
        HRGN rectsToRegion( long pagenum, HPS hps, LuDocument_LuRectSequence *rects, bool useZoom );
        void drawSelection( long pagenum, HPS hps, PRECTL r );
        void scrollToPos( HWND hwnd, HRGN hrgn, LONG xpos, LONG ypos, bool withSelection );
        void freeRects( LuDocument_LuRectSequence **rects );
        void freeLinks();
        void drawFound( long pagenum, HPS hps, PRECTL r );
        DrawAreas *findDrawAreas( PRECTL r );
        void determineCurrentPage();
        long posToPagenum( LONG yPosWin, double *pageRest );
        double pagenumToPos( long pagenum );

        static MRESULT EXPENTRY docViewProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
        static void searchthread( void *p );
        static void searchabort( void *p );
        static void drawthread( void *p );
        static long _System asynchCallbackFnDraw( void *data );
        static long _System asynchCallbackFnAbort( void *data );

        LuDocument *doc;
        HAB hab;
        HWND hMainFrame;
        HWND hWndDocFrame;
        HWND hWndDoc;
        HWND hWndHscroll;
        HWND hWndVscroll;
        SHORT sHscrollMax;
        SHORT sVscrollMax;
        SHORT sHscrollPos;
        SHORT sVscrollPos;
        LONG  sVscrollInc;
        LONG  sHscrollInc;
        ULONG realVscrollMax;
        LONG  cxClient;
        LONG  cyClient;
        LONG  spos_x;
        LONG  spos_y;
        HPS hpsBuffer;
        HDC hdcBuffer;
        Environment *ev;
        LuPixbuf *pixbuf;
        double width, height, zoom, realzoom, fullwidth, fullheight;
        long totalpages, currentpage;
        ProgressDlg *progressDlg;
        DrawAreas *drawareas;
        int drawareaIndex;

        // continuous view
        bool continuous;
        LuSize *pagesizes;
        SHORT VScrollStep;
        RECTL savedRcl;

        // asynch draw
        bool enableAsynchDraw;
        HMTX todrawAccess;
        HEV  haveDraw;
        bool abortAsynch;
        bool termdraw;
        TID  drawThreadId;

        // selection
        bool mousePressed;
        POINTL selectionStart;
        POINTL selectionEnd;
        LuRectangle selection;
        LuDocument_LuRectSequence **selrects;

        // links
        LuDocument_LuLinkMapSequence **links;
        HPOINTER handptr;

        // search
        LuDocument_LuRectSequence **foundrects;
        char *searchString;
        bool caseSensitive;
        bool continueSearch;
        bool abortSearch;
};

#endif // __DOCVIEWER_H

