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


#define INCL_WIN
#define INCL_DOS
#include <os2.h>

#include <string>
#include <stdio.h>
#include <process.h>

#include <ludoc.xh>

#include "Lucide.h"
#include "pluginman.h"
#include "pluginViewDlg.h"
#include "fontsInfoDlg.h"
#include "docInfoDlg.h"
#include "findDlg.h"
#include "progressDlg.h"
#include "docViewer.h"
#include "indexWindow.h"
#include "luutils.h"
#include "tb_spl.h"
#include "Lucide_res.h"
#include "messages.h"


#define ID_SPLITTER 1

const char *appName    = "Lucide";
const char *appVersion = VERSION;
const char *fwp        = "FrameWindowPos";
const char *lvd        = "LastViewedDir";
const char *splpos     = "SplitterPos";
const char *showind    = "ShowIndex";


HWND createToolbar( HWND hwnd );
void AboutBox( HWND hWndFrame );

HAB   hab            = NULLHANDLE;
HWND  hWndFrame      = NULLHANDLE;
HWND  hWndMenu       = NULLHANDLE;
HWND  hToolBar       = NULLHANDLE;
HWND  hVertSplitter  = NULLHANDLE;
HWND  hFrameSysmenu  = NULLHANDLE;
HWND  hFrameTitlebar = NULLHANDLE;
HWND  hFrameMinMax   = NULLHANDLE;

Environment    *ev        = somGetGlobalEnvironment();
LuDocument     *doc       = NULL;
PluginManager  *pluginMan = NULL;
DocumentViewer *docViewer = NULL;
IndexWindow    *indexWin  = NULL;
FindDlg        *findDlg   = NULL;
char           *title     = NULL;


bool  Lucide::dontSwitchPage = false;
SHORT Lucide::splitterPos    = 100;
bool  Lucide::showIndex      = true;
bool  Lucide::isFullscreen   = false;
LuWindowPos Lucide::winPos   = {0};


PFNWP pOldSplProc;

void Lucide::enableCopy( bool enable )
{
    WinEnableMenuItem( hWndMenu, CM_COPY, enable );
}

void Lucide::setOfPages( long pages )
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

void Lucide::enableZoomMenus()
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


void Lucide::setZoomChecks( SHORT cmd, SHORT cbind, double zoom )
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
        //WinEnableMenuItem( hWndMenu, CM_NAVPANE, FALSE );
        //WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_NAVPANE), (MPARAM)FALSE );
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
    checkMenus();
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


// static data for asynch loading document
ProgressDlg *Lucide::loadProgressDlg       = NULL;
char         Lucide::docName[ CCHMAXPATH ] = "";
bool         Lucide::docLoaded             = false;;
char        *Lucide::loadError             = NULL;

void Lucide::loadthread( void *p )
{
    HAB thab = WinInitialize( 0 );
    HMQ thmq = WinCreateMsgQueue( thab, 0 );

    docLoaded = doc->loadFile( ev, docName, NULL, &loadError );
    loadProgressDlg->hide();

    WinDestroyMsgQueue( thmq );
    WinTerminate( thab );
    _endthread();
}

void Lucide::loadDocument( const char *fn )
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
        // test if extension supported and then close previous opened document
        if ( pluginMan->createDocumentForExt( ext + 1, true ) == NULL )
        {
            WinMessageBox( HWND_DESKTOP, hWndFrame, msg,
                           NULL, 0, MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
        }
        else
        {
            docViewer->close();
            delete doc;
            doc = NULL;
            WinSetWindowText( hWndFrame, title );

            doc = pluginMan->createDocumentForExt( ext + 1, false );
            if ( doc == NULL ) {
                WinMessageBox( HWND_DESKTOP, hWndFrame, msg,
                               NULL, 0, MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
            }
            else
            {
                strcpy( docName, fn );
                docLoaded = false;;
                loadError = NULL;

#if 0
                loadProgressDlg = new ProgressDlg( hWndFrame );
                loadProgressDlg->setText( "Loading document, please wait..." );
                loadProgressDlg->show( loadthread, NULL ); // doc will be loaded
                delete loadProgressDlg;
#else
                docLoaded = doc->loadFile( ev, docName, NULL, &loadError );
#endif

                if ( docLoaded )
                {
                    char *t = new char[ 2048 ];
                    char _fn[ _MAX_NAME ];
                    char _ex[ _MAX_EXT ];
                    _splitpath( fn, NULL, NULL, _fn, _ex );
                    strcpy( t, _fn );
                    strcat( t, _ex );
                    strcat( t, " - " );
                    strcat( t, title );
                    WinSetWindowText( hWndFrame, t );
                    delete t;
                    setDocument( doc );
                }
                else
                {
                    if ( loadError == NULL )
                    {
                        char *m = newstrdupL( MSGS_FILE_LOAD_ERROR );
                        WinMessageBox( HWND_DESKTOP, hWndFrame, m,
                                       NULL, 0, MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
                        delete m;
                    }
                    else
                    {
                        WinMessageBox( HWND_DESKTOP, hWndFrame, loadError,
                                       NULL, 0, MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
                        SOMFree( loadError );
                    }

                    delete doc;
                    doc = NULL;
                }
            }

        }

    }
    delete msg;
}

void Lucide::openDocument()
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

void Lucide::checkNavpane()
{
    if ( Lucide::showIndex )
    {
        WinSendMsg( hWndMenu, MM_SETITEMATTR, MPFROM2SHORT( CM_NAVPANE, TRUE ),
                MPFROM2SHORT( MIA_CHECKED, MIA_CHECKED ) );
        WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT( CM_NAVPANE ), (MPARAM)TRUE );
    }
    else
    {
        WinSendMsg( hWndMenu, MM_SETITEMATTR, MPFROM2SHORT( CM_NAVPANE, TRUE ),
                MPFROM2SHORT( MIA_CHECKED, FALSE ) );
        WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT( CM_NAVPANE ), (MPARAM)FALSE );
    }
}


