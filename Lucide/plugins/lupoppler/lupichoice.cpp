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
 * Dmitriy Kuminov, netlabs.org.
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

#ifndef SOM_Module_lupichoice_Source
#define SOM_Module_lupichoice_Source
#endif
#define LuPopplerInputChoice_Class_Source

#include "lupichoice.xih"
#include "cpconv.h"

SOM_Scope void SOMLINK init_widgetChoice(LuPopplerInputChoice *somSelf,
                                          Environment *ev, somInitCtrl* ctrl,
                                         LuPopplerDocument* aDoc,
                                         long aPagenum, Page* aPage,
                                         FormWidgetChoice* aFormWidgetChoice)
{
    LuPopplerInputChoiceData *somThis = NULL; /* set in BeginInitializer */
    somInitCtrl globalCtrl;
    somBooleanVector myMask;
    LuPopplerInputChoice_BeginInitializer_init_widgetChoice;

    LuPopplerInputChoice_Init_LuPopplerInputField_init_widget(somSelf, ev, ctrl,
                                                              aDoc, aPagenum, aPage,
                                                              aFormWidgetChoice);
    LuPopplerInputChoice_Init_LuInputChoice_somDefaultInit(somSelf, ctrl);

    /* local LuPopplerInputField initialization code */

    somThis->widget = aFormWidgetChoice;
}


SOM_Scope void SOMLINK somDestruct(LuPopplerInputChoice *somSelf,
                                   octet doFree, som3DestructCtrl* ctrl)
{
    LuPopplerInputChoiceData *somThis; /* set in BeginDestructor */
    somDestructCtrl globalCtrl;
    somBooleanVector myMask;
    LuPopplerInputChoice_BeginDestructor;

    /* local LuPopplerInputField deinitialization code */

    LuPopplerInputChoice_EndDestructor;
}

SOM_Scope long  SOMLINK getCount(LuPopplerInputChoice *somSelf,
                                  Environment *ev)
{
    LuPopplerInputChoiceData *somThis = LuPopplerInputChoiceGetData(somSelf);
    LuPopplerInputChoiceMethodDebug("LuPopplerInputChoice","getCount");

    return somThis->widget->getNumChoices();
      //(LuPopplerInputChoice_parent_LuInputChoice_getCount(somSelf,
                                                             //  ev));
}

SOM_Scope string  SOMLINK getChoice(LuPopplerInputChoice *somSelf,
                                     Environment *ev, long aNumber)
{
    LuPopplerInputChoiceData *somThis = LuPopplerInputChoiceGetData(somSelf);
    LuPopplerInputChoiceMethodDebug("LuPopplerInputChoice","getChoice");

    delete[] somThis->mChoiceText;
    somThis->mChoiceText = NULL;

    GooString *gooStr = somThis->widget->getChoice(aNumber);
    if (gooStr)
      somThis->mChoiceText =  gooStr->getCString();
            //uniUtf16BEToUtf8( gooStr->getCString(), gooStr->getLength(),
            //                  NULL, NULL );
    return somThis->mChoiceText;
      //(LuPopplerInputChoice_parent_LuInputChoice_getChoice(somSelf,
                                //                                ev,
                                //                                aNumber));
}

SOM_Scope void  SOMLINK select(LuPopplerInputChoice *somSelf,
                                Environment *ev, long aNumber)
{
    LuPopplerInputChoiceData *somThis = LuPopplerInputChoiceGetData(somSelf);
    LuPopplerInputChoiceMethodDebug("LuPopplerInputChoice","select");

    LuPopplerInputChoice_parent_LuInputChoice_select(somSelf,
                                                     ev, aNumber);
}

SOM_Scope void  SOMLINK toggle(LuPopplerInputChoice *somSelf,
                                Environment *ev, long aNumber)
{
    LuPopplerInputChoiceData *somThis = LuPopplerInputChoiceGetData(somSelf);
    LuPopplerInputChoiceMethodDebug("LuPopplerInputChoice","toggle");

    LuPopplerInputChoice_parent_LuInputChoice_toggle(somSelf,
                                                     ev, aNumber);
}

