/* ***** BEGIN47 LICENSE BLOCK *****
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
#define INCL_SPL
#define INCL_SPLDOSPRINT
#include "os2all.h"

#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#if defined(__WATCOM__)
#include <dos.h>
#define find_t_name(find_t) find_t.name
#else
#include <unistd.h>
#include <emx/syscalls.h>
typedef _find find_t;
#define find_t_name(find_t) find_t.szName
#define _dos_findfirst __findfirst
#define _dos_findnext __findnext
#define _dos_findclose(a) do {} while(0)
#endif

#include <ludoc.xh>

#include "Lucide.h"
#include "pluginman.h"
#include "pluginViewDlg.h"
#include "fontsInfoDlg.h"
#include "docInfoDlg.h"
#include "findDlg.h"
#include "printDlg.h"
#include "progressDlg.h"
#include "settingsDlg.h"
#include "passwordDlg.h"
#include "docViewer.h"
#include "indexWindow.h"
#include "recent.h"
#include "lusettings.h"
#include "luutils.h"
#include "tb_spl.h"
#include "Lucide_res.h"
#include "messages.h"

//#define INCL_EXCEPTQ_CLASS
//#define INCL_LOADEXCEPTQ
//#include "exceptq.h"

#define ID_SPLITTER 1

const char *appName    = "Lucide";
const char *appVersion = VERSION;
const char *appBuild   = BUILD;
const char *appDate    = VERSIONDATE;
const char *prfFwp     = "FrameWindowPos";
const char *prfLvd     = "LastViewedDir";
const char *prfSplpos  = "SplitterPos";
const char *prfShowind = "ShowIndex";
const char *prfFullscreen   = "FullScreen";
const char *prfPresentation = "Presentation";

HWND createToolbar( HWND hwnd );
void AboutBox( HWND hWndFrame );
void initPipeMon( HWND hWndFrame );
void unInitPipeMon();
HWND LcdFileDlg( HWND hwndP, HWND hwndO, FILEDLG *pfild );


HAB   hab            = NULLHANDLE;
HWND  hWndFrame      = NULLHANDLE;
HWND  hWndMenu       = NULLHANDLE;
HWND  hToolBar       = NULLHANDLE;
HWND  hVertSplitter  = NULLHANDLE;
HWND  hHorizSplitter = NULLHANDLE;
HWND  hFrameSysmenu  = NULLHANDLE;
HWND  hFrameTitlebar = NULLHANDLE;
HWND  hFrameMinMax   = NULLHANDLE;
HELPINIT hini;
HINI hinilucideprofile;

Environment    *ev        = somGetGlobalEnvironment();
LuDocument     *doc       = NULL;
PluginManager  *pluginMan = NULL;
DocumentViewer *docViewer = NULL;
IndexWindow    *indexWin  = NULL;
FindDlg        *findDlg   = NULL;
LuSettings     *settings  = NULL;
RecentFiles    *recent    = NULL;
char           *title     = NULL;


bool         Lucide::dontSwitchPage                = false;
SHORT        Lucide::splitterPos                   = 100;
bool         Lucide::showIndex                     = true;
bool         Lucide::isFullscreen                  = false;
bool         Lucide::isPresentation                = false;
bool         Lucide::Thumbnail                     = true;
LuWindowPos  Lucide::winPos                        = {0};
char         Lucide::docFullName[ CCHMAXPATH ]     = "";
char         Lucide::docFileName[ CCHMAXPATHCOMP ] = "";
char         Lucide::docDirName[ CCHMAXPATHCOMP ]  = "";
char        *Lucide::password                      = NULL;
ActiveWindow Lucide::activeWindow                  = AwView;
// static data for asynch loading document
ProgressDlg *Lucide::loadProgressDlg               = NULL;
bool         Lucide::docLoaded                     = false;;
char        *Lucide::loadError                     = NULL;
long         Lucide::loadErrorCode                 = LU_LDERR_NO_ERROR;
char        *Lucide::thumbnailData                 = NULL;
int          Lucide::thumbnailDataLen              = 0;
HWND         Lucide::hwndHelp                      = NULLHANDLE;

// List of files in current directory
static std::vector<std::string> fileList;
static std::vector<std::string>::const_iterator fileListIterator;

HMODULE _hmod = NULLHANDLE;

unsigned APIENTRY LibMain( unsigned hmod, unsigned termination )
{
    if ( termination ) {
        // DLL is detaching from process
    } else {
        // DLL is attaching to process
        _hmod = hmod;
    }
    return( 1 );
}

#if !defined(__WATCOM__)
extern "C" unsigned long _System _DLL_InitTerm( unsigned long mod_handle,
                                                unsigned long flag )
{
    int _CRT_init();
    void _CRT_term();
    void __ctordtorInit();
    void __ctordtorTerm();

    switch ( flag ) {
        case 0:
            if ( _CRT_init() != 0 )
                return 0;
            __ctordtorInit();
            return LibMain( mod_handle, flag );
        case 1:
            __ctordtorTerm();
            _CRT_term ();
            return LibMain( mod_handle, flag );
        default:
            return 0;
    }
}
#endif


// stolen from xWorkplace sources
static
APIRET my_DosQueryProcAddr(PCSZ pcszModuleName, ULONG ulOrdinal, PFN *ppfn)
{
    HMODULE hmod = NULL;
    APIRET rc = 0;
    if (!(rc = DosQueryModuleHandle( (PSZ)pcszModuleName, &hmod))) {
        if ((rc = DosQueryProcAddr( hmod, ulOrdinal, NULL, ppfn))) {
            // the CP programming guide and reference says use
            // DosLoadModule if DosQueryProcAddr fails with this error
            if (rc == ERROR_INVALID_HANDLE) {
                if (!(rc = DosLoadModule(NULL, 0, (PSZ) pcszModuleName,
                                         &hmod))) {
                    rc = DosQueryProcAddr(hmod, ulOrdinal, NULL, ppfn);
                }
            }
        }
    }
    return rc;
}


PFNWP pOldFrameProc = NULL;
PFNWP pOldSplProc   = NULL;

void Lucide::enableCopy( bool enable )
{
    WinEnableMenuItem( hWndMenu, CM_COPY, enable );
}

void Lucide::setOfPages( long pages )
{
    char pgnum[ 32 ];

    // set current page
    WinSendDlgItemMsg( hToolBar, TBID_PAGENUM, SPBM_SETLIMITS,
                      MPFROMLONG( pages ), MPFROMLONG( 1 ) );

    // set of pages
    char *pgfrm = newstrdupL( TB_PAGENUM );
    snprintf( pgnum, sizeof( pgnum ), pgfrm, pages );
    delete pgfrm;
    WinSetDlgItemText( hToolBar, TBID_OFPAGES, pgnum );

}

void Lucide::checkNavigationMenus()
{
    WinEnableMenuItem( hWndMenu, CM_GOTOPAGE, TRUE );
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
    bool chkback = docViewer->getPreviousPage() >= 0;
    WinEnableMenuItem( hWndMenu, CM_BACKNAV, chkback );

    // set actual page
    bool tmp = dontSwitchPage;
    dontSwitchPage = true;
    char pgnum[32];
    WinSendDlgItemMsg( hToolBar, TBID_PAGENUM, SPBM_SETCURRENTVALUE,
                               MPFROMLONG( docViewer->getCurrentPage() + 1 ), MPVOID );
    dontSwitchPage = tmp;
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
    WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_ZOOM_IN_OUT), (MPARAM)scalable );
    WinEnableMenuItem( hWndMenu, CM_ZOOM_IN, scalable );
    WinEnableMenuItem( hWndMenu, CM_ZOOM_OUT, scalable );
    WinEnableControl( hToolBar, TBID_ZOOM, scalable );
    BOOL rotable = doc->isRotable( ev );
    WinEnableMenuItem( hWndMenu, CM_ROTATE90CW, rotable );
    WinEnableMenuItem( hWndMenu, CM_ROTATE90CCW, rotable );
}


void Lucide::setZoomChecks( SHORT cmd, SHORT cbind, double zoom )
{
    if ( cmd != -1 )
    {
        WinCheckMenuItem( hWndMenu, cmd, TRUE );
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

    WinCheckMenuItem( hWndMenu, CM_FITWINDOW, FALSE );
    WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT(CM_FITWINDOW), (MPARAM)FALSE );
    WinCheckMenuItem( hWndMenu, CM_ACTSIZE, FALSE );
    WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT(CM_ACTSIZE), (MPARAM)FALSE );
    WinCheckMenuItem( hWndMenu, CM_FITWIDTH, FALSE );
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

void Lucide::checkMenus( bool initial )
{
    if ( initial )
    {
        // pre-set "Actual size"
        setZoomChecks( CM_ACTSIZE, 0, 0 );
    }

    if ( doc == NULL )
    {
        if ( initial )
        {
            // "single page" mode by default
            WinCheckMenuItem( hWndMenu, CM_SINGLEPAGE, TRUE );
        }

        WinEnableMenuItem( hWndMenu, CM_BACK, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_BACK), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_SAVE, FALSE );
        WinEnableMenuItem( hWndMenu, CM_SAVEAS, FALSE );
        WinEnableMenuItem( hWndMenu, CM_CLOSE, FALSE );
        WinEnableMenuItem( hWndMenu, CM_PRINT, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_PRINT), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_DOCINFO, FALSE );
        WinEnableMenuItem( hWndMenu, CM_FONTSINFO, FALSE );

        WinEnableMenuItem( hWndMenu, CM_COPY, FALSE );
        WinEnableMenuItem( hWndMenu, CM_SELECTALL, FALSE );
        WinEnableMenuItem( hWndMenu, CM_FIND, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FIND), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_FINDAGAIN, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FINDAGAIN), (MPARAM)FALSE );

        WinEnableMenuItem( hWndMenu, CM_FIRSTPAGE, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FIRSTPAGE), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_PREVPAGE, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_PREVPAGE), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_NEXTPAGE, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_NEXTPAGE), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_LASTPAGE, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_LASTPAGE), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_GOTOPAGE, FALSE );
        WinEnableMenuItem( hWndMenu, CM_BACKNAV, FALSE );

        WinEnableMenuItem( hWndMenu, CM_FITWINDOW, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FITWINDOW), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_ACTSIZE, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_ACTSIZE), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_FITWIDTH, FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FITWIDTH), (MPARAM)FALSE );
        WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_ZOOM_IN_OUT), (MPARAM)FALSE );
        WinEnableMenuItem( hWndMenu, CM_ZOOM_IN, FALSE );
        WinEnableMenuItem( hWndMenu, CM_ZOOM_OUT, FALSE );
        WinEnableControl( hToolBar, TBID_ZOOM, FALSE );

        WinEnableMenuItem( hWndMenu, CM_ROTATE90CW, FALSE );
        WinEnableMenuItem( hWndMenu, CM_ROTATE90CCW, FALSE );
        WinEnableMenuItem( hWndMenu, CM_SINGLEPAGE, FALSE );
        WinEnableMenuItem( hWndMenu, CM_CONTINUOUS, FALSE );

        setOfPages( 0 );
        return;
    }


    checkNavigationMenus();
    enableZoomMenus();
    checkZoomMenus();

    WinEnableMenuItem( hWndMenu, CM_PRINT, TRUE );
    WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_PRINT), (MPARAM)TRUE );
    bool chkback = docViewer->getPreviousPage() >= 0;
    WinEnableMenuItem( hWndMenu, CM_BACK, chkback );
    WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_BACK), (MPARAM)chkback );
    WinEnableMenuItem( hWndMenu, CM_SAVE, doc->isSaveable( ev ) &&
                      doc->isHaveInputFields( ev ));
    WinEnableMenuItem( hWndMenu, CM_SAVEAS, doc->isSaveable( ev ) );
    WinEnableMenuItem( hWndMenu, CM_CLOSE, TRUE );
    setOfPages( doc->getPageCount( ev ) );
    WinEnableMenuItem( hWndMenu, CM_FONTSINFO, doc->isHaveFontInfo( ev ) );
    WinEnableMenuItem( hWndMenu, CM_DOCINFO, TRUE );

    BOOL haveText = doc->isHaveText( ev );
    WinEnableMenuItem( hWndMenu, CM_FIND, haveText );
    WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FIND), (MPARAM)haveText );
    WinEnableMenuItem( hWndMenu, CM_SELECTALL, haveText );

    WinEnableMenuItem( hWndMenu, CM_SINGLEPAGE, TRUE );
    WinEnableMenuItem( hWndMenu, CM_CONTINUOUS, TRUE );
}

void Lucide::goToPage( long page )
{
    if ( docViewer != NULL ) {
       if (page > (doc->getPageCount(ev) -1)) {
                page = doc->getPageCount(ev) -1;
       }
        docViewer->goToPage( page );
    }
}

long Lucide::pageCount( void )
{
    if ( doc != NULL ) {
        return doc->getPageCount( ev );
    } else {
        return 0;
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
    checkMenus( false );
}

void Lucide::setPageLayout( PgLayout layout )
{
    if ( layout == SinglePage ) {
        WinCheckMenuItem( hWndMenu, CM_SINGLEPAGE, TRUE );
        WinCheckMenuItem( hWndMenu, CM_CONTINUOUS, FALSE );
    }
    else {
        WinCheckMenuItem( hWndMenu, CM_SINGLEPAGE, FALSE );
        WinCheckMenuItem( hWndMenu, CM_CONTINUOUS, TRUE );
    }

    docViewer->setPageLayout( layout );
}


bool Lucide::closeDocument( bool force )
{
    if ( doc != NULL ) {
        if ( !docViewer->close( force ) && !force )
            return false;
        WinSendDlgItemMsg( hToolBar, TBID_PAGENUM, SPBM_SETLIMITS,
                      MPFROMLONG( 0 ), MPFROMLONG( 0 ) );
        delete doc;
        doc = NULL;
        WinSetWindowText( hWndFrame, title );
        checkMenus( false );
    }

    if ( thumbnailData != NULL ) {
        writeThumbnail( docFullName );
        delete thumbnailData;
        thumbnailData = NULL;
        thumbnailDataLen = 0;
    }

    // clear the index
    indexWin->clear( NULL );

    return true;
}

void Lucide::loadthread( void* p)
{
    HAB thab = WinInitialize( 0 );
    HMQ thmq = WinCreateMsgQueue( thab, 0 );

    docLoaded = doc->loadFile( ev, docFullName, password, &loadErrorCode,
                              &loadError );

    //From FM2 valid.c 339
    EASIZEBUF easize	= {0};
    ULONG   ulDataLen	= sizeof(EASIZEBUF);
    ULONG   ulParmLen	= 0;
    CHAR szPath[4] = {0};

    strncpy( szPath, docFullName, 3);
    DosFSCtl(&easize, sizeof(EASIZEBUF), &ulDataLen, NULL, ulParmLen,
             &ulParmLen, FSCTL_MAX_EASIZE, szPath, -1, FSCTL_PATHNAME);
    //End FM2 code
    
    if ( !p && docLoaded && !password  && Thumbnail && easize.cbMaxEASize > 0 &&
        doc->isCreateFileThumbnail( ev ) && isThumbNeeded( docFullName ) &&
       doc->isScalable( ev )) {
        loadProgressDlg->setText( getLocalizedString( MSGS_CREATING_THUMBNAIL ).c_str() );
        if (!createThumbnail( doc ))
        {
            docLoaded = FALSE;
        }
    }
    else if ( docLoaded && doc->getPageCount( ev ) > 0 ) {
        double width = 0, height = 0;
        doc->getPageSize( ev, 0, &width, &height );
        if ( width <= 0.00001 || height <= 0.00001 )
        {
            docLoaded = FALSE;
        }
    }
    else if (loadErrorCode != LU_LDERR_ENCRYPTED) // encrypted must loop to get password
    {
        docLoaded = FALSE;
    }
    if (!p) {
    ULONG sz = sizeof( bool );
    PrfQueryProfileData( hinilucideprofile, appName, "thumbnail", &Thumbnail, &sz );
    loadProgressDlg->hide();
    }

    WinDestroyMsgQueue( thmq );
    WinTerminate( thab );
    _endthread();
}

void Lucide::loadDocument( const char *fn, bool saveme )
{
    // test if file supported and then close previous opened document
    if ( pluginMan->createDocumentForFile( fn, true ) == NULL )
    {
        char *msg = newstrdupL( MSGS_NO_SUIT_PLUG );
        WinMessageBox( HWND_DESKTOP, hWndFrame, msg,
                       NULL, 0, MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
        delete msg;
    }
    else
    {
        if ( !closeDocument() )
            return;

        doc = pluginMan->createDocumentForFile( fn, false );
        if ( doc == NULL )
        {
            char *msg = newstrdupL( MSGS_NO_SUIT_PLUG );
            WinMessageBox( HWND_DESKTOP, hWndFrame, msg,
                           NULL, 0, MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
            delete msg;
        }
        else
        {
            _fullpath( docFullName, fn, CCHMAXPATH );

            if ( password != NULL ) {
                delete password;
                password = NULL;
            }
            bool once = true;
            while ( once || ( password != NULL ) )
            {
                once = false;
                docLoaded = false;
                loadError = NULL;

                // Load document asynchronously
                if ( saveme ) {
                    _beginthread( loadthread, NULL, 262144,(void *) 1 );
                    DosSleep(10);
                }
                else {
                    loadProgressDlg = new ProgressDlg( hWndFrame );
                    char *ldmsg = newstrdupL( MSGS_LOADING_DOCUMENT );
                    loadProgressDlg->setText( ldmsg );
                    delete ldmsg;
                    loadProgressDlg->show( loadthread, NULL ); // doc will be loaded
                    delete loadProgressDlg;
                }
                

                if ( password != NULL ) {
                    delete password;
                    password = NULL;
                }
                if ( docLoaded )
                {
                    char *t = new char[ 2048 ];
                    char _dr[ _MAX_DRIVE ];
                    char _di[ _MAX_DIR ];
                    char _fn[ _MAX_FNAME ];
                    char _ex[ _MAX_EXT ];
                    _splitpath( docFullName, _dr, _di, _fn, _ex );
                    strcpy( docDirName, _dr );
                    strcat( docDirName, _di );
                    strcpy( docFileName, _fn );
                    strcat( docFileName, _ex );
                    snprintf( t, 2048, "%s - %s", docFileName, title );
                    WinSetWindowText( hWndFrame, t );
                    delete t;
                    recent->addFile( docFullName );
                    setDocument( doc );
                }
                else
                {
                    if ( loadErrorCode == LU_LDERR_NO_ERROR )
                    {
                        char *m = newstrdupL( MSGS_FILE_LOAD_ERROR );
                        WinMessageBox( HWND_DESKTOP, hWndFrame, m,
                                      NULL, 0,
                                      MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
                        delete m;
                    }
                    else
                    {
                        std::string msgTempl = getLocalizedString( MSGS_LDERR );

                        const int errmsgLen = 1024;
                        char *errmsg = new char[ errmsgLen ];
                        memset( errmsg, 0, errmsgLen );

                        if ( loadErrorCode == LU_LDERR_CUSTOM )
                        {
                            snprintf( errmsg, errmsgLen, msgTempl.c_str(), loadError );
                            SOMFree( loadError );
                        }
                        else
                        {
                            const char *lmsg = NULL;
                            switch ( loadErrorCode )
                            {
                                case LU_LDERR_OUT_OF_MEMORY:
                                    lmsg = MSGS_LDERR_OUT_OF_MEMORY;
                                    break;
                                case LU_LDERR_OPEN_ERROR:
                                    lmsg = MSGS_LDERR_OPEN_ERROR;
                                    break;
                                case LU_LDERR_READ_ERROR:
                                    lmsg = MSGS_LDERR_READ_ERROR;
                                    break;
                                case LU_LDERR_DAMAGED:
                                    lmsg = MSGS_LDERR_DAMAGED;
                                    break;
                                case LU_LDERR_WRONG_FORMAT:
                                    lmsg = MSGS_LDERR_WRONG_FORMAT;
                                    break;
                                case LU_LDERR_ENCRYPTED:
                                    {
                                        lmsg = MSGS_LDERR_ENCRYPTED;

                                        PasswordDlg *pd = new PasswordDlg( hWndFrame );
                                        if ( pd->showDialog() == DID_OK ) {
                                            password = newstrdup( pd->getPassword() );
                                        }
                                        delete pd;
                                    }
                                    break;
                            }

                            if ( lmsg != NULL ) {
                                snprintf( errmsg, errmsgLen, msgTempl.c_str(),
                                          getLocalizedString( lmsg ).c_str() );
                            }
                        }

                        if ( password == NULL )
                        {
                            WinMessageBox( HWND_DESKTOP, hWndFrame, errmsg, NULL, 0,
                                           MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
                        }
                        delete[] errmsg;
                    } // ( loadErrorCode == LU_LDERR_NO_ERROR )

                    if ( doc && !password ) {
                        delete doc;
                        doc = NULL;
                    }
                } // ( docLoaded )
            } // while ( once || ( password != NULL ) )
        } // ( doc == NULL )
    } // ( pluginMan->createDocumentForFile( fn, true ) == NULL )

    loadFileList();
}

void Lucide::readMask( const char *mask )
{
    char *buf = new char[ CCHMAXPATH ];
    strcpy( buf, docFullName );
    char *r = buf + strlen( buf );
    while ( r >= buf && *r != '\\' && *r != '/')
        --r;
    if ( r >= buf )
    {
        *( r + 1 ) = 0;
        strcat( buf, mask );

        find_t ffblk;
        unsigned done = _dos_findfirst( buf, _A_RDONLY | _A_NORMAL, &ffblk );
        while ( done == 0 )
        {
            fileList.push_back( find_t_name( ffblk ) );
            done = _dos_findnext( &ffblk );
        }
        _dos_findclose( &ffblk );

    }
    delete[] buf;
}

// comparison, not case sensitive.
bool compare_nocase( const std::string &first, const std::string &second)
{
    // note: stricmp is locale aware in kLIBC
    return stricmp( first.c_str(), second.c_str() ) < 0;
}

void Lucide::loadFileList()
{
    fileList.clear();

    char *exts = newstrdup( pluginMan->getExtsMask().c_str() );

    char *p = strtok( exts, ";" );
    while ( p != NULL )
    {
        readMask( p );
        p = strtok( NULL, ";" );
    }
    delete exts;

    std::sort( fileList.begin(), fileList.end(), compare_nocase );
    fileListIterator = std::find( fileList.begin(), fileList.end(), docFileName );
}

void Lucide::openDocument()
{
    PFILEDLG fd = new FILEDLG;
    memset( fd, 0, sizeof( FILEDLG ) );
    fd->cbSize = sizeof( FILEDLG );
    fd->fl = FDS_CENTER | FDS_OPEN_DIALOG;
    PrfQueryProfileString( hinilucideprofile, appName, prfLvd, "",
                           fd->szFullFile, sizeof( fd->szFullFile ) );
    LcdFileDlg( HWND_DESKTOP, hWndFrame, fd );
    if ( fd->lReturn == DID_OK )
    {
        char drv[ _MAX_DRIVE ] = "";
        char dir[ _MAX_PATH ] = "";
        char buf[ _MAX_PATH ] = "";
        _splitpath( fd->szFullFile, drv, dir, NULL, NULL );
        _makepath( buf, drv, dir, NULL, NULL );
        PrfWriteProfileString( hinilucideprofile, appName, prfLvd, buf );

        loadDocument( fd->szFullFile );
    }
    delete fd;
}
#if 1
bool Lucide::saveDocument()
{
    bool saved = false;
    bool loaded = false;
    int buflen = 0;
    short vposition;
    short hposition;
    double zoom;
    long rotation;
    long page;
    char dirbuf[ CCHMAXPATH ];
    char tempbuf[ CCHMAXPATH ];

    if ( getenv( "TEMP" ))
        strcpy(dirbuf,  getenv( "TEMP" ));
    else if ( getenv( "TMP" ))
        strcpy(dirbuf,  getenv( "TMP" ));
    else if ( getenv( "TMPDIR" ))
        strcpy(dirbuf,  getenv( "TMPDIR" ));
    else
    {
        char *m = newstrdupL( MSGS_NO_TEMP_DIR_ERROR );
        WinMessageBox( HWND_DESKTOP, hWndFrame, m, NULL,
                       0, MB_OK | MB_ERROR | MB_MOVEABLE );
        delete m;
    }
    buflen = strlen(dirbuf);
    if ((dirbuf[buflen -1] != '\\') && (dirbuf[buflen -1] != '/') &&
        (buflen < sizeof(dirbuf)))
    {
       strcat(dirbuf, "\\");
    }

    char fil[ _MAX_FNAME ] = "";
    char ext[ _MAX_EXT ] = "";
    _splitpath( docFullName, NULL, NULL, fil, ext );
    strcat(dirbuf, fil);
    strcat(dirbuf, ext);
    strcpy(tempbuf, docFullName);
    if (!(saved = doc->saveAs( ev, dirbuf )))
    {
        char *m = newstrdupL( MSGS_TEMP_FILE_SAVE_ERROR );
        WinMessageBox( HWND_DESKTOP, hWndFrame, m, NULL,
                       0, MB_OK | MB_ERROR | MB_MOVEABLE );
        delete m;
        return saved;
    }
    else
    {
        WinShowWindow(docViewer->getFrameHWND(), false);
        WinShowWindow(docViewer->getViewHWND(), false);
        docViewer->resetModifiedState();
        rotation = docViewer->getRotation();
        zoom = docViewer->getZoom();
        vposition = docViewer->getVscrollPos();
        hposition = docViewer->getHscrollPos();
        page = docViewer->getCurrentPage();
        loadDocument( dirbuf, true );
    }
    if (!( saved = doc->saveAs( ev, tempbuf ) ) )
    {
        char *m = newstrdupL( MSGS_FILE_SAVE_ERROR );
        WinMessageBox( HWND_DESKTOP, hWndFrame, m, NULL,
                       0, MB_OK | MB_ERROR | MB_MOVEABLE );
        delete m;
    }
    else
    {
        loadDocument( tempbuf, true );
        docViewer->setZoom( zoom );
        docViewer->setRotation( rotation );
        goToPage( page );
        docViewer->vertScroll( docViewer->getViewHWND(),
                              MPFROM2SHORT( vposition, SB_SLIDERPOSITION ) );
        docViewer->horizScroll( docViewer->getViewHWND(),
                               MPFROM2SHORT( hposition, SB_SLIDERPOSITION ) );
    }
    unlink( dirbuf );
    docViewer->resetModifiedState();
    WinShowWindow(docViewer->getFrameHWND(), true);
    WinShowWindow(docViewer->getViewHWND(), true);
    return saved;
}
#endif
bool Lucide::saveDocumentAs()
{
    bool saved = false;
    int buflen = 0;

    char dirbuf[ CCHMAXPATH ];
    PFILEDLG fd = new FILEDLG;
    memset( fd, 0, sizeof( FILEDLG ) );
    fd->cbSize = sizeof( FILEDLG );
    fd->fl = FDS_CENTER | FDS_SAVEAS_DIALOG | FDS_ENABLEFILELB;
    PrfQueryProfileString( hinilucideprofile, appName, prfLvd, "",
                           dirbuf, sizeof( dirbuf ) );
    // it may be possible that the trailing \ is missing, so add it
    buflen = strlen(dirbuf);
    if ((dirbuf[buflen -1] != '\\') && (dirbuf[buflen -1] != '/') && (buflen < sizeof(dirbuf)))
    {
       strcat(dirbuf, "\\");
    }

    char fil[ _MAX_FNAME ] = "";
    char ext[ _MAX_EXT ] = "";
    _splitpath( docFullName, NULL, NULL, fil, ext );
    char filcopy[ _MAX_FNAME ] = "";
    snprintf( filcopy, sizeof( filcopy ),
              getLocalizedString( MSGS_FILE_COPY_SUFFIX ).c_str(), fil );
    snprintf( fd->szFullFile, sizeof( fd->szFullFile ),
              "%s%s%s", dirbuf, filcopy, ext );
    WinFileDlg( HWND_DESKTOP, hWndFrame, fd );
    if ( fd->lReturn == DID_OK )
    {
        bool doSave = true;
        if ( access( fd->szFullFile, F_OK ) == 0 )
        {
            char *t = newstrdupL( MSGS_WARNING );
            char *m = newstrdupL( MSGS_OVERWRITE_FILE );
            ULONG response = WinMessageBox( HWND_DESKTOP, hWndFrame, m, t,
                                            0, MB_YESNO | MB_WARNING | MB_MOVEABLE );
            delete m;
            delete t;

            doSave = ( response == MBID_YES );
        }

        if ( doSave )
        {
            // @todo poppler has troubles saving to the same file name
            // (some locking issues) so forbid it for now

           // we need to normalise the path
           strcpy(dirbuf, docFullName);
           for(buflen = 0; buflen < strlen(dirbuf); ++buflen)
           {
               if (dirbuf[buflen] == '/')
               {
                   dirbuf[buflen] = '\\';
               }
           }

            if ( ( saved = false, stricmp( dirbuf, fd->szFullFile ) == 0 ) ||
                 !( saved = doc->saveAs( ev, fd->szFullFile ) ) )
            {
                char *m = newstrdupL( MSGS_FILE_SAVE_ERROR );
                WinMessageBox( HWND_DESKTOP, hWndFrame, m, NULL,
                               0, MB_OK | MB_ERROR | MB_MOVEABLE );
                delete m;
            }
            else
            {
                if ( stricmp( docFullName, fd->szFullFile ) != 0 )
                    recent->addFile( fd->szFullFile );
                docViewer->resetModifiedState();
            }
        }
    }
    delete fd;
    return saved;
}

void Lucide::checkNavpane()
{
    if ( Lucide::showIndex ) {
        WinCheckMenuItem( hWndMenu, CM_NAVPANE, TRUE );
        WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT( CM_NAVPANE ), (MPARAM)TRUE );
    }
    else {
        WinCheckMenuItem( hWndMenu, CM_NAVPANE, FALSE );
        WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT( CM_NAVPANE ), (MPARAM)FALSE );
    }
}


void Lucide::toggleFullscreenEx( bool presentation, bool atStartup )
{
    enum TriState { NoChange, On, Off };
    TriState fullscreenState = NoChange;
    TriState presentationState = NoChange;

    if ( !presentation )
    {
        // fullscreen command issued
        if ( !isFullscreen )
        {
            if ( isPresentation ) {
                presentationState = Off;
                isPresentation = false;
            } else {
                fullscreenState = On;
            }
            isFullscreen = true;
        }
        else
        {
            if ( isPresentation ) {
                presentationState = Off;
                isPresentation = false;
            } else {
                fullscreenState = Off;
                isFullscreen = false;
            }
        }
    }
    else
    {
        // presentation command issued
        if ( !isPresentation )
        {
            presentationState = On;
            if ( !isFullscreen )
                fullscreenState = On;
        }
        else
        {
            presentationState = Off;
            if ( !isFullscreen )
                fullscreenState = Off;
        }

        isPresentation = !isPresentation;
    }

    ULONG ulFrameStyle = WinQueryWindowULong( hWndFrame, QWL_STYLE );

    if ( presentationState == Off )
    {
        docViewer->setPresentation( false );
        WinSetParent( hWndMenu, hWndFrame, FALSE );
    }
    else if ( presentationState == On )
    {
        docViewer->setPresentation( true );
        WinSetParent( hWndMenu, HWND_OBJECT, FALSE );
    }

    if ( fullscreenState == Off )
    {
        WinSetParent( hFrameSysmenu,  hWndFrame, FALSE );
        WinSetParent( hFrameTitlebar, hWndFrame, FALSE );
        WinSetParent( hFrameMinMax,   hWndFrame, FALSE );
        ulFrameStyle |= FS_SIZEBORDER;

        // PM does not synchronize the title bar hilite state when it is added
        // to the frame window. Do it ourselves
        BOOL active = WinQueryActiveWindow( HWND_DESKTOP ) == hWndFrame;
        WinSendMsg( hFrameTitlebar, TBM_SETHILITE,
                    MPFROMSHORT( active ), MPVOID );

        // reset the fullscreen menu check
        WinCheckMenuItem( hWndMenu, CM_FULLSCREEN, FALSE );
        WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT( CM_FULLSCREEN ), (MPARAM)FALSE );

    }
    else if ( fullscreenState == On )
    {
        if ( !atStartup )
        {
            WinQueryWindowPos( hWndFrame, &winPos.Swp );
            winPos.XRestore  = WinQueryWindowUShort( hWndFrame, QWS_XRESTORE );
            winPos.YRestore  = WinQueryWindowUShort( hWndFrame, QWS_YRESTORE );
            winPos.CXRestore = WinQueryWindowUShort( hWndFrame, QWS_CXRESTORE );
            winPos.CYRestore = WinQueryWindowUShort( hWndFrame, QWS_CYRESTORE );
            winPos.XMinimize = WinQueryWindowUShort( hWndFrame, QWS_XMINIMIZE );
            winPos.YMinimize = WinQueryWindowUShort( hWndFrame, QWS_YMINIMIZE );
        }

        // set the fullscreen menu check
        WinCheckMenuItem( hWndMenu, CM_FULLSCREEN, TRUE );
        WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT( CM_FULLSCREEN ), (MPARAM)TRUE );

        WinSetParent( hFrameSysmenu,  HWND_OBJECT, FALSE );
        WinSetParent( hFrameTitlebar, HWND_OBJECT, FALSE );
        WinSetParent( hFrameMinMax,   HWND_OBJECT, FALSE );
        ulFrameStyle &= ~FS_SIZEBORDER;
    }

    if ( fullscreenState != NoChange || presentationState != NoChange )
    {
        WinSetWindowULong( hWndFrame, QWL_STYLE, ulFrameStyle );
        WinSendMsg( hWndFrame, WM_UPDATEFRAME, MPVOID, MPVOID );
    }

    if ( presentationState == Off )
    {
        WinSendMsg( hVertSplitter, SBM_SETSPLITTERSIZE, MPFROMSHORT( -1 ), MPVOID );
        WinSendMsg( hVertSplitter, SBM_SETSPLITTERPOS,
                    MPFROMSHORT( Lucide::showIndex ? Lucide::splitterPos : 0 ), MPVOID );
        WinSendMsg( hHorizSplitter, SBM_SETFIXEDSIZE,
            MPFROMSHORT( DEFAULT_PICTSIZE + TOOLBAR_HEIGHT_ADD ), MPVOID );

        // reset the presentation menu check
        WinCheckMenuItem( hWndMenu, CM_PRESENTATION, FALSE );
        WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT( CM_PRESENTATION ), (MPARAM)FALSE );

    }
    else if ( presentationState == On )
    {
        WinSendMsg( hHorizSplitter, SBM_SETSPLITTERPOS, 0, MPVOID );
        WinSendMsg( hVertSplitter, SBM_SETSPLITTERPOS, 0, MPVOID );
        WinSendMsg( hVertSplitter, SBM_SETSPLITTERSIZE, 0, MPVOID );

        // set the presentation menu check
        WinCheckMenuItem( hWndMenu, CM_PRESENTATION, TRUE );
        WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT( CM_PRESENTATION ), (MPARAM)TRUE );
    }

    if ( fullscreenState == Off )
    {
        WinSetWindowUShort( hWndFrame, QWS_XRESTORE,  winPos.XRestore );
        WinSetWindowUShort( hWndFrame, QWS_YRESTORE,  winPos.YRestore );
        WinSetWindowUShort( hWndFrame, QWS_CXRESTORE, winPos.CXRestore );
        WinSetWindowUShort( hWndFrame, QWS_CYRESTORE, winPos.CYRestore );
        WinSetWindowUShort( hWndFrame, QWS_XMINIMIZE, winPos.XMinimize );
        WinSetWindowUShort( hWndFrame, QWS_YMINIMIZE, winPos.YMinimize );
        WinSetWindowPos( hWndFrame, NULLHANDLE,
                         winPos.Swp.x, winPos.Swp.y, winPos.Swp.cx, winPos.Swp.cy,
                         SWP_SIZE | SWP_MOVE | SWP_SHOW );
    }
    else if ( fullscreenState == On )
    {
        WinSetWindowPos( hWndFrame, NULLHANDLE, 0, 0,
                         WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN ),
                         WinQuerySysValue( HWND_DESKTOP, SV_CYSCREEN ),
                         SWP_SIZE | SWP_MOVE | SWP_SHOW );
    }
}


void Lucide::focusDocview()
{
    WinSetFocus( HWND_DESKTOP, docViewer->getViewHWND() );
}

void Lucide::focusIndex()
{
    WinSetFocus( HWND_DESKTOP, indexWin->getIndexHWND() );
}

void Lucide::cmdSwitchWindow()
{
    if ( activeWindow == AwIndex ) {
        focusDocview();
    } else {
        focusIndex();
    }
}

void Lucide::toggleZoom()
{
    if ( ( doc != NULL ) && doc->isScalable( ev ) )
    {
        bool isZoom = !docViewer->isZoomMode();
        WinSendMsg( hToolBar, TBM_SETCHECK, MPFROMSHORT( CM_ZOOM_IN_OUT ), (MPARAM)isZoom );
        docViewer->setZoomMode( isZoom );
    }
}

void Lucide::cmdMinimize()
{
    if ( isFullscreen ) {
        toggleFullscreen();
    }
    WinSetWindowPos( hWndFrame, HWND_TOP, 0, 0, 0, 0, SWP_MINIMIZE );
}

void Lucide::cmdSwitchToPresentation()
{
    if ( !isPresentation )
    {
        SWP pos = {0};
        WinQueryWindowPos( hWndFrame, &pos );

        if ( pos.fl & SWP_MINIMIZE ) {
            WinSetWindowPos( hWndFrame, HWND_TOP, 0, 0, 0, 0,
                    SWP_SHOW | SWP_ACTIVATE | SWP_RESTORE | SWP_ZORDER );
        }
        togglePresentation();
    }
}

void Lucide::newWindow( char *file, bool addDir )
{
    char *param = NULL;

    if ( file != NULL )
    {
        if ( addDir )
        {
            param = new char[ CCHMAXPATH ];
            strcpy( param, docFullName );
            char *lastSlash = strrchr( param, '\\' );
            if ( lastSlash != NULL ) {
                *( lastSlash + 1 ) = 0;
            }
            strcat( param, file );
        }
        else {
            param = newstrdup( file );
        }
    }

#if defined(__WATCOM__)
    const char *execname = __argv[0];
#else
    char execname[ _MAX_PATH ];
    _execname( execname, sizeof(execname) );
#endif

    PROGDETAILS pd;
    pd.Length                      = sizeof( PROGDETAILS );
    pd.progt.progc                 = PROG_DEFAULT;
    pd.progt.fbVisible             = SHE_VISIBLE;
    pd.pszTitle                    = NULL;
    pd.pszExecutable               = execname;
    pd.pszParameters               = NULL;
    pd.pszStartupDir               = NULL;
    pd.pszIcon                     = NULL;
    pd.pszEnvironment              = NULL;
    pd.swpInitial.fl               = SWP_ACTIVATE;
    pd.swpInitial.cy               = 0;
    pd.swpInitial.cx               = 0;
    pd.swpInitial.y                = 0;
    pd.swpInitial.x                = 0;
    pd.swpInitial.hwndInsertBehind = HWND_TOP;
    pd.swpInitial.hwnd             = NULLHANDLE;
    pd.swpInitial.ulReserved1      = 0;
    pd.swpInitial.ulReserved2      = 0;

    WinStartApp( NULLHANDLE, &pd, param, NULL, 0 );

    delete[] param;
}

void Lucide::gotoFile( FileList file )
{
    if ( fileList.size() == 0 ) {
        return;
    }

    if ( fileListIterator == fileList.end() ) {
        // If viewed file extension not in supported extensions
        //   list - fileListIterator will equal fileList.end()
        fileListIterator = fileList.begin();
    }

    if ( file == ListFirst ) {
        fileListIterator = fileList.begin();
    }
    else if ( file == ListPrevious )
    {
        if ( fileListIterator == fileList.begin() ) {
            fileListIterator = fileList.end();
        }
        fileListIterator--;
    }
    else if ( file == ListNext )
    {
        fileListIterator++;
        if ( fileListIterator == fileList.end() ) {
            fileListIterator = fileList.begin();
        }
    }
    else if ( file == ListLast ) {
        fileListIterator = fileList.end();
        fileListIterator--;
    }

    std::string fname = *fileListIterator;
    char *fn = new char[ CCHMAXPATH ];
    strcpy( fn, docDirName );
    strcat( fn, fname.c_str() );

    loadDocument( fn );
    delete[] fn;
}
/*
 * open Profile loads Lucide.ini and moves the ini entries from OS2.ini to itself.
 * The ini entries in luutils.cpp and stbrowser.c should remain in OS2.ini
 */
