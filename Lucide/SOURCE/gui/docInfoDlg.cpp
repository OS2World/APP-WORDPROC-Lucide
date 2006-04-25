#define INCL_WIN
#include <os2.h>

#include <string>

#include <ludoc.xh>

#include "luutils.h"
#include "docInfoDlg.h"
#include "Lucide_res.h"
#include "messages.h"


DocInfoDlg::DocInfoDlg( HWND hWndFrame, LuDocumentInfo *_dinfo )
{
    hFrame   = hWndFrame;
    dinfo    = _dinfo;
}

DocInfoDlg::~DocInfoDlg()
{
}

void DocInfoDlg::doDialog()
{
    WinDlgBox( HWND_DESKTOP, hFrame, docInfoDlgProc,
               NULLHANDLE, IDD_DOCINFO, this );
    delete this;
}


struct ListRec
{
    MINIRECORDCORE miniRecordCore;
    PSZ value;
};


void DocInfoDlg::insertPair( HWND cntr, const char *key, const char *value )
{
    ListRec *r = (ListRec *)WinSendMsg( cntr, CM_ALLOCRECORD,
        MPFROMLONG( ( sizeof( ListRec ) - sizeof( MINIRECORDCORE ) ) ),
                                MPFROMSHORT( 1 ) );

    r->miniRecordCore.cb = sizeof( MINIRECORDCORE );
    r->miniRecordCore.flRecordAttr = 0;
    r->miniRecordCore.ptlIcon.x = 0;
    r->miniRecordCore.ptlIcon.y = 0;
    r->miniRecordCore.pszIcon = newstrdupL( key );
    r->miniRecordCore.hptrIcon = NULLHANDLE;
    r->value = newstrdup( value );

    RECORDINSERT ri;
    ri.cb = sizeof( RECORDINSERT );
    ri.pRecordParent= NULL;
    ri.pRecordOrder = (PRECORDCORE)CMA_END;
    ri.zOrder = (USHORT)CMA_TOP;
    ri.cRecordsInsert = 1;
    ri.fInvalidateRecord = TRUE;
    WinSendMsg( cntr, CM_INSERTRECORD, MPFROMP( r ), MPFROMP( &ri ) );
}


void DocInfoDlg::loadValues( HWND cntr )
{
    if ( dinfo == NULL ) {
        return;
    }

    if ( dinfo->fields_mask & LU_DOCUMENT_INFO_TITLE ) {
        insertPair( cntr, DOCINFO_TITLE, dinfo->title );
    }
    if ( dinfo->fields_mask & LU_DOCUMENT_INFO_FORMAT ) {
        insertPair( cntr, DOCINFO_FORMAT, dinfo->format );
    }
    if ( dinfo->fields_mask & LU_DOCUMENT_INFO_AUTHOR ) {
        insertPair( cntr, DOCINFO_AUTHOR, dinfo->author );
    }
    if ( dinfo->fields_mask & LU_DOCUMENT_INFO_SUBJECT ) {
        insertPair( cntr, DOCINFO_SUBJECT, dinfo->subject );
    }
    if ( dinfo->fields_mask & LU_DOCUMENT_INFO_KEYWORDS ) {
        insertPair( cntr, DOCINFO_KEYWORDS, dinfo->keywords );
    }
    if ( dinfo->fields_mask & LU_DOCUMENT_INFO_CREATOR ) {
        insertPair( cntr, DOCINFO_CREATOR, dinfo->creator );
    }
    if ( dinfo->fields_mask & LU_DOCUMENT_INFO_PRODUCER ) {
        insertPair( cntr, DOCINFO_PRODUCER, dinfo->producer );
    }
    if ( dinfo->fields_mask & LU_DOCUMENT_INFO_CREATION_DATE ) {
        insertPair( cntr, DOCINFO_CREATION_DATE,
                    time2string( dinfo->creation_date ).c_str() );
    }
    if ( dinfo->fields_mask & LU_DOCUMENT_INFO_MOD_DATE ) {
        insertPair( cntr, DOCINFO_MOD_DATE,
                    time2string( dinfo->modified_date ).c_str() );
    }
}


