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


#include <os2.h>
#include <uconv.h>
#include <string.h>


// Converts special non-ascii chars to suitable ascii chars
extern "C" VOID APIENTRY uniConvertSpChars( UniChar *uni )
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
            case 0x2013:
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
extern "C" LONG APIENTRY uniLigaturesLength( UniChar *str )
{
    LONG llen = 0;
    while ( *str != 0 ) {
        llen += isLigature( *str++ );
    }
    return llen;
}

// replaces ligatures in src into dst
// src remains unchanged
extern "C" VOID APIENTRY uniReplaceLigatures( UniChar *src, UniChar *dst )
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

extern "C" char *APIENTRY uniConvertString( const char *s, size_t len, UconvObject from,
                                            UconvObject to, size_t *retLen )
{
    if ( s == NULL )
        return NULL;

    size_t cSubs = 0;
    size_t unilen = len + 1;
    UniChar *unibuf = new UniChar[ unilen ];
    memset( unibuf, 0, unilen * sizeof( UniChar ) );
    UniChar *tmpuni = unibuf;
    UniUconvToUcs( from, (void **)&s, &len, &tmpuni, &unilen, &cSubs );
    unilen = UniStrlen( unibuf );

    int liglen = uniLigaturesLength( unibuf );
    if ( liglen > 0 )  // string contain ligature(s)
    {
        size_t ulen_tmp = ( unilen + liglen + 1 ) * sizeof( UniChar );
        char *uni_tmp = new char[ ulen_tmp ];
        uniReplaceLigatures( unibuf, (UniChar *)uni_tmp );
        delete unibuf;
        unibuf = (UniChar *)uni_tmp;
        unilen = UniStrlen( unibuf );
    }
    uniConvertSpChars( unibuf );

    // take the maximum of 4 chars per each unicode char on output
    size_t blen = ( unilen + 1 ) * 4;
    char *b = new char[ blen ];
    memset( b, 0, blen );
    char *bsav = b;
    size_t blensav = blen;
    tmpuni = unibuf;
    cSubs = 0;
    UniUconvFromUcs( to, &tmpuni, &unilen, (void **)&b, &blen, &cSubs );
    delete unibuf;

    // tailor the buffer size and append 4 zeros as an all-in-one terminator
    blen = blensav - blen;
    b = new char[ blen + 4 ];
    memcpy( b, bsav, blen );
    memset( b + blen, 0, 4 );
    delete[] bsav;

    if ( retLen != NULL )
        *retLen = blen;
    return b;
}

static char *utf16_sys( const char *s, size_t len, UconvObject *utf16,
                        UconvObject *sys, size_t *retLen, bool from, bool isUtf8 )
{
    UconvObject utf16Tmp = NULL;
    UconvObject sysTmp = NULL;
    uconv_attribute_t attr;

    if ( utf16 == NULL )
        utf16 = &utf16Tmp;
    if ( sys == NULL )
        sys = &sysTmp;

    if ( *utf16 == NULL ) {
        UniCreateUconvObject( (UniChar *)L"UCS-2@endian=big", utf16 );
        UniQueryUconvObject( *utf16, &attr, sizeof(attr), NULL, NULL, NULL );
        attr.converttype &= ~(CVTTYPE_CTRL7F | CVTTYPE_PATH);
        attr.options = UCONV_OPTION_SUBSTITUTE_BOTH;
        UniSetUconvObject( *utf16, &attr );
    }
    if ( *sys == NULL ) {
        if ( isUtf8 )
            UniCreateUconvObject( (UniChar *)L"UTF-8", sys );
        else
            UniCreateUconvObject( (UniChar *)L"", sys );
        UniQueryUconvObject( *sys, &attr, sizeof(attr), NULL, NULL, NULL );
        attr.converttype &= ~(CVTTYPE_CTRL7F | CVTTYPE_PATH);
        attr.options = UCONV_OPTION_SUBSTITUTE_BOTH;
        UniSetUconvObject( *sys, &attr );
    }

    char *ret;
    if ( from )
        ret = uniConvertString( s, len, *utf16, *sys, retLen );
    else
        ret = uniConvertString( s, len, *sys, *utf16, retLen );

    if ( sys == &sysTmp )
        UniFreeUconvObject( sysTmp );
    if ( utf16 == &utf16Tmp )
        UniFreeUconvObject( utf16Tmp );

    return ret;
}

