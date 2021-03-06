
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
 * Eugene Romanenko, netlabs.org.
 * Portions created by the Initial Developer are Copyright (C) 2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 * Dmitriy Kuminov, netlabs.org.
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

#ifndef SOM_Module_ludoc_Source
#define SOM_Module_ludoc_Source
#endif
#define LuDocument_Class_Source

#include "ludoc.xih"


unsigned EXPENTRY LibMain( unsigned hmod, unsigned termination )
{
    if ( termination ) {
        /* DLL is detaching from process */
    } else {
        /* DLL is attaching to process */
    }
    return( 1 );
}


extern "C" LuDocument * EXPENTRY createObject()
{
    return new LuDocument;
}

extern "C" char * EXPENTRY getSupportedExtensions()
{
    return "";
}

extern "C" LuSignatureCheck * EXPENTRY getSignatureCheck()
{
	return NULL;
}

extern "C" char * EXPENTRY getDescription()
{
    return "NULL plugin, abstract base class for Lucide plugins.";
}


/*
 * SOM_Scope long  SOMLINK getBpp(LuDocument *somSelf,  Environment *ev)
 */

/*
 * The prototype for getBpp was replaced by the following prototype:
 */
SOM_Scope short  SOMLINK getBpp(LuDocument *somSelf,  Environment *ev)
{
    // Abstract method does nothing
    return 0;
}

SOM_Scope boolean  SOMLINK isScalable(LuDocument *somSelf,  Environment *ev)
{
    return FALSE;
}


SOM_Scope boolean  SOMLINK isFixedImage(LuDocument *somSelf,
                                         Environment *ev)
{
    return TRUE;
}


SOM_Scope boolean  SOMLINK isRotable(LuDocument *somSelf,  Environment *ev)
{
    return FALSE;
}


SOM_Scope long  SOMLINK getPageCount(LuDocument *somSelf,  Environment *ev)
{
    // Abstract method does nothing
    return 0;
}


SOM_Scope void  SOMLINK getPageSize(LuDocument *somSelf,  Environment *ev,
                                    long pagenum, double* width,
                                    double* height)
{
    // Abstract method does nothing
}


SOM_Scope boolean  SOMLINK renderPageToPixbuf(LuDocument *somSelf,
                                               Environment *ev,
                                              long pagenum, long src_x,
                                              long src_y, long src_width,
                                              long src_height,
                                              double scale, long rotation,
                                              LuPixbuf* pixbuf,
                                              long* errorCode,
                                              string* error)
{
    // Abstract method does nothing
    if ( errorCode != NULL ) {
        *errorCode = LU_LDERR_NO_ERROR;
    }
    return FALSE;
}


SOM_Scope boolean  SOMLINK isAsynchRenderingSupported(LuDocument *somSelf,
                                                       Environment *ev)
{
    return FALSE;
}



SOM_Scope void  SOMLINK renderPageToPixbufAsynch(LuDocument *somSelf,
                                                  Environment *ev,
                                                 long pagenum,
                                                 long src_x,
                                                 long src_y,
                                                 long src_width,
                                                 long src_height,
                                                 double scale,
                                                 long rotation,
                                                 LuPixbuf* pixbuf,
                                                 LuDocument_asynchCallbackFn fnd,
                                                 LuDocument_asynchCallbackFn fna,
                                                 somToken fndata,
                                                 long* errorCode,
                                                 string* error)
{
    // Abstract method does nothing
    if ( errorCode != NULL ) {
        *errorCode = LU_RERR_NO_ERROR;
    }
}


SOM_Scope boolean  SOMLINK isRenderIntoPS(LuDocument *somSelf,
                                           Environment *ev)
{
    return FALSE;
}


SOM_Scope boolean  SOMLINK renderPageToPS(LuDocument *somSelf,
                                           Environment *ev, long pagenum,
                                          long src_x, long src_y,
                                          long src_width, long src_height,
                                          double scale, long rotation,
                                          unsigned long hps,
                                          somMToken rect, long* errorCode,
                                          string* error)
{
    // Abstract method does nothing
    if ( errorCode != NULL ) {
        *errorCode = LU_LDERR_NO_ERROR;
    }
    return FALSE;
}


SOM_Scope boolean  SOMLINK isHaveText(LuDocument *somSelf,
                                      Environment *ev)
{
    return FALSE;
}


SOM_Scope LuDocument_LuRectSequence*  SOMLINK getSelectionRectangles(LuDocument *somSelf,
                                                                    Environment *ev,
                                                                   long pagenum,
                                                                   LuRectangle* selection)
{
    // Abstract method does nothing
    return NULL;
}