MRESULT EXPENTRY DocInfoDlg::docInfoDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    // This is a static method, so we don't know which instantiation we're
    // dealing with. But we can get a pseudo-this from the parameter to
    // WM_INITDLG, which we therafter store with the window and retrieve
    // as follows:
    DocInfoDlg *_this = (DocInfoDlg *)WinQueryWindowULong( hwnd, QWL_USER );

    switch (msg)
    {

        // Dialog has just been created
        case WM_INITDLG:
        {
            // Save the mp2 into our user data so that subsequent calls have
            // access to the parent C++ object
            WinSetWindowULong( hwnd, QWL_USER, (ULONG)mp2 );
            _this = (DocInfoDlg *)mp2;
            localizeDialog( hwnd );
            centerWindow( _this->hFrame, hwnd );

            // init container
            HWND cntr = WinWindowFromID( hwnd, IDC_PROPSLIST );
            CNRINFO ci;
            ci.cb = sizeof( CNRINFO );
            WinSendMsg( cntr, CM_QUERYCNRINFO, MPFROMP( &ci ), MPFROMSHORT( ci.cb ) );
            ci.flWindowAttr &= ~( CV_NAME | CV_FLOW | CV_TEXT | CV_ICON | CA_DETAILSVIEWTITLES );
            ci.flWindowAttr |= ( CV_DETAIL | CV_MINI );
            WinSendMsg( cntr, CM_SETCNRINFO, MPFROMP( &ci ), MPFROMLONG( CMA_FLWINDOWATTR ) );

            PFIELDINFO pFieldInfo = (PFIELDINFO)WinSendMsg( cntr, CM_ALLOCDETAILFIELDINFO,
                                             MPFROMSHORT( 2 ), MPVOID );
            PFIELDINFO pFldInfo = pFieldInfo;
            pFldInfo->cb = sizeof( FIELDINFO );
            pFldInfo->flData = CFA_STRING | CFA_HORZSEPARATOR;
            pFldInfo->flTitle = CFA_CENTER;
            pFldInfo->pTitleData = NULL;
            pFldInfo->offStruct = FIELDOFFSET( ListRec, miniRecordCore.pszIcon );
            pFldInfo = pFldInfo->pNextFieldInfo;
            pFldInfo->cb = sizeof( FIELDINFO );
            pFldInfo->flData = CFA_STRING | CFA_HORZSEPARATOR;
            pFldInfo->flTitle = CFA_CENTER;
            pFldInfo->pTitleData = NULL;
            pFldInfo->offStruct = FIELDOFFSET( ListRec, value );

            FIELDINFOINSERT fieldInfoInsert;
            fieldInfoInsert.cb = sizeof( FIELDINFOINSERT );
            fieldInfoInsert.pFieldInfoOrder = (PFIELDINFO)CMA_FIRST;
            fieldInfoInsert.cFieldInfoInsert = 2;
            fieldInfoInsert.fInvalidateFieldInfo = TRUE;
            WinSendMsg( cntr, CM_INSERTDETAILFIELDINFO,
                   MPFROMP( pFieldInfo ), MPFROMP( &fieldInfoInsert ) );

            _this->loadValues( cntr );

            return (MRESULT)FALSE;
        }

        case WM_DESTROY:
        {
            HWND cntr = WinWindowFromID( hwnd, IDC_PROPSLIST );
            ListRec *pRecords = (ListRec *)WinSendMsg( cntr, CM_QUERYRECORD,
                                MPFROMP( NULL ), MPFROM2SHORT( CMA_FIRST, CMA_ITEMORDER ) );
            ListRec *pr = pRecords;

            while ( pr != NULL )
            {
                delete pr->miniRecordCore.pszIcon;
                delete pr->value;
                pr = (ListRec *)WinSendMsg( cntr, CM_QUERYRECORD,
                                    MPFROMP( pr ), MPFROM2SHORT( CMA_NEXT, CMA_ITEMORDER ) );
            }
            WinSendMsg( cntr, CM_REMOVERECORD, MPFROMP( NULL ), MPFROM2SHORT( 0, CMA_FREE ) );
        }
        break;

    }
    return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}


