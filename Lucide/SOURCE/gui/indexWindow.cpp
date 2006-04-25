#define INCL_WIN
#include <os2.h>

#include <stdio.h>

#include <ludoc.xh>
#include "lucide.h"
#include "indexWindow.h"
#include "luutils.h"
#include "tb_spl.h"


#define ID_BAR      1
#define ID_INDEX    2


// IndexWindow constructor
IndexWindow::IndexWindow( HAB _hab, HWND hWndFrame )
{
    hab         = _hab;
    hMainFrame  = hWndFrame;
    hWndIndex   = NULLHANDLE;
    doc         = NULL;
    totalpages  = 0;
    ev          = somGetGlobalEnvironment();

    hWndPanel = WinCreateWindow( hWndFrame, WC_ER_SPLITTER, "",
                                 WS_VISIBLE | SBS_HSPLIT | SBS_SECONDFIXED,
                                 0, 0, 0, 0, hWndFrame, HWND_TOP, 0, NULL, NULL );
    WinSetWindowULong( hWndPanel, QWL_USER, (ULONG)this );
    pOldPanelProc = WinSubclassWindow( hWndPanel, panelProc );

    hWndBar = WinCreateWindow( hWndFrame, WC_STATIC, "index/thumbs switch will be here",
                               WS_VISIBLE | SS_TEXT | DT_LEFT | DT_VCENTER,
                               0, 0, 0, 0, hWndPanel, HWND_TOP, ID_BAR, NULL, NULL );
    WinSetPresParam( hWndBar, PP_FONTNAMESIZE, deffontlen, deffont );
    ULONG syscmenu = SYSCLR_MENU;
    WinSetPresParam( hWndBar, PP_BACKGROUNDCOLORINDEX, sizeof( ULONG ), &syscmenu );

    hWndIndex = WinCreateWindow( hWndFrame, WC_CONTAINER, "",
                        WS_VISIBLE|CCS_MINIRECORDCORE|CCS_READONLY|CCS_MINIICONS,
                        0, 0, 0, 0, hWndPanel, HWND_TOP, ID_INDEX, NULL, NULL );
    WinSetPresParam( hWndIndex, PP_FONTNAMESIZE, deffontlen, deffont );

    WinSendMsg( hWndPanel, SBM_SETWINDOWS,
                MPFROMHWND( hWndIndex ), MPFROMHWND( hWndBar ) );
    WinSendMsg( hWndPanel, SBM_SETFIXEDSIZE, MPFROMSHORT( 30 ), MPVOID );
}

// IndexWindow destructor
IndexWindow::~IndexWindow()
{
    clear( NULL );
}


void IndexWindow::setDocument( LuDocument *_doc )
{
    clear( NULL );

    doc = _doc;

    if ( doc == NULL ) {
        totalpages = 0;
    }
    else
    {
        totalpages = doc->getPageCount( ev );

        if ( doc->isHaveIndex( ev ) ) {
            loadIndex();
        }
        else {
            loadPagesList();
        }
    }
}

void IndexWindow::loadIndex()
{
    CNRINFO ci;
    ci.cb = sizeof( CNRINFO );
    WinSendMsg( hWndIndex, CM_QUERYCNRINFO, MPFROMP( &ci ), MPFROMSHORT( ci.cb ) );
    ci.flWindowAttr &= ~( CV_NAME | CV_FLOW | CV_TEXT | CV_ICON | CV_TREE );
    ci.flWindowAttr |= ( CV_TREE | CV_TEXT | CV_MINI | CA_TREELINE );
    WinSendMsg( hWndIndex, CM_SETCNRINFO, MPFROMP( &ci ), MPFROMLONG( CMA_FLWINDOWATTR ) );

    LuIndexNode *n = doc->getIndex( ev );
    LuIndexNode *cn = n->getFirstChild( ev );
    while ( cn != NULL )
    {
        addNodes( NULL, cn );
        cn = n->getNextChild( ev );
    }
    delete n;
}

