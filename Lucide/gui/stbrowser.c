/*
 *  Starts a browser with a given URL.
 *  by Eugene Romanenko
 *
 *  This code is in the public domain and has no copyright.
 */

#include "os2all.h"

#include <string.h>


static char browserExe[ CCHMAXPATH ] = "";
static char browserDir[ CCHMAXPATH ] = "";

static void detectBrowser();

// Starts the browser, returns 1 if started, 0 otherwise.
int startBrowser( const char *url )
{
    PROGDETAILS pd;
    HAPP happ = NULLHANDLE;

    if ( url == NULL ) {
        return 0;
    }

    if ( browserExe[0] == 0 ) {
        detectBrowser();
    }

    if ( browserExe[0] == 0 ) {
        return 0;
    }

    pd.Length          = sizeof( PROGDETAILS );
    pd.progt.progc     = PROG_DEFAULT;
    pd.progt.fbVisible = SHE_VISIBLE;
    pd.pszTitle        = NULL;
    pd.pszExecutable   = browserExe;
    pd.pszParameters   = NULL;
    pd.pszStartupDir   = ( browserDir[0] == 0 ) ? NULL : browserDir;
    pd.pszIcon         = NULL;
    pd.pszEnvironment  = NULL;
    pd.swpInitial.fl   = SWP_ACTIVATE;
    pd.swpInitial.cy   = 0;
    pd.swpInitial.cx   = 0;
    pd.swpInitial.y    = 0;
    pd.swpInitial.x    = 0;
    pd.swpInitial.hwndInsertBehind = HWND_TOP;
    pd.swpInitial.hwnd             = NULLHANDLE;
    pd.swpInitial.ulReserved1      = 0;
    pd.swpInitial.ulReserved2      = 0;
    happ = WinStartApp( NULLHANDLE, &pd, url, NULL, 0 );
    return ( happ != NULLHANDLE );
}

static void detectBrowser()
{
    char *prfApp = "WPURLDEFAULTSETTINGS";

    if ( browserExe[0] == 0 )
    {
        PrfQueryProfileString( HINI_USER, prfApp, "DefaultBrowserExe", "",
                               browserExe, CCHMAXPATH );
        PrfQueryProfileString( HINI_USER, prfApp, "DefaultWorkingDir", "",
                               browserDir, CCHMAXPATH );
    }

    if ( browserExe[0] == 0 )
    {
        APIRET rc;
        rc = DosSearchPath( SEARCH_CUR_DIRECTORY | SEARCH_ENVIRONMENT | SEARCH_IGNORENETERRS,
                            "PATH", "NETSCAPE.EXE", browserExe, CCHMAXPATH );
        if ( rc != 0 ) {
            strcpy( browserExe , "" );
        }
    }
}


