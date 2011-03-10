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

#ifndef _ERFONTCONFIG_H_
#define _ERFONTCONFIG_H_

typedef char    FcChar8;
typedef short   FcChar16;
typedef int     FcChar32;
typedef int     FcBool;


#define FcTrue      1
#define FcFalse     0

#define FC_FAMILY           "family"            /* String */
#define FC_STYLE            "style"             /* String */
#define FC_SLANT            "slant"             /* Int */
#define FC_WEIGHT           "weight"            /* Int */
#define FC_SPACING          "spacing"           /* Int */
#define FC_WIDTH            "width"             /* Int */
#define FC_FILE             "file"              /* String */
#define FC_INDEX            "index"             /* Int */
#define FC_LANG             "lang"              /* String RFC 3066 langs */

#define FC_WEIGHT_EXTRALIGHT    40
#define FC_WEIGHT_LIGHT         50
#define FC_WEIGHT_REGULAR       80
#define FC_WEIGHT_NORMAL        FC_WEIGHT_REGULAR
#define FC_WEIGHT_MEDIUM        100
#define FC_WEIGHT_DEMIBOLD      180
#define FC_WEIGHT_SEMIBOLD      FC_WEIGHT_DEMIBOLD
#define FC_WEIGHT_BOLD          200
#define FC_WEIGHT_EXTRABOLD     205
#define FC_WEIGHT_ULTRABOLD     FC_WEIGHT_EXTRABOLD
#define FC_WEIGHT_BLACK         210

#define FC_SLANT_ROMAN          0
#define FC_SLANT_ITALIC         100
#define FC_SLANT_OBLIQUE        110

#define FC_WIDTH_ULTRACONDENSED     50
#define FC_WIDTH_EXTRACONDENSED     63
#define FC_WIDTH_CONDENSED          75
#define FC_WIDTH_SEMICONDENSED      87
#define FC_WIDTH_NORMAL             100
#define FC_WIDTH_SEMIEXPANDED       113
#define FC_WIDTH_EXPANDED           125
#define FC_WIDTH_EXTRAEXPANDED      150
#define FC_WIDTH_ULTRAEXPANDED      200


#define FC_PROPORTIONAL         0
#define FC_MONO                 100

typedef enum _FcType {
    FcTypeVoid,
    FcTypeInteger,
    FcTypeDouble,
    FcTypeString,
    FcTypeBool,
    FcTypeMatrix,
    FcTypeCharSet,
    FcTypeFTFace,
    FcTypeLangSet
} FcType;


/*
 * A data structure to represent the available glyphs in a font.
 * This is represented as a sparse boolean btree.
 */

typedef enum _FcResult {
    FcResultMatch, FcResultNoMatch, FcResultTypeMismatch, FcResultNoId,
    FcResultOutOfMemory
} FcResult;

typedef struct _FcPattern   FcPattern;


typedef struct _FcFontSet {
    int     nfont;
    int     sfont;
    FcPattern   **fonts;
} FcFontSet;

typedef enum _FcMatchKind {
    FcMatchPattern, FcMatchFont
} FcMatchKind;


typedef struct _FcConfig    FcConfig;

typedef struct _FcCharSet FcCharSet;


FcConfig *FcConfigGetCurrent();


FcBool FcConfigSubstitute( FcConfig *config, FcPattern *p, FcMatchKind kind );

void FcDefaultSubstitute( FcPattern *pattern );

void FcFontSetDestroy( FcFontSet *s );

FcBool FcInit();

FcFontSet *FcFontSort( FcConfig *config, FcPattern *p, FcBool trim,
                       FcCharSet **csp, FcResult *result );

void FcFontSetSortDestroy( FcFontSet *fs );

void FcPatternDestroy( FcPattern *p );

FcResult FcPatternGetInteger( const FcPattern *p, const char *object, int n, int *i );

FcResult FcPatternGetString( const FcPattern *p, const char *object, int n, FcChar8 **s );

//FcPattern *FcPatternBuild( FcPattern *orig, ... );

FcPattern *FcPatternBuild(void *,
				const char *fcFamily, FcType tFamily, const char *family,
				const char *fcLang, FcType tLang, const char *lang,
                                void *);

void FcPatternAddInteger(FcPattern *p, const char *fcType, int value);

#endif // _ERFONTCONFIG_H_

