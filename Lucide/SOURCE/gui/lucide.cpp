#define INCL_WIN
#define INCL_DOS
#include <os2.h>

#include <string>
#include <stdio.h>
//#include <stdlib.h>

#include <ludoc.xh>

#include "Lucide.h"
#include "pluginman.h"
#include "pluginViewDlg.h"
#include "fontsInfoDlg.h"
#include "docInfoDlg.h"
#include "findDlg.h"
#include "docViewer.h"
#include "indexWindow.h"
#include "luutils.h"
#include "tb_spl.h"
#include "Lucide_res.h"
#include "messages.h"


const char *appName = "Lucide";
const char *fwp = "FrameWindowPos";
const char *lvd = "LastViewedDir";


HWND createToolbar( HWND hwnd );

HAB   hab;
HWND  hWndFrame;
HWND  hWndMenu;
HWND  hToolBar;

Environment    *ev        = somGetGlobalEnvironment();
LuDocument     *doc       = NULL;
PluginManager  *pluginMan = NULL;
DocumentViewer *docViewer = NULL;
IndexWindow    *indexWin  = NULL;
FindDlg        *findDlg   = NULL;

bool Lucide::dontSwitchPage = false;

PFNWP pOldSplProc;

void Lucide::enableCopy( bool enable )
{
    WinEnableMenuItem( hWndMenu, CM_COPY, enable );
}

static void setOfPages( long pages )
{
    char *pgfrm = newstrdupL( TB_PAGENUM );
    char pgnum[ 32 ];
    snprintf( pgnum, sizeof( pgnum ), pgfrm, pages );
    delete pgfrm;
    WinSetDlgItemText( hToolBar, TBID_OFPAGES, pgnum );
    WinSendDlgItemMsg( hToolBar, TBID_PAGENUM, SPBM_SETLIMITS, (MPARAM)pages, (MPARAM)1 );
}

void Lucide::checkNavigationMenus()
{
    BOOL enfirst = ( docViewer->getCurrentPage() != 0 );
    BOOL enlast = ( docViewer->getCurrentPage() != ( doc->getPageCount( ev ) - 1 ) );
    WinEnableMenuItem( hWndMenu, CM_FIRSTPAGE, enfirst );
    WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FIRSTPAGE), (MPARAM)enfirst );
    WinEnableMenuItem( hWndMenu, CM_PREVPAGE, enfirst );
    WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_PREVPAGE), (MPARAM)enfirst );
    WinEnableMenuItem( hWndMenu, CM_NEXTPAGE, enlast );
    WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_NEXTPAGE), (MPARAM)enlast );
    WinEnableMenuItem( hWndMenu, CM_LASTPAGE, enlast );
    WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_LASTPAGE), (MPARAM)enlast );

    dontSwitchPage = true;
    WinSendDlgItemMsg( hToolBar, TBID_PAGENUM, SPBM_SETCURRENTVALUE,
                       MPFROMLONG( docViewer->getCurrentPage() + 1 ), MPVOID );
    dontSwitchPage = false;
    indexWin->goToPage( NULL, docViewer->getCurrentPage() );
}

void enableZoomMenus()
{
    BOOL scalable = doc->isScalable( ev );
    WinEnableMenuItem( hWndMenu, CM_FITWINDOW, scalable );
    WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FITWINDOW), (MPARAM)scalable );
    WinEnableMenuItem( hWndMenu, CM_ACTSIZE, scalable );
    WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_ACTSIZE), (MPARAM)scalable );
    WinEnableMenuItem( hWndMenu, CM_FITWIDTH, scalable );
    WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FITWIDTH), (MPARAM)scalable );
    WinEnableControl( hToolBar, TBID_ZOOM, scalable );
    BOOL rotable = doc->isRotable( ev );
    WinEnableMenuItem( hWndMenu, CM_ROTATE90CW, rotable );
    WinEnableMenuItem( hWndMenu, CM_ROTATE90CCW, rotable );
}


