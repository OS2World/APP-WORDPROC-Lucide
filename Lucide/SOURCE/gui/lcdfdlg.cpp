#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>

#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>

#include "globals.h"
#include "pluginman.h"
#include "lucide_res.h"
#include "luutils.h"
#include "messages.h"


static HWND hWndFrame            = NULLHANDLE;
static char *szAllSupportedTypes = NULL;

void previewFile( HWND hwnd, const char *fn );

struct previewData
{
    PFNWP    oldPvProc;
    HDC      hdc;
    HPS      hps;
    HBITMAP  image;
    HBITMAP  mask;
    char     *text;
    HPS      hpsBuffer;
    HDC      hdcBuffer;
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
                RECTL rcl = {0};
                WinQueryWindowRect( hwnd, &rect );
                WinCopyRect( hab, &rcl, &rect );
                HPS hps = WinBeginPaint( hwnd, 0L, 0L );

                GpiSetColor( pd->hpsBuffer, SYSCLR_WINDOWTEXT );
                GpiSetBackColor( pd->hpsBuffer, SYSCLR_DIALOGBACKGROUND );
                WinFillRect( pd->hpsBuffer, &rect, SYSCLR_WINDOWFRAME );
                rect.xLeft++;
                rect.yBottom++;
                rect.xRight--;
                rect.yTop--;
                WinFillRect( pd->hpsBuffer, &rect, SYSCLR_DIALOGBACKGROUND );
                if ( pd->image == NULLHANDLE )
                {
                    WinDrawText( pd->hpsBuffer, -1, pd->text, &rect, 0, 0,
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

                    if ( pd->mask != NULLHANDLE )
                    {
                        GpiQueryBitmapParameters( pd->mask, &bmi );
                        GpiSetColor( pd->hpsBuffer, SYSCLR_DIALOGBACKGROUND );
                        GpiSetBackColor( pd->hpsBuffer, CLR_BLACK );
                        POINTL aptl[ 4 ] = { { xPos, yPos },
                                             { xPos + bmi.cx, yPos + (bmi.cy / 2) },
                                             { 0, bmi.cy / 2 }, { bmi.cx + 1, bmi.cy + 1 } };
                        GpiWCBitBlt( pd->hpsBuffer, pd->mask, 4, aptl, ROP_SRCAND, BBO_IGNORE );
                    }
                    if ( pd->image != NULLHANDLE )
                    {
                        GpiQueryBitmapParameters( pd->image, &bmi );
                        POINTL aptl1[ 4 ] = { { xPos, yPos },
                                              { xPos + bmi.cx, yPos + bmi.cy },
                                              { 0, 0 }, { bmi.cx + 1, bmi.cy + 1 } };
                        if ( pd->mask == NULLHANDLE ) {
                            WinDrawBitmap( pd->hpsBuffer, pd->image, NULL, aptl1, 0, 0, DBM_NORMAL );
                        }
                        else {
                            GpiWCBitBlt( pd->hpsBuffer, pd->image, 4, aptl1, ROP_SRCPAINT, BBO_IGNORE );
                        }
                    }
                }
                BlitGraphicsBuffer( hps, pd->hpsBuffer, &rcl );
                WinEndPaint( hps );
            }
            return (MRESULT)FALSE;

        case WM_DESTROY:
            pd->oldPvProc( hwnd, msg, mp1, mp2 );
            if ( pd->image != NULLHANDLE ) {
                GpiDeleteBitmap( pd->image );
            }
            if ( pd->mask != NULLHANDLE ) {
                GpiDeleteBitmap( pd->mask );
            }
            delete pd->text;
            DestroyGraphicsBuffer( pd->hpsBuffer, pd->hdcBuffer );
            delete pd;
            return (MRESULT)FALSE;
    }
    return pd->oldPvProc( hwnd, msg, mp1, mp2 );
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

static void previewImageCreate( HWND hwnd )
{
    previewData *pd = new previewData;
    memset( pd, 0, sizeof( previewData ) );
    RECTL rcl;
    WinQueryWindowRect( hwnd, &rcl );
    HPS hps = WinGetPS( hwnd );
    CreateGraphicsBuffer( hab, &rcl, hps, &pd->hpsBuffer, &pd->hdcBuffer );
    WinReleasePS( hps );
    pd->oldPvProc = WinSubclassWindow( hwnd, PreviewProc );
    pd->text = newstrdupL( FDLG_NO_PREVIEW_AVAILABLE );
    WinSetWindowULong( hwnd, QWL_USER, (ULONG)pd );
    WinInvalidateRect( hwnd, NULL, FALSE );
}

