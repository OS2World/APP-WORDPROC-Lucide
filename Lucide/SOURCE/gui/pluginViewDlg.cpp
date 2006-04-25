#define INCL_WIN
#include <os2.h>

#include "luutils.h"
#include "pluginViewDlg.h"
#include "Lucide_res.h"
#include "messages.h"


PluginViewDlg::PluginViewDlg( HWND hWndFrame, PluginInfoList *plist )
{
    hFrame   = hWndFrame;
    plugins  = plist;
    pname    = newstrdupL( PLUGLIST_PLUGIN_NAME );
    suppexts = newstrdupL( PLUGLIST_SUPP_EXTS );
    pdesc    = newstrdupL( PLUGLIST_PLUGIN_DESC );
}

PluginViewDlg::~PluginViewDlg()
{
    delete pname;
    delete suppexts;
    delete pdesc;
}

void PluginViewDlg::doDialog()
{
    WinDlgBox( HWND_DESKTOP, hFrame, pluginViewDlgProc,
               NULLHANDLE, IDD_VIEWPLUGINS, this );
    delete this;
}


struct ListRec
{
    MINIRECORDCORE miniRecordCore;
    PSZ extensions;
    PSZ description;
};


MRESULT EXPENTRY PluginViewDlg::pluginViewDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    // This is a static method, so we don't know which instantiation we're
    // dealing with. But we can get a pseudo-this from the parameter to
    // WM_INITDLG, which we therafter store with the window and retrieve
    // as follows:
    PluginViewDlg *_this = (PluginViewDlg *)WinQueryWindowULong( hwnd, QWL_USER );

    switch (msg)
    {

        // Dialog has just been created
        case WM_INITDLG:
        {
            // Save the mp2 into our user data so that subsequent calls have
            // access to the parent C++ object
            WinSetWindowULong( hwnd, QWL_USER, (ULONG)mp2 );
            _this = (PluginViewDlg *)mp2;
            localizeDialog( hwnd );
            centerWindow( _this->hFrame, hwnd );

            // init container
            HWND cntr = WinWindowFromID( hwnd, IDC_PLUGINSLIST );
            CNRINFO ci;
            ci.cb = sizeof( CNRINFO );
            WinSendMsg( cntr, CM_QUERYCNRINFO, MPFROMP( &ci ), MPFROMSHORT( ci.cb ) );
            ci.flWindowAttr &= ~( CV_NAME | CV_FLOW | CV_TEXT | CV_ICON );
            ci.flWindowAttr |= ( CV_DETAIL | CV_MINI | CA_DETAILSVIEWTITLES );
            WinSendMsg( cntr, CM_SETCNRINFO, MPFROMP( &ci ), MPFROMLONG( CMA_FLWINDOWATTR ) );

            PFIELDINFO pFieldInfo = (PFIELDINFO)WinSendMsg( cntr, CM_ALLOCDETAILFIELDINFO,
                                             MPFROMSHORT( 3 ), MPVOID );
            PFIELDINFO pFldInfo = pFieldInfo;
            pFldInfo->cb = sizeof( FIELDINFO );
            pFldInfo->flData = CFA_STRING | CFA_HORZSEPARATOR | CFA_SEPARATOR;
            pFldInfo->flTitle = CFA_CENTER;
            pFldInfo->pTitleData = (PVOID)_this->pname;
            pFldInfo->offStruct = FIELDOFFSET( ListRec, miniRecordCore.pszIcon );
            pFldInfo = pFldInfo->pNextFieldInfo;
            pFldInfo->cb = sizeof( FIELDINFO );
            pFldInfo->flData = CFA_STRING | CFA_HORZSEPARATOR | CFA_SEPARATOR;
            pFldInfo->flTitle = CFA_CENTER;
            pFldInfo->pTitleData = (PVOID)_this->suppexts;
            pFldInfo->offStruct = FIELDOFFSET( ListRec, extensions );
            pFldInfo = pFldInfo->pNextFieldInfo;
            pFldInfo->cb = sizeof( FIELDINFO );
            pFldInfo->flData = CFA_STRING | CFA_HORZSEPARATOR | CFA_SEPARATOR;
            pFldInfo->flTitle = CFA_CENTER;
            pFldInfo->pTitleData = (PVOID)_this->pdesc;
            pFldInfo->offStruct = FIELDOFFSET( ListRec, description );

            FIELDINFOINSERT fieldInfoInsert;
            fieldInfoInsert.cb = sizeof( FIELDINFOINSERT );
            fieldInfoInsert.pFieldInfoOrder = (PFIELDINFO)CMA_FIRST;
            fieldInfoInsert.cFieldInfoInsert = 3;
            fieldInfoInsert.fInvalidateFieldInfo = TRUE;
            WinSendMsg( cntr, CM_INSERTDETAILFIELDINFO, MPFROMP( pFieldInfo ), MPFROMP( &fieldInfoInsert ) );

            for ( int i = 0; i < _this->plugins->size(); i++ )
            {
                PluginInfo *pi = &(*_this->plugins)[ i ];

                ListRec *r = (ListRec *)WinSendMsg( cntr, CM_ALLOCRECORD,
                    MPFROMLONG( ( sizeof( ListRec ) - sizeof( MINIRECORDCORE ) ) ),
                                            MPFROMSHORT( 1 ) );

                r->miniRecordCore.cb = sizeof( MINIRECORDCORE );
                r->miniRecordCore.flRecordAttr = 0;
                r->miniRecordCore.ptlIcon.x = 0;
                r->miniRecordCore.ptlIcon.y = 0;
                r->miniRecordCore.pszIcon = newstrdup( pi->name.c_str() );
                r->miniRecordCore.hptrIcon = NULLHANDLE;
                r->extensions = newstrdup( pi->extensions.c_str() );
                r->description = newstrdup( pi->description.c_str() );

                RECORDINSERT ri;
                ri.cb = sizeof( RECORDINSERT );
                ri.pRecordParent= NULL;
                ri.pRecordOrder = (PRECORDCORE)CMA_END;
                ri.zOrder = (USHORT)CMA_TOP;
                ri.cRecordsInsert = 1;
                ri.fInvalidateRecord = TRUE;
                WinSendMsg( cntr, CM_INSERTRECORD, MPFROMP( r ), MPFROMP( &ri ) );
            }

            return (MRESULT)FALSE;
        }

        case WM_DESTROY:
        {
            HWND cntr = WinWindowFromID( hwnd, IDC_PLUGINSLIST );
            ListRec *pRecords = (ListRec *)WinSendMsg( cntr, CM_QUERYRECORD,
                                MPFROMP( NULL ), MPFROM2SHORT( CMA_FIRST, CMA_ITEMORDER ) );
            ListRec *pr = pRecords;

            while ( pr != NULL )
            {
                delete pr->miniRecordCore.pszIcon;
                delete pr->extensions;
                delete pr->description;
                pr = (ListRec *)WinSendMsg( cntr, CM_QUERYRECORD,
                                    MPFROMP( pr ), MPFROM2SHORT( CMA_NEXT, CMA_ITEMORDER ) );
            }
            WinSendMsg( cntr, CM_REMOVERECORD, MPFROMP( NULL ), MPFROM2SHORT( 0, CMA_FREE ) );
        }
        break;

    }
    return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}