void Lucide::toggleFullscreen()
{
    ULONG ulFrameStyle = WinQueryWindowULong( hWndFrame, QWL_STYLE );

    if ( isFullscreen )
    {
        WinSetParent( hFrameSysmenu,  hWndFrame, FALSE );
        WinSetParent( hFrameTitlebar, hWndFrame, FALSE );
        WinSetParent( hFrameMinMax,   hWndFrame, FALSE );
        ulFrameStyle |= FS_SIZEBORDER;
    }
    else
    {
        WinQueryWindowPos( hWndFrame, &winPos.Swp );
        winPos.XRestore  = WinQueryWindowUShort( hWndFrame, QWS_XRESTORE );
        winPos.YRestore  = WinQueryWindowUShort( hWndFrame, QWS_YRESTORE );
        winPos.CXRestore = WinQueryWindowUShort( hWndFrame, QWS_CXRESTORE );
        winPos.CYRestore = WinQueryWindowUShort( hWndFrame, QWS_CYRESTORE );
        winPos.XMinimize = WinQueryWindowUShort( hWndFrame, QWS_XMINIMIZE );
        winPos.YMinimize = WinQueryWindowUShort( hWndFrame, QWS_YMINIMIZE );

        WinSetParent( hFrameSysmenu,  HWND_OBJECT, FALSE );
        WinSetParent( hFrameTitlebar, HWND_OBJECT, FALSE );
        WinSetParent( hFrameMinMax,   HWND_OBJECT, FALSE );
        ulFrameStyle &= ~FS_SIZEBORDER;
    }

    WinSetWindowULong( hWndFrame, QWL_STYLE, ulFrameStyle );
    WinSendMsg( hWndFrame, WM_UPDATEFRAME,
                MPFROMLONG( FCF_TITLEBAR | FCF_SIZEBORDER | FCF_SYSMENU | FCF_MINMAX ),
                MPVOID );

    if ( isFullscreen )
    {
        WinSetWindowUShort( hWndFrame, QWS_XRESTORE,  winPos.XRestore );
        WinSetWindowUShort( hWndFrame, QWS_YRESTORE,  winPos.YRestore );
        WinSetWindowUShort( hWndFrame, QWS_CXRESTORE, winPos.CXRestore );
        WinSetWindowUShort( hWndFrame, QWS_CYRESTORE, winPos.CYRestore );
        WinSetWindowUShort( hWndFrame, QWS_XMINIMIZE, winPos.XMinimize );
        WinSetWindowUShort( hWndFrame, QWS_YMINIMIZE, winPos.YMinimize );
        ULONG swpopt = SWP_MOVE | SWP_SIZE | SWP_SHOW;
        WinSetWindowPos( hWndFrame, NULLHANDLE,
                         winPos.Swp.x, winPos.Swp.y, winPos.Swp.cx, winPos.Swp.cy,
                         swpopt );
    }
    else
    {
        WinSetWindowPos( hWndFrame, HWND_TOP, 0, 0,
                         WinQuerySysValue( HWND_DESKTOP, SV_CXFULLSCREEN ) - 1,
                         WinQuerySysValue( HWND_DESKTOP, SV_CYFULLSCREEN ) +
                            WinQuerySysValue( HWND_DESKTOP, SV_CYTITLEBAR ),
                         SWP_SIZE | SWP_MOVE | SWP_ZORDER );
    }

    isFullscreen = !isFullscreen;
}