void setZoomChecks( SHORT cmd, SHORT cbind, double zoom )
{
    if ( cmd != -1 )
    {
        WinSendMsg( hWndMenu, MM_SETITEMATTR, MPFROM2SHORT( cmd, TRUE ),
                            MPFROM2SHORT( MIA_CHECKED, MIA_CHECKED ) );
        WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT( cmd ), (MPARAM)TRUE );
    }

    if ( cbind != -1 )
    {
        char buf[ 255 ] = "";
        WinSendDlgItemMsg( hToolBar, TBID_ZOOM, LM_QUERYITEMTEXT,
                           MPFROM2SHORT( cbind, sizeof( buf ) ), MPFROMP( buf ) );
        WinSetDlgItemText( hToolBar, TBID_ZOOM, buf );
    }

    if ( zoom != 0 )
    {
        std::string z = str( zoom * 100.0 ) + "%";
        WinSetDlgItemText( hToolBar, TBID_ZOOM, z.c_str() );
    }
}

void Lucide::checkZoomMenus()
{
    double zoom = docViewer->getZoom();

    WinSendMsg( hWndMenu, MM_SETITEMATTR, MPFROM2SHORT( CM_FITWINDOW, TRUE ),
                        MPFROM2SHORT( MIA_CHECKED, FALSE ) );
    WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT(CM_FITWINDOW), (MPARAM)FALSE );
    WinSendMsg( hWndMenu, MM_SETITEMATTR, MPFROM2SHORT( CM_ACTSIZE, TRUE ),
                        MPFROM2SHORT( MIA_CHECKED, FALSE ) );
    WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT(CM_ACTSIZE), (MPARAM)FALSE );
    WinSendMsg( hWndMenu, MM_SETITEMATTR, MPFROM2SHORT( CM_FITWIDTH, TRUE ),
                        MPFROM2SHORT( MIA_CHECKED, FALSE ) );
    WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT(CM_FITWIDTH), (MPARAM)FALSE );

    if ( zoom == -2 ) {
        setZoomChecks( CM_FITWINDOW, 1, 0 );
    } else if ( zoom == -1 ) {
        setZoomChecks( CM_FITWIDTH, 2, 0 );
    } else if ( zoom == 1 ) {
        setZoomChecks( CM_ACTSIZE, 0, 0 );
    } else {
        setZoomChecks( -1, -1, zoom );
    }
}

void Lucide::checkMenus()
{
    // pre-set "Actual size"
    setZoomChecks( CM_ACTSIZE, 0, 0 );

    if ( doc == NULL )
    {
        // "single page" mode by default
        WinSendMsg( hWndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT( CM_SINGLEPAGE, TRUE ),
                    MPFROM2SHORT( MIA_CHECKED, MIA_CHECKED ) );

        WinEnableMenuItem( hWndMenu, CM_SAVEAS, FALSE );
        WinEnableMenuItem( hWndMenu, CM_EXPORTTOPS, FALSE );
        WinEnableMenuItem( hWndMenu, CM_PAGESETUP, FALSE );
        WinEnableMenuItem( hWndMenu, CM_PRINT, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_PRINT), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_DOCINFO, FALSE );
        WinEnableMenuItem( hWndMenu, CM_FONTSINFO, FALSE );

        WinEnableMenuItem( hWndMenu, CM_COPY, FALSE );
        WinEnableMenuItem( hWndMenu, CM_SELECTALL, FALSE );
        WinEnableMenuItem( hWndMenu, CM_FIND, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FIND), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_FINDAGAIN, FALSE );

        WinEnableMenuItem( hWndMenu, CM_FIRSTPAGE, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FIRSTPAGE), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_PREVPAGE, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_PREVPAGE), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_NEXTPAGE, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_NEXTPAGE), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_LASTPAGE, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_LASTPAGE), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_GOTOPAGE, FALSE );

        WinEnableMenuItem( hWndMenu, CM_FITWINDOW, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FITWINDOW), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_ACTSIZE, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_ACTSIZE), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_FITWIDTH, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FITWIDTH), (MPARAM)FALSE );
        WinEnableControl( hToolBar, TBID_ZOOM, FALSE );

        WinEnableMenuItem( hWndMenu, CM_ROTATE90CW, FALSE );
        WinEnableMenuItem( hWndMenu, CM_ROTATE90CCW, FALSE );
        WinEnableMenuItem( hWndMenu, CM_NAVPANE, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_NAVPANE), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_SINGLEPAGE, FALSE );
        WinEnableMenuItem( hWndMenu, CM_CONTINUOUS, FALSE );

        setOfPages( 0 );
        return;
    }


    checkNavigationMenus();
    enableZoomMenus();
    checkZoomMenus();

    setOfPages( doc->getPageCount( ev ) );
    WinEnableMenuItem( hWndMenu, CM_FONTSINFO, doc->isHaveFontInfo( ev ) );
    WinEnableMenuItem( hWndMenu, CM_DOCINFO, TRUE );

    BOOL haveText = doc->isHaveText( ev );
    WinEnableMenuItem( hWndMenu, CM_FIND, haveText );
    WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FIND), (MPARAM)haveText );

    WinEnableMenuItem( hWndMenu, CM_SINGLEPAGE, TRUE );
    WinEnableMenuItem( hWndMenu, CM_CONTINUOUS, TRUE );
}

