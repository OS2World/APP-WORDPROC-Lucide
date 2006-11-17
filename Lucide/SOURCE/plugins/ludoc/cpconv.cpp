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


#include <uconv.h>


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

