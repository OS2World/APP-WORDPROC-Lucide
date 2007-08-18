#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>

#include "globals.h"
#include "lucide_res.h"
#include "luutils.h"
#include "messages.h"


static HWND hWndFrame = NULLHANDLE;

void previewFile( HWND hwnd, const char *fn );

struct previewData
{
    PFNWP   oldPvProc;
    HDC     hdc;
    HPS     hps;
    HBITMAP image;
    char    *text;
};

#define IMAGE_X 256
#define IMAGE_Y 256

static MRESULT EXPENTRY PreviewProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    previewData *pd = (previewData *)WinQueryWindowULong( hwnd, QWL_USER );

    switch ( msg )
    {
        case WM_PAINT:
            {
                RECTL rect = {0};
                WinQueryWindowRect( hwnd, &rect );
                HPS hps = WinBeginPaint( hwnd, 0L, 0L );
                WinFillRect( hps, &rect, SYSCLR_WINDOWFRAME );
                rect.xLeft++;
                rect.yBottom++;
                rect.xRight--;
                rect.yTop--;
                WinFillRect( hps, &rect, SYSCLR_DIALOGBACKGROUND );
                if ( pd->image == NULLHANDLE ) {
                    WinDrawText( hps, -1, pd->text, &rect, 0, 0,
                                 DT_TEXTATTRS | DT_CENTER | DT_VCENTER );
                }
                else
                {
                    WinQueryWindowRect( hwnd, &rect );
                    BITMAPINFOHEADER bmi = { 0 };
                    bmi.cbFix = sizeof( BITMAPINFOHEADER );
                    GpiQueryBitmapParameters( pd->image, &bmi );
                    LONG xPos = ( rect.xRight - bmi.cx ) / 2;
                    LONG yPos = ( rect.yTop - bmi.cy ) / 2;
                    POINTL ptl = { xPos, yPos };
                    WinDrawBitmap( hps, pd->image, NULL, &ptl, 0, 0, DBM_NORMAL );
                }
                WinEndPaint( hps );
            }
            return (MRESULT)FALSE;

        case WM_DESTROY:
            pd->oldPvProc( hwnd, msg, mp1, mp2 );
            if ( pd->image != NULLHANDLE ) {
                GpiDeleteBitmap( pd->image );
            }
            delete pd->text;
            delete pd;
            return (MRESULT)FALSE;
    }
    return pd->oldPvProc( hwnd, msg, mp1, mp2 );
}

static void previewImageCreate( HWND hwnd )
{
    previewData *pd = new previewData;
    memset( pd, 0, sizeof( previewData ) );
    pd->oldPvProc = WinSubclassWindow( hwnd, PreviewProc );
    pd->text = newstrdupL( FDLG_NO_PREVIEW_AVAILABLE );
    WinSetWindowULong( hwnd, QWL_USER, (ULONG)pd );
    WinInvalidateRect( hwnd, NULL, FALSE );
}

static void resizePreview( HWND hwnd )
{
    HWND previewWindow = WinWindowFromID( hwnd, IDC_PREVIEW );
    RECTL rect = {0};
    WinQueryWindowRect( previewWindow, &rect );
    WinSetWindowPos( previewWindow, HWND_TOP, 0, 0, IMAGE_X + 2, rect.yTop, SWP_SIZE );
    WinQueryWindowRect( previewWindow, &rect );
    WinMapWindowPoints( previewWindow, hwnd, (PPOINTL)&rect, 2 );
    LONG xRight = rect.xRight;
    WinQueryWindowRect( hwnd, &rect );
    WinSetWindowPos( hwnd, HWND_TOP, 0, 0, xRight + 8, rect.yTop, SWP_SIZE );
}