extern "C" char *APIENTRY uniUtf16BEToSys( const char *s, size_t len, UconvObject *utf16,
                                           UconvObject *sys )
{
    if ( s == NULL )
        return NULL;
    if ( len >= 2 && s[0] == (int)(char)0xfe && s[1] == (int)(char)0xff ) {
        s += 2;
        len -= 2;
    }
    return utf16_sys( s, len, utf16, sys, NULL, true, false );
}

extern "C" char *APIENTRY uniSysToUtf16BE( const char *s, UconvObject *sys,
                                           UconvObject *utf16, size_t *retLen )
{
    if ( s == NULL )
        return NULL;
    return utf16_sys( s, strlen( s ), utf16, sys, retLen, false, false );
}

extern "C" char *APIENTRY uniUtf16BEToUtf8( const char *s, size_t len, UconvObject *utf16,
                                            UconvObject *utf8 )
{
    if ( s == NULL )
        return NULL;
    if ( len >= 2 && s[0] == (char)0xfe && s[1] == (char)0xff ) {
        s += 2;
        len -= 2;
    }
    return utf16_sys( s, len, utf16, utf8, NULL, true, true );
}

extern "C" char *APIENTRY uniUtf8ToUtf16BE( const char *s, UconvObject *utf8,
                                            UconvObject *utf16, size_t *retLen )
{
    if ( s == NULL )
        return NULL;
    return utf16_sys( s, strlen( s ), utf16, utf8, retLen, false, true );
}

static char *utf8_sys( const char *s, UconvObject *utf8, UconvObject *sys, bool from )
{
    UconvObject utf8Tmp = NULL;
    UconvObject sysTmp = NULL;
    uconv_attribute_t attr;

    if ( utf8 == NULL )
        utf8 = &utf8Tmp;
    if ( sys == NULL )
        sys = &sysTmp;

    if ( *utf8 == NULL ) {
        UniCreateUconvObject( (UniChar *)L"UTF-8", utf8 );
        UniQueryUconvObject( *utf8, &attr, sizeof(attr), NULL, NULL, NULL );
        attr.converttype &= ~(CVTTYPE_CTRL7F | CVTTYPE_PATH);
        attr.options = UCONV_OPTION_SUBSTITUTE_BOTH;
        UniSetUconvObject( *utf8, &attr );
    }
    if ( *sys == NULL ) {
        UniCreateUconvObject( (UniChar *)L"", sys );
        UniQueryUconvObject( *sys, &attr, sizeof(attr), NULL, NULL, NULL );
        attr.converttype &= ~(CVTTYPE_CTRL7F | CVTTYPE_PATH);
        attr.options = UCONV_OPTION_SUBSTITUTE_BOTH;
        UniSetUconvObject( *sys, &attr );
    }

    char *ret;
    if ( from )
        ret = uniConvertString( s, strlen( s ), *utf8, *sys, NULL );
    else
        ret = uniConvertString( s, strlen( s ), *sys, *utf8, NULL );

    if ( sys == &sysTmp )
        UniFreeUconvObject( sysTmp );
    if ( utf8 == &utf8Tmp )
        UniFreeUconvObject( utf8Tmp );

    return ret;
}

extern "C" char *APIENTRY uniUtf8ToSys( const char *s, UconvObject *utf8,
                                        UconvObject *sys )
{
    if ( s == NULL )
        return NULL;
    return utf8_sys( s, utf8, sys, true );
}

extern "C" char *APIENTRY uniSysToUtf8( const char *s, UconvObject *sys,
                                        UconvObject *utf8 )
{
    if ( s == NULL )
        return NULL;
    return utf8_sys( s, utf8, sys, false );
}

