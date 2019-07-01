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



/*
 *  This file was generated by the SOM Compiler.
 *  Generated using:
 *     SOM incremental update: 2.24
 */


/*
 *  This file was generated by the SOM Compiler and Emitter Framework.
 *  Generated using template emitter:
 *      SOM Emitter emitxtm: 2.23.1.9
 */

#ifndef SOM_Module_lupixbuf_Source
#define SOM_Module_lupixbuf_Source
#endif
#define LuPixbuf_Class_Source

#define INCL_DOS
#include <os2.h>

#include <assert.h>
#include <algorithm>

#include "lupixbuf.xih"


SOM_Scope void SOMLINK LuPixbufInit(LuPixbuf *somSelf,  Environment *ev,
                                    somInitCtrl* ctrl, long w,
                                    long h, short bpp)
{
    APIRET rc = 0;
    LuPixbufData *somThis = NULL;
    somInitCtrl globalCtrl;
    somBooleanVector myMask;
    LuPixbuf_BeginInitializer_LuPixbufInit;
    LuPixbuf_Init_SOMObject_somDefaultInit(somSelf, ctrl);

    // local LuPixbuf initialization code
    somThis->width = w;
    somThis->height = h;
    somThis->bpp = bpp;
    somThis->rowsize = ( somThis->width * somThis->bpp );
    if ( bpp != 4 ) {
        somThis->rowsize = (somThis->rowsize + 3) &~3;
    }
    somThis->dlen = somThis->rowsize * somThis->height;

    //somPrintf( "LuPixbufInit: allocating %d bytes\n", somThis->dlen );

    // To support HUGE pixbufs we need HMA
    // (Is OBJ_ANY compatible with old (9.0xx) kernels?)
    rc = DosAllocMem( &(somThis->data), somThis->dlen, PAG_COMMIT | fPERM | OBJ_ANY );
    assert( rc == 0 );

    memset( somThis->data, 0xff, somThis->dlen );
}


SOM_Scope long  SOMLINK getWidth(LuPixbuf *somSelf,  Environment *ev)
{
    LuPixbufData *somThis = LuPixbufGetData(somSelf);
    return somThis->width;
}

SOM_Scope long  SOMLINK getHeight(LuPixbuf *somSelf,  Environment *ev)
{
    LuPixbufData *somThis = LuPixbufGetData(somSelf);
    return somThis->height;
}

SOM_Scope short  SOMLINK getBpp(LuPixbuf *somSelf,  Environment *ev)
{
    LuPixbufData *somThis = LuPixbufGetData(somSelf);
    return somThis->bpp;
}

SOM_Scope long  SOMLINK getRowSize(LuPixbuf *somSelf,  Environment *ev)
{
    LuPixbufData *somThis = LuPixbufGetData(somSelf);
    return somThis->rowsize;
}

SOM_Scope long  SOMLINK getDataLen(LuPixbuf *somSelf,  Environment *ev)
{
    LuPixbufData *somThis = LuPixbufGetData(somSelf);
    return somThis->dlen;
}

SOM_Scope void*  SOMLINK getDataPtr(LuPixbuf *somSelf,  Environment *ev)
{
    LuPixbufData *somThis = LuPixbufGetData(somSelf);
    return somThis->data;
}

SOM_Scope void  SOMLINK putAt(LuPixbuf *somSelf,  Environment *ev,
                              LuPixbuf* p, long x, long y)
{
    LuPixbufData *somThis = LuPixbufGetData(somSelf);
    int xlen = std::min( somThis->width - x, p->getWidth( ev ) ) * somThis->bpp;
    int ylen = std::min( somThis->height - y, p->getHeight( ev ) );
    int rowstribe = p->getRowSize( ev );
    char *fromdt = (char *)p->getDataPtr( ev );
    char *todt = (char *)somThis->data + ( somThis->rowsize * y );
    for ( int i = 0; i < ylen; i++ )
    {
        char *from = fromdt + ( i * rowstribe );
        char *to = todt + ( i * somThis->rowsize ) + ( x * somThis->bpp );
        memcpy( to, from, xlen );
    }
}

SOM_Scope void SOMLINK somDestruct(LuPixbuf *somSelf, octet doFree,
                                   som3DestructCtrl* ctrl)
{
    LuPixbufData *somThis = NULL;
    somDestructCtrl globalCtrl;
    somBooleanVector myMask;
    LuPixbuf_BeginDestructor;

    // local LuPixbuf deinitialization code
    DosFreeMem( somThis->data );
    // local LuPixbuf deinitialization code end

    LuPixbuf_EndDestructor;
}