void Lucide::openProfile()
{
    char filename[CCHMAXPATH];
    ULONG sz = sizeof( filename );

    if (PrfQueryProfileString( HINI_USERPROFILE, appName, "Path", "", filename, sz ))
        strcat( strupr(filename), "\\LUCIDE.INI" );
    else
        strcpy( filename, "LUCIDE.INI" );
    hinilucideprofile = PrfOpenProfile(hab, filename);

    bool converted = FALSE;
    sz = sizeof( bool );
    PrfQueryProfileData(hinilucideprofile, appName, "convertedINI", &converted, &sz );
    
    if ( !converted ) {
        sz = sizeof( bool );
        PrfQueryProfileData( HINI_USERPROFILE, appName, "thumbnail", &Thumbnail, &sz );
        sz = sizeof( bool );
        PrfWriteProfileData( hinilucideprofile, appName, "thumbnail", &Thumbnail, sz );
        sz = sizeof( bool );
        PrfWriteProfileData( HINI_USERPROFILE, appName, "thumbnail", NULL, sz );
        sz = sizeof( filename );
        PrfQueryProfileString( HINI_USERPROFILE, appName, prfLvd, "", filename, sz );
        PrfWriteProfileString( hinilucideprofile, appName,  prfLvd, filename );
        PrfWriteProfileString( HINI_USERPROFILE, appName,  prfLvd, NULL );
        char valbuf[ 3 ] = "";
        PrfQueryProfileInt( HINI_USERPROFILE, appName, prfSplpos, Lucide::splitterPos );
        PrfWriteProfileString( hinilucideprofile, appName, prfSplpos,
                              itoa( Lucide::splitterPos, valbuf, 10 ) );
        PrfWriteProfileString( HINI_USERPROFILE, appName, prfSplpos, NULL );
        PrfQueryProfileInt( HINI_USERPROFILE, appName, prfShowind, Lucide::showIndex );
        PrfWriteProfileString( hinilucideprofile, appName, prfShowind,
                              itoa( Lucide::showIndex, valbuf, 10 ) );
        PrfWriteProfileString( HINI_USERPROFILE, appName, prfShowind, NULL );
        if ( PrfQueryProfileInt( HINI_USERPROFILE, appName, prfFullscreen, 0 ) == 1) {
            PrfWriteProfileString( hinilucideprofile, appName, prfFullscreen, "1" );
            PrfWriteProfileString( HINI_USERPROFILE, appName, prfFullscreen, NULL );
        }
        if (PrfQueryProfileInt( HINI_USERPROFILE, appName, prfPresentation, 0 ) == 1) {
            PrfWriteProfileString( hinilucideprofile, appName, prfPresentation, "1" );
            PrfWriteProfileString( HINI_USERPROFILE, appName, prfPresentation, NULL );
        }
        double   zoom;
        sz = sizeof( zoom );
        PrfQueryProfileData( HINI_USERPROFILE, appName, "Zoom", &zoom, &sz );
        sz = sizeof( zoom );
        PrfWriteProfileData( hinilucideprofile, appName, "Zoom", &zoom, sz );
        sz = sizeof( zoom );
        PrfWriteProfileData( HINI_USERPROFILE, appName, "Zoom", NULL, sz );
        PgLayout layout;
        char buff[ 10 ];
        PrfQueryProfileInt( HINI_USERPROFILE, appName, "Layout", layout );
        PrfWriteProfileString( hinilucideprofile, appName, "Layout", itoa( layout, buff, 10 ) );
        PrfWriteProfileString( HINI_USERPROFILE, appName, "Layout", NULL );
        int buttonctl = 0;
        buttonctl = PrfQueryProfileInt(HINI_USERPROFILE, appName, "useAsImage", buttonctl);
        PrfWriteProfileString(hinilucideprofile, appName, "useAsImage",
                              itoa(buttonctl, buff, 10));
        PrfWriteProfileString(HINI_USERPROFILE, appName, "useAsImage", NULL );
        buttonctl = 0;
        buttonctl = PrfQueryProfileInt(HINI_USERPROFILE, appName, "useHigherImageQuality", buttonctl);
        PrfWriteProfileString(hinilucideprofile, appName, "useHigherImageQuality",
                              itoa(buttonctl, buff, 10));
        PrfWriteProfileString(HINI_USERPROFILE, appName, "useHigherImageQuality",NULL );
        buttonctl = 0;
        buttonctl = PrfQueryProfileInt(HINI_USERPROFILE, appName, "IgnMargins", buttonctl);
        PrfWriteProfileString(hinilucideprofile, appName, "IgnMargins",
                              itoa(buttonctl, buff, 10));
        PrfWriteProfileString(HINI_USERPROFILE, appName, "IgnMargins", NULL);
        buttonctl = 0;
        buttonctl = PrfQueryProfileInt(HINI_USERPROFILE, appName, "PageRange", buttonctl);
        PrfWriteProfileString(hinilucideprofile, appName, "PageRange",
                              itoa(buttonctl, buff, 10));
        PrfWriteProfileString(HINI_USERPROFILE, appName, "PageRange", NULL);
        int bufsize = ( CCHMAXPATH * RECENT_SIZE ) + RECENT_SIZE + 2;
        char *buf = new char[ bufsize ];
        memset( buf, 0, bufsize );
        PrfQueryProfileString( HINI_USERPROFILE, appName, "RecentFiles", "", buf, bufsize );
        PrfWriteProfileString( hinilucideprofile, appName, "RecentFiles", buf );
        PrfWriteProfileString( HINI_USERPROFILE, appName, "RecentFiles", NULL );
        converted = TRUE;
        sz = sizeof( bool );
        PrfWriteProfileData( hinilucideprofile, appName, "convertedINI", &converted, sz );
    }
}