void IndexWindow::addNodes( TreeRecord *parent, LuIndexNode *n )
{
    if ( n == NULL ) {
        return;
    }

    LuLink *link = n->getLink( ev );

    RECORDINSERT ri;
    TreeRecord *pr = (TreeRecord *)WinSendMsg( hWndIndex, CM_ALLOCRECORD,
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
    WinSendMsg( hWndIndex, CM_INSERTRECORD, MPFROMP( pr ), MPFROMP( &ri ) );

    LuIndexNode *cn = n->getFirstChild( ev );
    while ( cn != NULL )
    {
        addNodes( pr, cn );
        cn = n->getNextChild( ev );
    }
}

void IndexWindow::loadPagesList()
{
    CNRINFO ci;
    ci.cb = sizeof( CNRINFO );
    WinSendMsg( hWndIndex, CM_QUERYCNRINFO, MPFROMP( &ci ), MPFROMSHORT( ci.cb ) );
    ci.flWindowAttr &= ~( CV_NAME | CV_FLOW | CV_TEXT | CV_ICON | CV_TREE );
    ci.flWindowAttr |= ( CV_TEXT | CV_MINI );
    WinSendMsg( hWndIndex, CM_SETCNRINFO, MPFROMP( &ci ), MPFROMLONG( CMA_FLWINDOWATTR ) );

    char pgbuf[ 20 ];
    for ( int i = 0; i < totalpages; i++ )
    {
        snprintf( pgbuf, sizeof(pgbuf), "Page %d", i + 1 );
        RECORDINSERT ri;
        TreeRecord *pr = (TreeRecord *)WinSendMsg( hWndIndex, CM_ALLOCRECORD,
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
        WinSendMsg( hWndIndex, CM_INSERTRECORD, MPFROMP( pr ), MPFROMP( &ri ) );
    }
}

void IndexWindow::clear( TreeRecord *parent )
{
    SHORT atr = ( parent == NULL ) ? CMA_FIRST : CMA_FIRSTCHILD;
    TreeRecord *precs = (TreeRecord *)WinSendMsg( hWndIndex, CM_QUERYRECORD,
                            MPFROMP( parent ), MPFROM2SHORT( atr, CMA_ITEMORDER ) );
    TreeRecord *pr = precs;
    while ( ( pr != NULL ) && ( (int)pr != -1 ) )
    {
        delete pr->miniRecordCore.pszIcon;
        clear( pr );
        pr = (TreeRecord *)WinSendMsg( hWndIndex, CM_QUERYRECORD,
                                MPFROMP( pr ), MPFROM2SHORT( CMA_NEXT, CMA_ITEMORDER ) );
    }

    if ( parent == NULL ) {  // top level call
        WinSendMsg( hWndIndex, CM_REMOVERECORD, MPFROMP( NULL ),
                                    MPFROM2SHORT( 0, CMA_INVALIDATE ) );
    }
}

bool IndexWindow::goToPage( TreeRecord *parent, long page )
{
    SHORT atr = ( parent == NULL ) ? CMA_FIRST : CMA_FIRSTCHILD;
    TreeRecord *pr = (TreeRecord *)WinSendMsg( hWndIndex, CM_QUERYRECORD,
                            MPFROMP( parent ), MPFROM2SHORT( atr, CMA_ITEMORDER ) );
    while ( ( pr != NULL ) && ( (int)pr != -1 ) )
    {
        if ( pr->page == page )
        {
            if ( parent != NULL ) {
                WinSendMsg( hWndIndex, CM_EXPANDTREE, MPFROMP( parent ), MPVOID );
            }
            WinSendMsg( hWndIndex, CM_SETRECORDEMPHASIS, MPFROMP( pr ),
                        MPFROM2SHORT( TRUE, CRA_SELECTED | CRA_CURSORED ) );
            return true;
        }

        if ( goToPage( pr, page ) ) {
            return true;
        }

        pr = (TreeRecord *)WinSendMsg( hWndIndex, CM_QUERYRECORD,
                                MPFROMP( pr ), MPFROM2SHORT( CMA_NEXT, CMA_ITEMORDER ) );
    }
    return false;
}


// static, window procedure
MRESULT EXPENTRY IndexWindow::panelProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    IndexWindow *_this = (IndexWindow *)WinQueryWindowULong( hwnd, QWL_USER );

    switch ( msg )
    {
        case WM_CONTROL:
            switch ( SHORT1FROMMP( mp1 ) )
            {
                case ID_INDEX:
                    switch ( SHORT2FROMMP( mp1 ) )
                    {
                        case CN_ENTER:
                            {
                                PNOTIFYRECORDENTER re = (PNOTIFYRECORDENTER)mp2;
                                TreeRecord *tr = (TreeRecord *)re->pRecord;
                                Lucide::dontSwitchPage = true;
                                Lucide::goToPage( tr->page );
                                Lucide::dontSwitchPage = false;
                            }
                            break;
                    }
                    break;
            }
            break;
    }

    return _this->pOldPanelProc( hwnd, msg, mp1, mp2 );
}


