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


#include "os2all.h"

#include <process.h>

#include <ludoc.xh>

#include "globals.h"
#include "luutils.h"
#include "fontsInfoDlg.h"
#include "Lucide_res.h"
#include "messages.h"
#include "cpconv.h"


FontsInfoDlg::FontsInfoDlg( HWND hWndFrame, LuDocument *_doc )
{
    hFrame     = hWndFrame;
    doc        = _doc;
    hDialog    = NULLHANDLE;
    hContainer = NULLHANDLE;
    name       = newstrdupL( FONTINFO_NAME );
    type       = newstrdupL( FONTINFO_TYPE );
    embed      = newstrdupL( FONTINFO_EMBEDDED );
    emb_notembedded    = newstrdupL( FONTINFO_EMBED_NOT_EMBEDDED );
    emb_embedded       = newstrdupL( FONTINFO_EMBED_EMBEDDED );
    emb_embeddedsubset = newstrdupL( FONTINFO_EMBED_EMBEDDED_SUBSET );
}

FontsInfoDlg::~FontsInfoDlg()
{
    delete name;
    delete type;
    delete embed;
    delete emb_notembedded;
    delete emb_embedded;
    delete emb_embeddedsubset;
}

void FontsInfoDlg::doDialog()
{
    WinDlgBox( HWND_DESKTOP, hFrame, fontsInfoDlgProc,
               _hmod, IDD_FONTINFO, this );
    delete this;
}


struct ListRec
{
    MINIRECORDCORE miniRecordCore;
    PSZ type;
    PSZ embed;
};


void FontsInfoDlg::loadList()
{
    LuDocument_LuFontInfoSequence *fonts = doc->getFontInfo( ev );

    if ( fonts != NULL )
    {
        for ( int i = 0; i < fonts->_length; i++ )
        {
            ListRec *r = (ListRec *)WinSendMsg( hContainer, CM_ALLOCRECORD,
              MPFROMLONG( ( sizeof( ListRec ) - sizeof( MINIRECORDCORE ) ) ),
                                      MPFROMSHORT( 1 ) );

            r->miniRecordCore.cb = sizeof( MINIRECORDCORE );
            r->miniRecordCore.flRecordAttr = 0;
            r->miniRecordCore.ptlIcon.x = 0;
            r->miniRecordCore.ptlIcon.y = 0;
            r->miniRecordCore.pszIcon = newstrdup( fonts->_buffer[i].name );
            r->miniRecordCore.hptrIcon = NULLHANDLE;
            r->type = newstrdup( fonts->_buffer[i].type );
            r->embed = NULL;
            switch ( fonts->_buffer[i].embedded )
            {
                case LU_FONTEMBED_NOT_EMBEDDED:
                    r->embed = newstrdup( emb_notembedded );
                    break;
                case LU_FONTEMBED_EMBEDDED:
                    r->embed = newstrdup( emb_embedded );
                    break;
                case LU_FONTEMBED_EMBEDDED_SUBSET:
                    r->embed = newstrdup( emb_embeddedsubset );
                    break;
            }

            RECORDINSERT ri;
            ri.cb = sizeof( RECORDINSERT );
            ri.pRecordParent= NULL;
            ri.pRecordOrder = (PRECORDCORE)CMA_END;
            ri.zOrder = (USHORT)CMA_TOP;
            ri.cRecordsInsert = 1;
            ri.fInvalidateRecord = TRUE;
            WinSendMsg( hContainer, CM_INSERTRECORD, MPFROMP( r ), MPFROMP( &ri ) );
        }

        LuDocument::freeFontInfo( ev, fonts );
    }
}

void FontsInfoDlg::loadthread( void *p )
{
    FontsInfoDlg *_this = (FontsInfoDlg *)p;
    HAB thab = WinInitialize( 0 );
    HMQ thmq = WinCreateMsgQueue( thab, 0 );

    _this->loadList();

    WinSetDlgItemText( _this->hDialog, IDC_ENUMLABEL, "" );
    WinEnableControl( _this->hDialog, DID_OK, TRUE );
    WinInvalidateRect( _this->hDialog, NULL, TRUE );

    WinDestroyMsgQueue( thmq );
    WinTerminate( thab );
    _endthread();
}

static bool addPropToString( HWND hwndCntr, PRECORDCORE pRec, void *pUser )
{
    ListRec *rec = reinterpret_cast<ListRec *>( pRec );
    std::string *str = static_cast<std::string *>( pUser );
    if ( !str->empty() )
        *str += '\n';
    *str += rec->miniRecordCore.pszIcon;
    *str += " | ";
    *str += rec->type;
    *str += " | ";
    *str += rec->embed;
    return true;
}

static bool selectProp( HWND hwndCntr, PRECORDCORE pRec, void *pUser )
{
    ListRec *rec = reinterpret_cast<ListRec *>( pRec );
    return WinSendMsg( hwndCntr, CM_SETRECORDEMPHASIS,
                       MPFROMP( &rec->miniRecordCore ),
                       MPFROM2SHORT( TRUE, CRA_SELECTED ) ) == (MRESULT)TRUE;
}

