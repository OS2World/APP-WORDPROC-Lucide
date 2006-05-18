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
    char drive[ _MAX_DRIVE ];
    char dir[ _MAX_DIR ];
    _splitpath( __argv[0], drive, dir, NULL, NULL );
    _makepath( buffer, drive, dir, NULL, NULL );
    strcat( buffer, "\\LU*.DLL" );

    // enum plugins, except for LUDOC.DLL, which is 'null' plugin
    struct find_t ffblk;
    unsigned done = _dos_findfirst( buffer, _A_RDONLY | _A_NORMAL, &ffblk );
    while ( done == 0 )
    {
        if ( stricmp( ffblk.name, "LUDOC.DLL" ) != 0 ) {
            loadPlugin( ffblk.name );
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

void PluginManager::loadPlugin( const char *dllname )
{
    // Function pointer variables
    LuDocument * APIENTRY (*pCreateObject)();
    char * APIENTRY (*pGetSupportedExtensions)();
    char * APIENTRY (*pGetDescription)();

    // cut DLL name at last point
    char *lpoint = strrchr( dllname, '.' );
    *lpoint = '\0';

    // load a DLL
    HMODULE h = NULLHANDLE;
    bool res = false;
    do
    {
        if ( DosLoadModule( NULL, 0, dllname, &h ) != 0 )
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

