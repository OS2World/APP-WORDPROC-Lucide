/*
 *
 *  Copyrights? Public domain, nah!
 *
 */

#define INCL_WIN
#define INCL_GPI
#include <os2.h>

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "wwbtn.h"

#define MAXTEXTLEN 256

/*static void adjustSize( HWND hwnd, LONG height )
{
    RECTL rect;
    LONG adjustment, halfadj;

    WinQueryWindowRect( hwnd , &rect );

    adjustment = height - rect.yTop;
    halfadj = adjustment / 2;

    WinMapWindowPoints( hwnd, WinQueryWindow( hwnd, QW_PARENT ), (PPOINTL)&rect, 2 );

    rect.yTop += ( adjustment - halfadj );
    rect.yBottom -= halfadj;

    WinSetWindowPos( hwnd, NULLHANDLE, rect.xLeft, rect.yBottom,
         rect.xRight - rect.xLeft + 1, height, SWP_SIZE | SWP_MOVE );
} */

static void DrawWWText( HWND hwnd, HPS hps, const char *text, PRECTL rect,
                        BOOL disabled, LONG color )
{
    ULONG style;
    LONG lChars = 0, charsdrawn = 0, height = 0, drawpos, lineoffs;
    RECTL rect1;
    char *text1;
    int lines = 0;
    const int len = strlen( text );
    ULONG alignStyle = WinQueryWindowULong( hwnd, QWL_STYLE ) & 
    					( DT_LEFT | DT_CENTER | DT_RIGHT );

    // определить количество строк и их совокупную высоту
    text1 = (char *)text;
    while ( charsdrawn < len )
    {
        memcpy( &rect1, rect, sizeof( RECTL ) );
        style=DT_MNEMONIC|DT_TOP|DT_WORDBREAK|DT_QUERYEXTENT|alignStyle;
        lChars = WinDrawText( hps, -1, text1, &rect1,
                              color, SYSCLR_DIALOGBACKGROUND, style );
        lines++;
        //printf( "text: %s, height: %d, charsdrawn: %d\n",
        //        text1, ( rect1.yTop - rect1.yBottom ), lChars );
        height += ( rect1.yTop - rect1.yBottom );
        text1 += lChars;
        charsdrawn += lChars;
    }

    //if ( height > rect->yTop )
    //{
    //    adjustSize( hwnd, height );
    //    rect->yTop = height;
    //}

    // draw lines
    text1 = (char *)text;
    charsdrawn = 0;
    lineoffs = 0;
    while ( charsdrawn < strlen( text ) )
    {
        memcpy( &rect1, rect, sizeof( RECTL ) );

        //printf( "xLeft: %d, yBottom: %d, xRight: %d, yTop: %d\n",
        //        rect->xLeft, rect->yBottom, rect->xRight, rect->yTop );

        drawpos = ( ( rect->yTop - rect->yBottom ) + height ) / 2;
        //printf( "drawpos 1 : %d \n", drawpos );
        drawpos += rect->yBottom;
        //printf( "drawpos 2 : %d \n", drawpos );
        drawpos -= lineoffs;
        //printf( "drawpos 3 : %d \n", drawpos );
        rect1.yTop = drawpos;

        style=DT_MNEMONIC|DT_TOP|DT_WORDBREAK|DT_ERASERECT|alignStyle;
        if ( disabled )
            style |= DT_HALFTONE;
        lChars = WinDrawText( hps, -1, text1, &rect1,
                              color, SYSCLR_DIALOGBACKGROUND, style );
        if ( lChars == 0 )
            break;

        style=DT_MNEMONIC|DT_TOP|DT_WORDBREAK|DT_QUERYEXTENT|alignStyle;
        WinDrawText( hps, -1, text1, &rect1,
                     color, SYSCLR_DIALOGBACKGROUND, style );

        //WinDrawBorder( hps, &rect1, 1, 1,CLR_BLUE,CLR_YELLOW,DB_PATCOPY);

        lineoffs += ( rect1.yTop - rect1.yBottom );
        text1 += lChars;
        charsdrawn += lChars;
    }
}

static void halftoneDraw( HPS hps , PRECTL r )
{
    POINTL ptl;
    LONG i , j;
    GpiSetColor( hps , SYSCLR_DIALOGBACKGROUND );
    for ( i = 0 ; i <= ( r->xRight - r->xLeft ) ; i++ )
    {
        ptl.x = i + r->xLeft;
        for ( j = 0 ; j <= ( r->yTop - r->yBottom ) ; j++ )
        {
            ptl.y = j + r->yBottom;
            if ( !( j & 1 ) )
            {
                if ( i & 1 )  ptl.y++;
                GpiSetPel( hps , &ptl );
            }
        }
    }
}

