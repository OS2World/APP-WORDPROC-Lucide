#define INCL_DOS
#define INCL_WIN
#include <os2.h>

#include <fstream>
#include <map>
#include <string>
using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <io.h>

#include "lucide.h"
#include "wwbtn.h"
#include "luutils.h"

#define LINEBUF_LEN     4096

static bool langLoaded = false;

static map<string,string> *langDefault = NULL;
static map<string,string> *langCurrent = NULL;

#define NUM_ESCAPES     2
static const char *escapes[NUM_ESCAPES][2] = { { "\\t", "\t" }, { "\\r", "\r" } };

static string unescapeControls( const char *s )
{
    string r = s;
    for ( int i = 0; i < NUM_ESCAPES; i++ )
    {
        const char *r_c = r.c_str();
        char *p = strstr( r_c, escapes[i][0] );
        if ( p != NULL )
        {
            int len = strlen( r_c ) + 1;
            char *tmp = new char[ len ];
            memset( tmp, 0, len );
            memcpy( tmp, r_c, p - r_c );
            strcat( tmp, escapes[i][1] );
            strcat( tmp, p + strlen( escapes[i][0] ) );
            r = tmp;
            delete tmp;
        }
    }
    return r;
}


static void loadLng( map<string,string> *array, const char *file, bool exitOnError )
{
    ifstream lngFile( file );
    if ( !lngFile )
    {
        if ( exitOnError )
        {
            char msgbuf1[ 500 ];
            char msgbuf2[ 100 ];
            snprintf( msgbuf1, sizeof( msgbuf1 ),
                      "Default language file \"%s\" not found!", file );
            snprintf( msgbuf2, sizeof( msgbuf2 ), "%s error!", appName );

            WinMessageBox( HWND_DESKTOP, HWND_DESKTOP, msgbuf1, msgbuf2,
                           10000, MB_CANCEL | MB_ERROR | MB_ICONHAND | MB_MOVEABLE );

            DosExit( EXIT_PROCESS, 1 );  // ??? exit() crashes
        }
        return;
    }
    else
    {
        char *line = new char[ LINEBUF_LEN ];

        while ( !lngFile.eof() )
        {
            char ch;
            lngFile.get( line, LINEBUF_LEN );
            lngFile.get( ch );
            if ( ( line[ 0 ] != '#' ) && ( line[ 0 ] != ' ' ) )
            {
                char *eqpos = NULL;
                if ( ( eqpos = strchr( line, '=' ) ) != NULL )
                {
                    *eqpos = '\0';
                    string key   = line;
                    string value = unescapeControls( eqpos + 1 );
                    (*array)[ key ] = value;
                }
            }
        }

        /*map<string,string>::const_iterator iter;
        for ( iter=array->begin(); iter != array->end(); iter++ )
        {
            cout << "K:" << (*iter).first.c_str()
                 << " V:" << (*iter).second.c_str() << endl;
        }*/
    }
}

static const char *lfilespec1 = "%sLUCIDE_%s.LNG";
static const char *lfilespec2 = "%sLUCIDE.LNG";

void loadLang()
{
    if ( langLoaded ) {
        return;
    }
    langLoaded = true;

    char appdir[ _MAX_PATH ];
    char drive[ _MAX_DRIVE ];
    char dir[ _MAX_DIR ];
    _splitpath( __argv[0], drive, dir, NULL, NULL );
    _makepath( appdir, drive, dir, NULL, NULL );

    langDefault = new map<string,string>;
    langCurrent = new map<string,string>;

    afbuf lfile( _MAX_PATH );

    snprintf( lfile.buffer, lfile.getSize(), lfilespec1, appdir, "EN" );
    if ( access( lfile.buffer, F_OK ) == 0 ) {
        loadLng( langDefault, lfile.buffer, true );
    }
    else {
        snprintf( lfile.buffer, lfile.getSize(), lfilespec2, appdir );
        loadLng( langDefault, lfile.buffer, true );
    }

    char *lng = getenv( "LANG" );
    if ( lng == NULL ) {
        return;
    }
    char *upos = strchr( lng, '_' );
    if ( upos == NULL ) {
        return;
    }
    int lngSpecLen = upos - lng;
    if ( lngSpecLen > 2 ) {
        return;
    }
    char lngSpec[ 4 ];
    memset( lngSpec, 0, sizeof( lngSpec ) );
    strncpy( lngSpec, lng, lngSpecLen );
    if ( stricmp( lngSpec, "EN" ) != 0 )
    {
        snprintf( lfile.buffer, lfile.getSize(), lfilespec1, appdir, lngSpec );
        loadLng( langCurrent, lfile.buffer, false );
    }
}

