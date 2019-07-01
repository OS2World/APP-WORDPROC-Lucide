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


#ifndef __DOCVIEWER_H
#define __DOCVIEWER_H

#include <vector>

#include <ludoc.xh>
#include "lucide.h"

class ProgressDlg;
class LuInputText;
class LuInputChoice;

struct LuSize  { double x, y; };

struct PageDrawArea
{
    long   pagenum;
    LuSize startpos;
    RECTL  drawrect;
};

struct PageInputFields
{
    LuDocument_LuInputFieldSequence *fields;

    struct Cache
    {
        LuRectangle *rect;
        LuInputField_Type type;
        bool supported;
        bool modified;
    };

    Cache *cache;

    void fillCache( int i );
};

typedef std::vector<PageDrawArea> DrawAreas;

class DocumentViewer
{
    public:
        DocumentViewer( HWND hWndFrame );
        virtual ~DocumentViewer();

        void setPageLayout( PgLayout layout );
        PgLayout getPageLayout() { return layout; }

        HWND getFrameHWND() { return hWndDocFrame; }
        HWND getViewHWND() { return hWndDoc; }

        short getVscrollPos() { return sVscrollPos; }
        short getHscrollPos() { return sHscrollPos; }
        void setDocument( LuDocument *_doc );
        bool close( bool force = false );
        void goToPage( long page );
        long getCurrentPage() { return currentpage; }  // Zero based
        long getPreviousPage() { return previouspage; }  // Zero based
        void unsetPreviousPage() { previouspage = -1; }
        void setZoom( double _zoom );
        double getZoom() { return zoom; }
        double getRealZoom() { return realzoom; }
        void setZoomMode( bool _zoomMode ) { zoomMode = _zoomMode; }
        bool isZoomMode() { return zoomMode; }
        void setRotation( long _rotation );
        long getRotation() { return rotation; }
        void selectAll();
        void unhideMouse();
        void copyToClipbrd();
        void searchDocument( const char *_searchString, bool _caseSensitive,
                             bool _continueSearch, bool _findBack );
        void setPresentation( bool _presentation );
        void zoomInOut( bool zoomIn );
        void resetModifiedState();

        static void registerClass();

        MRESULT vertScroll( HWND hwnd, MPARAM mp2 );
        MRESULT horizScroll( HWND hwnd, MPARAM mp2 );
        // Internal stuffs
    private:

        void drawPage();
        void adjustSize();
        void countPagesizes();
        
        MRESULT wmDragOver( PDRAGINFO dragInfo );
        void wmDrop( PDRAGINFO dragInfo );
        void wmSize( HWND hwnd, MPARAM mp2 );
        void wmPaint( HWND hwnd );
        void wmPaintCont( HWND hwnd );
        void wmPaintAsynch( HWND hwnd );
        void wmPaintContAsynch( HWND hwnd );
        void wmButton1Down( HWND hwnd, SHORT xpos, SHORT ypos );
        void wmButton1Up();
        void wmButton2Down( HWND hwnd, SHORT xpos, SHORT ypos );
        void wmButton2Up();
        BOOL wmMouseMove( HWND hwnd, SHORT xpos, SHORT ypos );
        BOOL wmClick( HWND hwnd, SHORT xpos, SHORT ypos );
        BOOL wmRightClick( HWND hwnd, SHORT xpos, SHORT ypos );
        BOOL wmChar( HWND hwnd, MPARAM mp1, MPARAM mp2 );
        void wmTimer( USHORT idTimer );
        void wmControl( USHORT idControl, USHORT notifyCode, HWND hwndControl );
        void winPosToDocPos( PPOINTL startpoint, PPOINTL endpoint, LuRectangle *r );
        void winPosToDocPos( PageDrawArea *pda, LuRectangle *r );
        void docPosToWinPos( long pagenum, LuRectangle *r, PRECTL rcl );
        void rotateRectangle( long pagenum, LuRectangle *r );
        HRGN rectsToRegion( long pagenum, HPS hps, LuDocument_LuRectSequence *rects );
        void drawSelection( long pagenum, HPS hps, PRECTL r );
        void scrollToPos( HWND hwnd, LONG xpos, LONG ypos, bool withSelection );
        void freeRects( LuDocument_LuRectSequence **rects );
        void freeLinks();
        void freeInputFields();
        void drawFound( long pagenum, HPS hps, PRECTL r );
        DrawAreas *findDrawAreas( PRECTL r );
        void determineCurrentPage();
        long posToPagenum( LONG yPosWin, double *pageRest );
        double pagenumToPos( long pagenum );
        bool isRotated() { return ( (rotation==90) || (rotation==270) ); }
        bool isContinuous() { return ( layout == Continuous ); };
        void showTextField( long page, long index, PRECTL r = NULL );
        void positionTextField( PRECTL r = NULL );
        void hideTextField( bool apply = true, PPOINTL ptl = NULL );
        void showChoiceField( long page, long index, PRECTL r = NULL );
        void positionChoiceField( PRECTL r = NULL );
        void hideChoiceField( bool apply = true, PPOINTL ptl = NULL );

        static MRESULT EXPENTRY docViewProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
        static MRESULT EXPENTRY docFrameProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
        static void searchthread( void *p );
        static void searchabort( void *p );
        static void drawthread( void *p );
        static long _System asynchCallbackFnDraw( void *data );
        static long _System asynchCallbackFnAbort( void *data );

        LuDocument *doc;
        HWND hMainFrame;
        HWND hWndDocFrame;
        HWND hWndPopupMenu;
        HWND hWndDoc;
        HWND hWndEntry;
        HWND hWndMLE;
        HWND hWndList;
        HWND hWndBubble;
        LuInputText *textField;
        LuInputChoice *choiceField;
        long textFieldPage;
        long textFieldIndex;
        long choiceFieldPage;
        long choiceFieldIndex;
        PFNWP oldFrameProc;
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
        LuPixbuf *pixbuf;
        short bpp;
        double width, height, zoom, realzoom, fullwidth, fullheight;
        boolean zoomMode;
        long rotation;
        long totalpages, currentpage, previouspage;
        ProgressDlg *progressDlg;
        DrawAreas *drawareas;
        int drawareaIndex;
        bool closed;
        bool drawPS;
        PgLayout layout;

        // mouse drag using right button
        bool docDraggingStarted;
        POINTL docDraggingStart;
        POINTL docDraggingEnd;

        // presentation
        bool presentation;
        bool mouseHidden;
        bool inFocus;
        SHORT xLastPos;
        SHORT yLastPos;
        PgLayout pglSave;
        double zoomSave;

        // continuous view
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
        LuRectangle *selection;
        LuDocument_LuRectSequence **selrects;

        // links
        LuDocument_LuLinkMapSequence **links;

        // input fields
        PageInputFields *inputFields;

        // search
        LuDocument_LuRectSequence **foundrects;
        char *searchString;
        bool caseSensitive;
        bool continueSearch;
        bool findBack;
        bool abortSearch;

        // pointers
        HPOINTER handPtr;
        HPOINTER handClosedPtr;
        HPOINTER zoomInPtr;
        HPOINTER zoomOutPtr;
        HPOINTER textPtr;
};

#endif // __DOCVIEWER_H

