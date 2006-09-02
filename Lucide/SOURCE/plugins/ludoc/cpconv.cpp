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

#include <string.h>
#include <malloc.h>
#include <stdio.h>

#include <uconv.h>


class cpconv
{
    protected:
        int  err;
        void *objtoucs;
        void *objfromucs;
    public:
        cpconv( int cpfrom, int cpto = 0 );
        cpconv( UniChar *cpfrom, UniChar *cpto );
        ~cpconv();
        int conv( int chfrom );
        int conv( const char **in, size_t *in_left, char **out, size_t *out_left );
};

cpconv::cpconv( UniChar *cpfrom, UniChar *cpto )
{
    err = 0;
    int         rc = ULS_SUCCESS;

    rc = UniCreateUconvObject( cpfrom, &objtoucs );
    if (rc != ULS_SUCCESS)
    {
        err = 1;
        return;
    }

    uconv_attribute_t attr;
    UniQueryUconvObject(objtoucs, &attr, sizeof(attr), NULL, NULL, NULL);
    attr.converttype &= ~(CVTTYPE_CTRL7F | CVTTYPE_PATH);
    UniSetUconvObject(objtoucs, &attr);

    rc = UniCreateUconvObject( cpto, &objfromucs );
    if (rc != ULS_SUCCESS)
    {
        UniFreeUconvObject( objtoucs );
        err = 1;
        return;
    }
    UniQueryUconvObject(objfromucs, &attr, sizeof(uconv_attribute_t), NULL, NULL, NULL);
    attr.options = UCONV_OPTION_SUBSTITUTE_BOTH;
    UniSetUconvObject(objfromucs, &attr);
}

cpconv::cpconv( int cpfrom, int cpto )
{
    err = 0;

    UniChar     ucs_code_page[12];
    size_t      num_elems = 12;
    int         rc = ULS_SUCCESS;

    rc = UniMapCpToUcsCp(cpfrom, ucs_code_page, num_elems);
    if (rc != ULS_SUCCESS)
    {
        err = 1;
        return;
    }

    rc = UniCreateUconvObject(ucs_code_page, &objtoucs);
    if (rc != ULS_SUCCESS)
    {
        err = 1;
        return;
    }

    uconv_attribute_t attr;
    UniQueryUconvObject(objtoucs, &attr, sizeof(attr), NULL, NULL, NULL);
    attr.converttype &= ~(CVTTYPE_CTRL7F | CVTTYPE_PATH);
    UniSetUconvObject(objtoucs, &attr);

    rc = UniMapCpToUcsCp(cpto, ucs_code_page, num_elems);
    if (rc != ULS_SUCCESS)
    {
        UniFreeUconvObject( objtoucs );
        err = 1;
        return;
    }

    rc = UniCreateUconvObject(ucs_code_page, &objfromucs);
    if (rc != ULS_SUCCESS)
    {
        UniFreeUconvObject( objtoucs );
        err = 1;
        return;
    }
    UniQueryUconvObject(objfromucs, &attr, sizeof(uconv_attribute_t), NULL, NULL, NULL);
    attr.options = UCONV_OPTION_SUBSTITUTE_BOTH;
    UniSetUconvObject(objfromucs, &attr);
}

cpconv::~cpconv()
{
    if ( !err )
    {
        UniFreeUconvObject( objtoucs );
        UniFreeUconvObject( objfromucs );
    }
}

// convert one char
int cpconv::conv( int chfrom )
{
    int rc = ULS_SUCCESS;
    size_t ns = 0;
    int chto = 0;

    if ( err )  return chfrom;

    size_t len = 1;
    UniChar unichar;
    UniChar *punichar = &unichar;
    void *pchfrom = &chfrom;
    void *pchto = &chto;

    rc = UniUconvToUcs( objtoucs, &pchfrom, &len, &punichar, &len, &ns);
    if ( rc != ULS_SUCCESS )  return chfrom;

    len = 1;
    punichar = &unichar;
    ns = 0;
    rc = UniUconvFromUcs( objfromucs, &punichar, &len, &pchto, &len, &ns);
    if ( rc != ULS_SUCCESS )  return chfrom;

    return chto;
}