void localizeMenu( HWND hmenu )
{
    if ( hmenu == NULLHANDLE ) {
        return;
    }

    afbuf mtext( 1024 );

    SHORT id, len;
    SHORT cnt = (SHORT)WinSendMsg( hmenu, MM_QUERYITEMCOUNT, MPVOID, MPVOID );
    for ( SHORT i = 0; i < cnt; i++ )
    {
        id = (SHORT)WinSendMsg( hmenu, MM_ITEMIDFROMPOSITION, MPFROMSHORT( i ), MPVOID );

        len = (SHORT)WinSendMsg( hmenu, MM_QUERYITEMTEXT, MPFROM2SHORT( id, mtext.getSize() ),
                                 MPFROMP( mtext.buffer ) );

        if ( len > 0 )
        {
            string r = getLocalizedString( mtext.buffer );
            if ( r != mtext.buffer ) {
                WinSendMsg( hmenu, MM_SETITEMTEXT, MPFROMSHORT( id ), MPFROMP( r.c_str() ) );
            }
        }

        MENUITEM mitem = { 0 };
        BOOL itemQueried = (BOOL)WinSendMsg( hmenu, MM_QUERYITEM, MPFROM2SHORT( id, FALSE ),
                                             MPFROMP( &mitem ) );
        if ( itemQueried )
        {
            if ( mitem.afStyle & MIS_SUBMENU ) {
                localizeMenu( mitem.hwndSubMenu );
            }
        }
    }
}

void localizeDialog( HWND hdlg )
{
    if ( hdlg == NULLHANDLE ) {
        return;
    }

    afbuf itemtext( 256 );

    HWND  hwndNext;
    LONG  lText;
    HENUM henum = WinBeginEnumWindows( hdlg );

    while ( ( hwndNext = WinGetNextWindow( henum ) ) != NULLHANDLE )
    {
        char clname[ 5 ];
        WinQueryClassName( hwndNext, sizeof( clname ), clname );

        if ( clname[0] == '#' )
        {
            lText = WinQueryWindowText( hwndNext, itemtext.getSize(), itemtext.buffer );
            if ( lText )
            {
                string r = getLocalizedString( itemtext.buffer );
                if ( r != itemtext.buffer )
                {
                    if ( clname[1] == '5' ) { // static
                        if ( WinQueryWindowULong( hwndNext, QWL_STYLE ) & SS_TEXT ) {
                            toWordWrapLabel( hwndNext );
                        }
                    }

                    WinSetWindowText( hwndNext, r.c_str() );
                }
            }
        }
    }
    WinEndEnumWindows( henum );
}

string getLocalizedString( const char *t )
{
    map<string,string>::const_iterator iter;

    if ( ( iter = langCurrent->find( t ) ) == langCurrent->end() )
    {
        if ( ( iter = langDefault->find( t ) ) == langDefault->end() ) {
            return t;
        }
    }

    return (*iter).second;
}

void getLocalizedString( const char *key, LONG maxLen, char *buf )
{
    strncpy( buf, getLocalizedString( key ).c_str(), maxLen - 1 );
}

char *newstrdupL( const char *key )
{
    return newstrdup( getLocalizedString( key ).c_str() );
}

