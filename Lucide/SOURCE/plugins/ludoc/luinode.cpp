
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

#ifndef SOM_Module_luinode_Source
#define SOM_Module_luinode_Source
#endif
#define LuIndexNode_Class_Source

#include <string.h>
#include <vector>
using namespace std;

#include "luinode.xih"



static char *newstrdup( const char *s )
{
    if ( s == NULL ) {
        return NULL;
    }
    char *temp = new char[ strlen( s ) + 1 ];
    strcpy( temp, s );
    return temp;
}


typedef vector<LuIndexNode *> NodeList;


struct LuINodeData
{
    LuLink link;
    NodeList *nodes;
    int index;

    LuINodeData( LuLink *l );
    ~LuINodeData();
};

LuINodeData::LuINodeData( LuLink *l )
{
    memset( &link, 0, sizeof( LuLink ) );
    if ( l != NULL )
    {
        link.title = newstrdup( l->title );
        link.uri = newstrdup( l->uri );
        link.type = l->type;
        link.page = l->page;
    }

    nodes = new NodeList;

    index = 0;
}

LuINodeData::~LuINodeData()
{
    delete link.title;
    delete link.uri;

    for ( int i = 0; i < nodes->size(); i++ ) {
        delete (*nodes)[i];
    }
    delete nodes;
}


SOM_Scope void SOMLINK LuIndexNodeInit(LuIndexNode *somSelf,
                                        Environment *ev, somInitCtrl* ctrl,
                                       LuLink* link)
{
    LuIndexNodeData *somThis;
    somInitCtrl globalCtrl;
    somBooleanVector myMask;
    LuIndexNode_BeginInitializer_LuIndexNodeInit;

    LuIndexNode_Init_SOMObject_somDefaultInit(somSelf, ctrl);

    // local LuIndexNode initialization code added by programmer
    LuINodeData *d = new LuINodeData( link );
    somThis->data = d;
}


SOM_Scope void  SOMLINK addChild(LuIndexNode *somSelf,  Environment *ev,
                                 LuIndexNode* node)
{
    LuIndexNodeData *somThis = LuIndexNodeGetData(somSelf);
    LuINodeData *d = (LuINodeData *)somThis->data;
    d->nodes->push_back( node );
}


SOM_Scope LuIndexNode*  SOMLINK getFirstChild(LuIndexNode *somSelf,
                                               Environment *ev)
{
    LuIndexNodeData *somThis = LuIndexNodeGetData(somSelf);
    LuINodeData *d = (LuINodeData *)somThis->data;
    d->index = 0;
    if ( d->nodes->size() == 0 ) {
        return NULL;
    }
    return (*(d->nodes))[ d->index++ ];
}


SOM_Scope LuIndexNode*  SOMLINK getNextChild(LuIndexNode *somSelf,
                                              Environment *ev)
{
    LuIndexNodeData *somThis = LuIndexNodeGetData(somSelf);
    LuINodeData *d = (LuINodeData *)somThis->data;
    if ( d->index >= d->nodes->size() ) {
        return NULL;
    }
    return (*(d->nodes))[ d->index++ ];
}


SOM_Scope LuLink*  SOMLINK getLink(LuIndexNode *somSelf,  Environment *ev)
{
    LuIndexNodeData *somThis = LuIndexNodeGetData(somSelf);
    LuINodeData *d = (LuINodeData *)somThis->data;
    return &(d->link);
}


SOM_Scope void SOMLINK somDestruct(LuIndexNode *somSelf, octet doFree,
                                   som3DestructCtrl* ctrl)
{
    LuIndexNodeData *somThis;
    somDestructCtrl globalCtrl;
    somBooleanVector myMask;
    LuIndexNode_BeginDestructor;

    // local LuIndexNode deinitialization code begin
    LuINodeData *d = (LuINodeData *)somThis->data;
    //somPrintf( "LuIndexNode destructor, title %s\n", d->link.title );
    delete d;
    // local LuIndexNode deinitialization code end

    LuIndexNode_EndDestructor;
}


