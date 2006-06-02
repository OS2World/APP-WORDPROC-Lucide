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

#ifndef SOM_Module_evdjvu_Source
#define SOM_Module_evdjvu_Source
#endif
#define LuDjvuDocument_Class_Source

#include "ludjvu.xih"
#include <ddjvuapiw.h>


#define DJVU_SCALE 0.2


struct DjvuDocument
{
    ddjvu_context_t  *d_context;
    ddjvu_document_t *d_document;
    ddjvu_format_t   *d_format;
};


unsigned _System LibMain( unsigned hmod, unsigned termination )
{
    if ( termination ) {
        /* DLL is detaching from process */
    } else {
        /* DLL is attaching to process */
    }
    return( 1 );
}

extern "C" LuDocument * _System createObject()
{
    return new LuDjvuDocument;
}

extern "C" char * _System getSupportedExtensions()
{
    return "DJVU";
}

extern "C" char * _System getDescription()
{
    return "DjVu plugin, based on DjVuLibre.";
}

SOM_Scope boolean  SOMLINK loadFile(LuDjvuDocument *somSelf,
                                     Environment *ev, string filename,
                                    string password, string* error)
{
    LuDjvuDocumentData *somThis = LuDjvuDocumentGetData(somSelf);
    DjvuDocument *d = (DjvuDocument *)somThis->data;
    ddjvu_document_t *doc;

    doc = ddjvu_document_create_by_filename( d->d_context, filename, TRUE );

    if ( !doc ) {
        return FALSE;
    }

    if ( d->d_document ) {
        ddjvu_document_release( d->d_document );
    }

    d->d_document = doc;

    while ( !ddjvu_document_decoding_done( d->d_document ) ) {
        ddjvu_message_wait( d->d_context );
        ddjvu_message_pop( d->d_context );
    }

    return TRUE;
}

SOM_Scope short  SOMLINK getBpp(LuDjvuDocument *somSelf,  Environment *ev)
{
    return 3;
}

SOM_Scope boolean  SOMLINK isScalable(LuDjvuDocument *somSelf,
                                       Environment *ev)
{
    return TRUE;
}

SOM_Scope long  SOMLINK getPageCount(LuDjvuDocument *somSelf,
                                      Environment *ev)
{
    LuDjvuDocumentData *somThis = LuDjvuDocumentGetData(somSelf);
    DjvuDocument *d = (DjvuDocument *)somThis->data;
    return ddjvu_document_get_pagenum( d->d_document );
}

SOM_Scope void  SOMLINK getPageSize(LuDjvuDocument *somSelf,
                                     Environment *ev, long pagenum,
                                    double* width, double* height)
{
    LuDjvuDocumentData *somThis = LuDjvuDocumentGetData(somSelf);
    DjvuDocument *d = (DjvuDocument *)somThis->data;

    ddjvu_pageinfo_t info = { 0 };

    while ( ddjvu_document_get_pageinfo( d->d_document, pagenum, &info ) < DDJVU_JOB_OK ) {
        ddjvu_message_wait( d->d_context );
        ddjvu_message_pop( d->d_context );
    }

    if ( width != NULL ) {
        *width = info.width * DJVU_SCALE;
    }
    if ( height != NULL ) {
        *height = info.height * DJVU_SCALE;
    }
}

SOM_Scope void  SOMLINK renderPageToPixbuf(LuDjvuDocument *somSelf,
                                            Environment *ev,
                                           long pagenum, long src_x,
                                           long src_y, long src_width,
                                           long src_height, double scale,
                                           long rotation, LuPixbuf* pixbuf)
{
    LuDjvuDocumentData *somThis = LuDjvuDocumentGetData(somSelf);
    DjvuDocument *d = (DjvuDocument *)somThis->data;

    //somPrintf( "src_x: %d  src_y: %d  src_width: %d  src_height: %d\n",
    //            src_x, src_y, src_width, src_height );

    ddjvu_rect_t rrect;
    ddjvu_rect_t prect;
    ddjvu_page_t *d_page;

    double page_width, page_height;

    d_page = ddjvu_page_create_by_pageno( d->d_document, pagenum );

    while ( !ddjvu_page_decoding_done( d_page ) ) {
        ddjvu_message_wait( d->d_context );
        ddjvu_message_pop( d->d_context );
    }

    page_width = ddjvu_page_get_width( d_page ) * scale * DJVU_SCALE;
    page_height = ddjvu_page_get_height( d_page ) * scale * DJVU_SCALE;

    prect.x = 0;
    prect.y = 0;
    prect.w = (int)( page_width + 0.5 );
    prect.h = (int)( page_height + 0.5 );
    rrect.x = src_x;
    rrect.y = ( prect.h - src_y ) - src_height;
    rrect.w = src_width;
    rrect.h = src_height;

    long pixbuf_rowsize = pixbuf->getRowSize( ev );
    long pixbuf_height = pixbuf->getHeight( ev );
    short bpp = getBpp( somSelf, ev );

    LuPixbuf *pb = new LuPixbuf( ev, prect.w, prect.h, bpp );
    long pb_rowsize = pb->getRowSize( ev );
    char *pbbuf = (char *)pb->getDataPtr( ev );
    ddjvu_page_render( d_page, DDJVU_RENDER_COLOR,
                       &prect, &rrect, d->d_format,
                       pb_rowsize, pbbuf );

    char *pixbuf_data = (char *)pixbuf->getDataPtr( ev );
    char *src, *dst;
    int i, y;
    for ( y = (src_height-1), i = 0; i < src_height; y--, i++ )
    {
        src = pbbuf + (y * pb_rowsize);
        dst = pixbuf_data + (i * pixbuf_rowsize);
        memcpy( dst, src, src_width * bpp );
    }
    delete pb;
}