MRESULT EXPENTRY FontsInfoDlg::fontsInfoDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    // This is a static method, so we don't know which instantiation we're
    // dealing with. But we can get a pseudo-this from the parameter to
    // WM_INITDLG, which we therafter store with the window and retrieve
    // as follows:
    FontsInfoDlg *_this = (FontsInfoDlg *)WinQueryWindowULong( hwnd, QWL_USER );

    switch (msg)
    {

        // Dialog has just been created
        case WM_INITDLG:
        {
            // Save the mp2 into our user data so that subsequent calls have
            // access to the parent C++ object
            WinSetWindowULong( hwnd, QWL_USER, (ULONG)mp2 );
            _this = (FontsInfoDlg *)mp2;
            _this->hDialog = hwnd;
            _this->hContainer = WinWindowFromID( hwnd, IDC_FONTSLIST );
            localizeDialog( hwnd );
            centerWindow( _this->hFrame, hwnd );

            // setup the accelerators
            WinSetAccelTable( hab, WinLoadAccelTable( hab, _hmod, IDA_FONTSINFOACCEL ), hwnd );

            // init container
            CNRINFO ci;
            ci.cb = sizeof( CNRINFO );
            WinSendMsg( _this->hContainer, CM_QUERYCNRINFO, MPFROMP( &ci ), MPFROMSHORT( ci.cb ) );
            ci.flWindowAttr &= ~( CV_NAME | CV_FLOW | CV_TEXT | CV_ICON );
            ci.flWindowAttr |= ( CV_DETAIL | CV_MINI | CA_DETAILSVIEWTITLES );
            WinSendMsg( _this->hContainer, CM_SETCNRINFO, MPFROMP( &ci ), MPFROMLONG( CMA_FLWINDOWATTR ) );

            PFIELDINFO pFieldInfo = (PFIELDINFO)WinSendMsg( _this->hContainer, CM_ALLOCDETAILFIELDINFO,
                                             MPFROMSHORT( 3 ), MPVOID );
            PFIELDINFO pFldInfo = pFieldInfo;
            pFldInfo->cb = sizeof( FIELDINFO );
            pFldInfo->flData = CFA_STRING | CFA_HORZSEPARATOR | CFA_SEPARATOR;
            pFldInfo->flTitle = CFA_CENTER;
            pFldInfo->pTitleData = (PVOID)_this->name;
            pFldInfo->offStruct = FIELDOFFSET( ListRec, miniRecordCore.pszIcon );
            pFldInfo = pFldInfo->pNextFieldInfo;
            pFldInfo->cb = sizeof( FIELDINFO );
            pFldInfo->flData = CFA_STRING | CFA_HORZSEPARATOR | CFA_SEPARATOR;
            pFldInfo->flTitle = CFA_CENTER;
            pFldInfo->pTitleData = (PVOID)_this->type;
            pFldInfo->offStruct = FIELDOFFSET( ListRec, type );
            pFldInfo = pFldInfo->pNextFieldInfo;
            pFldInfo->cb = sizeof( FIELDINFO );
            pFldInfo->flData = CFA_STRING | CFA_HORZSEPARATOR | CFA_SEPARATOR;
            pFldInfo->flTitle = CFA_CENTER;
            pFldInfo->pTitleData = (PVOID)_this->embed;
            pFldInfo->offStruct = FIELDOFFSET( ListRec, embed );

            FIELDINFOINSERT fieldInfoInsert;
            fieldInfoInsert.cb = sizeof( FIELDINFOINSERT );
            fieldInfoInsert.pFieldInfoOrder = (PFIELDINFO)CMA_FIRST;
            fieldInfoInsert.cFieldInfoInsert = 3;
            fieldInfoInsert.fInvalidateFieldInfo = TRUE;
            WinSendMsg( _this->hContainer, CM_INSERTDETAILFIELDINFO,
                        MPFROMP( pFieldInfo ), MPFROMP( &fieldInfoInsert ) );

            _beginthread( loadthread, NULL, 32768, _this );

            return (MRESULT)FALSE;
        }

        case WM_DESTROY:
        {
            ListRec *pRecords = (ListRec *)WinSendMsg( _this->hContainer, CM_QUERYRECORD,
                                MPFROMP( NULL ), MPFROM2SHORT( CMA_FIRST, CMA_ITEMORDER ) );
            ListRec *pr = pRecords;

            while ( pr != NULL )
            {
                delete pr->miniRecordCore.pszIcon;
                delete pr->type;
                delete pr->embed;
                pr = (ListRec *)WinSendMsg( _this->hContainer, CM_QUERYRECORD,
                                    MPFROMP( pr ), MPFROM2SHORT( CMA_NEXT, CMA_ITEMORDER ) );
            }
            WinSendMsg( _this->hContainer, CM_REMOVERECORD,
                        MPFROMP( NULL ), MPFROM2SHORT( 0, CMA_FREE ) );
        }
        break;

        case WM_COMMAND:
        {
            switch( SHORT1FROMMP(mp1) )
            {
                case CM_COPY:
                {
                    HWND cntr = WinWindowFromID( hwnd, IDC_PROPSLIST );
                    std::string props;
                    enumCntrEmphasis( cntr, CRA_SELECTED, addPropToString, &props );
                    if ( !props.empty()) {
                        char *utf8 = uniSysToUtf8( props.c_str(), NULL, NULL );
                        if ( utf8 )
                            textToClipbrd( hab, utf8 );
                        delete[] utf8;
                    }
                }
                return (MRESULT)FALSE;

                case CM_SELECTALL:
                {
                    HWND cntr = WinWindowFromID( hwnd, IDC_PROPSLIST );
                    enumCntrRecords( cntr, selectProp, NULL );
                }
                return (MRESULT)FALSE;

                default:
                    break;
            }
        }
        break;
    }
    return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}