SOM_Scope void  SOMLINK deselectAll(LuPopplerInputChoice *somSelf,
                                     Environment *ev)
{
    LuPopplerInputChoiceData *somThis = LuPopplerInputChoiceGetData(somSelf);
    LuPopplerInputChoiceMethodDebug("LuPopplerInputChoice","deselectAll");

    LuPopplerInputChoice_parent_LuInputChoice_deselectAll(somSelf,
                                                          ev);
}

SOM_Scope void  SOMLINK setChoiceText(LuPopplerInputChoice *somSelf,
                                       Environment *ev, string aText)
{
    LuPopplerInputChoiceData *somThis = LuPopplerInputChoiceGetData(somSelf);
    LuPopplerInputChoiceMethodDebug("LuPopplerInputChoice","setChoiceText");

    LuPopplerInputChoice_parent_LuInputChoice_setChoiceText(somSelf,
                                                            ev,
                                                            aText);
}

SOM_Scope string  SOMLINK getChoiceText(LuPopplerInputChoice *somSelf,
                                         Environment *ev)
{
    LuPopplerInputChoiceData *somThis = LuPopplerInputChoiceGetData(somSelf);
    LuPopplerInputChoiceMethodDebug("LuPopplerInputChoice","getChoiceText");

    return (LuPopplerInputChoice_parent_LuInputChoice_getChoiceText(somSelf,
                                                                    ev));
}

SOM_Scope boolean  SOMLINK isSelected(LuPopplerInputChoice *somSelf,
                                       Environment *ev, long aNumber)
{
    LuPopplerInputChoiceData *somThis = LuPopplerInputChoiceGetData(somSelf);
    LuPopplerInputChoiceMethodDebug("LuPopplerInputChoice","isSelected");

    return (LuPopplerInputChoice_parent_LuInputChoice_isSelected(somSelf,
                                                                 ev,
                                                                 aNumber));
}

SOM_Scope boolean  SOMLINK isComboBox(LuPopplerInputChoice *somSelf,
                                       Environment *ev)
{
    LuPopplerInputChoiceData *somThis = LuPopplerInputChoiceGetData(somSelf);
    LuPopplerInputChoiceMethodDebug("LuPopplerInputChoice","isComboBox");

    return (LuPopplerInputChoice_parent_LuInputChoice_isComboBox(somSelf,
                                                                 ev));
}

SOM_Scope boolean  SOMLINK isEditable(LuPopplerInputChoice *somSelf,
                                       Environment *ev)
{
    LuPopplerInputChoiceData *somThis = LuPopplerInputChoiceGetData(somSelf);
    LuPopplerInputChoiceMethodDebug("LuPopplerInputChoice","isEditable");

    return (LuPopplerInputChoice_parent_LuInputChoice_isEditable(somSelf,
                                                                 ev));
}

SOM_Scope boolean  SOMLINK isMultiSelectable(LuPopplerInputChoice *somSelf,
                                              Environment *ev)
{
    LuPopplerInputChoiceData *somThis = LuPopplerInputChoiceGetData(somSelf);
    LuPopplerInputChoiceMethodDebug("LuPopplerInputChoice","isMultiSelectable");

    return (LuPopplerInputChoice_parent_LuInputChoice_isMultiSelectable(somSelf,
                                                                        ev));
}

SOM_Scope boolean  SOMLINK isSpellCheckable(LuPopplerInputChoice *somSelf,
                                             Environment *ev)
{
    LuPopplerInputChoiceData *somThis = LuPopplerInputChoiceGetData(somSelf);
    LuPopplerInputChoiceMethodDebug("LuPopplerInputChoice","isSpellCheckable");

    return (LuPopplerInputChoice_parent_LuInputChoice_isSpellCheckable(somSelf,
                                                                       ev));
}