int cpconv::conv( const char **in, size_t *in_left, char **out, size_t *out_left )
{
    int       rc;
    size_t    sl;
    size_t    nonid;
    UniChar  *ucs;
    UniChar  *orig_ucs;
    size_t    retval = 0;

    if (!in || !*in) {
        return 0;
    }

    sl =  *in_left;
    //ucs = new UniChar[ sl ];
    // have crashes in libc memmanager due to frequent alloc/free
    // use system malloc routines as workaround
    DosAllocMem( (PPVOID)&ucs, sl * sizeof( UniChar ), fALLOC );
    orig_ucs = ucs;

    rc = UniUconvToUcs( objtoucs, (void **)in, in_left, &ucs, &sl, &retval );
    if ( rc != 0 ) {
        //delete ucs;
        DosFreeMem( ucs );
        err = 1;
        return -1;
    }

    sl = ucs - orig_ucs;
    ucs = orig_ucs;
    rc = UniUconvFromUcs( objfromucs, &ucs, &sl, (void **)out, out_left, &nonid );
    //delete ucs;
    DosFreeMem( ucs );

    if ( rc != 0 ) {
        err = 1;
        return -1;
    }

    retval += nonid;
    return 0;
}

extern "C" LONG APIENTRY cnvUniToUTF8( const char **in, unsigned *in_left,
                                       char **out, unsigned *out_left )
{
    cpconv c( 1200, 1208 );
    return c.conv( in, in_left, out, out_left );
}

extern "C" LONG APIENTRY cnvUniBEToUTF8( const char **in, unsigned *in_left,
                                         char **out, unsigned *out_left )
{
    cpconv c( (UniChar *)(L"UCS-2@endian=big"), (UniChar *)(L"UTF-8") );
    return c.conv( in, in_left, out, out_left );
}

extern "C" LONG APIENTRY cnvUTF8ToUni( const char **in, unsigned *in_left,
                                       char **out, unsigned *out_left )
{
    cpconv c( 1208, 1200 );
    return c.conv( in, in_left, out, out_left );
}


// Converts special non-ascii chars to suitable ascii chars
static void convSpchars( UniChar *uni )
{
    while ( *uni )
    {
        switch ( *uni )
        {
            case 0x2018:
            case 0x2019:
            case 0x2032:
                *uni = 0x0027; // '
                break;
            case 0x201C:
            case 0x201D:
            case 0x00AB:
            case 0x00BB:
                *uni = 0x0022; // "
                break;
            case 0x2014:
                *uni = 0x002D; // -
                break;
        }
        *uni++;
    }
}


// Ligatures table
struct Ligature { UniChar unicode;  wchar_t *equivalent;  int equivalentLength; };

// Table from [http://en.wikipedia.org/wiki/Ligature_(typography)#Unicode]
#define NUM_LIGATURES   38
static Ligature ligatures[ NUM_LIGATURES ] = {
    { 0x00DF, L"fs",  2 }, { 0x00E6, L"AE",  2 }, { 0x00C6, L"ae",  2 },
    { 0x0152, L"OE",  2 }, { 0x0153, L"oe",  2 }, { 0x0276, L"oe",  2 },
    { 0x0132, L"IJ",  2 }, { 0x0133, L"ij",  2 }, { 0x014A, L"Ng",  2 },
    { 0x014B, L"ng",  2 }, { 0x01F6, L"Hv",  2 }, { 0x0195, L"hv",  2 },
    { 0x01C4, L"DZ",  2 }, { 0x01C5, L"Dz",  2 }, { 0x01C6, L"dz",  2 },
    { 0x01C7, L"LJ",  2 }, { 0x01C8, L"Lj",  2 }, { 0x01C9, L"lj",  2 },
    { 0x01CA, L"NJ",  2 }, { 0x01CB, L"Nj",  2 }, { 0x01CC, L"nj",  2 },
    { 0x01F1, L"DZ",  2 }, { 0x01F2, L"Dz",  2 }, { 0x01F3, L"dz",  2 },
    { 0x02A3, L"dz",  2 }, { 0x02A6, L"ts",  2 }, { 0x02A9, L"fng", 3 },
    { 0x02AA, L"ls",  2 }, { 0x02AB, L"lz",  2 }, { 0x02AC, L"ww",  2 },
    { 0x1D6B, L"ue",  2 }, { 0xFB00, L"ff",  2 }, { 0xFB01, L"fi",  2 },
    { 0xFB02, L"fl",  2 }, { 0xFB03, L"ffi", 3 }, { 0xFB04, L"ffl", 3 },
    { 0xFB05, L"ft",  2 }, { 0xFB06, L"st",  2 }
};

