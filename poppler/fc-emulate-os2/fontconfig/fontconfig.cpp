/*
 * Copyright (c) 2006, Eugene Romanenko, netlabs.org
 *
 *----------------------------------------------------------------------
 * This file is part of poppler plugin for Lucide (lupoppler).
 *
 *  lupoppler is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  lupoppler is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *----------------------------------------------------------------------
 */

// This file is fontconfig replacement which emulates functions
// used by poppler.

#define INCL_DOS
#define INCL_WIN
#if defined(__EMX__)
#define OS2EMX_PLAIN_CHAR
#endif
#include <os2.h>

#include <map>
#include <string>
using namespace std;

#include <stdio.h>
#include <string.h>

#if defined( __WATCOMC__ )
#include <dos.h>
#else
#include <io.h>
#include <sys/stat.h>
#endif

#include "fontconfig.h"

#include <ft2build.h>
#include FT_FREETYPE_H


static char *newstrdup( const char *s )
{
    if ( s == NULL ) {
        return NULL;
    }
    char *temp = new char[ strlen( s ) + 1 ];
    strcpy( temp, s );
    return temp;
}

static string rtrim( const char *p )
{
    size_t len = strlen( p );
    char *temp = new char[ len + 1 ];
    strcpy( temp, p );

    for ( int i = len - 1; i >= 0; i-- )
    {
        if ( isspace( temp[ i ] ) ) {
            temp[ i ] = 0;
        }
        else {
            break;
        }
    }
    string r = temp;
    delete temp;
    return r;
}

// er_tokens - utility class
class er_tokens
{
    private:
        char   separator;
        size_t len;
        char   *str;
        char   *tmp;
        size_t curoffs;
    public:
        er_tokens( const char *s, char sep );
        ~er_tokens();
        char *nexttoken();
};

er_tokens::er_tokens( const char *s, char sep )
{
    separator = sep;
    len = strlen( s );
    str = new char[ len + 1 ];
    strcpy( str , s );
    tmp = new char[ len + 1 ];
    curoffs = 0;
}

er_tokens::~er_tokens()
{
    delete str;
    delete tmp;
}

char *er_tokens::nexttoken()
{
    if ( curoffs >= len ) {
        return NULL;
    }

    memset( tmp, 0, len + 1 );

    if ( str[ curoffs ] == separator ) {
        curoffs++;
    }
    else
    {
        char *t1 = str + curoffs;
        char *t2 = tmp;

        while ( ( *t1 != separator ) && ( *t1 != 0 ) ) {
            *t2++ = *t1++;
            curoffs++;
        }
        curoffs++;
    }

    return tmp;
}

struct FcfRecord
{
    char filename[ _MAX_PATH ];
    char family[ 64 ];
    char style[ 64 ];
    long size;
    long modified;
};

static map<string,string>    *fontmap = NULL;   // font name / font filename
static map<string,FcfRecord> *fcfmap = NULL;    // font filename / FcfRecord
static bool fcfChanged = false;
static FT_Library ftlib;


struct _FcPattern
{
    char *family;
    int slant;
    int weight;
    int width;
    int spacing;
    char *lang;

    char *filename;
};


FcConfig *FcConfigGetCurrent()
{
    // STUB
    return NULL;
}

FcBool FcConfigSubstitute( FcConfig *config, FcPattern *p, FcMatchKind kind )
{
    // STUB
    return FcTrue;
}


void FcDefaultSubstitute( FcPattern *pattern )
{
    // STUB
}

void FcFontSetDestroy( FcFontSet *s )
{
    for ( int i = 0; i < s->nfont; i++ ) {
        FcPatternDestroy( s->fonts[i] );
    }
    delete s->fonts;
    delete s;
}