void Lucide::savePosition()
{
    if ( !WinIsWindow( hab, hWndFrame ) )
        return;

    char valbuf[ 3 ] = "";
    PrfWriteProfileString( hinilucideprofile, appName, prfSplpos,
                           itoa( Lucide::splitterPos, valbuf, 10 ) );
    PrfWriteProfileString( hinilucideprofile, appName, prfShowind,
                           itoa( Lucide::showIndex, valbuf, 10 ) );

    if ( isFullscreen )
        PrfWriteProfileString( hinilucideprofile, appName, prfFullscreen, "1" );
    else
        PrfWriteProfileString( hinilucideprofile, appName, prfFullscreen, NULL );

    if ( isPresentation )
        PrfWriteProfileString( hinilucideprofile, appName, prfPresentation, "1" );
    else
        PrfWriteProfileString( hinilucideprofile, appName, prfPresentation, NULL );

    if ( !isFullscreen && !isPresentation ) {
        WinQueryWindowPos( hWndFrame, &winPos.Swp );
        winPos.XRestore  = WinQueryWindowUShort( hWndFrame, QWS_XRESTORE );
        winPos.YRestore  = WinQueryWindowUShort( hWndFrame, QWS_YRESTORE );
        winPos.CXRestore = WinQueryWindowUShort( hWndFrame, QWS_CXRESTORE );
        winPos.CYRestore = WinQueryWindowUShort( hWndFrame, QWS_CYRESTORE );
        winPos.XMinimize = WinQueryWindowUShort( hWndFrame, QWS_XMINIMIZE );
        winPos.YMinimize = WinQueryWindowUShort( hWndFrame, QWS_YMINIMIZE );
    }

    PrfWriteProfileData( HINI_USERPROFILE, appName, prfFwp, &winPos, sizeof( winPos ) );
}

