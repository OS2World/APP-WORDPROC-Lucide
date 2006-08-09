
/*
 *  This file was generated by the SOM Compiler.
 *  Generated using:
 *     SOM incremental update: 2.24
 */


/*
 * Copyright (c) 2006, Eugene Romanenko, netlabs.org
 *
 *----------------------------------------------------------------------
 * This file is part of djvu plugin for Lucide (ludjvu).
 *
 *  ludjvu is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  ludjvu is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *----------------------------------------------------------------------
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
#ifdef __WATCOMC__
#include <ddjvuapiw.h>
#else
#include <ddjvuapi.h>
#endif
#ifdef __GNUC__
#define __min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#define SCALE_FACTOR 0.2


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
    return "DJVU;DJV";
}

extern "C" char * _System getDescription()
{
    return "DjVu plugin, based on DjVuLibre.";
}


static void djvu_handle_events( ddjvu_context_t *ctx )
{
    const ddjvu_message_t *msg;

    if ( ctx == NULL ) {
        return;
    }

    msg = ddjvu_message_wait( ctx );
    while ( ( msg = ddjvu_message_peek( ctx ) ) )
    {
        switch ( msg->m_any.tag )
        {
            case DDJVU_ERROR:
                // TODO: error message
            default:
                break;
        }
        ddjvu_message_pop( ctx );
    }
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
        djvu_handle_events( d->d_context );
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
        djvu_handle_events( d->d_context );
    }

    if ( width != NULL ) {
        *width = info.width * SCALE_FACTOR;
    }
    if ( height != NULL ) {
        *height = info.height * SCALE_FACTOR;
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
        djvu_handle_events( d->d_context );
    }

    page_width = ddjvu_page_get_width( d_page ) * scale * SCALE_FACTOR;
    page_height = ddjvu_page_get_height( d_page ) * scale * SCALE_FACTOR;

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
    long pb_height = pb->getHeight( ev );
    char *pbbuf = (char *)pb->getDataPtr( ev );
    ddjvu_page_render( d_page, DDJVU_RENDER_COLOR,
                       &prect, &rrect, d->d_format,
                       pb_rowsize, pbbuf );

    char *pixbuf_data = (char *)pixbuf->getDataPtr( ev );
    char *src, *dst;
    int i, y;
    int rowsize = __min( pb_rowsize, pixbuf_rowsize );
    int height = __min( pb_height, pixbuf_height );
    for ( y = (height-1), i = 0; i < height; y--, i++ )
    {
        src = pbbuf + (y * pb_rowsize);
        dst = pixbuf_data + (i * pixbuf_rowsize);
        memcpy( dst, src, rowsize );
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
        djvu_handle_events( d->d_context );
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


SOM_Scope boolean  SOMLINK isSaveable(LuDjvuDocument *somSelf,
                                       Environment *ev)
{
#ifdef __GNUC__
    return TRUE;
#else
    return FALSE;
#endif
}


SOM_Scope boolean  SOMLINK saveAs(LuDjvuDocument *somSelf,  Environment *ev,
                                  string filename)
{
#ifdef __GNUC__
    LuDjvuDocumentData *somThis = LuDjvuDocumentGetData(somSelf);
    DjvuDocument *d = (DjvuDocument *)somThis->data;

    FILE *f = NULL;
    if ( ( f = fopen( filename, "wb" ) ) == NULL ) {
        return FALSE;
    }

    ddjvu_job_t *job = ddjvu_document_save( d->d_document, f, 0, NULL );
    while ( !ddjvu_job_done( job ) ) {
        djvu_handle_events( d->d_context );
    }
    fclose( f );

    return TRUE;
#else
    return FALSE;
#endif
}


SOM_Scope boolean  SOMLINK isPostScriptExportable(LuDjvuDocument *somSelf,
                                                   Environment *ev)
{
#ifdef __GNUC__
    return TRUE;
#else
    return FALSE;
#endif
}


SOM_Scope boolean  SOMLINK exportToPostScript(LuDjvuDocument *somSelf,
                                    Environment *ev, string filename,
                                    long first_page, long last_page,
                                    double width, double height,
                                    boolean duplex, boolean* brkExport)
{
#ifdef __GNUC__
    LuDjvuDocumentData *somThis = LuDjvuDocumentGetData(somSelf);
    DjvuDocument *d = (DjvuDocument *)somThis->data;

    FILE *f = NULL;
    if ( ( f = fopen( filename, "wb" ) ) == NULL ) {
        return FALSE;
    }

    char pgbuf[ 20 ];
    snprintf( pgbuf, 20, "-page=%d-%d", first_page + 1, last_page + 1 );
    const char *optv[] = { pgbuf };

    ddjvu_job_t *job = ddjvu_document_print( d->d_document, f, 1, optv );
    while ( !ddjvu_job_done( job ) && !(*brkExport) ) {
        djvu_handle_events( d->d_context );
    }
    fclose( f );

    return TRUE;
#else
    return FALSE;
#endif
}


SOM_Scope boolean  SOMLINK isFixedImage(LuDjvuDocument *somSelf, 
                                         Environment *ev)
{
    return FALSE;
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
    LuDjvuDocumentData *somThis; // set in BeginDestructor
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