static void ftLoad( char *fn )
{
    //printf( "Loading font %s\n", fn );
    int l = strlen( fn );
    if ( l < 5 ) {
        return;
    }

    if ( ( stricmp( fn + ( l - 4 ), ".OFM" ) != 0 ) &&
         ( stricmp( fn + ( l - 4 ), ".PFB" ) != 0 ) &&
         ( stricmp( fn + ( l - 4 ), ".PFA" ) != 0 ) &&
         ( stricmp( fn + ( l - 4 ), ".TTF" ) != 0 ) &&
         ( stricmp( fn + ( l - 4 ), ".TTC" ) != 0 ) )
    {
        return;
    }

    if ( stricmp( fn + ( l - 4 ), ".OFM" ) == 0 ) {
        fn[ l - 3 ] = 'P';
        fn[ l - 1 ] = 'B';
    }

    string familyName = "";
    string styleName = "";

    bool needread = false;
    struct stat st = {0};
    stat( fn, &st );

    if ( fcfmap->find( fn ) == fcfmap->end() ) {
        needread = true;
    }
    else {
        FcfRecord r = (*fcfmap)[ fn ];
        if ( ( r.size == st.st_size ) && ( r.modified == st.st_mtime ) ) {
            familyName = rtrim( r.family );
            styleName = rtrim( r.style );
        }
        else {
            needread = true;
        }
    }

    if ( needread )
    {
        //printf( "read: %s\n", fn );
        fcfChanged = true;

        FT_Face ftface;
        if ( FT_New_Face( ftlib, fn, 0, &ftface ) ) {
            return;
        }
        //printf( "readed, family_name: %s   style_name: %s\n", ftface->family_name, ftface->style_name );

        if ( ( ftface->family_name == NULL ) || ( ftface->style_name == NULL ) ) {
            printf( "Broken font file: %s\n", fn );
            FT_Done_Face( ftface );
            return;
        }

        familyName = rtrim( ftface->family_name );
        styleName = rtrim( ftface->style_name );

        FT_Done_Face( ftface );
    }

    string key = familyName;
    if ( stricmp( styleName.c_str(), "regular" ) != 0 &&
         stricmp( styleName.c_str(), "book" ) != 0 ) {
        key += ' ';
        key += styleName;
    }

    char *tmpkey = newstrdup( key.c_str() );
    strlwr( tmpkey );
    key = tmpkey;
    delete tmpkey;

    (*fontmap)[ key ] = fn;
    //printf( "%s: %s\n", fn, key.c_str() );

    FcfRecord fcfr = {0};
    strcpy( fcfr.filename, fn );
    strncpy( fcfr.family, familyName.c_str(), sizeof( fcfr.family ) - 1 );
    strncpy( fcfr.style, styleName.c_str(), sizeof( fcfr.style ) - 1 );
    fcfr.size = st.st_size;
    fcfr.modified = st.st_mtime;

    (*fcfmap)[ fn ] = fcfr;
    //printf( "Done loading font %s\n", fn );
}


static string getFcfName()
{
    char fullpath[ _MAX_PATH ];
    char drive[ _MAX_DRIVE ];
    char dir[ _MAX_DIR ];
    char fname[ _MAX_FNAME ];
#if defined( __WATCOMC__ )
    _splitpath( __argv[0], drive, dir, fname, NULL );
#else
    _execname( fullpath, sizeof(fullpath) );
    _splitpath( fullpath, drive, dir, fname, NULL );
#endif
    strlwr( fname );
    _makepath( fullpath, drive, dir, fname, ".fcf" );
    return fullpath;
}

/*static void loadDir( string path )
{
    string pathnam = path + "\\*";

    struct find_t ffblk;
    unsigned done = _dos_findfirst( pathnam.c_str(), _A_RDONLY | _A_NORMAL, &ffblk );
    while ( done == 0 )
    {
        string fname = path + '\\' + ffblk.name;
        char *fn = newstrdup( fname.c_str() );
        ftLoad( fn );
        delete fn;
        done = _dos_findnext( &ffblk );
    }
    _dos_findclose( &ffblk );
} */

static void saveFcf( const char *fn )
{
    FILE *f = NULL;

    if ( ( f = fopen( fn, "w" ) ) == NULL ) {
        return;
    }

    fputs( "# Font configuration file.\n" \
           "# Auto-generated file, do not edit!\n", f );

    map<string,FcfRecord>::const_iterator iter;
    for ( iter = fcfmap->begin(); iter != fcfmap->end(); iter++ )
    {
        FcfRecord r = (*iter).second;
        fprintf( f, "|%s|%s|%s|%ld|%ld|\n", r.filename, r.family, r.style,
                 r.size, r.modified );
    }
    fclose( f );
}

#define READ_BUF    4096
static void readFcf( const char *fn )
{
    if ( access( fn, 0 ) != 0 ) {
        return;
    }

    FILE *f = NULL;

    if ( ( f = fopen( fn, "r" ) ) == NULL ) {
        return;
    }

    char *buf = new char[ READ_BUF ];

    while( fgets( buf, READ_BUF, f ) != NULL )
    {
        if ( buf[0] == '|' )
        {
            FcfRecord r = {0};

            er_tokens tkn( buf + 1, '|' );
            strncpy( r.filename, tkn.nexttoken(), sizeof( r.filename ) - 1 );
            strncpy( r.family, tkn.nexttoken(), sizeof( r.family ) - 1 );
            strncpy( r.style, tkn.nexttoken(), sizeof( r.style ) - 1 );
            r.size = atol( tkn.nexttoken() );
            r.modified = atol( tkn.nexttoken() );

            (*fcfmap)[ r.filename ] = r;
        }
    }

    fclose( f );
}