static MRESULT EXPENTRY LcdFileDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch ( msg )
    {
        case WM_INITDLG:
        {
            resizePreview( hwnd );
            localizeDialog( hwnd );
            centerWindow( hWndFrame, hwnd );
            previewImageCreate( WinWindowFromID( hwnd, IDC_PREVIEW ) );
        }
        break;

        case WM_CONTROL:
        {
            switch (SHORT1FROMMP(mp1))
            {
                case DID_FILES_LB:
                    if (SHORT2FROMMP(mp1) == LN_SELECT)
                    {
                        const MRESULT mr = WinDefFileDlgProc(hwnd, msg, mp1, mp2);

                        const HWND lbHwnd = HWNDFROMMP(mp2);
                        const LONG index  = WinQueryLboxSelectedItem(lbHwnd);

                        char itemText[ CCHMAXPATH ] = { 0 };


                        if ( index >= 0 )
                        {
                            char fn[ CCHMAXPATH ] = { 0 };
                            FILEDLG *pfild = (FILEDLG *)WinQueryWindowULong(hwnd, QWL_USER);
                            WinQueryLboxItemText( lbHwnd, (SHORT)index, itemText, CCHMAXPATH );
                            strcpy( fn, pfild->szFullFile );
                            strcat( fn, itemText );
                            previewFile( WinWindowFromID( hwnd, IDC_PREVIEW ), fn );
                        }

                        return mr;
                    }
                    break;
            }
        }
        break;

    }

    return WinDefFileDlgProc( hwnd, msg, mp1, mp2 );
}


HWND LcdFileDlg( HWND hwndP, HWND hwndO, FILEDLG *pfild )
{
    hWndFrame = hwndO;

    pfild->fl |= FDS_CUSTOM;

    if ( pfild->pfnDlgProc == NULL ) {
        pfild->pfnDlgProc = LcdFileDlgProc;
    }

    pfild->hMod    = _hmod;
    pfild->usDlgId = IDD_LCD_FILEDLG;

    return WinFileDlg( hwndP, hwndO, pfild );
}


#define BUFSIZE      2000
#define BUFSIZEEAOP2 65000

static PVOID getEA( const char *pszPath, const char *pszEAname, PULONG ealen )
{
    CHAR   *pBuffer;
    PDENA2 pDena;
    ULONG  count;
    ULONG  offset;
    ULONG  length;
    PEAOP2 pEAOP2;
    PGEA2  pGea2;
    PFEA2  pFEA2;
    CHAR   *pEABase;
    PVOID  pEAValue = NULL;

    *ealen = 0;
    count = -1;

    if ( ( pBuffer = (char*)malloc(BUFSIZE) ) != NULL )
    {
        memset( pBuffer, 127, BUFSIZE );

        if ( DosEnumAttribute( ENUMEA_REFTYPE_PATH, (PSZ)pszPath, 1, pBuffer, BUFSIZE,
                               &count, ENUMEA_LEVEL_NO_VALUE ) == 0 )
        {
            pDena = (PDENA2)pBuffer;
            offset = 0;
            if ( (pEAOP2=(PEAOP2)malloc(BUFSIZEEAOP2)) != NULL )
            {
                pEAOP2->fpGEA2List = (PGEA2LIST)((CHAR*)pEAOP2 + sizeof(EAOP2));
                pGea2 = (&(pEAOP2->fpGEA2List->list[0]));
                if ( count != 0 )
                {
                    do
                    {
                        pDena = (PDENA2)((CHAR*)(pDena) + offset);
                        strcpy( pGea2->szName, pDena->szName );
                        pGea2->cbName = pDena->cbName;
                        offset = pDena->oNextEntryOffset;
                        length = pGea2->cbName+1 + sizeof(pGea2->cbName) +
                                            sizeof(pGea2->oNextEntryOffset);
                        if ((length%4) != 0 )
                            length += 4-(length%4);
                        if (!strcmp(pDena->szName, pszEAname))
                            pGea2->oNextEntryOffset = 0;
                        else
                            pGea2->oNextEntryOffset = offset ? length : 0;
                        pGea2 = (PGEA2)((CHAR*)pGea2 + length);
                    } while ( pDena->oNextEntryOffset != 0 );

                    pEAOP2->fpGEA2List->cbList = ((CHAR*)pGea2 - (CHAR*)(pEAOP2->fpGEA2List));
                    pEAOP2->fpFEA2List = (PFEA2LIST)((CHAR*)pEAOP2->fpGEA2List + pEAOP2->fpGEA2List->cbList);
                    pEAOP2->fpFEA2List->cbList = BUFSIZEEAOP2 - ((CHAR*)pEAOP2->fpFEA2List - (CHAR*)pEAOP2);

                    if ( ( DosQueryPathInfo( pszPath, FIL_QUERYEASFROMLIST, pEAOP2,
                                sizeof(EAOP2) ) == 0 ) && pEAOP2->fpFEA2List->cbList )
                    {
                        offset = 0;
                        pFEA2 = pEAOP2->fpFEA2List->list;
                        do
                        {
                            pFEA2 = (PFEA2)((CHAR*)pFEA2 + offset);
                            if ( !strcmp( pFEA2->szName, pszEAname ) )
                            {
                                pEABase = (CHAR*)pFEA2->szName + pFEA2->cbName+1;
                                USHORT len = pFEA2->cbValue;
                                if(len) {
                                    pEAValue=malloc( len );
                                    memcpy( pEAValue, pEABase, len );
                                    *ealen = len;
                                }
                                break;
                            }
                            offset = pFEA2->oNextEntryOffset;
                        } while ( offset );
                    }
                }
                free( pEAOP2 );
            }
        }
        free( pBuffer );
    }
    return pEAValue;
}


