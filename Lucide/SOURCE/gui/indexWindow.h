#ifndef __INDEXWINDOW_H
#define __INDEXWINDOW_H

#include <ludoc.xh>


struct TreeRecord
{
    MINIRECORDCORE miniRecordCore;
    long page;
};


class IndexWindow
{
    public:
        IndexWindow( HAB _hab, HWND hWndFrame );
        virtual ~IndexWindow();

        HWND getHWND() { return hWndPanel; }
        
        void setDocument( LuDocument *_doc );
		bool goToPage( TreeRecord *parent, long page );
        
        // Internal stuffs
    private:
        
        void loadIndex();
        void loadPagesList();
		void addNodes( TreeRecord *parent, LuIndexNode *n );
		void clear( TreeRecord *parent );
    
		
        static MRESULT EXPENTRY panelProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
		PFNWP pOldPanelProc;
        
    	LuDocument *doc;
        HAB hab;
        HWND hMainFrame;
        HWND hWndPanel;
        HWND hWndBar;
    	HWND hWndIndex;
		Environment *ev;
		long totalpages;
};

#endif // __INDEXWINDOW_H