static MRESULT EXPENTRY splProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch ( msg )
    {
        case WM_CONTROL:
        {
            if ( ( SHORT1FROMMP( mp1 ) == ID_SPLITTER ) &&
                 ( SHORT2FROMMP( mp1 ) == SBN_POSITIONCHANGED ) )
            {
                SHORT pos = SHORT1FROMMP( mp2 );
                if ( pos > 0 ) {
                    Lucide::splitterPos = pos;
                    Lucide::showIndex = true;
                }
                else {
                    Lucide::showIndex = false;
                }
                Lucide::checkNavpane();
            }
        }
        break;

        case WM_COMMAND:
        {
            switch ( SHORT1FROMMP(mp1) )
            {
                case CM_OPEN:
                    Lucide::openDocument();
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

                case CM_NAVPANE:
                    {
                        Lucide::showIndex = !Lucide::showIndex;
                        Lucide::checkNavpane();
                        WinSendMsg( hVertSplitter, SBM_SETSPLITTERPOS,
                            MPFROMSHORT( Lucide::showIndex ? Lucide::splitterPos : 0 ), MPVOID );
                    }
                    return (MRESULT)FALSE;

                case CM_FULLSCREEN:
                    Lucide::toggleFullscreen();
                    return (MRESULT)FALSE;

                case CM_PRODINFO:
                    AboutBox( hWndFrame );
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
#ifdef __TEST__
    PPIB pib;
    PTIB tib;
    DosGetInfoBlocks(&tib, &pib);
    pib->pib_ultype = 3;
#endif

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
    title = newstrdupL( MSGS_MAIN_WIN_TITLE );
    hWndFrame = WinCreateStdWindow( HWND_DESKTOP, 0, &ulFrameFlags, NULL, title,
                                    WS_SYNCPAINT|WS_VISIBLE, NULLHANDLE, 100, NULL );
    hFrameSysmenu  = WinWindowFromID( hWndFrame, FID_SYSMENU );
    hFrameTitlebar = WinWindowFromID( hWndFrame, FID_TITLEBAR );
    hFrameMinMax   = WinWindowFromID( hWndFrame, FID_MINMAX );
    WinSetAccelTable( hab, WinLoadAccelTable( hab, NULLHANDLE, IDA_MAINACCEL ), hWndFrame );
    hWndMenu = WinLoadMenu( hWndFrame, NULLHANDLE, IDM_MAINMENU );
    localizeMenu( hWndMenu );
    WinSetWindowUShort( hWndMenu, QWS_ID, FID_MENU );

    // Vertical splitter and his windows - Index and Document view
    hVertSplitter = WinCreateWindow( hWndFrame, WC_ER_SPLITTER, "",
                                     WS_VISIBLE | SBS_VSPLIT,
                                     0, 0, 0, 0, hWndFrame, HWND_TOP,
                                     ID_SPLITTER, NULL, NULL );

    indexWin = new IndexWindow( hab, hWndFrame );

    DocumentViewer::registerClass( hab );

    docViewer = new DocumentViewer( hab, hWndFrame );

    WinSendMsg( hVertSplitter, SBM_SETWINDOWS,
                MPFROMHWND( indexWin->getHWND() ), MPFROMHWND( docViewer->getHWND() ) );
    Lucide::splitterPos = PrfQueryProfileInt( HINI_USERPROFILE, appName, splpos, Lucide::splitterPos );
    Lucide::showIndex = PrfQueryProfileInt( HINI_USERPROFILE, appName, showind, Lucide::showIndex );
    WinSendMsg( hVertSplitter, SBM_SETSPLITTERPOS,
                MPFROMSHORT( Lucide::showIndex ? Lucide::splitterPos : 0 ), MPVOID );

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

    // Показать окно программы
    if ( !PMRestoreWindowPos( NULL, appName, fwp, hWndFrame,
                              TRUE, TRUE, FALSE, FALSE, FALSE ) ) {
        WinSetWindowPos( hWndFrame, HWND_TOP, 100, 100, 630, 400,
                         SWP_SIZE | SWP_MOVE | SWP_SHOW | SWP_ACTIVATE );
    }

    if ( argc > 1 ) {
        Lucide::loadDocument( argv[1] );
    }

    Lucide::checkNavpane();

    // Messsage loop
    while ( WinGetMsg( hab, &qmsg, 0, 0, 0 ) ) {
        WinDispatchMsg( hab, &qmsg );
    }

    if ( WinIsWindow( hab, hWndFrame ) )
    {
        char valbuf[ 3 ] = "";
        PrfWriteProfileString( HINI_USERPROFILE, appName, splpos,
                               itoa( Lucide::splitterPos, valbuf, 10 ) );
        PrfWriteProfileString( HINI_USERPROFILE, appName, showind,
                               itoa( Lucide::showIndex, valbuf, 10 ) );
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
    delete title;

    return 0;
}