HBITMAP LoadBitmap( HAB hab, HDC hdc, HPS *hps, PSZ pszFileName );

static void readGif( HWND hwnd, const char *fn )
{
    previewData *pd = (previewData *)WinQueryWindowULong( hwnd, QWL_USER );
    pd->hdc = DevOpenDC( WinQueryAnchorBlock( hwnd ), OD_MEMORY, "*", 0L, NULL, 0 );
    pd->image = LoadBitmap( WinQueryAnchorBlock(hwnd), pd->hdc, &pd->hps, (PSZ)fn );
    if ( pd->image == NULLHANDLE )
    {
        if ( pd->hps != NULLHANDLE ) {
            GpiDestroyPS( pd->hps );
            pd->hps = NULLHANDLE;
        }
        if ( pd->hdc != NULLHANDLE ) {
            DevCloseDC( pd->hdc );
            pd->hdc = NULLHANDLE;
        }
    }
    WinInvalidateRect( hwnd, NULL, FALSE );
}

static void previewFile( HWND hwnd, const char *fn )
{
    previewData *pd = (previewData *)WinQueryWindowULong( hwnd, QWL_USER );

    if ( pd->image != NULLHANDLE ) {
        GpiDeleteBitmap( pd->image );
        pd->image = NULLHANDLE;
    }
    if ( pd->hps != NULLHANDLE ) {
        GpiDestroyPS( pd->hps );
        pd->hps = NULLHANDLE;
    }
    if ( pd->hdc != NULLHANDLE ) {
        DevCloseDC( pd->hdc );
        pd->hdc = NULLHANDLE;
    }
    WinInvalidateRect( hwnd, NULL, FALSE );


    ULONG ealen = 0;
    PVOID eadata = getEA( fn, "LUCIDE_THUMBNAIL", &ealen );

    if ( eadata != NULL )
    {
        char *tmpgif = new char[ CCHMAXPATH ];
        getTmpDir( tmpgif );
        strcat( tmpgif, "LUTHUMBR.GIF" );

        int h = open( tmpgif, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY,
                              S_IWRITE | S_IREAD );
        if ( h != -1 )
        {
            ULONG wrt = write( h, eadata, ealen );
            close( h );
            if ( wrt == ealen ) {
                readGif( hwnd, tmpgif );
            }
            unlink( tmpgif );
        }
        delete tmpgif;
        free( eadata );
    }
}

