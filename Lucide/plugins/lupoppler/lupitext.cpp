
/*
 *  This file was generated by the SOM Compiler.
 *  Generated using:
 *     SOM incremental update: 2.24
 */


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
 * Dmitry A. Kuminov, netlabs.org.
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



/*
 *  This file was generated by the SOM Compiler and Emitter Framework.
 *  Generated using template emitter:
 *      SOM Emitter emitxtm: 2.23.1.9
 */

#ifndef SOM_Module_lupitext_Source
#define SOM_Module_lupitext_Source
#endif
#define LuPopplerInputText_Class_Source

#include "lupitext.xih"
#include "cpconv.h"


SOM_Scope void SOMLINK init_widgetText(LuPopplerInputText *somSelf,
                                        Environment *ev, somInitCtrl* ctrl,
                                       LuPopplerDocument* aDoc,
                                       long aPagenum, Page* aPage,
                                       FormWidgetText* aFormWidgetText)
{
    LuPopplerInputTextData *somThis; /* set in BeginInitializer */
    somInitCtrl globalCtrl;
    somBooleanVector myMask;
    LuPopplerInputText_BeginInitializer_init_widgetText;

    LuPopplerInputText_Init_LuPopplerInputField_init_widget(somSelf, ev, ctrl,
                                                            aDoc, aPagenum, aPage,
                                                            aFormWidgetText);
    LuPopplerInputText_Init_LuInputText_somDefaultInit(somSelf, ctrl);

    /* local LuPopplerInputField initialization code */

    somThis->widget = aFormWidgetText;
    somThis->contents = NULL;
}


SOM_Scope void SOMLINK somDestruct(LuPopplerInputText *somSelf,
                                   octet doFree, som3DestructCtrl* ctrl)
{
    LuPopplerInputTextData *somThis; /* set in BeginDestructor */
    somDestructCtrl globalCtrl;
    somBooleanVector myMask;
    LuPopplerInputText_BeginDestructor;

    /* local LuPopplerInputField deinitialization code */

    delete[] somThis->contents;

    LuPopplerInputText_EndDestructor;
}


SOM_Scope string  SOMLINK getContents(LuPopplerInputText *somSelf,
                                       Environment *ev)
{
    LuPopplerInputTextData *somThis = LuPopplerInputTextGetData(somSelf);

    delete[] somThis->contents;
    somThis->contents = NULL;

    GooString *gooStr = somThis->widget->getContent();
    if ( gooStr )
        somThis->contents =
            uniUtf16BEToUtf8( gooStr->getCString(), gooStr->getLength(),
                              NULL, NULL );

    return somThis->contents;
}

SOM_Scope void  SOMLINK setContents(LuPopplerInputText *somSelf,
                                     Environment *ev, string aContents)
{
    LuPopplerInputTextData *somThis = LuPopplerInputTextGetData(somSelf);

    size_t len = 0;
    char *str = uniUtf8ToUtf16BE( aContents, NULL, NULL, &len );
    GooString *contents = new GooString( str, len );
    delete[] str;
    somThis->widget->setContent( contents );
    delete contents;
}

SOM_Scope boolean  SOMLINK isMultiLine(LuPopplerInputText *somSelf,
                                        Environment *ev)
{
    LuPopplerInputTextData *somThis = LuPopplerInputTextGetData(somSelf);

    return somThis->widget->isMultiline();
}

SOM_Scope boolean  SOMLINK isPassword(LuPopplerInputText *somSelf,
                                       Environment *ev)
{
    LuPopplerInputTextData *somThis = LuPopplerInputTextGetData(somSelf);

    return somThis->widget->isPassword();
}

SOM_Scope boolean  SOMLINK isFileName(LuPopplerInputText *somSelf,
                                       Environment *ev)
{
    LuPopplerInputTextData *somThis = LuPopplerInputTextGetData(somSelf);

    return somThis->widget->isFileSelect();
}

SOM_Scope boolean  SOMLINK isSpellCheckable(LuPopplerInputText *somSelf,
                                             Environment *ev)
{
    LuPopplerInputTextData *somThis = LuPopplerInputTextGetData(somSelf);

    return !somThis->widget->noSpellCheck();
}

SOM_Scope boolean  SOMLINK isScrollable(LuPopplerInputText *somSelf,
                                         Environment *ev)
{
    LuPopplerInputTextData *somThis = LuPopplerInputTextGetData(somSelf);

    return !somThis->widget->noScroll();
}

SOM_Scope boolean  SOMLINK isComb(LuPopplerInputText *somSelf,
                                   Environment *ev)
{
    LuPopplerInputTextData *somThis = LuPopplerInputTextGetData(somSelf);

    return somThis->widget->isComb();
}

SOM_Scope boolean  SOMLINK isRichText(LuPopplerInputText *somSelf,
                                       Environment *ev)
{
    LuPopplerInputTextData *somThis = LuPopplerInputTextGetData(somSelf);

    return somThis->widget->isRichText();
}

SOM_Scope long  SOMLINK getMaximumLength(LuPopplerInputText *somSelf,
                                          Environment *ev)
{
    LuPopplerInputTextData *somThis = LuPopplerInputTextGetData(somSelf);

    return somThis->widget->getMaxLen();
}