static void DrawCheckBitmap( HPS hps, PRECTL rect, int buttonType,
                             ULONG state, USHORT checkstate )
{
    RECTL subrect, htrect;
    LONG bwidth, bheight;
    BITMAPINFOHEADER2 bhdr;
    POINTL pos;
    HBITMAP bitmap = WinGetSysBitmap( HWND_DESKTOP, SBMP_CHECKBOXES );

    bhdr.cbFix = 16;
    GpiQueryBitmapInfoHeader( bitmap, &bhdr );
    bwidth = bhdr.cx / 4;
    bheight = bhdr.cy / 3;
    subrect.xLeft = bwidth * checkstate;

    if ( state & BDS_HILITED )
        subrect.xLeft += (bwidth * 2);

    subrect.yBottom = bheight * buttonType;
    subrect.xRight = subrect.xLeft + bwidth;
    subrect.yTop = subrect.yBottom + bheight;
    pos.x = 0;
    pos.y = ( ( rect->yTop - rect->yBottom ) / 2 ) - ( ( bheight / 2 ) + 1 );
    WinDrawBitmap( hps, bitmap, &subrect, &pos, 0, 0, DBM_NORMAL );
    if ( state & BDS_DISABLED )
    {
        htrect.xLeft = pos.x;
        htrect.yBottom = pos.y;
        htrect.xRight = pos.x + bwidth;
        htrect.yTop = pos.y + bheight;
        halftoneDraw( hps , &htrect );
    }
    GpiDeleteBitmap( bitmap );
    rect->xLeft += ( bwidth + 2 );
}

static void DrawWordWrapButton( PUSERBUTTON ubtn, int buttonType, USHORT checkstate )
{
    RECTL rect;
    char *text = (char *)malloc( MAXTEXTLEN );
    WinQueryWindowText( ubtn->hwnd, MAXTEXTLEN, text);
    WinQueryWindowRect( ubtn->hwnd , &rect );
    DrawCheckBitmap( ubtn->hps, &rect, buttonType, ubtn->fsState, checkstate );
    DrawWWText( ubtn->hwnd, ubtn->hps, text, &rect,
                ubtn->fsState & BDS_DISABLED, SYSCLR_WINDOWTEXT );
    free(text);
}


void UButtonJob( HWND owner, MPARAM mp1, MPARAM mp2, int buttonType, PUSHORT group )
{
    HWND btn = WinWindowFromID( owner, SHORT1FROMMP( mp1 ) );
    int ncode = SHORT2FROMMP( mp1 );
    USHORT checkstate = SHORT1FROMMR( WinSendMsg( btn, BM_QUERYCHECK, MPVOID, MPVOID ) );

    switch ( ncode )
    {
        case BN_CLICKED:
            if ( ( buttonType == UBTNTYPE_RADIOBUTTON ) && ( group != NULL ) )
            {
                USHORT i;
                for ( i = 0; i < group[0]; i++ )
                {
                    WinCheckButton( owner, group[ i + 1 ], FALSE );
                }
                WinSendMsg( btn, BM_SETCHECK, MPFROMSHORT( TRUE ), MPVOID );
            }
            else  WinSendMsg( btn, BM_SETCHECK, MPFROMSHORT( !checkstate ), MPVOID );
            break;
        case BN_PAINT:
            DrawWordWrapButton( (PUSERBUTTON)mp2, buttonType, checkstate );
            break;
    }
}


typedef struct
{
    PFNWP labelProc;
} wwlData;

static MRESULT EXPENTRY WordWrapLabelProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    wwlData *ld = (wwlData *)WinQueryWindowULong( hwnd, QWL_USER );
    switch ( msg )
    {
        case WM_PAINT:
            {
                HPS hps;
                RECTL rect;
                ULONG style;
                char *text = (char *)malloc( MAXTEXTLEN );
                WinQueryWindowText( hwnd, MAXTEXTLEN, text);
                WinQueryWindowRect( hwnd , &rect );
                style = WinQueryWindowULong( hwnd, QWL_STYLE );
                hps = WinBeginPaint( hwnd , 0L , 0L );

                DrawWWText( hwnd, hps, text, &rect, style & WS_DISABLED,
                            SYSCLR_WINDOWSTATICTEXT );

                WinEndPaint( hps );
                free( text );
            }
            return (MRESULT)FALSE;
        case WM_DESTROY:
            ld->labelProc( hwnd, msg, mp1, mp2 );
            free( ld );
            return (MRESULT)FALSE;
    }
    return ld->labelProc( hwnd, msg, mp1, mp2 );
}

void toWordWrapLabel( HWND hwnd )
{
    wwlData *ld;
    ld = (wwlData *)malloc( sizeof( wwlData ) );
    memset( ld, 0, sizeof( wwlData ) );
    ld->labelProc = WinSubclassWindow( hwnd, WordWrapLabelProc );
    WinSetWindowULong( hwnd, QWL_USER, (ULONG)ld );
    WinInvalidateRect( hwnd, NULL, FALSE );
}