void Lucide::goToPage( long page )
{
    if ( docViewer != NULL ) {
        docViewer->goToPage( page );
    }
}

void Lucide::setZoom( double zoom )
{
    if ( docViewer != NULL ) {
        docViewer->setZoom( zoom );
        checkZoomMenus();
    }
}

void Lucide::setDocument( LuDocument *_doc )
{
    docViewer->setDocument( _doc );
    indexWin->setDocument( _doc );
    Lucide::checkMenus();
}

void Lucide::setViewMode( ViewMode mode )
{
    if ( mode == SinglePage )
    {
        WinSendMsg( hWndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT( CM_SINGLEPAGE, TRUE ),
                    MPFROM2SHORT( MIA_CHECKED, MIA_CHECKED ) );
        WinSendMsg( hWndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT( CM_CONTINUOUS, TRUE ),
                    MPFROM2SHORT( MIA_CHECKED, FALSE ) );
    }
    else
    {
        WinSendMsg( hWndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT( CM_SINGLEPAGE, TRUE ),
                    MPFROM2SHORT( MIA_CHECKED, FALSE ) );
        WinSendMsg( hWndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT( CM_CONTINUOUS, TRUE ),
                    MPFROM2SHORT( MIA_CHECKED, MIA_CHECKED ) );
    }

    docViewer->setViewMode( mode );
}