void Lucide::restorePosition()
{
    splitterPos = PrfQueryProfileInt( hinilucideprofile, appName, prfSplpos,
                                      Lucide::splitterPos );
    showIndex = PrfQueryProfileInt( hinilucideprofile, appName, prfShowind,
                                    Lucide::showIndex );

    WinSendMsg( hVertSplitter, SBM_SETSPLITTERPOS,
                MPFROMSHORT( showIndex ? splitterPos : 0 ), MPVOID );

    bool fullscreen = PrfQueryProfileInt( hinilucideprofile, appName,
                                          prfFullscreen, 0 ) == 1;
    bool presentation = PrfQueryProfileInt( hinilucideprofile, appName,
                                            prfPresentation, 0 ) == 1;

    LONG sx, sy;
    sx = WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN );
    sy = WinQuerySysValue( HWND_DESKTOP, SV_CYSCREEN );

    ULONG SwpOptions = SWP_MOVE | SWP_SIZE | SWP_ACTIVATE | SWP_SHOW;
    bool atStartup = true;

    ULONG ulWpSize = sizeof( winPos );
    if ( PrfQueryProfileData( HINI_USERPROFILE, appName, prfFwp, &winPos, &ulWpSize ) )
    {
        if ( winPos.Swp.fl & SWP_MAXIMIZE ) {
            SwpOptions |= SWP_MAXIMIZE;
        }
        else if ( winPos.Swp.fl & SWP_MINIMIZE ) {
            SwpOptions |= SWP_MINIMIZE;
        }

        LONG sx, sy;
        sx = WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN );
        sy = WinQuerySysValue( HWND_DESKTOP, SV_CYSCREEN );

        if ( winPos.Swp.x > sx ) {
            winPos.Swp.x = sx - winPos.Swp.cx;
        }
        if ( winPos.Swp.y > sy ) {
            winPos.Swp.y = sy - winPos.Swp.cy;
        }

        // Just a note: the FID_CLIENT window is only resized by WinSetWindowPos()
        // on the frame if the size is actually changed *and* the SWP_SHOW flag
        // is present (PM bug?). Therefore, when the saved normal size the same
        // as fullscreen and we should go fullscreen at startup, WinSetWindowPos()
        // issued from toggleFullscreenEx() will not resize FID_CLIENT even
        // though it will contain SWP_SHOW

        if ( !fullscreen && !presentation ) {
            // only set the normal size if no if fullscreen or presentation is
            // requested, to avoid flicker. We could also avoid flicker by
            // omitting SWP_SHOW but see the note above
            WinSetWindowPos( hWndFrame, NULLHANDLE,
                             winPos.Swp.x, winPos.Swp.y, winPos.Swp.cx, winPos.Swp.cy,
                             SwpOptions );
        }

        WinSetWindowUShort( hWndFrame, QWS_XRESTORE,  winPos.XRestore );
        WinSetWindowUShort( hWndFrame, QWS_YRESTORE,  winPos.YRestore );
        WinSetWindowUShort( hWndFrame, QWS_CXRESTORE, winPos.CXRestore );
        WinSetWindowUShort( hWndFrame, QWS_CYRESTORE, winPos.CYRestore );
        WinSetWindowUShort( hWndFrame, QWS_XMINIMIZE, winPos.XMinimize );
        WinSetWindowUShort( hWndFrame, QWS_YMINIMIZE, winPos.YMinimize );

        // we don't the app to be minimized at startup
        if ( SwpOptions & SWP_MINIMIZE )
            WinSetWindowPos( hWndFrame, NULLHANDLE, 0, 0, 0, 0, SWP_RESTORE );
    }
    else
    {
        typedef
        BOOL ( APIENTRY *WinQueryDesktopWorkArea_T ) ( HWND hwndDesktop,
                                                       PRECTL pwrcWorkArea );
        static WinQueryDesktopWorkArea_T WinQueryDesktopWorkArea =
            (WinQueryDesktopWorkArea_T) ~0;

        if ( (ULONG) WinQueryDesktopWorkArea == (ULONG) ~0 ) {
            if ( my_DosQueryProcAddr( "PMMERGE", 5469,
                                      (PFN *) &WinQueryDesktopWorkArea ) )
                WinQueryDesktopWorkArea = NULL;
        }

        SWP swp;
        RECTL rcl;
        if ( WinQueryDesktopWorkArea &&
             WinQueryDesktopWorkArea( HWND_DESKTOP, &rcl ) ) {
            swp.x = rcl.xLeft;
            swp.y = rcl.yBottom;
            swp.cx = rcl.xRight - rcl.xLeft;
            swp.cy = rcl.yTop - rcl.yBottom;
        } else {
            swp.x = 0;
            swp.y = 0;
            swp.cx = sx;
            swp.cy = sy;
        }

        swp.x += 16;
        swp.y += 16;
        swp.cx -= 32;
        swp.cy -= 32;

        WinSetWindowPos( hWndFrame, NULLHANDLE, swp.x, swp.y, swp.cx, swp.cy,
                         SwpOptions );

        // we don't initialize winPos here so reset atStartup to let
        // toggleFullscreenEx() do this
        atStartup = false;
    }

    if ( fullscreen )
    {
        toggleFullscreenEx( false, atStartup );
        isFullscreen = fullscreen;
    }
    else if ( presentation )
    {
        toggleFullscreenEx( true, atStartup );
    }
}

