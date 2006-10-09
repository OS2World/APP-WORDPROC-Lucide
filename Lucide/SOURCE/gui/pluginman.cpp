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
#include <os2.h>

#include "pluginman.h"
#include "luutils.h"
#include <dos.h>
#include <ludoc.xh>


PluginManager::PluginManager()
{
    plugins = new PluginInfoList;

    // Find exe path
    char buffer[ _MAX_PATH ];
    char path[ _MAX_PATH ];
    char drive[ _MAX_DRIVE ];
    char dir[ _MAX_DIR ];
    _splitpath( __argv[0], drive, dir, NULL, NULL );
    _makepath( path, drive, dir, NULL, NULL );
    strcpy( buffer, path );
    strcat( buffer, "LU*.DLL" );

    // enum plugins, (LU*.DLL) except for LUDOC.DLL, which is 'null' plugin
    // and Lucide.dll, which isn't plugin.
    struct find_t ffblk;
    unsigned done = _dos_findfirst( buffer, _A_RDONLY | _A_NORMAL, &ffblk );
    while ( done == 0 )
    {
        if ( ( stricmp( ffblk.name, "LUDOC.DLL" ) != 0 ) &&
             ( stricmp( ffblk.name, "LUCIDE.DLL" ) != 0 ) )
        {
            loadPlugin( path, ffblk.name );
        }
        done = _dos_findnext( &ffblk );
    }
    _dos_findclose( &ffblk );
}

PluginManager::~PluginManager()
{
    for ( int i = 0; i < plugins->size(); i++ )
    {
        PluginInfo *pi = &(*plugins)[ i ];
        DosFreeModule( pi->handle );
        //printf( "NAME: %s  EXT: %s  DESC: %s\n", pi->name.c_str(),
        //        pi->extensions.c_str(), pi->description.c_str() );
    }
    delete plugins;
}

void PluginManager::loadPlugin( const char *path, const char *dllname )
{
    // Function pointer variables
    LuDocument * APIENTRY (*pCreateObject)();
    char * APIENTRY (*pGetSupportedExtensions)();
    char * APIENTRY (*pGetDescription)();

    std::string fulldllname = path;
    fulldllname += dllname;

    // cut DLL name at last point
    char *lpoint = strrchr( dllname, '.' );
    *lpoint = '\0';

    // load a DLL
    HMODULE h = NULLHANDLE;
    bool res = false;
    do
    {
        if ( DosLoadModule( NULL, 0, fulldllname.c_str(), &h ) != 0 )
            break;
        if ( DosQueryProcAddr( h, 0, "createObject", (PFN *)&pCreateObject ) != 0 )
            break;
        if ( DosQueryProcAddr( h, 0, "getSupportedExtensions", (PFN *)&pGetSupportedExtensions ) != 0 )
            break;
        if ( DosQueryProcAddr( h, 0, "getDescription", (PFN *)&pGetDescription ) != 0 )
            break;

        res = true;
    } while (0);

    if ( res )
    {
        PluginInfo pi;
        pi.handle = h;
        pi.name = dllname;
        pi.extensions = pGetSupportedExtensions();
        pi.description = pGetDescription();

        plugins->push_back( pi );
    }
}


// returns NULL if not suitable plugin found
// if checkOnly is true - just check if suitable plugin exist
LuDocument *PluginManager::createDocumentForExt( const char *ext, bool checkOnly )
{
    if ( ext == NULL ) {
        return NULL;
    }

    LuDocument * APIENTRY (*pCreateObject)();

    for ( int i = 0; i < plugins->size(); i++ )
    {
        PluginInfo *pi = &(*plugins)[ i ];

        char *cExt = new char[ strlen( ext ) + 5 ];
        strcpy( cExt, ";" );
        strcat( cExt, ext );
        strcat( cExt, ";" );
        strupr( cExt );

        char *cExts = new char[ pi->extensions.length() + 5 ];
        strcpy( cExts, ";" );
        strcat( cExts, pi->extensions.c_str() );
        strcat( cExts, ";" );
        strupr( cExts );

        if ( strstr( cExts, cExt ) != NULL )
        {
            if ( DosQueryProcAddr( pi->handle, 0, "createObject",
                                   (PFN *)&pCreateObject ) == 0 )
            {
                delete cExt;
                delete cExts;

                if ( checkOnly ) {
                    return (LuDocument *)TRUE;
                }
                else {
                    return pCreateObject();
                }
            }
        }

        delete cExt;
        delete cExts;
    }

    return NULL;
}


std::string PluginManager::getExtsMask()
{
    std::string cRet = "";

    for ( int i = 0; i < plugins->size(); i++ )
    {
        PluginInfo *pi = &(*plugins)[ i ];
        char *tmpexts = newstrdup( pi->extensions.c_str() );
        char *p = strtok( tmpexts, ";" );
        while( p != NULL ) {
            cRet += "*.";
            cRet += p;
            cRet += ";";
            p = strtok( NULL, ";" );
        }
    }
    return cRet;
}