SOM_Scope boolean  SOMLINK getThumbnailSize(LuDjvuDocument *somSelf,
                                             Environment *ev,
                                            long pagenum,
                                            short suggested_width,
                                            short* width, short* height)
{
    LuDjvuDocumentData *somThis = LuDjvuDocumentGetData(somSelf);
    
    double page_ratio;
    double p_width = 0, p_height = 0;
    getPageSize( somSelf, ev, pagenum, &p_width, &p_height );

    page_ratio = p_height / p_width;
    *width = suggested_width;
    *height = (short)( suggested_width * page_ratio );

    return TRUE;
}

SOM_Scope LuPixbuf*  SOMLINK getThumbnail(LuDjvuDocument *somSelf,
                                           Environment *ev, long pagenum,
                                          short suggested_width)
{
    LuDjvuDocumentData *somThis = LuDjvuDocumentGetData(somSelf);
    DjvuDocument *d = (DjvuDocument *)somThis->data;

    short thumb_width = 0, thumb_height = 0;
    getThumbnailSize( somSelf, ev, pagenum, suggested_width, &thumb_width, &thumb_height );

    while ( ddjvu_thumbnail_status( d->d_document, pagenum, 1 ) < DDJVU_JOB_OK ) {
            ddjvu_message_wait( d->d_context );
            ddjvu_message_pop( d->d_context );  
    }
        
    int t_width = thumb_width;
    int t_height = thumb_height;
    short bpp = getBpp( somSelf, ev );
    LuPixbuf *tmppb = new LuPixbuf( ev, thumb_width, thumb_height, bpp );
    char *tmppb_data = (char *)tmppb->getDataPtr( ev );
    int tmppb_rowstride = tmppb->getRowSize( ev );

    ddjvu_thumbnail_render( d->d_document, pagenum, &t_width, &t_height,
                            d->d_format, tmppb_rowstride, tmppb_data );

    LuPixbuf *pixbuf = new LuPixbuf( ev, thumb_width, thumb_height, bpp );
    char *pixbuf_data = (char *)pixbuf->getDataPtr( ev );
    int pixbuf_rowstride = pixbuf->getRowSize( ev );
    char *src, *dst;
    int i, j;
    for ( i = 0, j = ( thumb_height - 1 ); i < thumb_height; i++, j-- )
    {
        src = tmppb_data + ( j * tmppb_rowstride );
        dst = pixbuf_data + (i * pixbuf_rowstride);
        memcpy( dst, src, pixbuf_rowstride );
    }
    delete tmppb;

    return pixbuf;
}

SOM_Scope void SOMLINK somDefaultInit(LuDjvuDocument *somSelf,
                                      som3InitCtrl* ctrl)
{
    LuDjvuDocumentData *somThis;
    somInitCtrl globalCtrl;
    somBooleanVector myMask;
    LuDjvuDocument_BeginInitializer_somDefaultInit;
    LuDjvuDocument_Init_LuDocument_somDefaultInit(somSelf, ctrl);

    // local LuDjvuDocument initialization code
    DjvuDocument *d = new DjvuDocument;
    memset( d, 0, sizeof( DjvuDocument ) );
    d->d_context = ddjvu_context_create("Lucide");
    d->d_format = ddjvu_format_create( DDJVU_FORMAT_BGR24, 0, 0 );
    ddjvu_format_set_row_order( d->d_format, 1 );
    d->d_document = NULL;

    somThis->data = d;
}


SOM_Scope void SOMLINK somDestruct(LuDjvuDocument *somSelf, octet doFree,
                                   som3DestructCtrl* ctrl)
{
    LuDjvuDocumentData *somThis; /* set in BeginDestructor */
    somDestructCtrl globalCtrl;
    somBooleanVector myMask;
    LuDjvuDocument_BeginDestructor;

    // local LuDjvuDocument deinitialization code
    DjvuDocument *d = (DjvuDocument *)somThis->data;
    if ( d->d_document ) {
        ddjvu_document_release( d->d_document );
    }
    ddjvu_context_release( d->d_context );
    ddjvu_format_release( d->d_format );
    delete d;
    // end of local LuDjvuDocument deinitialization code

    LuDjvuDocument_EndDestructor;
}