static bool isAncestorOf( HWND hwnd1, HWND hwnd2 )
{
    static HWND desktop = NULLHANDLE;
    if ( desktop == NULLHANDLE )
        desktop = WinQueryDesktopWindow( hab, NULLHANDLE );

    if ( hwnd1 == NULLHANDLE || hwnd2 == NULLHANDLE )
        return false;

    while ( hwnd2 != hwnd1 && hwnd2 != desktop )
        hwnd2 = WinQueryWindow( hwnd2, QW_PARENT );

    return hwnd2 == hwnd1;
}

static MRESULT EXPENTRY frameProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch ( msg )
    {
        case WM_TRANSLATEACCEL:
        {
            // change the accel logic by first letting the focus window process
            // WM_CHAR and only translate it to accel if not handled (this makes
            // sure that standard keyboard shortcuts in e.g. input fields work
            // even if we define our own accelerators from these shortcuts in
            // the main window). Make an exception for VK_TAB since it's always
            // eaten by the standard window procedure and therefore the accel
            // table will never be called. Note that we do this trick only for
            // the document window and its children: other windows such as the
            // standard frame controls like menu etc. are known to demonstrate
            // weird behavior (for example, the menu window seems to exit the
            // menu mode on any WM_CHAR sent to it)
            HWND focus = WinQueryFocus( HWND_DESKTOP );
            if ( !isAncestorOf( docViewer->getFrameHWND(), focus ) )
                break;
            PQMSG pqmsg = (PQMSG)mp1;
            if ( pqmsg->msg != WM_CHAR )
                break;
            if ( !( SHORT1FROMMP( pqmsg->mp1 ) & KC_VIRTUALKEY ) ||
                 !( SHORT2FROMMP( pqmsg->mp2 ) == VK_TAB ) )
            {
                if ( focus == pqmsg->hwnd && focus != hwnd ) {
                    if ( WinDispatchMsg( hab, pqmsg ) ) {
                        pqmsg->msg = WM_NULL;
                        return (MRESULT)TRUE;
                    }
                }
            }
            // in presentation mode, we hide the menu which effectively makes
            // all disabled items work through accelerators which is completely
            // unexpected. Fix it by translating accels manually and checking
            // if they are disabled in the hidden menu
            BOOL ok = WinTranslateAccel( hab, hwnd,
                                         WinQueryAccelTable( hab, hwnd ),
                                         pqmsg );
            // try the menu mnemonics if no explicit accels found
            if ( !ok )
                ok = (BOOL)WinSendMsg( hwnd, 0x0195 /*WM_TRANSLATEMNEMONIC*/,
                                       MPFROMP( pqmsg ), NULL );
            if ( ok )
            {
                if ( pqmsg->msg == WM_COMMAND ) {
                    SHORT cm = SHORT1FROMMP(pqmsg->mp1);
                    if ( !WinIsMenuItemEnabled( hWndMenu, cm ) )
                        pqmsg->msg = WM_NULL;
                }
                return (MRESULT)TRUE;
            }
            return (MRESULT)FALSE;
        }

        case WM_SYSCOMMAND:
        {
            if ( SHORT1FROMMP(mp1) == SC_CLOSE ) {
                // the system menu is disabled in fullscreen/presentation mode
                // but we still want to exit with Alt-F4 so always handle it here
                WinPostMsg( hWndFrame, WM_CLOSE, NULL, NULL );
                return (MRESULT)FALSE;
            }
        }
        break;
    }

    return pOldFrameProc( hwnd, msg, mp1, mp2 );
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
                case CM_NEW_WINDOW:
                    Lucide::newWindow( NULL, false );
                    return (MRESULT)FALSE;

                case CM_OPEN:
                    Lucide::openDocument();
                    return (MRESULT)FALSE;

                case CM_FILEFIRST:
                    Lucide::gotoFile( ListFirst );
                    return (MRESULT)FALSE;

                case CM_FILEPREVIOUS:
                    Lucide::gotoFile( ListPrevious );
                    return (MRESULT)FALSE;

                case CM_FILENEXT:
                    Lucide::gotoFile( ListNext );
                    return (MRESULT)FALSE;

                case CM_FILELAST:
                    Lucide::gotoFile( ListLast );
                    return (MRESULT)FALSE;

                case CM_RECENT + 1:
                case CM_RECENT + 2:
                case CM_RECENT + 3:
                case CM_RECENT + 4:
                case CM_RECENT + 5:
                case CM_RECENT + 6:
                case CM_RECENT + 7:
                case CM_RECENT + 8:
                case CM_RECENT + 9:
                {
                    std::string f = recent->getFile( SHORT1FROMMP(mp1) );
                    Lucide::loadDocument( f.c_str() );
                    return (MRESULT)FALSE;
                }

                case CM_RECENTCLEAR:
                    recent->clear();
                    return (MRESULT)FALSE;

                case CM_BACK:
                case CM_BACKNAV:
                    docViewer->goToPage(docViewer->getPreviousPage());
                    docViewer->unsetPreviousPage();
                    Lucide::checkMenus( false );
                    Lucide::checkNavigationMenus();
                    return (MRESULT)FALSE;

                case CM_SAVEAS:
                    Lucide::saveDocumentAs();
                    return (MRESULT)FALSE;

                case CM_SAVE:
                    Lucide::saveDocument();
                    return (MRESULT)FALSE;

                case CM_CLOSE:
                    Lucide::closeDocument();
                    return (MRESULT)FALSE;

                case CM_PRINT:
                {
                    PrintDlg *d = new PrintDlg( hWndFrame, doc, Lucide::docFileName,
                                                docViewer->getCurrentPage() + 1 );
                    if ( d->showDialog() == DID_OK )
                    {
                        // print
                        PrintSetup *p = new PrintSetup;
                        memset( p, 0, sizeof( PrintSetup ) );
                        d->getPrintSetup( p );
                        printDocument( hWndFrame, doc, Lucide::docFileName, p );
                        delete p;
                    }
                    delete d;
                    return (MRESULT)FALSE;
                }

                case CM_EXIT:
                    WinPostMsg( hWndFrame, WM_CLOSE, NULL, NULL );
                    return (MRESULT)FALSE;

                case CM_DOCINFO:
                {
                    LuDocumentInfo *dinfo = doc->getDocumentInfo( ev );
                    DocInfoDlg *d = new DocInfoDlg( hWndFrame, dinfo, Lucide::docFileName );
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

                case CM_SELECTALL:
                    docViewer->selectAll();
                    return (MRESULT)FALSE;

                case CM_FIND:
                    if ( findDlg->showDialog() == DID_OK ) {
                        if ( strlen( findDlg->getSearchString() ) >= 0 )
                        {
                            bool clear = TRUE;
                            docViewer->searchDocument( findDlg->getSearchString(),
                                            findDlg->isCaseSensitive(), false, findDlg->doFindBack() );

                            if ( strlen( findDlg->getSearchString() ) == 0 )
                                clear = FALSE;
                            WinEnableMenuItem( hWndMenu, CM_FINDAGAIN, clear );
                            WinSendMsg( hToolBar, TBM_ENABLEITEM, MPFROMSHORT(CM_FINDAGAIN), (MPARAM)clear );
                        }
                    }
                    return (MRESULT)FALSE;

                case CM_FINDAGAIN:
                    docViewer->searchDocument( findDlg->getSearchString(),
                                               findDlg->isCaseSensitive(), true, findDlg->doFindBack() );
                    return (MRESULT)FALSE;

                case CM_SETTINGS:
                {
                    SettingsDlg *d = new SettingsDlg( hWndFrame, settings );
                    d->doDialog();
                    return (MRESULT)FALSE;
                }

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

                case CM_GOTOPAGE:
                {
                    GotoDlg *d = new GotoDlg( hWndFrame, doc->getPageCount( ev ),
                                                docViewer->getCurrentPage() + 1 );
                    if ( d->showDialog() == DID_OK ) {
                        long pg = d->getPage();
                        if ( pg > 0 ) {
                            Lucide::goToPage( pg - 1 );
                        }
                    }
                    delete d;
                    return (MRESULT)FALSE;
                }

                case CM_FITWINDOW:
                    Lucide::setZoom( -2 );
                    return (MRESULT)FALSE;

                case CM_ACTSIZE:
                    Lucide::setZoom( 1 );
                    return (MRESULT)FALSE;

                case CM_FITWIDTH:
                    Lucide::setZoom( -1 );
                    return (MRESULT)FALSE;

                case CM_ZOOM_IN_OUT:
                    Lucide::toggleZoom();
                    return (MRESULT)FALSE;

                case CM_ZOOM_IN:
                    docViewer->zoomInOut( true );
                    return (MRESULT)FALSE;

                case CM_ZOOM_OUT:
                    docViewer->zoomInOut( false );
                    return (MRESULT)FALSE;

                case CM_SINGLEPAGE:
                    Lucide::setPageLayout( SinglePage );
                    return (MRESULT)FALSE;

                case CM_CONTINUOUS:
                    Lucide::setPageLayout( Continuous );
                    return (MRESULT)FALSE;

                case CM_ROTATE90CW:
                    docViewer->setRotation( docViewer->getRotation() + 90 );
                    return (MRESULT)FALSE;

                case CM_ROTATE90CCW:
                    docViewer->setRotation( docViewer->getRotation() - 90 );
                    return (MRESULT)FALSE;

                case CM_NAVPANE:
                    {
                        Lucide::showIndex = !Lucide::showIndex;
                        Lucide::checkNavpane();
                        WinSendMsg( hVertSplitter, SBM_SETSPLITTERPOS,
                            MPFROMSHORT( Lucide::showIndex ? Lucide::splitterPos : 0 ), MPVOID );
                        if ( !Lucide::showIndex ) {
                            Lucide::focusDocview();
                        }
                    }
                    return (MRESULT)FALSE;

                case CM_FULLSCREEN:
                    Lucide::toggleFullscreen();
                    return (MRESULT)FALSE;

                case CM_PRESENTATION:
                    Lucide::togglePresentation();
                    return (MRESULT)FALSE;

                case WM_HELP:
                    if (Lucide::hwndHelp)
                        WinSendMsg(Lucide::hwndHelp,HM_DISPLAY_HELP,
                                   MPFROM2SHORT(1, 0), MPFROMSHORT(HM_RESOURCEID));
                    break;

                case CM_HELPKEYS:
                    if (Lucide::hwndHelp)
                            WinSendMsg(Lucide::hwndHelp,HM_DISPLAY_HELP,
                                       MPFROM2SHORT(400, 0), MPFROMSHORT(HM_RESOURCEID));
                    return (MRESULT)FALSE;

                case CM_HELPPDF:
                    if (Lucide::hwndHelp)
                            WinSendMsg(Lucide::hwndHelp,HM_DISPLAY_HELP,
                                       MPFROM2SHORT(710, 0), MPFROMSHORT(HM_RESOURCEID));
                    return (MRESULT)FALSE;

                case CM_HELPDJVU:
                    if (Lucide::hwndHelp)
                            WinSendMsg(Lucide::hwndHelp,HM_DISPLAY_HELP,
                                       MPFROM2SHORT(780, 0), MPFROMSHORT(HM_RESOURCEID));
                    return (MRESULT)FALSE;

                case CM_PRODINFO:
                    AboutBox( hWndFrame );
                    return (MRESULT)FALSE;

                case CM_MINIMIZE:
                    Lucide::cmdMinimize();
                    return (MRESULT)FALSE;

                case CM_TOPRESENTATION:
                    Lucide::cmdSwitchToPresentation();
                    return (MRESULT)FALSE;

                case CM_SWITCHWINDOW:
                    Lucide::cmdSwitchWindow();
                    return (MRESULT)FALSE;
            }
        }
        break;

        case WM_CLOSE:
            if ( !Lucide::closeDocument() )
                return (MRESULT)FALSE;
        break;
    }
    return pOldSplProc( hwnd, msg, mp1, mp2 );
}