SOM_Scope void  SOMLINK freeRectangles(Environment *ev,
                                       LuDocument_LuRectSequence* rectangles)
{
    if ( rectangles != NULL )
    {
        if ( ( ( rectangles->_maximum != 0 ) ||
               ( rectangles->_length != 0 ) ) &&
                   ( rectangles->_buffer != NULL ) )
        {
            SOMFree( rectangles->_buffer );
        }
        SOMFree( rectangles );
    }
}


SOM_Scope string  SOMLINK getText(LuDocument *somSelf,  Environment *ev,
                                  long pagenum, LuRectangle* selection)
{
    // Abstract method does nothing
    return NULL;
}


SOM_Scope boolean  SOMLINK isHaveLinks(LuDocument *somSelf,  Environment *ev)
{
    return FALSE;
}


SOM_Scope LuDocument_LuLinkMapSequence*  SOMLINK getLinkMapping(LuDocument *somSelf,
                                                                 Environment *ev,
                                                                long pagenum)
{
    // Abstract method, returns empty sequence
    LuDocument_LuLinkMapSequence *mapping = NULL;
    mapping = (LuDocument_LuLinkMapSequence *)SOMMalloc( sizeof( LuDocument_LuLinkMapSequence ) );
    mapping->_maximum = 0;
    mapping->_length = 0;
    mapping->_buffer = NULL;
    return mapping;
}


SOM_Scope void  SOMLINK freeLinkMapping(Environment *ev,
                                        LuDocument_LuLinkMapSequence* mapping)
{
    if ( mapping != NULL )
    {
        if ( ( ( mapping->_maximum != 0 ) ||
               ( mapping->_length != 0 ) ) &&
                   ( mapping->_buffer != NULL ) )
        {
            for ( int i = 0; i < mapping->_length; i++ )
            {
                if ( mapping->_buffer[ i ].link.title != NULL ) {
                    SOMFree( mapping->_buffer[ i ].link.title );
                }
                if ( mapping->_buffer[ i ].link.uri != NULL ) {
                    SOMFree( mapping->_buffer[ i ].link.uri );
                }
            }

            SOMFree( mapping->_buffer );
        }
        SOMFree( mapping );
    }
}


SOM_Scope boolean  SOMLINK isSaveable(LuDocument *somSelf,  Environment *ev)
{
    return FALSE;
}


SOM_Scope boolean  SOMLINK saveAs(LuDocument *somSelf,  Environment *ev,
                                  string filename)
{
    // Abstract method does nothing
    return FALSE;
}


SOM_Scope boolean  SOMLINK isPostScriptExportable(LuDocument *somSelf,
                                           Environment *ev)
{
    return FALSE;
}


SOM_Scope boolean  SOMLINK exportToPostScript(LuDocument *somSelf,
                                               Environment *ev,
                                              string filename,
                                              long first_page,
                                              long last_page,
                                              double width, double height,
                                              boolean* brkExport)
{
    // Abstract method does nothing
    return FALSE;
}


SOM_Scope boolean  SOMLINK isHaveFontInfo(LuDocument *somSelf,
                                           Environment *ev)
{
    return FALSE;
}


SOM_Scope LuDocument_LuFontInfoSequence*  SOMLINK getFontInfo(LuDocument *somSelf,
                                                               Environment *ev)
{
    // Abstract method does nothing
    return NULL;
}


SOM_Scope void  SOMLINK freeFontInfo(Environment *ev,
                                     LuDocument_LuFontInfoSequence* fonts)
{
    if ( fonts != NULL )
    {
        if ( ( ( fonts->_maximum != 0 ) ||
               ( fonts->_length != 0 ) ) &&
                   ( fonts->_buffer != NULL ) )
        {
            for ( int i = 0; i < fonts->_length; i++ )
            {
                if ( fonts->_buffer[ i ].name != NULL ) {
                    SOMFree( fonts->_buffer[ i ].name );
                }
                if ( fonts->_buffer[ i ].type != NULL ) {
                    SOMFree( fonts->_buffer[ i ].type );
                }
            }

            SOMFree( fonts->_buffer );
        }
        SOMFree( fonts );
    }
}


SOM_Scope boolean  SOMLINK isHaveIndex(LuDocument *somSelf,  Environment *ev)
{
    return FALSE;
}


SOM_Scope LuIndexNode*  SOMLINK getIndex(LuDocument *somSelf,
                                          Environment *ev)
{
    // Abstract method does nothing
    return NULL;
}