// If unichar is ligature - returns number of additional chars
// which replaces the ligature, zero otherwise.
inline int isLigature( UniChar ch )
{
    for ( int i = 0; i < NUM_LIGATURES; i++ ) {
        if ( ch == ligatures[ i ].unicode ) {
            return ligatures[ i ].equivalentLength - 1;
        }
    }
    return 0;
}

// If unichar is ligature - returns pointer to struct Ligature
// which contains replacement for ligature, NULL otherwise.
inline Ligature *getReplLigature( UniChar ch )
{
    for ( int i = 0; i < NUM_LIGATURES; i++ ) {
        if ( ch == ligatures[ i ].unicode ) {
            return &( ligatures[ i ] );
        }
    }
    return NULL;
}

// Return number of chars which should be added to string
// length to fit the string with converted ligatures.
// If no ligatures in string - returns zero.
static int ligaturesLength( UniChar *str )
{
    int llen = 0;
    while ( *str != 0 ) {
        llen += isLigature( *str++ );
    }
    return llen;
}

// replaces ligatures in src into dst
// src remains unchanged
static void replLigatures( UniChar *src, UniChar *dst )
{
    while ( *src != 0 )
    {
        Ligature *lig = getReplLigature( *src );
        if ( lig == NULL ) {
            *dst++ = *src++;
        }
        else {
            for ( int i = 0; i < lig->equivalentLength; i++ ) {
                *dst++ = lig->equivalent[ i ];
            }
            *src++;
        }
    }
}

extern "C" LONG APIENTRY cnvUTF8ToSys( const char **in, unsigned *in_left,
                                       char **out, unsigned *out_left )
{
    unsigned ulen = ( (*in_left) * 2 ) + 2;
    char *uni = new char[ ulen ];
    memset( uni, 0, ulen );
    char *savuni = uni;
    unsigned savulen = ulen;
    cnvUTF8ToUni( in, in_left, &uni, &ulen );
    uni = savuni;
    ulen = savulen;
    int liglen = ligaturesLength( (UniChar *)uni );
    if ( liglen > 0 )  // string contain ligature(s)
    {
        unsigned ulen_tmp = ulen + ( liglen * 2 );
        char *uni_tmp = new char[ ulen_tmp ];
        replLigatures( (UniChar *)uni, (UniChar *)uni_tmp );
        delete uni;
        uni = uni_tmp;
        ulen = ulen_tmp;
    }
    convSpchars( (UniChar *)uni );
    cpconv c( 1200 );
    LONG rc = c.conv( (const char **)&uni, &ulen, out, out_left );
    uni = savuni;
    delete uni;
    return rc;
}

extern "C" LONG APIENTRY cnvUniBEToSys( const char **in, unsigned *in_left,
                                         char **out, unsigned *out_left )
{
    unsigned ulen = ( (*in_left) * 2 ) + 2;
    char *uni = new char[ ulen ];
    memset( uni, 0, ulen );
    char *savuni = uni;
    unsigned savulen = ulen;
    cpconv c1( (UniChar *)(L"UCS-2@endian=big"), (UniChar *)(L"UCS-2") );
    c1.conv( in, in_left, &uni, &ulen );
    uni = savuni;
    ulen = savulen;
    convSpchars( (UniChar *)uni );
    cpconv c2( 1200 );
    LONG rc = c2.conv( (const char **)&uni, &ulen, out, out_left );
    uni = savuni;
    delete uni;
    return rc;
}

extern "C" LONG APIENTRY cnvUniToSys( const char **in, unsigned *in_left,
                                      char **out, unsigned *out_left )
{
    convSpchars( (UniChar *)in );
    cpconv c( 1200 );
    return c.conv( (const char **)&in, in_left, out, out_left );
}

extern "C" LONG APIENTRY cnvSysToUCS2( const char **in, unsigned *in_left,
                                       char **out, unsigned *out_left )
{
    cpconv c( (UniChar *)(L""), (UniChar *)(L"UCS-2") );
    return c.conv( in, in_left, out, out_left );
}


// test
/*void main()
{
    const char *testutf8 = "test UTF-8  Тест! Проверка!";
    char buf[ 100 ];
    memset( buf, 0, sizeof( buf ) );
    char *bufsav = buf;
    char *buf1 = buf;
    unsigned in_len = strlen( testutf8 );
    unsigned out_len = sizeof( buf );

    cnvUTF8ToUCS4( &testutf8, &in_len, &buf1, &out_len );

    for ( int i = 0; i<100; i++ )
    {
        printf( ":%d:", (int)bufsav[i] );
    }
    printf( "\n" );
}
*/