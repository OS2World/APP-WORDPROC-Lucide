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
#include <fcntl.h>
#include <stdio.h>
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
    // and Lucide.dll, which is not a plugin.
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
    LuDocument       * APIENTRY (*pCreateObject)()           = NULL;
    char             * APIENTRY (*pGetSupportedExtensions)() = NULL;
    char             * APIENTRY (*pGetDescription)()         = NULL;
    LuSignatureCheck * APIENTRY (*pGetSignatureCheck)()      = NULL;

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

        // optional
        if ( DosQueryProcAddr( h, 0, "getSignatureCheck", (PFN *)&pGetSignatureCheck ) != 0 ) {
            pGetSignatureCheck = NULL;
        }

        res = true;
    } while (0);

    if ( res )
    {
        PluginInfo pi;
        pi.handle      = h;
        pi.name        = dllname;
        pi.extensions  = pGetSupportedExtensions();
        pi.description = pGetDescription();
        pi.signatures  = ( pGetSignatureCheck == NULL ) ? NULL : pGetSignatureCheck();

        plugins->push_back( pi );
    }
}

static LuDocument *createDocFromDll( HMODULE handle, bool checkOnly )
{
    LuDocument * APIENTRY (*pCreateObject)() = NULL;

    if ( DosQueryProcAddr( handle, 0, "createObject", (PFN *)&pCreateObject ) == 0 )
    {
        if ( checkOnly ) {
            return (LuDocument *)TRUE;
        }
        else {
            return pCreateObject();
        }
    }

    return NULL;
}

// returns NULL if no suitable plugin found
// if checkOnly is true - just check if suitable plugin exist
LuDocument *PluginManager::createDocumentForExt( const char *ext, bool checkOnly )
{
    if ( ext == NULL ) {
        return NULL;
    }

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
            LuDocument *d = createDocFromDll( pi->handle, checkOnly );
            if ( d != NULL )
            {
                delete cExt;
                delete cExts;
                return d;
            }
        }

        delete cExt;
        delete cExts;
    }

    return NULL;
}

static bool checkSignature( LuSignature *signature, int h )
{
    lseek( h, signature->offset, ( signature->origin == 0 ) ? SEEK_SET : SEEK_END );
    unsigned char *buf = new char[ signature->length ];
    read( h, buf, signature->length );
    bool result = ( memcmp( signature->data, buf, signature->length ) == 0 );
    delete buf;
    return result;
}

static bool checkSignatureList( LuSignatureList *siglist, int h )
{
    bool result = true;

    // all signatures must be checked for positive result
    for ( unsigned long i = 0; i < siglist->count; i++ )
    {
        if ( !checkSignature( &(siglist->signatures[ i ]), h ) ) {
            result = false;
            break;
        }
    }

    return result;
}

static bool checkSignatures( LuSignatureCheck *signatures, const char *file )
{
    int h = open( file, O_RDONLY | O_BINARY );

    if ( h == -1 ) {
        return false;
    }

    bool result = false;

    // if one signature list checked - result is positive
    for ( unsigned long i = 0; i < signatures->count; i++ )
    {
        if ( result = checkSignatureList( &(signatures->slists[ i ]), h ) ) {
            break;
        }
    }
    close( h );

    return result;
}

// returns NULL if no suitable plugin found
// if checkOnly is true - just check if suitable plugin exist
LuDocument *PluginManager::createDocumentForFile( const char *file, bool checkOnly )
{
    LuDocument *ld = NULL;

    // Search by extension
    char *ext = strrchr( file, '.' );
    if ( ext != NULL ) {
        ld = createDocumentForExt( ext + 1, checkOnly );
    }

    if ( ld != NULL ) {
        return ld;
    }

    // Search by checkstruct
    for ( int i = 0; i < plugins->size(); i++ )
    {
        PluginInfo *pi = &(*plugins)[ i ];

        if ( pi->signatures != NULL )
        {
            if ( checkSignatures( pi->signatures, file ) )
            {
                LuDocument *d = createDocFromDll( pi->handle, checkOnly );
                if ( d != NULL ) {
                    return d;
                }
            }
        }
    }


    // Search by isFileSupported()
    BOOL APIENTRY (*pIsFileSupported)(PCSZ) = NULL;

    for ( int i = 0; i < plugins->size(); i++ )
    {
        PluginInfo *pi = &(*plugins)[ i ];

        if ( DosQueryProcAddr( pi->handle, 0, "isFileSupported",
                               (PFN *)&pIsFileSupported ) == 0 )
        {
            if ( pIsFileSupported( file ) )
            {
                LuDocument *d = createDocFromDll( pi->handle, checkOnly );
                if ( d != NULL ) {
                    return d;
                }
            }
        }
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
        while ( p != NULL ) {
            cRet += "*.";
            cRet += p;
            cRet += ";";
            p = strtok( NULL, ";" );
        }
    }
    return cRet;
}


