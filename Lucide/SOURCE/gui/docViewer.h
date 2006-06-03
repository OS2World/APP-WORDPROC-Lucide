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
        void close();
        void goToPage( long page );
        long getCurrentPage() { return currentpage; }
        void setZoom( double _zoom );
        double getZoom() { return zoom; }
        double getRealZoom() { return realzoom; }
        void selectAll();
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
        MRESULT wmDragOver( PDRAGINFO dragInfo );
		void wmDrop( PDRAGINFO dragInfo );
		void wmSize( HWND hwnd, MPARAM mp2 );
        void wmPaint( HWND hwnd );
        void wmPaintCont( HWND hwnd );
        void wmPaintAsynch( HWND hwnd );
        void wmPaintContAsynch( HWND hwnd );
        void wmButton1Down( HWND hwnd, SHORT xpos, SHORT ypos );
        void wmButton1Up();
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
        short bpp;
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
        LuRectangle *selection;
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

