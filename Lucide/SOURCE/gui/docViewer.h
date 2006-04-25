#ifndef __DOCVIEWER_H
#define __DOCVIEWER_H

#include <vector>
using namespace std;

#include <ludoc.xh>

class ProgressDlg;

struct LuSize  { double x, y; };

struct PageDrawArea
{
    long   pagenum;
    LuSize startpos;
    RECTL  drawrect;
};

typedef vector<PageDrawArea> DrawAreas;


class DocumentViewer
{
    public:
        DocumentViewer( HAB _hab, HWND hWndFrame );
        virtual ~DocumentViewer();

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
        BOOL wmMouseMove( HWND hwnd, SHORT xpos, SHORT ypos );
        BOOL wmClick( HWND hwnd, SHORT xpos, SHORT ypos );
        BOOL wmChar( HWND hwnd, MPARAM mp1, MPARAM mp2 );
        void winPosToDocPos( PPOINTL startpoint, PPOINTL endpoint, LuRectangle *r );
        void docPosToWinPos( LuRectangle *r, PRECTL rcl );
        HRGN rectsToRegion( HPS hps, LuDocument_LuRectSequence *rects, bool useScale );
        void drawSelection( HPS hps, PRECTL r );
        void scrollToPos( HWND hwnd, HRGN hrgn, SHORT xpos, SHORT ypos, bool withSelection );
        void freeFoundrects();
        void drawFound( HPS hps, PRECTL r );
        DrawAreas *foundDrawAreas( PRECTL r );
        void foundCurrentPage();
        long posToPagenum( double yPos, double *pageRest );

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

        // continuous view
        bool continuous;
        LuSize *pagesizes;
        SHORT VScrollStep;
        DrawAreas *drawareas;

        // asynch draw
        bool enableAsynchDraw;
        RECTL drawRect;
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
        LuDocument_LuRectSequence *selrects;

        // links
        LuDocument_LuLinkMapSequence *links;
        HPOINTER handptr;

        // search
        LuDocument_LuRectSequence **foundrects;
        char *searchString;
        bool caseSensitive;
        bool continueSearch;
        bool abortSearch;
};

#endif // __DOCVIEWER_H
