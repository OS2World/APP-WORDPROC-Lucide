/*
 *  Transfer a label into link.
 *  by Eugene Romanenko
 *
 *  This code is in the public domain and has no copyright.
 */

#define INCL_WIN
#define INCL_GPI
#include <os2.h>

#include <string.h>
#include <malloc.h>


int startBrowser( const char *url );


#define MAXTEXTLEN 256

static HPOINTER handPtr = NULLHANDLE;

typedef struct
{
    PFNWP labelProc;
    RECTL textRect;
    char  *url;
} linkData;

static MRESULT EXPENTRY LinkLabelProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    linkData *ld = (linkData *)WinQueryWindowULong( hwnd, QWL_USER );
    switch ( msg )
    {
        case WM_PAINT:
            {
                FONTMETRICS fm;
                FATTRS fat;
                HPS hps;
                ULONG style;
                char *text = (char *)malloc( MAXTEXTLEN );
                WinQueryWindowText( hwnd, MAXTEXTLEN, text);
                hps = WinBeginPaint( hwnd, 0L, 0L );
                GpiQueryFontMetrics( hps, sizeof( FONTMETRICS ), &fm );
                memset( &fat, 0, sizeof( fat ) );
                fat.usRecordLength = sizeof( FATTRS );
                fat.lMatch = fm.lMatch;
                fat.fsSelection = FATTR_SEL_UNDERSCORE;
                strcpy( fat.szFacename, fm.szFacename );
                GpiDeleteSetId( hps, 1 );
                GpiCreateLogFont( hps, 0, 1, &fat );
                GpiSetCharSet( hps, 1 );
                WinQueryWindowRect( hwnd, &ld->textRect );
                style = WinQueryWindowULong( hwnd, QWL_STYLE );
                style &= DT_LEFT|DT_CENTER|DT_RIGHT|DT_TOP|DT_VCENTER|DT_BOTTOM;
                WinDrawText( hps, -1, text, &ld->textRect,
                             CLR_BLUE, SYSCLR_DIALOGBACKGROUND,
                             style | DT_ERASERECT | DT_UNDERSCORE );
                WinDrawText( hps, -1, text, &ld->textRect,
                             CLR_BLUE, SYSCLR_DIALOGBACKGROUND,
                             style | DT_QUERYEXTENT | DT_UNDERSCORE );
                WinEndPaint( hps );
                free( text );
            }
            return (MRESULT)FALSE;

        case WM_MOUSEMOVE:
            {
                if ( handPtr != NULLHANDLE )
                {
                    POINTL ptl;
                    ptl.x = SHORT1FROMMP( mp1 );
                    ptl.y = SHORT2FROMMP( mp1 );
                    if ( WinPtInRect( WinQueryAnchorBlock( hwnd ), &ld->textRect, &ptl) )
                    {
                        WinSetPointer( HWND_DESKTOP, handPtr );
                        return (MRESULT)FALSE;
                    }
                }
            }
            break;

        case WM_BUTTON1CLICK:
            {
                char *text;
                POINTL ptl;

                ptl.x = SHORT1FROMMP( mp1 );
                ptl.y = SHORT2FROMMP( mp1 );
                if ( !WinPtInRect( WinQueryAnchorBlock( hwnd ), &ld->textRect, &ptl) ) {
                    break;
                }

                if ( ld->url == NULL ) {
                    text = (char *)malloc( MAXTEXTLEN );
                    WinQueryWindowText( hwnd, MAXTEXTLEN, text);
                }
                else {
                    text = strdup( ld->url );
                }

                startBrowser( text );

                free( text );
            }
            break;

        case WM_DESTROY:
            ld->labelProc( hwnd, msg, mp1, mp2 );
            if ( ld->url != NULL ) {
                free( ld->url );
            }
            free( ld );
            return (MRESULT)FALSE;
    }

    return ld->labelProc( hwnd, msg, mp1, mp2 );
}


void setLinkPointer( HPOINTER hp )
{
    handPtr = hp;
}


void toLink( HWND hwnd )
{
    linkData *ld;
    ld = (linkData *)malloc( sizeof( linkData ) );
    memset( ld, 0, sizeof( linkData ) );
    ld->labelProc = WinSubclassWindow( hwnd, LinkLabelProc );
    WinSetWindowULong( hwnd, QWL_USER, (ULONG)ld );
    WinInvalidateRect( hwnd, NULL, FALSE );
}

void toLinkWithUrl( HWND hwnd, char *url )
{
    linkData *ld;
    ld = (linkData *)malloc( sizeof( linkData ) );
    memset( ld, 0, sizeof( linkData ) );
    ld->url = strdup( url );
    ld->labelProc = WinSubclassWindow( hwnd, LinkLabelProc );
    WinSetWindowULong( hwnd, QWL_USER, (ULONG)ld );
    WinInvalidateRect( hwnd, NULL, FALSE );
}

