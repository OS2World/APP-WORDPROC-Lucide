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

#include "globals.h"
#include "wwbtn.h"
#include "luutils.h"

#define LINEBUF_LEN     4096

static bool langLoaded = false;

static map<string,string> *langDefault = NULL;
static map<string,string> *langCurrent = NULL;


#define NUM_ESCAPES 3
static const char *escapes[NUM_ESCAPES][2] = {
    { "\\t", "\t" }, { "\\r", "\r" }, { "%APPNAME%", appName } };

static string unescapeControls( const char *s )
{
    string r = s;
    for ( int i = 0; i < NUM_ESCAPES; i++ )
    {
        string::size_type startpos = 0;
        string::size_type findpos = string::npos;
        while ( ( findpos = r.find( escapes[i][0], startpos ) ) != string::npos ) {
            r.replace( findpos, strlen( escapes[i][0] ), escapes[i][1] );
            startpos = findpos + 1;
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

static const char *lfilespec1 = "%sLUCIDE_%s_%s.LNG";
static const char *lfilespec2 = "%sLUCIDE_%s.LNG";
static const char *lfilespec3 = "%sLUCIDE.LNG";

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

    snprintf( lfile.buffer, lfile.getSize(), lfilespec2, appdir, "EN" );
    if ( access( lfile.buffer, F_OK ) == 0 ) {
        loadLng( langDefault, lfile.buffer, true );
    }
    else {
        snprintf( lfile.buffer, lfile.getSize(), lfilespec3, appdir );
        loadLng( langDefault, lfile.buffer, true );
    }

    char *lng = getenv( "LANG" );
    if ( lng == NULL ) {
        return;
    }

    // Find language specifier
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

    // Find territory specifier
    char *lrest = upos + 1;
    char terrSpec[ 4 ];
    memset( terrSpec, 0, sizeof( terrSpec ) );
    if ( strlen( lrest ) >= 2 ) {
        strncpy( terrSpec, lrest, 2 );
    }

    bool nlsLoaded = false;
    if ( terrSpec[0] != 0 )
    {
        // First, search the file with territory specifier
        snprintf( lfile.buffer, lfile.getSize(), lfilespec1, appdir, lngSpec, terrSpec );
        if ( access( lfile.buffer, F_OK ) == 0 ) {
            // File with territory specifier exist, load it
            loadLng( langCurrent, lfile.buffer, false );
            nlsLoaded = true;
        }

    }
    if ( !nlsLoaded )
    {
        // File with territory specifier not found, load file without territory specifier
        snprintf( lfile.buffer, lfile.getSize(), lfilespec2, appdir, lngSpec );
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