char deffont[] = "9.WarpSans";
int deffontlen = sizeof( deffont );

__declspec(dllexport) _System APIRET APIENTRY LucideMain( int argc, char *argv[] )
{
    //ScopedExceptqLoader sel;
    HMQ   hmq;
    QMSG  qmsg;

    hab = WinInitialize( 0 );
    hmq = WinCreateMsgQueue( hab, 0 );
    
    loadLang();
    // Open the INI file
    Lucide::openProfile();

    pluginMan = new PluginManager;

    InitPMSplitterClass( hab );
    InitPMToolbarClass( hab );

    ULONG ulFrameFlags = FCF_TITLEBAR | FCF_SIZEBORDER | FCF_SYSMENU |
                         FCF_MINMAX | FCF_TASKLIST | FCF_NOBYTEALIGN | FCF_ICON;
    title = newstrdupL( MSGS_MAIN_WIN_TITLE );
    hWndFrame = WinCreateStdWindow( HWND_DESKTOP, 0, &ulFrameFlags, NULL, title,
                                    WS_SYNCPAINT|WS_VISIBLE, _hmod, IDI_MAIN_ICON, NULL );
    pOldFrameProc = WinSubclassWindow( hWndFrame, frameProc );
    WinSetWindowUShort( hWndFrame, QWS_ID, MAIN_FRAME );

    hFrameSysmenu  = WinWindowFromID( hWndFrame, FID_SYSMENU );
    hFrameTitlebar = WinWindowFromID( hWndFrame, FID_TITLEBAR );
    hFrameMinMax   = WinWindowFromID( hWndFrame, FID_MINMAX );
    WinSetAccelTable( hab, WinLoadAccelTable( hab, _hmod, IDA_MAINACCEL ), hWndFrame );
    hWndMenu = WinLoadMenu( hWndFrame, _hmod, IDM_MAINMENU );
    localizeMenu( hWndMenu );
    WinSetWindowUShort( hWndMenu, QWS_ID, FID_MENU );
    
    
    // Vertical splitter and his windows - Index and Document view
    hVertSplitter = WinCreateWindow( hWndFrame, WC_ER_SPLITTER, "",
                                     WS_VISIBLE | SBS_VSPLIT,
                                     0, 0, 0, 0, hWndFrame, HWND_TOP,
                                     ID_SPLITTER, NULL, NULL );

    indexWin = new IndexWindow( hWndFrame );

    DocumentViewer::registerClass();

    docViewer = new DocumentViewer( hWndFrame );

    WinSendMsg( hVertSplitter, SBM_SETWINDOWS,
                MPFROMHWND( indexWin->getHWND() ), MPFROMHWND( docViewer->getFrameHWND() ) );

    // Horizontal splitter and its windows - Toolbar and Vertical splitter
    // Horizontal splitter is client window
    hHorizSplitter = WinCreateWindow( hWndFrame, WC_ER_SPLITTER, "",
                                      WS_VISIBLE | SBS_HSPLIT | SBS_SECONDFIXED,
                                      0, 0, 0, 0, hWndFrame, HWND_TOP,
                                      FID_CLIENT, NULL, NULL );
    pOldSplProc = WinSubclassWindow( hHorizSplitter, splProc );

    hToolBar = createToolbar( hWndFrame );

    WinSendMsg( hHorizSplitter, SBM_SETWINDOWS,
                MPFROMHWND( hVertSplitter ), MPFROMHWND( hToolBar ) );
    
    WinSendMsg( hHorizSplitter, SBM_SETFIXEDSIZE,
                MPFROMSHORT( DEFAULT_PICTSIZE + TOOLBAR_HEIGHT_ADD ), MPVOID );

    settings = new LuSettings;
    settings->load();
    Lucide::checkMenus( true );
    Lucide::setPageLayout( settings->layout );
    Lucide::setZoom( settings->zoom );

    findDlg = new FindDlg( hWndFrame );
    recent  = new RecentFiles( hWndMenu );
    
    Lucide::restorePosition();

    Lucide::focusDocview();

    if ( argc > 1 ) {
        Lucide::loadDocument( argv[1] );
    }

    Lucide::checkNavpane();
    initPipeMon( hWndFrame );

    // start help
    FILESTATUS3 fs3;
    char helpfile[CCHMAXPATH];
    char *env  = getenv("LUCIDEHELP");
    if (env)  {
        strcpy(helpfile, env);
    }
    else {
        char *lang = getenv("LANG");
        if (lang) {
            if (!strnicmp(lang, "es", 2)) {      //Spanish
                strcpy(helpfile, "lucide_es.hlp");
            }
            else if (!strnicmp(lang, "de", 2)) { // German
                strcpy(helpfile, "lucide_en.hlp"); 
            }
            else if (!strnicmp(lang, "cs", 2)) { // Czech
                strcpy(helpfile, "lucide_en.hlp"); 
            }
            else if (!strnicmp(lang, "nl", 2)) { // Dutch
                strcpy(helpfile, "lucide_en.hlp"); 
            }
            else if (!strnicmp(lang, "fr", 2)) { // French
                strcpy(helpfile, "lucide_en.hlp"); 
            }
            else if (!strnicmp(lang, "it", 2)) { // Itailian
                strcpy(helpfile, "lucide_en.hlp"); 
            }
            else if (!strnicmp(lang, "da", 2)) { // Norwegian
                strcpy(helpfile, "lucide_en.hlp"); 
            }
            else if (!strnicmp(lang, "ru", 2)) { // Russian
                strcpy(helpfile, "lucide_en.hlp"); 
            }
            else if (!strnicmp(lang, "sv", 2)) { //  Swedish
                strcpy(helpfile, "lucide_en.hlp"); 
            }
            else if (!strnicmp(lang, "zh", 2)) { //  Chinese
                strcpy(helpfile, "lucide_en.hlp"); 
            }
            else if (!strnicmp(lang, "pl", 2)) { //  Polish
                strcpy(helpfile, "lucide_en.hlp"); 
            }
            else {
                strcpy(helpfile, "lucide_en.hlp");
            }
        }
        else
            strcpy(helpfile, "lucide_en.hlp");
    }
    char *hlptitle = newstrdupL( HLP_TITLE );
    memset(&hini, 0, sizeof(HELPINIT));
    hini.cb = sizeof(HELPINIT);
    hini.phtHelpTable = (PHELPTABLE) MAKELONG(ID_HELPTABLE, 0xffff);
    hini.hmodAccelActionBarModule = (HMODULE) 0;
    hini.pszHelpWindowTitle = (PSZ) hlptitle; //"Lucide User's Guide";
    hini.hmodHelpTableModule = _hmod;
    hini.fShowPanelId = CMIC_HIDE_PANEL_ID;
    hini.pszHelpLibraryName = helpfile;
    Lucide::hwndHelp = WinCreateHelpInstance(hab, &hini);
    if (!Lucide::hwndHelp) {
        char helppath[CCHMAXPATH];
        char *env = getenv("LUCIDEINSTALLPATH");
        if (env) {
            strcpy(helppath, env);
            DosError(FERR_DISABLEHARDERR);
            if (!DosQueryPathInfo(helppath, FIL_STANDARD, &fs3, sizeof(fs3))) {
                if (fs3.attrFile & FILE_DIRECTORY) {
                    if (strrchr(helppath, '\\') != helppath + strlen(helppath))
                        strcat(helppath, "\\");
                    strcat(helppath,  helpfile); 
                    hini.pszHelpLibraryName = (CHAR *) helppath;
                    Lucide::hwndHelp = WinCreateHelpInstance(hab, &hini);
                    if (!Lucide::hwndHelp) {
                        char *msg = newstrdupL( MSGS_HELP_INSTANCE_FAILED );
                        WinMessageBox( HWND_DESKTOP, hWndFrame, msg,
                                      NULL, 0, MB_OK | MB_ICONEXCLAMATION | MB_MOVEABLE );
                        delete msg;
                    }
                }
            }
        }
    }
    delete hlptitle;
    if ( Lucide::hwndHelp )
        WinAssociateHelpInstance ( Lucide::hwndHelp, hWndFrame );
    
    // Messsage loop
    while ( WinGetMsg( hab, &qmsg, 0, 0, 0 ) ) {
        WinDispatchMsg( hab, &qmsg );
    }

    Lucide::savePosition();

    WinDestroyWindow( hWndFrame );

    recent->save();

    PrfCloseProfile(hinilucideprofile);

    Lucide::closeDocument( true );

    delete docViewer;
    delete indexWin;

    // must be freed _after_ document
    delete pluginMan;

    delete findDlg;
    delete recent;
    delete title;
    delete settings;
    unInitPipeMon();

    WinDestroyMsgQueue( hmq );
    WinTerminate( hab );
    return 0;
}

