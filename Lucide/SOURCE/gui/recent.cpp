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
#include <os2.h>

#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>

#include "recent.h"
#include "globals.h"
#include "luutils.h"
#include "Lucide_res.h"
#include "messages.h"

const char * const sRecentFiles = "RecentFiles";


RecentFiles::RecentFiles( HWND hMenu )
{
    hWndMenu = hMenu;

    MENUITEM mi = { 0 };
    WinSendMsg( hWndMenu, MM_QUERYITEM, MPFROM2SHORT( CM_RECENT, TRUE ), (MPARAM)&mi );
    hSubMenu = mi.hwndSubMenu;

    files = new std::vector<std::string>;
    clearList = newstrdupL( "MENU_CLEAR_LIST" );
    load();

    if ( files->size() == 0 ) {
        clearMenu();
    }
}

RecentFiles::~RecentFiles()
{
    delete files;
    delete clearList;
}

void RecentFiles::addFile( const char *f, bool atEnd )
{
    // if such item exist - erase it
    std::vector<std::string>::iterator iter;
    for ( iter = files->begin(); iter != files->end(); iter++ ) {
        if ( stricmp( (*iter).c_str(), f ) == 0 ) {
            files->erase( iter );
            break;
        }
    }

    if ( atEnd ) {
        files->push_back(  f );
    }
    else {
        // put to beginning
        files->insert( files->begin(), f );
    }

    // shrink to RECENT_SIZE
    while ( files->size() > RECENT_SIZE ) {
        files->pop_back();
    }

    fillSubmenu();
}

void RecentFiles::clear()
{
    files->clear();
    clearMenu();
}

void RecentFiles::fillSubmenu()
{
    clearMenu();

    MENUITEM mi = { 0 };
    int id = 1;
    std::vector<std::string>::const_iterator iter;
    for ( iter = files->begin(); iter != files->end(); iter++ )
    {
        char txt[ CCHMAXPATH + 10 ];
        snprintf( txt, sizeof( txt ), "~%d  %s", id, (*iter).c_str() );

        mi.iPosition   = MIT_END;
        mi.afStyle     = MIS_TEXT;
        mi.afAttribute = 0;
        mi.id          = CM_RECENT + id++;
        mi.hwndSubMenu = NULLHANDLE;
        mi.hItem       = 0;
        WinSendMsg( hSubMenu, MM_INSERTITEM, (MPARAM)&mi, MPFROMP( txt ) );
    }

    if ( files->size() > 0 )
    {
        WinEnableMenuItem( hWndMenu, CM_RECENT, TRUE );

        mi.iPosition   = MIT_END;
        mi.afStyle     = MIS_SEPARATOR;
        mi.afAttribute = 0;
        mi.id          = CM_RECENT + id++;
        mi.hwndSubMenu = NULLHANDLE;
        mi.hItem       = 0;
        WinSendMsg( hSubMenu, MM_INSERTITEM, (MPARAM)&mi, MPFROMP( "" ) );

        mi.iPosition   = MIT_END;
        mi.afStyle     = MIS_TEXT;
        mi.afAttribute = 0;
        mi.id          = CM_RECENTCLEAR;
        mi.hwndSubMenu = NULLHANDLE;
        mi.hItem       = 0;
        WinSendMsg( hSubMenu, MM_INSERTITEM, (MPARAM)&mi, MPFROMP( clearList ) );
    }
}

void RecentFiles::load()
{
    int bufsize = ( CCHMAXPATH * RECENT_SIZE ) + RECENT_SIZE + 2;
    char *buf = new char[ bufsize ];
    memset( buf, 0, bufsize );

    PrfQueryProfileString( HINI_USERPROFILE, appName, sRecentFiles, "", buf, bufsize );

    char *p = strtok( buf, "|" );
    while ( p != NULL ) {
        addFile( p, true );
        p = strtok( NULL, "|" );
    }

    delete buf;
}

void RecentFiles::save()
{
    std::string s = "";
    std::vector<std::string>::const_iterator iter;
    for ( iter = files->begin(); iter != files->end(); iter++ )
    {
        s += *iter;
        s += '|';
    }

    PrfWriteProfileString( HINI_USERPROFILE, appName, sRecentFiles, s.c_str() );
}


void RecentFiles::clearMenu()
{
    int id = CM_RECENT + 1;
    while ( WinSendMsg( hSubMenu, MM_DELETEITEM,
                        MPFROM2SHORT( id++, TRUE ), MPVOID ) != 0 );
    WinEnableMenuItem( hWndMenu, CM_RECENT, FALSE );
}

std::string RecentFiles::getFile( USHORT cmd )
{
    cmd = ( cmd - CM_RECENT ) - 1;
    return (*files)[ cmd ];
}

