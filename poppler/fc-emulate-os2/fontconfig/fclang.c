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

#include "fcint.h"


/*
 * test langset for language support
 * FcLangSetHasLang checks whether ls supports lang. If ls has a matching
 * language and territory pair, this function returns FcLangEqual. If ls has
 * a matching language but differs in which territory that language is for,
 * this function returns FcLangDiffentTerritory. If ls has no matching
 * language, this function returns FcLangDifferentLang.
 */
fcExport FcLangResult FcLangSetHasLang(const FcLangSet *ls, const FcChar8 *lang)
{
  // Stub
  return FcLangEqual;
}

