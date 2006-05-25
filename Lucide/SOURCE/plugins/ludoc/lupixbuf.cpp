
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

#include "lupixbuf.xih"



/*
 * SOM_Scope void SOMLINK LuPixbufInit(LuPixbuf *somSelf,  Environment *ev,
 *                                     somInitCtrl* ctrl, long w, long h)
 */

/*
 * The prototype for LuPixbufInit was replaced by the following prototype:
 */
SOM_Scope void SOMLINK LuPixbufInit(LuPixbuf *somSelf,  Environment *ev, 
                                    somInitCtrl* ctrl, long w, 
                                    long h, short bpp)
{
    LuPixbufData *somThis;
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
    somThis->data = new char[ somThis->dlen ];
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
    int xlen = __min( somThis->width - x, p->getWidth( ev ) ) * somThis->bpp;
    int ylen = __min( somThis->height - y, p->getHeight( ev ) );
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
    LuPixbufData *somThis;
    somDestructCtrl globalCtrl;
    somBooleanVector myMask;
    LuPixbuf_BeginDestructor;

    // local LuPixbuf deinitialization code
    delete somThis->data;
    // local LuPixbuf deinitialization code end

    LuPixbuf_EndDestructor;
}