static void loadDocument( const char *fn )
{
    char *msg = newstrdupL( MSGS_NO_SUIT_PLUG );

    // find extension
    char *ext = strrchr( fn, '.' );
    if ( ext == NULL ) {
        WinMessageBox( HWND_DESKTOP, hWndFrame, msg,
                       NULL, 0, MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
    }
    else
    {
        doc = pluginMan->createDocumentForExt( ext + 1 );
        if ( doc == NULL ) {
            WinMessageBox( HWND_DESKTOP, hWndFrame, msg,
                           NULL, 0, MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
        }
        else
        {
            char *error = NULL;
            if ( doc->loadFile( ev, (char *)fn, NULL, &error ) ) {
                Lucide::setDocument( doc );
            }
            else
            {
                if ( error == NULL ) {
                    char *m = newstrdupL( MSGS_FILE_LOAD_ERROR );
                    WinMessageBox( HWND_DESKTOP, hWndFrame, m,
                                   NULL, 0, MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
                    delete m;
                }
                else {
                    WinMessageBox( HWND_DESKTOP, hWndFrame, error,
                                   NULL, 0, MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
                    SOMFree( error );
                }

                delete doc;
                doc = NULL;
            }
        }
    }
    delete msg;
}

static void openDocument()
{
    PFILEDLG fd = new FILEDLG;
    memset( fd, 0, sizeof( FILEDLG ) );
    fd->cbSize = sizeof( FILEDLG );
    fd->fl = FDS_CENTER | FDS_OPEN_DIALOG;
    PrfQueryProfileString( HINI_USERPROFILE, appName, lvd, "",
                           fd->szFullFile, sizeof( fd->szFullFile ) );
    strcat( fd->szFullFile, pluginMan->getExtsMask().c_str() );
    WinFileDlg( HWND_DESKTOP, hWndFrame, fd );
    if ( fd->lReturn == DID_OK )
    {
        char drv[ _MAX_DRIVE ] = "";
        char dir[ _MAX_PATH ] = "";
        char buf[ _MAX_PATH ] = "";
        _splitpath( fd->szFullFile, drv, dir, NULL, NULL );
        _makepath( buf, drv, dir, NULL, NULL );
        PrfWriteProfileString( HINI_USERPROFILE, appName, lvd, buf );

        loadDocument( fd->szFullFile );
    }
    delete fd;
}


static MRESULT EXPENTRY splProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch ( msg )
    {

        case WM_COMMAND:
        {
            switch ( SHORT1FROMMP(mp1) )
            {
                case CM_OPEN:
                    openDocument();
                    return (MRESULT)FALSE;

                case CM_EXIT:
                    WinPostMsg( hWndFrame, WM_CLOSE, NULL, NULL );
                    return (MRESULT)FALSE;

                case CM_DOCINFO:
                {
                    LuDocumentInfo *dinfo = doc->getDocumentInfo( ev );
                    DocInfoDlg *d = new DocInfoDlg( hWndFrame, dinfo );
                    d->doDialog();
                    LuDocument::freeDocumentInfo( ev, dinfo );
                    return (MRESULT)FALSE;
                }

                case CM_FONTSINFO:
                {
                    FontsInfoDlg *d = new FontsInfoDlg( hWndFrame, doc );
                    d->doDialog();
                    return (MRESULT)FALSE;
                }

                case CM_PLUGINSLIST:
                {
                    PluginViewDlg *d = new PluginViewDlg( hWndFrame,
                                                pluginMan->getPluginsList() );
                    d->doDialog();
                    return (MRESULT)FALSE;
                }

                case CM_COPY:
                    docViewer->copyToClipbrd();
                    return (MRESULT)FALSE;

                case CM_FIND:
                    if ( findDlg->showDialog() == DID_OK ) {
                        if ( strlen( findDlg->getSearchString() ) > 0 )
                        {
                            docViewer->searchDocument( findDlg->getSearchString(),
                                            findDlg->isCaseSensitive(), false );

                            WinEnableMenuItem( hWndMenu, CM_FINDAGAIN, TRUE );
                        }
                    }
                    return (MRESULT)FALSE;

                case CM_FINDAGAIN:
                    docViewer->searchDocument( findDlg->getSearchString(),
                                               findDlg->isCaseSensitive(), true );
                    return (MRESULT)FALSE;

                case CM_FIRSTPAGE:
                    Lucide::goToPage( 0 );
                    return (MRESULT)FALSE;

                case CM_NEXTPAGE:
                    Lucide::goToPage( docViewer->getCurrentPage() + 1 );
                    return (MRESULT)FALSE;

                case CM_PREVPAGE:
                    Lucide::goToPage( docViewer->getCurrentPage() - 1 );
                    return (MRESULT)FALSE;

                case CM_LASTPAGE:
                    Lucide::goToPage( doc->getPageCount( ev ) - 1 );
                    return (MRESULT)FALSE;

                case CM_FITWINDOW:
                    Lucide::setZoom( -2 );
                    return (MRESULT)FALSE;

                case CM_ACTSIZE:
                    Lucide::setZoom( 1 );
                    return (MRESULT)FALSE;

                case CM_FITWIDTH:
                    Lucide::setZoom( -1 );
                    return (MRESULT)FALSE;

                case CM_SINGLEPAGE:
                    Lucide::setViewMode( SinglePage );
                    return (MRESULT)FALSE;

                case CM_CONTINUOUS:
                    Lucide::setViewMode( Continuous );
                    return (MRESULT)FALSE;
            }
        }
        break;
    }
    return pOldSplProc( hwnd, msg, mp1, mp2 );
}


char deffont[] = "9.WarpSans";
int deffontlen = sizeof( deffont );

int main( int argc, char **argv )
{
    PPIB pib;
    PTIB tib;
    DosGetInfoBlocks(&tib, &pib);
    pib->pib_ultype = 3;

    HMQ   hmq;
    QMSG  qmsg;
    hab = WinInitialize( 0 );
    hmq = WinCreateMsgQueue( hab, 0 );

    loadLang();

    pluginMan = new PluginManager;

    InitPMSplitterClass( hab );
    InitPMToolbarClass( hab );

    ULONG ulFrameFlags = FCF_TITLEBAR | FCF_SIZEBORDER | FCF_SYSMENU |
                         FCF_MINMAX | FCF_TASKLIST | FCF_NOBYTEALIGN;
    char *title = newstrdupL( MSGS_MAIN_WIN_TITLE );
    hWndFrame = WinCreateStdWindow( HWND_DESKTOP, 0, &ulFrameFlags, NULL, title,
                                    WS_SYNCPAINT|WS_VISIBLE, NULLHANDLE, 100, NULL );
    delete title;
    WinSetAccelTable( hab, WinLoadAccelTable( hab, NULLHANDLE, IDA_MAINACCEL ), hWndFrame );
    hWndMenu = WinLoadMenu( hWndFrame, NULLHANDLE, IDM_MAINMENU );
    localizeMenu( hWndMenu );
    WinSetWindowUShort( hWndMenu, QWS_ID, FID_MENU );

    // Vertical splitter and his windows - Index and Document view
    HWND hVertSplitter = WinCreateWindow( hWndFrame, WC_ER_SPLITTER, "",
                                          WS_VISIBLE | SBS_VSPLIT,
                                          0, 0, 0, 0, hWndFrame, HWND_TOP,
                                          0, NULL, NULL );

    indexWin = new IndexWindow( hab, hWndFrame );

    DocumentViewer::registerClass( hab );

    docViewer = new DocumentViewer( hab, hWndFrame );

    WinSendMsg( hVertSplitter, SBM_SETWINDOWS,
                MPFROMHWND( indexWin->getHWND() ), MPFROMHWND( docViewer->getHWND() ) );
    WinSendMsg( hVertSplitter, SBM_SETSPLITTERPOS, MPFROMSHORT( 80 ), MPVOID );

    // Horizontal splitter and its windows - Toolbar and Vertical splitter
    // Horizontal splitter is client window
    HWND hHorizSplitter = WinCreateWindow( hWndFrame, WC_ER_SPLITTER, "",
                                           WS_VISIBLE | SBS_HSPLIT | SBS_SECONDFIXED,
                                           0, 0, 0, 0, hWndFrame, HWND_TOP,
                                           FID_CLIENT, NULL, NULL );
    pOldSplProc = WinSubclassWindow( hHorizSplitter, splProc );

    hToolBar = createToolbar( hWndFrame );

    WinSendMsg( hHorizSplitter, SBM_SETWINDOWS,
                MPFROMHWND( hVertSplitter ), MPFROMHWND( hToolBar ) );
    // установить фиксированный размер для тулбара
    WinSendMsg( hHorizSplitter, SBM_SETFIXEDSIZE,
                MPFROMSHORT( DEFAULT_PICTSIZE + TOOLBAR_HEIGHT_ADD ), MPVOID );

    findDlg = new FindDlg( hWndFrame );
    Lucide::checkMenus();
    if ( argc > 1 ) {
        loadDocument( argv[1] );
    }

    // Показать окно программы
    if ( !PMRestoreWindowPos( NULL, appName, fwp, hWndFrame,
                              TRUE, TRUE, FALSE, FALSE, FALSE ) )
    {
        WinSetWindowPos( hWndFrame, HWND_TOP, 100, 100, 630, 400,
                         SWP_SIZE | SWP_MOVE | SWP_SHOW | SWP_ACTIVATE );
    }

    // Messsage loop
    while ( WinGetMsg( hab, &qmsg, 0, 0, 0 ) ) {
        WinDispatchMsg( hab, &qmsg );
    }

    if ( WinIsWindow( hab, hWndFrame ) ) {
        PMStoreWindowPos( NULL, appName, fwp, hWndFrame );
    }

    WinDestroyWindow( hWndFrame );
    WinDestroyMsgQueue( hmq );
    WinTerminate( hab );

    delete docViewer;
    delete indexWin;
    // must be freed _before_ plugin manager
    delete doc;
    // must be freed _after_ document
    delete pluginMan;

    delete findDlg;

    return 0;
}