#define FLIST_SIZE  (1024*64)


FcBool FcInit()
{
    if ( fontmap != NULL ) {
        return FcTrue;
    }

    if ( FT_Init_FreeType( &ftlib ) ) {
        return FcFalse;
    }

    fcfChanged = false;

    string fcfname = getFcfName();

    fontmap = new map<string,string>;
    fcfmap  = new map<string,FcfRecord>;

    readFcf( fcfname.c_str() );

    // enum installed fonts
    ULONG uldrv = 0;
    DosQuerySysInfo( QSV_BOOT_DRIVE, QSV_BOOT_DRIVE, &uldrv, sizeof( ULONG ) );
    char drv = (char)( uldrv + '@' );

    const char *pmfonts = "PM_Fonts";
    char *fnames = new char[ FLIST_SIZE ];
    memset( fnames, 0, FLIST_SIZE );
    PrfQueryProfileString( HINI_USER, pmfonts, NULL, NULL, fnames, FLIST_SIZE );

    char *fn1 = new char[ CCHMAXPATH ];
    char *fn2 = new char[ CCHMAXPATH ];
    int noffset = 0;
    while ( fnames[ noffset ] != 0 )
    {
        const char *fname = fnames + noffset;

        PrfQueryProfileString( HINI_USER, pmfonts, fname, "", fn1, CCHMAXPATH );

        if ( fn1[ 0 ] == '\\' ) {
            fn2[ 0 ] = drv;
            fn2[ 1 ] = ':';
            fn2[ 2 ] = 0;
            strcat( fn2, fn1 );
        }
        else {
            strcpy( fn2, fn1 );
        }

        ftLoad( fn2 );

        noffset += ( strlen( fname ) + 1 );
    }
    delete fn1;
    delete fn2;
    delete fnames;

    // TODO: load some fonts dir?
    //loadDir( "Fonts" );

    if ( fcfChanged ) {
        saveFcf( fcfname.c_str() );
    }

    return FcTrue;
}


//
// Assume fonts "Times New Roman", "Helvetica" and "Courier" always
// present on any system (see GPI Guide and Reference, section
// "Fonts" -> "About Fonts" -> "PM-Supplied Fonts").
//
#define DEFAULT_SERIF_FONT          "times new roman"
#define DEFAULT_SERIF_FONTJA       "times new roman wt j"
#define DEFAULT_SANSSERIF_FONT      "helvetica"
#define DEFAULT_MONOSPACED_FONT     "courier"
#define DEFAULT_SYMBOL_FONT         "symbol set"

static bool isSansserif( const char *family )
{
    return ( ( strstr( family, "swiss" ) != NULL ) ||
             ( strstr( family, "sans" ) != NULL ) ||
             ( strcmp( family, "arial" ) == 0 ) ||
             ( strcmp( family, "tahoma" ) == 0 ) ||
             ( strcmp( family, "verdana" ) == 0 ) );
}

