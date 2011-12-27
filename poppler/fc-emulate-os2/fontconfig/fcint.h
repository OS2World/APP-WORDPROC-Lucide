/*
 * This code is (C) Netlabs.org
 * Authors:
 *    Doodle <doodle@netlabs.org>
 *    Peter Weilbacher <mozilla@weilbacher.org>
 *
 * Contributors:
 *    KO Myung-Hun <komh78@gmail.com>
 *    Alex Taylor <alex@altsan.org>
 *    Rich Walsh <rich@e-vertise.com>
 *    Silvan Scherrer <silvan.scherrer@aroa.ch>
 *
 */

#ifndef _FCINT_H_
#define _FCINT_H_

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <math.h> /* for fabs */
#include <float.h> /* for DBL_EPSILON */
#include <iconv.h>
#define INCL_DOS
#define INCL_WIN
#define INCL_DOSERRORS
#define INCL_SHLERRORS
#include <os2.h>
#include <fontconfig/fontconfig.h>
#include <fontconfig/fcfreetype.h>
#include <fontconfig/fcprivate.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_SFNT_NAMES_H
#include FT_TRUETYPE_IDS_H

#ifdef FC_CACHE_VERSION_STRING
#undef FC_CACHE_VERSION_STRING
#endif
#define FC_CACHE_VERSION_STRING "v1.3_with_GCC"


#ifdef FC_EXPORT_FUNCTIONS
# define fcExport __declspec(dllexport)
#else
# define fcExport
#endif

// #define LOOKUP_SFNT_NAME_DEBUG
// #define FONTCONFIG_DEBUG_PRINTF
// #define MATCH_DEBUG

#define DEFAULT_SERIF_FONT          "Times New Roman"
#define DEFAULT_SERIF_FONTJA        "Times New Roman WT J"
#define DEFAULT_SANSSERIF_FONT      "Helvetica"
#define DEFAULT_MONOSPACED_FONT     "Courier"
#define DEFAULT_SYMBOL_FONT         "Symbol Set"
#define DEFAULT_DINGBATS_FONT       "DejaVu Sans"

/* structure for the font cache in OS2.INI  */
typedef struct FontDescriptionCache_s
{
  char achFileName[CCHMAXPATH];
  struct stat FileStatus;
  char achFamilyName[128];
  char achStyleName[128];
  long lFontIndex;

  struct FontDescriptionCache_s *pNext;
} FontDescriptionCache_t, *FontDescriptionCache_p;

struct _FcPattern
{
    char *family;
    int slant;
    int weight;
    double pixelsize;
    int spacing;
    FcBool hinting;
    FcBool antialias;
    FcBool embolden;
    FcBool verticallayout;
    int hintstyle;
    FcBool autohint;
    FcBool bitmap;
    FcBool outline;
    int rgba;
    double size;
    char *style;
    FT_Face face;
    int ref;
    char *lang;
    FontDescriptionCache_p pFontDesc;
};

void *pConfig;

#endif /* _FCINT_H_ */