static bool isAllFiles( HWND hwnd )
{
    char ftext[ 200 ];
    WinQueryDlgItemText( hwnd, DID_FILTER_CB, sizeof( ftext ), ftext );
    return ( strcmp( ftext, szAllSupportedTypes ) != 0 );
}

static BOOL checkFile( char *file, std::vector<std::string> *extList )
{
    BOOL rVal = FALSE;
    std::vector<std::string>::const_iterator iter;
    for ( iter = extList->begin(); iter != extList->end(); iter++ )
    {
        char ext[ 100 ];
        ext[0] = '.';
        ext[1] = 0;
        strcat( ext, (*iter).c_str() );
        int flen = strlen( file );
        int elen = strlen( ext );

        if ( flen < elen ) {
            continue;
        }

        char *compare_pos = file + flen - elen;
        if ( stricmp( compare_pos, ext ) == 0 ) {
            rVal = TRUE;
            break;
        }
    }

    return rVal;
}


struct LcdFDlgData
{
    bool isAllFiles;
    std::vector<std::string> *extList;

    LcdFDlgData() {
        isAllFiles = false;
        extList = new std::vector<std::string>;
    }

    ~LcdFDlgData() {
        delete extList;
    }
};

static MRESULT EXPENTRY LcdFileDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    FILEDLG *pfild = (FILEDLG *)WinQueryWindowULong( hwnd, QWL_USER );

    switch ( msg )
    {
        case WM_INITDLG:
        {
            resizePreview( hwnd );
            localizeDialog( hwnd );
            centerWindow( hWndFrame, hwnd );
            previewImageCreate( WinWindowFromID( hwnd, IDC_PREVIEW ) );
            SHORT sInx = SHORT1FROMMR( WinSendDlgItemMsg( hwnd, DID_FILTER_CB, LM_SEARCHSTRING,
                    MPFROM2SHORT( LSS_CASESENSITIVE, 0 ), MPFROMP( szAllSupportedTypes ) ) );
            WinSendDlgItemMsg( hwnd, DID_FILTER_CB, LM_SELECTITEM,
                               MPFROMSHORT( sInx ), MPFROMSHORT( TRUE ) );

            ((LcdFDlgData *)pfild->ulUser)->isAllFiles = isAllFiles( hwnd );
        }
        break;

        case FDM_FILTER:
            if ( ((LcdFDlgData *)pfild->ulUser)->isAllFiles ) {
                return (MRESULT)TRUE;
            }
            else {
                return (MRESULT)checkFile( (char *)mp1,
                                           ((LcdFDlgData *)pfild->ulUser)->extList );
            }

        case WM_CONTROL:
        {
            switch ( SHORT1FROMMP(mp1) )
            {
                case DID_FILES_LB:
                    if (SHORT2FROMMP(mp1) == LN_SELECT)
                    {
                        const MRESULT mr = WinDefFileDlgProc( hwnd, msg, mp1, mp2 );

                        const HWND lbHwnd = HWNDFROMMP(mp2);
                        const LONG index  = WinQueryLboxSelectedItem(lbHwnd);

                        char itemText[ CCHMAXPATH ] = { 0 };

                        if ( index >= 0 )
                        {
                            char fn[ CCHMAXPATH ] = { 0 };
                            WinQueryLboxItemText( lbHwnd, (SHORT)index, itemText, CCHMAXPATH );
                            strcpy( fn, pfild->szFullFile );
                            strcat( fn, itemText );
                            previewFile( WinWindowFromID( hwnd, IDC_PREVIEW ), fn );
                        }

                        return mr;
                    }
                    break;

                case DID_FILTER_CB:
                    ((LcdFDlgData *)pfild->ulUser)->isAllFiles = isAllFiles( hwnd );
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
    if ( szAllSupportedTypes == NULL ) {
        szAllSupportedTypes = newstrdupL( FDLG_ALL_SUPPORTED_TYPES );
    }

    pfild->fl |= FDS_CUSTOM;

    if ( pfild->pfnDlgProc == NULL ) {
        pfild->pfnDlgProc = LcdFileDlgProc;
    }

    pfild->hMod    = _hmod;
    pfild->usDlgId = IDD_LCD_FILEDLG;

    char **apsz;
    apsz = (char **)malloc( sizeof( char* ) * 2 );
    apsz[ 0 ] = szAllSupportedTypes;
    apsz[ 1 ] = NULL;
    pfild->papszITypeList = (PAPSZ)apsz;
    pfild->ulUser = (ULONG)new LcdFDlgData;
    pluginMan->getExtsList( ((LcdFDlgData *)pfild->ulUser)->extList );
    HWND hDlg = WinFileDlg( hwndP, hwndO, pfild );
    free( apsz );
    delete ((LcdFDlgData *)pfild->ulUser);
    return hDlg;
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
                                USHORT len = 0;
                                PVOID pValue = NULL;
                                pEABase = (CHAR*)pFEA2->szName + pFEA2->cbName + 1;
                                if ( pszEAname[0] == '.' ) {
                                    len = *(USHORT *)( pEABase + sizeof( USHORT ) );
                                    pValue = pEABase + ( sizeof( USHORT ) * 2 );
                                }
                                else {
                                    len = pFEA2->cbValue;
                                    pValue = pEABase;
                                }
                                if ( len )
                                {
                                    pEAValue = malloc( len );
                                    memcpy( pEAValue, pValue, len );
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
}

static BOOL GetPointerBitmaps( HWND hwnd, PBYTE pchIcon, PBITMAPARRAYFILEHEADER2 pbafh2,
                               HBITMAP *phbmPointer, HBITMAP *phbmColor, USHORT usIconSize )
{
    HPS   hps;
    USHORT usBitCount, usRGB;
    PBITMAPFILEHEADER2 pbfh2;
    PBITMAPINFOHEADER2 pbmp2;
    USHORT usExtra, usExp;
    PBYTE  p;

    *phbmPointer = (HBITMAP)0;
    *phbmColor   = (HBITMAP)0;

    // Is it the correct icon type ?
    switch (pbafh2->usType)
    {
        case BFT_BITMAPARRAY:
            pbfh2 = &pbafh2->bfh2;
            break;

        case BFT_ICON:
        case BFT_BMAP:
        case BFT_POINTER:
        case BFT_COLORICON:
        case BFT_COLORPOINTER:
            pbfh2 = (PBITMAPFILEHEADER2)pbafh2;
            break;

        default :
            return FALSE;
    }
    pbmp2 = &pbfh2->bmp2;

    // Is it a BITMAPINFOHEADER or BITMAPINFOHEADER2 ?
    if (pbmp2->cbFix == sizeof (BITMAPINFOHEADER2))
    {
        usRGB = sizeof (RGB2);
        usBitCount = pbmp2->cBitCount;
        if (usIconSize && pbmp2->cx != usIconSize)
            return FALSE;
    }
    else if (pbmp2->cbFix == sizeof (BITMAPINFOHEADER))
    {
        PBITMAPINFOHEADER pbmp = (PBITMAPINFOHEADER)pbmp2;
        usRGB = sizeof (RGB);
        usBitCount = pbmp->cBitCount;
        if (usIconSize && pbmp->cx != usIconSize)
            return FALSE;
    }
    else  // Unknown length found
        return FALSE;

    // Create the first pointer by getting the presentation space first
    // and than call GpiCreateBitmap
    hps = WinGetPS(hwnd);
    *phbmPointer = GpiCreateBitmap( hps, pbmp2, CBM_INIT,
                                    (PBYTE)pchIcon + pbfh2->offBits, (PBITMAPINFO2)pbmp2 );
    if (*phbmPointer == GPI_ERROR)
    {
        WinReleasePS(hps);
        return FALSE;
    }
    WinReleasePS(hps);

    // If it is a color icon than another BITMAPFILEHEADER follow after
    // the color information. This color information contains of a number
    // of RGB or RGB2 structures. The number depends of the number of colors
    // in the bitmap. The number of colors is calculated by looking at
    // the Number of bits per pel and using this number as an exponent on 2.
    if (pbfh2->usType != BFT_COLORICON && pbfh2->usType != BFT_COLORPOINTER)
        return TRUE;

    // Calculate beginning of BITMAPFILEHEADER structure 2^Bits_per_pel
    for (usExtra = 1, usExp = 0; usExp < usBitCount; usExp++)
        usExtra *= 2;

    p = (PBYTE)(pbfh2) + (pbfh2->cbSize + usExtra * usRGB);
    pbfh2 = (PBITMAPFILEHEADER2)p;
    // Get adress of BITMAPINFOHEADER
    pbmp2 = &pbfh2->bmp2;

    if (pbmp2->cbFix == sizeof (BITMAPINFOHEADER2))
    {
        if (pbmp2->cBitCount == 1)
            return TRUE;
    }
    else if (pbmp2->cbFix == sizeof (BITMAPINFOHEADER))
    {
        PBITMAPINFOHEADER pbmp = (PBITMAPINFOHEADER)pbmp2;
        if (pbmp->cBitCount == 1)
            return TRUE;
    }
    else  // Unknown length found
        return TRUE;

    // And create bitmap number 2
    hps = WinGetPS(hwnd);
    *phbmColor = GpiCreateBitmap( hps, pbmp2, CBM_INIT,
                                  (PBYTE)pchIcon + pbfh2->offBits, (PBITMAPINFO2)pbmp2 );
    if (*phbmColor == GPI_ERROR)
    {
        GpiDeleteBitmap(*phbmPointer);
        return FALSE;
    }
    WinReleasePS(hps);
    return TRUE;
}

static BOOL IconBufferToBitmaps( HWND hwnd, PBYTE pchIcon, USHORT usIconSize,
                                 HBITMAP *clr, HBITMAP *ptr )
{
    static USHORT usDeviceCX = 0;
    static USHORT usDeviceCY = 0;
    BOOL fContinue, fIconFound;
    POINTERINFO PointerInfo;
    PBITMAPARRAYFILEHEADER2 pbafh2;
    PBYTE p;
    HPOINTER hptrIcon = NULLHANDLE;

    memset( &PointerInfo, 0, sizeof PointerInfo );

    if ( !usDeviceCX ) {
        usDeviceCX = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
        usDeviceCY = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);
    }

    fIconFound = FALSE;
    pbafh2 = (PBITMAPARRAYFILEHEADER2)pchIcon;

    switch (pbafh2->usType)
    {
        case BFT_BITMAPARRAY:
            break;
        case BFT_ICON:
        case BFT_BMAP:
        case BFT_POINTER:
        case BFT_COLORICON:
        case BFT_COLORPOINTER:
            if (GetPointerBitmaps( hwnd, pchIcon, pbafh2, &PointerInfo.hbmPointer,
                                   &PointerInfo.hbmColor, 0))
            {
                fIconFound = TRUE;
            }
            else
                return FALSE;
            break;
        default :
            return FALSE;
    }

    // First see if the icon contains an icon for the current device size.
    fContinue = TRUE;
    while (!fIconFound && fContinue)
    {
        if (pbafh2->cxDisplay == usDeviceCX && pbafh2->cyDisplay == usDeviceCY)
        {
            if (GetPointerBitmaps( hwnd, pchIcon, pbafh2, &PointerInfo.hbmPointer,
                                   &PointerInfo.hbmColor, usIconSize ))
            {
                fIconFound = TRUE;
                break;
            }
        }

        p = (PBYTE)pchIcon + pbafh2->offNext;
        if (!pbafh2->offNext)
            break;
        pbafh2 = (PBITMAPARRAYFILEHEADER2)p;
    }

    // Now look for the independed icons
    if (!fIconFound)
    {
        pbafh2 = (PBITMAPARRAYFILEHEADER2)pchIcon;
        fContinue = TRUE;
        while (fContinue)
        {
            if (pbafh2->cxDisplay == 0 && pbafh2->cyDisplay == 0)
            {
                if (GetPointerBitmaps( hwnd, pchIcon, pbafh2, &PointerInfo.hbmPointer,
                                       &PointerInfo.hbmColor, usIconSize ))
                {
                    fIconFound = TRUE;
                    break;
                }
            }

            p = (PBYTE)pchIcon + pbafh2->offNext;
            if (!pbafh2->offNext)
                break;
            pbafh2 = (PBITMAPARRAYFILEHEADER2)p;
        }
    }

    // if we still haven't found an icon we take the first icon there is
    if (!fIconFound)
    {
        pbafh2 = (PBITMAPARRAYFILEHEADER2)pchIcon;
        if (GetPointerBitmaps( hwnd, pchIcon, pbafh2, &PointerInfo.hbmPointer,
                               &PointerInfo.hbmColor, 0 ))
        {
            fIconFound = TRUE;
        }
    }

    if (!fIconFound)
        return FALSE;

    *clr = PointerInfo.hbmColor;
    *ptr = PointerInfo.hbmPointer;

    return TRUE;
}

static void previewFile( HWND hwnd, const char *fn )
{
    previewData *pd = (previewData *)WinQueryWindowULong( hwnd, QWL_USER );

    if ( pd->image != NULLHANDLE ) {
        GpiDeleteBitmap( pd->image );
        pd->image = NULLHANDLE;
    }
    if ( pd->mask != NULLHANDLE ) {
        GpiDeleteBitmap( pd->mask );
        pd->mask = NULLHANDLE;
    }
    if ( pd->hps != NULLHANDLE ) {
        GpiDestroyPS( pd->hps );
        pd->hps = NULLHANDLE;
    }
    if ( pd->hdc != NULLHANDLE ) {
        DevCloseDC( pd->hdc );
        pd->hdc = NULLHANDLE;
    }


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
    else // eadata == NULL
    {
        eadata = getEA( fn, ".ICON", &ealen );
        if ( eadata != NULL )
        {
            IconBufferToBitmaps( hwnd, (PBYTE)eadata, ealen, &pd->image, &pd->mask );
            free( eadata );
        }
    }

    WinInvalidateRect( hwnd, NULL, FALSE );
}