SOM_Scope LuDocumentInfo*  SOMLINK getDocumentInfo(LuDocument *somSelf,
                                                    Environment *ev)
{
    LuDocumentInfo *info = (LuDocumentInfo *)SOMMalloc( sizeof( LuDocumentInfo ) );
    memset( info, 0, sizeof( LuDocumentInfo ) );
    return info;
}


SOM_Scope void  SOMLINK freeDocumentInfo(Environment *ev, LuDocumentInfo* info)
{
    if ( info != NULL )
    {
        if ( info->fields_mask & LU_DOCUMENT_INFO_TITLE ) {
            SOMFree( info->title );
        }
        if ( info->fields_mask & LU_DOCUMENT_INFO_FORMAT ) {
            SOMFree( info->format );
        }
        if ( info->fields_mask & LU_DOCUMENT_INFO_AUTHOR ) {
            SOMFree( info->author );
        }
        if ( info->fields_mask & LU_DOCUMENT_INFO_SUBJECT ) {
            SOMFree( info->subject );
        }
        if ( info->fields_mask & LU_DOCUMENT_INFO_KEYWORDS ) {
            SOMFree( info->keywords );
        }
        if ( info->fields_mask & LU_DOCUMENT_INFO_CREATOR ) {
            SOMFree( info->creator );
        }
        if ( info->fields_mask & LU_DOCUMENT_INFO_PRODUCER ) {
            SOMFree( info->producer );
        }

        SOMFree( info );
    }
}


SOM_Scope boolean  SOMLINK getThumbnailSize(LuDocument *somSelf,
                                             Environment *ev,
                                            long pagenum,
                                            short suggested_width,
                                            short* width, short* height)
{
    // Abstract method does nothing
    return FALSE;
}


SOM_Scope LuPixbuf*  SOMLINK getThumbnail(LuDocument *somSelf,
                                           Environment *ev, long pagenum,
                                          short suggested_width)
{
    // Abstract method does nothing
    return NULL;
}



/*
 * SOM_Scope LuDocument_LuRectSequence*  SOMLINK searchText(LuDocument *somSelf,
 *                                                           Environment *ev,
 *                                                          long pagenum,
 *                                                          string text,
 *                                                          boolean caseSensitive
 *                                                          boolean findBack)
 */

/*
 * The prototype for searchText was replaced by the following prototype:
 */
SOM_Scope LuDocument_LuRectSequence*  SOMLINK searchText(LuDocument *somSelf, 
                                                          Environment *ev, 
                                                         long pagenum, 
                                                         string text, 
                                                         boolean caseSensitive, 
                                                         boolean findBack)
{
    // Abstract method does nothing
    return NULL;
}


SOM_Scope boolean  SOMLINK isCreateFileThumbnail(LuDocument *somSelf,
                                                  Environment *ev)
{
    return FALSE;
}


SOM_Scope boolean  SOMLINK isHaveInputFields(LuDocument *somSelf,
                                              Environment *ev)
{
    return FALSE;
}

SOM_Scope LuDocument_LuInputFieldSequence*  SOMLINK getInputFields(LuDocument *somSelf,
                                                                    Environment *ev,
                                                                   long pagenum)
{
    // Abstract method, returns empty sequence
    LuDocument_LuInputFieldSequence *fields = NULL;
    fields = (LuDocument_LuInputFieldSequence *)SOMMalloc( sizeof( LuDocument_LuInputFieldSequence ) );
    fields->_maximum = 0;
    fields->_length = 0;
    fields->_buffer = NULL;
    return fields;
}


SOM_Scope void  SOMLINK freeInputFields(Environment *ev, LuDocument_LuInputFieldSequence* aInputFields)
{
    if ( aInputFields != NULL ) {
        if ( ( ( aInputFields->_maximum != 0 ) ||
               ( aInputFields->_length != 0 ) ) &&
                   ( aInputFields->_buffer != NULL ) ) {
            for ( size_t i = 0; i < aInputFields->_length; ++i )
                delete aInputFields->_buffer[i];
            SOMFree( aInputFields->_buffer );
        }
        SOMFree( aInputFields );
    }
}


SOM_Scope void SOMLINK somDefaultInit(LuDocument *somSelf, som3InitCtrl* ctrl)
{
    somInitCtrl globalCtrl;
    somBooleanVector myMask;
    LuDocument_BeginInitializer_somDefaultInit;
    LuDocument_Init_SOMObject_somDefaultInit(somSelf, ctrl);
}


SOM_Scope boolean  SOMLINK loadFile(LuDocument *somSelf,  Environment *ev,
                                    string filename, string password,
                                    long* errorCode, string* error)
{
    // Abstract method does nothing
    if ( errorCode != NULL ) {
        *errorCode = LU_LDERR_NO_ERROR;
    }
    return FALSE;
}

