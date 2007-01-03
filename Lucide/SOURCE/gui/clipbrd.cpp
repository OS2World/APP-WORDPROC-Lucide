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

#include <uconv.h>
#include <unidef.h>

#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "cpconv.h"


#define kUnicodeMimeMozilla "text/unicode"
#define kUnicodeMimeOdin    "Odin32 UnicodeText"

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
    RegisterClipboardFormat( kUnicodeMimeMozilla );
    RegisterClipboardFormat( kUnicodeMimeOdin );
}


void textToClipbrd( HAB hab, const char *text )
{
    void *objtouni, *objtosys;
    int rc = ULS_SUCCESS;
    rc = UniCreateUconvObject( (UniChar *)L"UTF-8", &objtouni );
    if ( rc != ULS_SUCCESS ) {
        return;
    }
    rc = UniCreateUconvObject( (UniChar *)L"", &objtosys );
    if ( rc != ULS_SUCCESS ) {
        UniFreeUconvObject( objtouni );
        return;
    }

    uconv_attribute_t attr;
    UniQueryUconvObject( objtouni, &attr, sizeof(attr), NULL, NULL, NULL );
    attr.converttype &= ~(CVTTYPE_CTRL7F | CVTTYPE_PATH);
    UniSetUconvObject( objtouni, &attr );
    UniQueryUconvObject( objtosys, &attr, sizeof(attr), NULL, NULL, NULL );
    attr.options = UCONV_OPTION_SUBSTITUTE_BOTH;
    UniSetUconvObject( objtosys, &attr );

    size_t len = 0;
    size_t olen = 0;

    if ( WinOpenClipbrd( hab ) )
    {
        WinEmptyClipbrd( hab );

        size_t cSubs = 0;
        len = strlen( text );
        olen = ( len + 2 ) * 2;
        void *shmemuni = NULL;
        void *shmemsys = NULL;

        // place to clipboard as unicode for Odin
        if ( DosAllocSharedMem( &shmemuni, NULL, olen, fALLOCSHR ) == 0 )
        {
            memset( shmemuni, 0, olen );
            size_t unilen = olen / sizeof( UniChar );
            UniChar *tmpuni = (UniChar *)shmemuni;
            UniUconvToUcs( objtouni, (void **)&text, &len, &tmpuni, &unilen, &cSubs );
            unilen = UniStrlen( (UniChar *)shmemuni );
            void *memuni = (void *)new char[ olen ];
            memcpy( memuni, shmemuni, olen );

            ULONG ulFormatID = RegisterClipboardFormat( kUnicodeMimeOdin );
            WinSetClipbrdData( hab, (ULONG)shmemuni, ulFormatID, CFI_POINTER );

            // place to clipboard as unicode for Mozilla
            if ( DosAllocSharedMem( &shmemuni, NULL, olen, fALLOCSHR ) == 0 )
            {
                memcpy( shmemuni, memuni, olen );
                ulFormatID = RegisterClipboardFormat( kUnicodeMimeMozilla );
                WinSetClipbrdData( hab, (ULONG)shmemuni, ulFormatID, CFI_POINTER );
            }

            int liglen = uniLigaturesLength( (UniChar *)memuni );
            if ( liglen > 0 )  // string contain ligature(s)
            {
                unsigned ulen_tmp = ( unilen + liglen + 1 ) * sizeof( UniChar );
                char *uni_tmp = new char[ ulen_tmp ];
                uniReplaceLigatures( (UniChar *)memuni, (UniChar *)uni_tmp );
                delete memuni;
                memuni = uni_tmp;
                unilen = UniStrlen( (UniChar *)memuni );
            }
            uniConvertSpChars( (UniChar *)memuni );

            // place to clipboard as current codepage
            if ( DosAllocSharedMem( &shmemsys, NULL, olen, fALLOCSHR ) == 0 )
            {
                memset( shmemsys, 0, olen );

                cSubs = 0;
                tmpuni = (UniChar *)memuni;
                void *tmpsys = shmemsys;
                UniUconvFromUcs( objtosys, &tmpuni, &unilen, &tmpsys, &olen, &cSubs );

                WinSetClipbrdData( hab, (ULONG)shmemsys, CF_TEXT, CFI_POINTER );
            }
            delete memuni;
        }

        WinCloseClipbrd( hab );
    }

    UniFreeUconvObject( objtouni );
    UniFreeUconvObject( objtosys );
}

