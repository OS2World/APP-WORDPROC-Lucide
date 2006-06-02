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


#define INCL_WIN
#define INCL_DOS
#include <os2.h>

#include <string.h>
#include <malloc.h>
#include "cpconv.h"


#define kUnicodeMime "text/unicode"

inline ULONG RegisterClipboardFormat(PCSZ pcszFormat)
{
    ATOM atom = WinFindAtom(WinQuerySystemAtomTable(), pcszFormat);
    if (!atom) {
        atom = WinAddAtom(WinQuerySystemAtomTable(), pcszFormat);
    }
    return atom;
}

void initClipbrd()
{
    RegisterClipboardFormat( kUnicodeMime );
}

void textToClipbrd( HAB hab, const char *text )
{
    size_t len = 0;
    size_t olen = 0;
    const char *tsav = text;

    if ( WinOpenClipbrd( hab ) )
    {
        WinEmptyClipbrd( hab );

        len = strlen( text );
        olen = (len + 2)*2;

        void *memuni = NULL;

        // place to clipboard as unicode
        if ( DosAllocSharedMem( &memuni, NULL, olen ,
                                PAG_WRITE | PAG_COMMIT | OBJ_GIVEABLE ) == 0 )
        {
            memset( memuni, 0, olen );
            void *tmem = memuni;

            //cpconv c( 1208, 1200 );
            tsav = text;
            //c.conv( &text, &len, (char **)&memuni, &olen );
            cnvUTF8ToUni( &text, &len, (char **)&memuni, &olen );
            text = tsav;

            ULONG ulFormatID = RegisterClipboardFormat( kUnicodeMime );
            WinSetClipbrdData( hab, (ULONG)tmem, ulFormatID, CFI_POINTER );
        }

        len = strlen( text );
        olen = (len + 2)*2;
        void *memcp = NULL;

        // place to clipboard as current codepage
        if ( DosAllocSharedMem( &memcp, NULL, olen ,
                                PAG_WRITE | PAG_COMMIT | OBJ_GIVEABLE ) == 0 )
        {
            memset( memcp, 0, olen );
            void *tmem = memcp;

            //cpconv c( 1208 );
            tsav = text;
            //c.conv( &text, &len, (char **)&memcp, &olen );
            cnvUTF8ToSys( &text, &len, (char **)&memcp, &olen );
			text = tsav;

            WinSetClipbrdData( hab, (ULONG)tmem, CF_TEXT, CFI_POINTER );
        }


        WinCloseClipbrd( hab );
    }
}