static string buildFontKey( FcPattern *p )
{
    string key = p->family;

    // From http://en.wikipedia.org/wiki/Portable_Document_Format:
    //
    // There are fourteen typefaces that have a special significance to PDF
    // documents:
    //
    //  * Times (v3) (in regular, italic, bold, and bold italic)
    //  * Courier (in regular, oblique, bold and bold oblique)
    //  * Helvetica (v3) (in regular, oblique, bold and bold oblique)
    //  * Symbol
    //  * Zapf Dingbats
    //
    // These fonts, sometimes referred to as the "base fourteen fonts" should
    // always be present (actually present or a close substitute) and so need
    // not be embedded in a PDF.[46]  PDF viewers must know about the metrics
    // of these fonts. Other fonts may be substituted if they are not embedded
    // in a PDF.
    //
    // The following code is based on this information and guarantees that we
    // always return a valid font for those (except Zapf Dingbats for which we
    // don't have a pre-installed OS/2 font).

    bool ignoreStyle = false;

    if ( fontmap->find( key ) == fontmap->end() ) {
        // not found: try substitutions
        if (!stricmp(p->lang, "ja"))
        {
            key = DEFAULT_SERIF_FONTJA;
        } else {

        if ( p->spacing == FC_MONO ) {
            key = DEFAULT_MONOSPACED_FONT;
        } else {
            if ( isSansserif( p->family ) ) {
                key = DEFAULT_SANSSERIF_FONT;
            } else {
                if ( key == "symbol" ) {
                    ignoreStyle = true;
                    key = "opensymbol";
                    if ( fontmap->find( key ) == fontmap->end() )
                        key = DEFAULT_SYMBOL_FONT;
                } else if ( key == "zapfdingbats" || key == "zapf dingbats" ) {
                    ignoreStyle = true;
                    key = "dejavu sans";
                    // last resort, quite meaningless but we must provide something
                    if ( fontmap->find( key ) == fontmap->end() )
                        key = DEFAULT_SYMBOL_FONT;
                } else {
                        key = DEFAULT_SERIF_FONT;
                }
            }
        }
       }
    }

    if ( !ignoreStyle ) {
        if ( p->weight > FC_WEIGHT_NORMAL ) {
            key += ' ';
            key += "bold";
        }
        if ( (p->slant == FC_SLANT_ITALIC) || (p->slant == FC_SLANT_OBLIQUE) ) {
            key += ' ';
            key += "italic";
        }
    }

    return key;
}

FcFontSet *FcFontSort( FcConfig *config, FcPattern *p, FcBool trim,
                       FcCharSet **csp, FcResult *result )
{
    // we need to make sure the fonfconfig is initialised.
    if (!FcInit())
       {
          return NULL;
       }

    FcPattern *pat = new FcPattern;
    pat->family   = newstrdup( p->family );
    pat->slant    = p->slant;
    pat->weight   = p->weight;
    pat->width    = p->width;
    pat->spacing  = p->spacing;
    pat->lang     = newstrdup( p->lang );
    pat->filename = NULL;

    string key = buildFontKey( pat );
    pat->filename = newstrdup( (*fontmap)[ key ].c_str() );

    printf( "fontfamily: %s --> MATCHED STYLE: %s, FILENAME: %s\n", pat->family, key.c_str(), pat->filename );
    printf("SLANT: %d, WEIGHT:%d, WIDTH:%d, SPACING:%d, LANG:%s\n", pat->slant, pat->weight, pat->width, pat->spacing, pat->lang);

    FcFontSet *fs = new FcFontSet;
    fs->nfont = 1;
    fs->sfont = 1;
    fs->fonts = new FcPattern *[ 1 ];
    fs->fonts[ 0 ] = pat;

    return fs;
}

void FcFontSetSortDestroy( FcFontSet *fs )
{
    // STUB
}

void FcPatternDestroy( FcPattern *p )
{
    delete p->family;
    delete p->lang;
    delete p->filename;
}

FcResult FcPatternGetInteger( const FcPattern *p, const char *object, int n, int *i )
{
    // STUB
    *i = 0;
    return FcResultMatch;
}

FcResult FcPatternGetString( const FcPattern *p, const char *object, int n, FcChar8 **s )
{
    if ( strcmp( object, FC_FILE ) == 0 )
    {
        *s = p->filename;
        return FcResultMatch;
    }
    return FcResultNoMatch;
}

FcPattern *FcPatternBuild( void *,
                    const char *fcFamily, FcType tFamily, const char *family,
                    const char *fcLang, FcType tLang, const char *lang, void * )
{
//    printf( "FAMILY: %s, LANG: %s\n", family, lang );

    FcPattern *p = new FcPattern;
    p->family   = newstrdup( family );
    strlwr( p->family );
    p->slant    = -1;
    p->weight   = -1;
    p->width    = -1;
    p->spacing  = -1;
    p->lang     = newstrdup( lang );
    p->filename = NULL;

    return p;
}

void FcPatternAddInteger(FcPattern *p, const char *fcType, int value)
{
// handle all possible int values
   if (!strcmp(fcType, FC_SLANT)) {
      p->slant = value;
   }

   if (!strcmp(fcType, FC_WEIGHT)) {
      p->weight = value;
   }

   if (!strcmp(fcType, FC_WIDTH)) {
      p->width = value;
   }

   if (!strcmp(fcType, FC_SPACING)) {
      p->spacing = value;
   }

//   printf("FAMILY: %s, SLANT: %d, WEIGHT:%d, WIDTH:%d, SPACING:%d\n", p->family, p->slant, p->weight, p->width, p->spacing);

   return;
}

