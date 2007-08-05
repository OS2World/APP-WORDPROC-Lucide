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
#include <stdlib.h>
#include "cpconv.h"

#include "UClip.h"


static BOOL APIENTRY (*pUWinOpenClipbrd)(HAB)                      = NULL;
static BOOL APIENTRY (*pUWinEmptyClipbrd)(HAB)                     = NULL;
static BOOL APIENTRY (*pUWinSetClipbrdData)(HAB,ULONG,ULONG,ULONG) = NULL;
static BOOL APIENTRY (*pUWinCloseClipbrd)(HAB)                     = NULL;

static bool loadUClip();

static HMODULE ucHandle = NULLHANDLE;
static bool uclipLoaded = loadUClip();


static void freeUClip()
{
    if ( ucHandle != NULLHANDLE ) {
        DosFreeModule( ucHandle );
    }
}

static bool loadUClip()
{
    bool res = false;
    do
    {
      if ( DosLoadModule( NULL, 0, "UCLIP", &ucHandle ) != 0 )
        break;
      if (DosQueryProcAddr(ucHandle,0,"UWinOpenClipbrd",(PFN *)&pUWinOpenClipbrd)!= 0)
        break;
      if (DosQueryProcAddr(ucHandle,0,"UWinEmptyClipbrd",(PFN *)&pUWinEmptyClipbrd)!= 0)
        break;
      if (DosQueryProcAddr(ucHandle,0,"UWinSetClipbrdData",(PFN *)&pUWinSetClipbrdData)!= 0)
        break;
      if (DosQueryProcAddr(ucHandle,0,"UWinCloseClipbrd",(PFN *)&pUWinCloseClipbrd)!= 0)
        break;

      res = true;
    } while (0);

    atexit( freeUClip );

    return res;
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

    if ( uclipLoaded ? pUWinOpenClipbrd( hab ) : WinOpenClipbrd( hab ) )
    {
        if ( uclipLoaded ) {
            pUWinEmptyClipbrd( hab );
        } else {
            WinEmptyClipbrd( hab );
        }

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

            if ( uclipLoaded ) {
                pUWinSetClipbrdData( hab,(ULONG)shmemuni,UCLIP_CF_UNICODETEXT,CFI_POINTER );
            } else {
                DosFreeMem( shmemuni );
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

                if ( uclipLoaded ) {
                    pUWinSetClipbrdData( hab, (ULONG)shmemsys, UCLIP_CF_TEXT, CFI_POINTER );
                } else {
                    WinSetClipbrdData( hab, (ULONG)shmemsys, CF_TEXT, CFI_POINTER );
                }
            }
            delete memuni;
        }

        if ( uclipLoaded ) {
            pUWinCloseClipbrd( hab );
        } else {
            WinCloseClipbrd( hab );
        }
    }

    UniFreeUconvObject( objtouni );
    UniFreeUconvObject( objtosys );
}

