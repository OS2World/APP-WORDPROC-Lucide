/*
 *  PM Toolbar implementation.
 *  by Eugene Romanenko
 *
 *  This code is in the public domain and has no copyright.
 */

#include "os2all.h"

#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "tb_spl.h"


class t_timer
{
    protected:
        long msecs;
    public:
        t_timer();
        void reset();
        long elapsed();
};

inline t_timer::t_timer() { reset(); }

void t_timer::reset()
{
    DosQuerySysInfo( QSV_MS_COUNT, QSV_MS_COUNT, &msecs, sizeof( msecs ) );
}

long t_timer::elapsed()
{
    long now;
    DosQuerySysInfo( QSV_MS_COUNT, QSV_MS_COUNT, &now, sizeof( now ) );
    return ( now - msecs );
}

static char *newstrdup( const char *s )
{
    if ( s == NULL ) {
        return NULL;
    }
    char *temp = new char[ strlen( s ) + 1 ];
    strcpy( temp, s );
    return temp;
}

const unsigned long lBufMax = 256;

static char *newstrdup( HAB hab, ULONG resId, HMODULE hModule )
{
    char *pBuf = new char[ lBufMax ];
    WinLoadString( hab, hModule, resId, lBufMax, pBuf );
    char *b = newstrdup( pBuf );
    delete[] pBuf;
    return b;
}


static void InternalDrawTransparentBitmap( HPS hps, HPS hpsDraw, PPOINTL drawptl,
                                           PBITMAPINFOHEADER pbmih )
{
    int             blen, hlen;
    PUCHAR          buf;
    PBITMAPINFO2    pbmi;
    LONG            color, transColor;

    hlen = sizeof( BITMAPINFO2 ) + sizeof( RGB ) * 256;
    blen = ( ( pbmih->cBitCount * pbmih->cx + 31 ) / 32 ) * pbmih->cPlanes * 4;

    pbmi = (PBITMAPINFO2)malloc( hlen );
    memset( pbmi, 0, hlen );
    buf = (PUCHAR)malloc( blen );
    memset( buf, 0, blen );

    pbmi->cbFix = 16;
    pbmi->cPlanes = pbmih->cPlanes;
    pbmi->cBitCount = pbmih->cBitCount;

    POINTL ptl = { 0, 0 };
    int x, y, k;
    BOOL first = TRUE;
    for ( y = 0; y < pbmih->cy; y++ )
    {
        GpiQueryBitmapBits( hps, y, 1, (PBYTE)buf, pbmi );

        for ( x = 0; x < pbmih->cx; x++ )
        {
            k = x * 3;
            color = ((buf[k]) | (buf[k+1] << 8) | (buf[k+2] << 16));
            if ( first )
            {
                transColor = color;
                first = FALSE;
            }
            else
            {
                if ( color != transColor )
                {
                    ptl.x = x + drawptl->x;
                    ptl.y = y + drawptl->y;
                    GpiSetColor( hpsDraw, color );
                    GpiSetPel( hpsDraw, &ptl );
                }
            }
        }
    }

    free( pbmi );
    free( buf );
}

BOOL DrawTransparentBitmap( HAB hab, HPS hpsDraw, PPOINTL drawptl, HBITMAP hbmp )
{
    HDC               hdc;
    HPS               hps;
    SIZEL             siz;
    BITMAPINFOHEADER  bmi;
    HBITMAP           hbm, hbmPre;

    if ( hbmp == NULLHANDLE ) {
        return FALSE;
    }

    hdc = DevOpenDC( hab, OD_MEMORY, "*", 0L, NULL, NULLHANDLE );
    if ( hdc == NULLHANDLE ) {
        return FALSE;
    }
    siz.cx = siz.cy = 0;
    hps = GpiCreatePS( hab, hdc, &siz, PU_PELS | GPIF_DEFAULT | GPIT_MICRO | GPIA_ASSOC );
    if ( hps == NULLHANDLE ) {
        DevCloseDC( hdc );
        return FALSE;
    }

    BITMAPINFOHEADER b = { 0 };
    GpiQueryBitmapParameters( hbmp, &b );

    if ( ( b.cx == 0 ) || ( b.cy == 0 ) )
    {
        GpiDestroyPS( hps );
        DevCloseDC( hdc );
        return FALSE;
    }

    bmi.cbFix     = sizeof( BITMAPINFOHEADER );
    bmi.cx        = b.cx;
    bmi.cy        = b.cy;
    bmi.cPlanes   = 1;
    bmi.cBitCount = 24;

    hbm = GpiCreateBitmap( hps, (PBITMAPINFOHEADER2)&bmi, 0, NULL, NULL );
    if ( hbm == NULLHANDLE ) {
        GpiDestroyPS( hps );
        DevCloseDC( hdc );
        return FALSE;
    }

    hbmPre = GpiSetBitmap( hps, hbm );

    POINTL ptl = { 0, 0 };
    WinDrawBitmap( hps, hbmp, NULL, &ptl, 0, 0, DBM_NORMAL );

    GpiCreateLogColorTable( hpsDraw, 0, LCOLF_RGB, 0, 0, NULL );
    InternalDrawTransparentBitmap( hps, hpsDraw, drawptl, &bmi );

    GpiSetBitmap( hps, hbmPre );
    GpiDeleteBitmap( hbm );
    GpiDestroyPS( hps );
    DevCloseDC( hdc );
    return TRUE;
}

static LONG getBmpClr( HPS hps, PBITMAPINFOHEADER2 pbmih2 )
{
    int             blen, hlen;
    PUCHAR          buf;
    PBITMAPINFO2    pbmi;
    LONG            color;

    hlen = sizeof( BITMAPINFO2 ) + sizeof( RGB ) * 256;
    blen = ( ( pbmih2->cBitCount * pbmih2->cx + 31 ) / 32 ) * pbmih2->cPlanes * 4;

    pbmi = (PBITMAPINFO2)malloc( hlen );
    memset( pbmi, 0, hlen );
    buf = (PUCHAR)malloc( blen );
    memset( buf, 0, blen );

    pbmi->cbFix = 16;
    pbmi->cPlanes = pbmih2->cPlanes;
    pbmi->cBitCount = pbmih2->cBitCount;

    LONG r = GpiQueryBitmapBits( hps, 0, 1, (PBYTE)buf, pbmi );

    if ( r < 0 ) {
        color = -1;
    } else {
        color = ( (buf[0] << 16) | (buf[1] << 8) | buf[2] );
    }

    free( pbmi );
    free( buf );

    return color;
}

static LONG getBitmapColor( HAB hab, HBITMAP hbmp )
{
    HDC               hdc;
    HPS               hps;
    SIZEL             siz;
    BITMAPINFOHEADER2 bmi;
    HBITMAP           hbm, hbmPre;
    LONG              color;

    if ( hbmp == NULLHANDLE ) {
        return -1;
    }

    hdc = DevOpenDC( hab, OD_MEMORY, "*", 0L, NULL, NULLHANDLE );
    if ( hdc == NULLHANDLE ) {
        return -1;
    }
    siz.cx = siz.cy = 0;
    hps = GpiCreatePS( hab, hdc, &siz, PU_PELS | GPIF_DEFAULT | GPIT_MICRO | GPIA_ASSOC );
    if ( hps == NULLHANDLE ) {
        DevCloseDC( hdc );
        return -1;
    }

    BITMAPINFOHEADER b = { 0 };
    GpiQueryBitmapParameters( hbmp, &b );

    if ( ( b.cx == 0 ) || ( b.cy == 0 ) ) {
        GpiDestroyPS( hps );
        DevCloseDC( hdc );
        return -1;
    }

    bmi.cbFix = sizeof( BITMAPINFOHEADER2 );
    bmi.cx            = b.cx;
    bmi.cy            = b.cy;
    bmi.cPlanes       = 1;
    bmi.cBitCount     = 24;
    bmi.ulCompression = 0;
    bmi.cclrUsed      = 0;
    bmi.cclrImportant = 0;

    hbm = GpiCreateBitmap( hps, &bmi, 0, NULL, NULL );
    if ( hbm == NULLHANDLE ) {
        GpiDestroyPS( hps );
        DevCloseDC( hdc );
        return -1;
    }

    hbmPre = GpiSetBitmap( hps, hbm );

    POINTL ptl = { 0, 0 };
    WinDrawBitmap( hps, hbmp, NULL, &ptl, 0, 0, DBM_NORMAL );

    color = getBmpClr( hps, &bmi );

    GpiSetBitmap( hps, hbmPre );
    GpiDeleteBitmap( hbm );
    GpiDestroyPS( hps );
    DevCloseDC( hdc );
    return color;
}

#define ITYPE_PUSHBUTTON    1
#define ITYPE_SEPARATOR     2
#define ITYPE_CONTROL       3

#define TOOLBAR_XINDENT 4
#define TOOLBAR_YINDENT 4
#define TOOLBAR_SSIZE   2


struct twsItem
{
    BYTE    type;
    BOOL    checked;
    BOOL    enabled;
    USHORT  cmd;
    char    *bText;
    HBITMAP hbmp;
    LONG    tcolor;
    RECTL   rcl;
    HWND    bubble;
    HWND    hmenu;
    t_timer *tmr;
    // if control
    HWND  ctrlHandle;

    twsItem *next;
    twsItem();
    ~twsItem();
};

twsItem::twsItem()
{
    type    = ITYPE_PUSHBUTTON;
    checked = FALSE;
    enabled = TRUE;
    cmd     = 0;
    bText   = NULL;
    hbmp    = NULLHANDLE;
    tcolor  = -1;
    bubble  = NULLHANDLE;
    hmenu   = NULLHANDLE;
    tmr     = NULL;
    next    = NULL;
    ctrlHandle = NULLHANDLE;
}

twsItem::~twsItem()
{
    if ( hbmp != NULLHANDLE ) {
        GpiDeleteBitmap( hbmp );
    }
    if ( bText != NULL ) {
        delete bText;
    }
    if ( tmr != NULL ) {
        delete tmr;
    }
    if ( ctrlHandle != NULLHANDLE ) {
        WinDestroyWindow( ctrlHandle );
    }
}


class toolbarWndStruct
{
    private:
        ULONG size;
        twsItem *pitem;
    public:
        BOOL bPressed;
        HAB  hab;
        BOOL mshowed;
        USHORT pictSize;

        toolbarWndStruct();
        ~toolbarWndStruct();
        twsItem *get( ULONG i );
        VOID add( HWND hwnd, BYTE type, void *s );
        ULONG getSize() const  {  return size;  }
        BOOL queryCheck( USHORT cmd );
        VOID setCheck( USHORT cmd, BOOL chk );
        VOID enableItem( USHORT cmd, BOOL en );
        VOID setBubbleText( USHORT cmd, PCSZ text );
};

toolbarWndStruct::toolbarWndStruct()
{
    bPressed = FALSE;
    hab = NULLHANDLE;
    size = 0;
    mshowed = FALSE;
    pictSize = DEFAULT_PICTSIZE;
    pitem = new twsItem;
}

toolbarWndStruct::~toolbarWndStruct()
{
    twsItem *t = pitem;
    for ( ULONG j = 0; j < size; j++ ) {
        twsItem *tmp = t->next;
        delete t;
        t = tmp;
    }
    delete t;
}

twsItem *toolbarWndStruct::get( ULONG i )
{
    twsItem *t = pitem;
    for ( ULONG j = 0; j < i; j++ ) {
        twsItem *tmp = t->next;
        t = tmp;
    }
    return t;
}

BOOL toolbarWndStruct::queryCheck( USHORT cmd )
{
    BOOL rval = FALSE;
    for ( ULONG i = 0; i < size; i++ )
    {
        twsItem *ti = get( i );
        if ( ti->cmd == cmd ) {
            rval = ti->checked;
            break;
        }
    }
    return rval;
}

VOID toolbarWndStruct::setCheck( USHORT cmd, BOOL chk )
{
    for ( ULONG i = 0; i < size; i++ )
    {
        twsItem *ti = get( i );
        if ( ti->cmd == cmd ) {
            ti->checked = chk;
            break;
        }
    }
}

VOID toolbarWndStruct::enableItem( USHORT cmd, BOOL en )
{
    for ( ULONG i = 0; i < size; i++ )
    {
        twsItem *ti = get( i );
        if ( ti->cmd == cmd )
        {
            ti->enabled = en;

            // Если кнопка запрещается, удалить всплывающую
            // подсказку и таймер
            if ( !en )
            {
                if ( ti->bubble != NULLHANDLE ) {
                    WinDestroyWindow( ti->bubble );
                    ti->bubble = NULLHANDLE;
                }
                if ( ti->tmr != NULL ) {
                    delete ti->tmr;
                    ti->tmr = NULL;
                }
            }

            break;
        }
    }
}

VOID toolbarWndStruct::add( HWND hwnd, BYTE type, void *s )
{
    AddBtnStruct *bs = (AddBtnStruct *)s;
    AddCtrlStruct *cs = (AddCtrlStruct *)s;

    twsItem *i = get( size );

    i->type = type;
    switch ( type )
    {
        case ITYPE_PUSHBUTTON:
            i->cmd  = bs->cmd;
            i->checked = bs->checked;
            i->enabled = bs->enabled;
            break;

        case ITYPE_SEPARATOR:
            i->cmd  = 0;
            i->checked = FALSE;
            i->enabled = FALSE;
            break;

        case ITYPE_CONTROL:
            i->cmd  = 0;
            i->checked = FALSE;
            i->enabled = TRUE;
            i->ctrlHandle = cs->ctrlHandle;
            break;
    }

    i->next = new twsItem;
    if ( size == 0 )
    {
        i->rcl.xLeft   = TOOLBAR_XINDENT * 2;
        i->rcl.yBottom = TOOLBAR_YINDENT;
    }
    else
    {
        twsItem *tmp = get( size - 1 );
        i->rcl.xLeft = tmp->rcl.xRight + ( TOOLBAR_XINDENT * 2 );
        i->rcl.yBottom = TOOLBAR_YINDENT; //tmp->rcl.yBottom;
    }

    i->rcl.yTop = i->rcl.yBottom + pictSize - 1;
    if ( i->type == ITYPE_SEPARATOR ) {
        i->rcl.xRight = i->rcl.xLeft + TOOLBAR_SSIZE - 1;
    } else if ( i->type == ITYPE_CONTROL ) {
        i->rcl.xRight = i->rcl.xLeft + cs->cx - 1;
        //if ( cs->cy < 0 ) {
            //i->rcl.yTop = i->rcl.yBottom + cs->cy - 1;
            i->rcl.yBottom += cs->cy;
        //}
        WinSetWindowPos( i->ctrlHandle, HWND_TOP,
                         i->rcl.xLeft, i->rcl.yBottom,
                         i->rcl.xRight-i->rcl.xLeft, i->rcl.yTop-i->rcl.yBottom + 1,
                         SWP_SIZE|SWP_MOVE|SWP_ZORDER|SWP_SHOW );
    } else {
        i->rcl.xRight = i->rcl.xLeft + pictSize - 1;
    }

    size++;

    if ( i->type == ITYPE_PUSHBUTTON )
    {
        if ( bs->bubbleText != NULL ) {
            i->bText = newstrdup( bs->bubbleText );
        } else if ( bs->bubbleRes != 0 ) {
            i->bText = newstrdup( WinQueryAnchorBlock( hwnd ),
                                  bs->bubbleRes, bs->bubbleHmod );
        }

        if ( bs->pictRes != 0 )
        {
            HPS hps = WinGetPS( hwnd );
            i->hbmp = GpiLoadBitmap( hps, bs->pictHmod, bs->pictRes, 0, 0 );
            WinReleasePS( hps );

            i->tcolor = getBitmapColor( hab, i->hbmp );
        }

        if ( bs->menuRes != 0 ) {
            i->hmenu = WinLoadMenu( hwnd, bs->menuHmod, bs->menuRes );
        }
    }

    if ( i->type == ITYPE_CONTROL )
    {
        if ( cs->bubbleText != NULL ) {
            i->bText = newstrdup( cs->bubbleText );
        } else if ( bs->bubbleRes != 0 ) {
            i->bText = newstrdup( WinQueryAnchorBlock( hwnd ),
                                  cs->bubbleRes, cs->bubbleHmod );
        }
    }
}

VOID toolbarWndStruct::setBubbleText( USHORT cmd, PCSZ text )
{
    for ( ULONG i = 0; i < size; i++ )
    {
        twsItem *ti = get( i );
        if ( ti->cmd == cmd )
        {
            if ( ti->bText != NULL ) {
                delete ti->bText;
                ti->bText = NULL;
            }

            if ( text != NULL ) {
                ti->bText = newstrdup( text );
            }

            break;
        }
    }
}

static VOID drFr( HPS hps, PRECTL prcl, BOOL framed, BOOL pressed )
{
    POINTL ptl;
    if ( framed )
    {
        GpiSetColor( hps, pressed ? SYSCLR_BUTTONDARK : SYSCLR_BUTTONLIGHT );
        ptl.x = prcl->xLeft - 2;
        ptl.y = prcl->yBottom - 2;
        GpiMove( hps, &ptl );
        ptl.y = prcl->yTop + 2;
        GpiLine( hps, &ptl );
        ptl.x = prcl->xRight + 2;
        GpiLine( hps, &ptl );
        GpiSetColor( hps, pressed ? SYSCLR_BUTTONLIGHT : SYSCLR_BUTTONDARK );
        ptl.y = prcl->yBottom - 2;
        GpiLine( hps, &ptl );
        ptl.x = prcl->xLeft - 2;
        GpiLine( hps, &ptl );
    }
    else
    {
        GpiSetColor( hps, SYSCLR_MENU );
        ptl.x = prcl->xLeft - 2;
        ptl.y = prcl->yBottom - 2;
        GpiMove( hps, &ptl );
        ptl.x = prcl->xRight + 2;
        ptl.y = prcl->yTop + 2;
        GpiBox( hps, DRO_OUTLINE, &ptl, 0, 0 );
    }
}

static VOID htDraw( HPS hps, PRECTL r, BOOL halfTone )
{
    POINTL ptl;
    LONG i, j;
    GpiSetColor( hps, halfTone ? SYSCLR_MENU : CLR_WHITE );
    for ( i = 0; i <= ( r->xRight - r->xLeft ); i++ )
    {
        ptl.x = i + r->xLeft;
        for ( j = 0; j <= ( r->yTop - r->yBottom ); j++ )
        {
            ptl.y = j + r->yBottom;
            if ( !( j & 1 ) )
            {
                if ( i & 1 ) {
                    ptl.y++;
                }
                GpiSetPel( hps, &ptl );
            }
        }
    }
}

static VOID btnDraw( HAB hab, HPS hps, twsItem *ti, USHORT pictSize )
{
    BOOL useSafeDraw = ( getenv( "ERTOOLBARSAFEDRAW" ) != NULL );

    LONG ltabl[ 1 ] = { ti->tcolor };

    if ( !useSafeDraw )
    {
        GpiCreateLogColorTable( hps, 0, LCOLF_CONSECRGB, 100, 1, ltabl );
        GpiSetBackMix( hps, BM_SRCTRANSPARENT );
        GpiSetBackColor( hps, 100 );
    }

    if ( ti->checked )
    {
        RECTL rcl = { ti->rcl.xLeft - 1, ti->rcl.yBottom - 1,
                      ti->rcl.xRight + 1, ti->rcl.yTop + 1 };
        htDraw( hps, &rcl, FALSE );
    }
    POINTL aptl[ 4 ] = { { ti->rcl.xLeft, ti->rcl.yBottom },
                         { ti->rcl.xRight, ti->rcl.yTop },
                         { 0, 0 }, { pictSize, pictSize } };
    if ( useSafeDraw ) {
        DrawTransparentBitmap( hab, hps, &aptl[ 0 ], ti->hbmp );
    } else {
        GpiWCBitBlt( hps, ti->hbmp, 4L, aptl, ROP_SRCCOPY, BBO_IGNORE );
    }

    if ( !ti->enabled ) {
        htDraw( hps, &ti->rcl, TRUE );
    }
    if ( ti->checked ) {
        drFr( hps, &ti->rcl, TRUE, TRUE );
    }
}

static VOID sepDraw( HPS hps, twsItem *ti )
{
    POINTL ptl = { ti->rcl.xLeft, ti->rcl.yBottom };
    GpiMove( hps, &ptl );
    GpiSetColor( hps, SYSCLR_BUTTONDARK );
    ptl.y = ti->rcl.yTop;
    GpiLine( hps, &ptl );
    ptl.x++;
    GpiMove( hps, &ptl );
    ptl.y = ti->rcl.yBottom;
    GpiSetColor( hps, SYSCLR_BUTTONLIGHT );
    GpiLine( hps, &ptl );
}

static VOID drawFramed( HWND hwnd, PRECTL prcl, BOOL framed, BOOL pressed )
{
    HPS hps = WinGetPS( hwnd );
    drFr( hps, prcl, framed, pressed );
    WinReleasePS( hps );
}


static CHAR ppFont[]     = "8.Helv";
static ULONG ulBackColor = 0x00ffffe4;  //RGB_RED;
static ULONG ulForeColor = RGB_BLACK;

static VOID wrkMouseMove( HAB hab, HWND hwnd, MPARAM mp1, twsItem *ti )
{
    if ( ti->type == ITYPE_SEPARATOR ) {
        return;
    }
    if ( !ti->enabled ) {
        return;
    }

    POINTL ptl = { SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ) };
    if ( WinPtInRect( hab, &ti->rcl, &ptl ) )
    {
        if ( ti->type == ITYPE_PUSHBUTTON ) {
            drawFramed( hwnd, &ti->rcl, TRUE, FALSE );
        }

        if ( !( WinQueryWindowUShort( WinQueryWindow( hwnd, QW_PARENT ),
                                      QWS_FLAGS ) & FF_ACTIVE ) ) {
            return;
        }

        if ( ti->bText == NULL ) {
            return;
        }

        if ( ti->bubble == NULLHANDLE )
        {
            if ( ti->tmr == NULL ) {
                ti->tmr = new t_timer;
            }
            else
            {
                if ( ti->tmr->elapsed() > 500 )
                {
                    delete ti->tmr;
                    ti->tmr = NULL;
                    HPS hpsTemp;
                    HWND hwndBC;
                    ULONG ulStyle = FCF_BORDER | FCF_NOBYTEALIGN;
                    LONG  lWidth,lHight;
                    POINTL txtPointl[ TXTBOX_COUNT ];
                    POINTL ptlWork;
                    ptlWork.x = ti->rcl.xLeft + ( ( ti->rcl.xRight - ti->rcl.xLeft ) / 2 );
                    ptlWork.y = ti->rcl.yBottom;
                    ti->bubble = WinCreateStdWindow( HWND_DESKTOP, 0,
                                       &ulStyle, WC_STATIC, "",
                                       SS_TEXT | DT_CENTER |  DT_VCENTER,
                                       NULLHANDLE, 2, &hwndBC );
                    WinSetPresParam( hwndBC, PP_FONTNAMESIZE, sizeof( ppFont ), ppFont );
                    WinSetPresParam( hwndBC, PP_BACKGROUNDCOLOR, sizeof( ulBackColor ), &ulBackColor );
                    WinSetPresParam( hwndBC, PP_FOREGROUNDCOLOR, sizeof( ulForeColor ), &ulForeColor );

                    hpsTemp = WinGetPS( hwndBC );

                    GpiQueryTextBox( hpsTemp, strlen( ti->bText ),
                                     ti->bText, TXTBOX_COUNT,
                                     (PPOINTL)&txtPointl[ 0 ] );
                    WinReleasePS( hpsTemp );

                    WinSetWindowText( hwndBC, ti->bText );

                    lWidth = txtPointl[ TXTBOX_TOPRIGHT ].x -
                             txtPointl[ TXTBOX_TOPLEFT ].x + 6;

                    lHight = txtPointl[TXTBOX_TOPLEFT   ].y -
                             txtPointl[TXTBOX_BOTTOMLEFT].y + 4;

                    WinMapWindowPoints( hwnd, HWND_DESKTOP, &ptlWork, 1 );

                    if( ( ptlWork.y - ( lHight + 5 ) ) < 0 ) {
                        ptlWork.y = 1;
                    } else {
                        ptlWork.y -= ( lHight + 5 );
                    }

                    if ( ( ptlWork.x + lWidth ) >= WinQuerySysValue( HWND_DESKTOP, SV_CXFULLSCREEN ) ) {
                        ptlWork.x = WinQuerySysValue( HWND_DESKTOP, SV_CXFULLSCREEN )
                                        - lWidth - 1;
                    }

                    WinSetWindowPos( ti->bubble, HWND_TOP, ptlWork.x,
                                     ptlWork.y, lWidth, lHight,
                                     SWP_SHOW | SWP_MOVE | SWP_SIZE );
                }
            }
        }
    }
    else
    {
        if ( ti->checked ) {
            drawFramed( hwnd, &ti->rcl, TRUE, TRUE );
        } else {
            drawFramed( hwnd, &ti->rcl, FALSE, FALSE );
        }
        if ( ti->bubble != NULLHANDLE ) {
            WinDestroyWindow( ti->bubble );
            ti->bubble = NULLHANDLE;
        }
        if ( ti->tmr != NULL ) {
            delete ti->tmr;
            ti->tmr = NULL;
        }
    }
}


static VOID wrkMouseDown( HAB hab, HWND hwnd, MPARAM mp1, twsItem *ti,
                          BOOL up, BOOL *inPtl )
{
    if ( ti->type != ITYPE_PUSHBUTTON ) {
        return;
    }
    if ( !ti->enabled ) {
        return;
    }

    POINTL ptl = { SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ) };
    if ( WinPtInRect( hab, &ti->rcl, &ptl ) )
    {
        drawFramed( hwnd, &ti->rcl, TRUE, !up );
        if ( up )
        {
            WinSendMsg( WinQueryWindow( hwnd, QW_PARENT ), WM_COMMAND,
                        MPFROMSHORT( ti->cmd ),
                        MPFROM2SHORT( CMDSRC_OTHER, TRUE ) );
        }
        *inPtl = TRUE;
    }
}

static VOID showPopup( toolbarWndStruct *tws, HWND hwnd, MPARAM mp1, twsItem *ti )
{
    if ( ti->type != ITYPE_PUSHBUTTON ) {
        return;
    }
    if ( !ti->enabled ) {
        return;
    }
    if ( ti->hmenu == NULLHANDLE ) {
        return;
    }
    if ( tws->mshowed ) {
        return;
    }

    POINTL ptl = { SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ) };
    if ( WinPtInRect( tws->hab, &ti->rcl, &ptl ) )
    {
        tws->mshowed = TRUE;
        USHORT id = SHORT1FROMMR( WinSendMsg( ti->hmenu, MM_ITEMIDFROMPOSITION,
                                              MPFROMSHORT( 0 ), MPVOID ) );
        WinPopupMenu( hwnd, WinQueryWindow( hwnd, QW_PARENT ),
                      ti->hmenu, ptl.x, ptl.y, id,
                      PU_POSITIONONITEM | PU_MOUSEBUTTON1DOWN | PU_MOUSEBUTTON1 );
    }
}

static int sss = 0;

static MRESULT EXPENTRY toolbarProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    toolbarWndStruct *tws = (toolbarWndStruct *)WinQueryWindowULong( hwnd, sizeof( ULONG ) );
    if ( tws == NULL )
    {
        tws = new toolbarWndStruct;
        tws->hab = WinQueryAnchorBlock( hwnd );
        WinSetWindowULong( hwnd, sizeof( ULONG ), (ULONG)tws );
        WinStartTimer( tws->hab, hwnd, 2, 500 );
    }

    switch ( msg )
    {
        case TBM_ADDBUTTON:
            tws->add( hwnd, ITYPE_PUSHBUTTON, mp1 );
            return (MRESULT)(TRUE);

        case TBM_ADDSEPARATOR:
            tws->add( hwnd, ITYPE_SEPARATOR, NULL );
            return (MRESULT)(TRUE);

        case TBM_ADDCONTROL:
            tws->add( hwnd, ITYPE_CONTROL, mp1 );
            return (MRESULT)(TRUE);

        case TBM_QUERYCHECK:
            return (MRESULT)tws->queryCheck( SHORT1FROMMP( mp1 ) );

        case TBM_SETCHECK:
            tws->setCheck( SHORT1FROMMP( mp1 ), (BOOL)mp2 );
            WinInvalidateRect( hwnd, NULL, TRUE );
            return (MRESULT)(TRUE);

        case TBM_ENABLEITEM:
            tws->enableItem( SHORT1FROMMP( mp1 ), (BOOL)mp2 );
            WinInvalidateRect( hwnd, NULL, TRUE );
            return (MRESULT)(TRUE);

        case TBM_SETBUBBLETEXT:
            tws->setBubbleText( SHORT1FROMMP( mp1 ), (PCSZ)mp2 );
            return (MRESULT)(TRUE);

        case TBM_SETPICTSIZE:
            tws->pictSize = SHORT1FROMMP( mp1 );
            return (MRESULT)(TRUE);

        case WM_DESTROY:
            delete tws;
            break;

        case WM_PAINT:
            {
                RECTL rcl;
                POINTL ptl;
                HPS hps = WinBeginPaint( hwnd, NULLHANDLE, NULL );
                WinQueryWindowRect( hwnd, &rcl );
                rcl.yTop = tws->pictSize + TOOLBAR_HEIGHT_ADD;
                rcl.yBottom++;
                WinFillRect( hps, &rcl, SYSCLR_MENU );
                ptl.x = rcl.xLeft;
                ptl.y = rcl.yBottom - 1;
                GpiMove( hps, &ptl );
                ptl.x = rcl.xRight;
                GpiSetColor( hps, SYSCLR_BUTTONDARK );
                GpiLine( hps, &ptl );

                for ( ULONG i = 0; i < tws->getSize(); i++ )
                {
                    twsItem *ti = tws->get( i );
                    switch ( ti->type )
                    {
                        case ITYPE_PUSHBUTTON:
                            btnDraw( tws->hab, hps, ti, tws->pictSize );
                            break;

                        case ITYPE_SEPARATOR:
                            sepDraw( hps, ti );
                            break;
                    }
                }
                WinEndPaint( hps );
            }
            return (MRESULT)(FALSE);

        case WM_MOUSEMOVE:
            {
                for ( ULONG i = 0; i < tws->getSize(); i++ ) {
                    twsItem *ti = tws->get( i );
                    wrkMouseMove( tws->hab, hwnd, mp1, ti );
                }
            }
            break;

        case WM_BUTTON1DOWN:
            {
                BOOL inPtl = FALSE;
                tws->bPressed = TRUE;
                tws->mshowed = FALSE;
                WinStartTimer( tws->hab, hwnd, 3, 500 );
                for ( ULONG i = 0; i < tws->getSize(); i++ ) {
                    twsItem *ti = tws->get( i );
                    wrkMouseDown( tws->hab, hwnd, mp1, ti, FALSE, &inPtl );
                }
                if ( !inPtl ) {
                    WinSetActiveWindow( HWND_DESKTOP, hwnd );
                }
            }
            return (MRESULT)(FALSE);

        case WM_BUTTON1UP:
            {
                BOOL inPtl = FALSE;
                WinStopTimer( tws->hab, hwnd, 3 );
                tws->bPressed = FALSE;
                tws->mshowed = FALSE;
                for ( ULONG i = 0; i < tws->getSize(); i++ ) {
                    twsItem *ti = tws->get( i );
                    wrkMouseDown( tws->hab, hwnd, mp1, ti, TRUE, &inPtl );
                }
            }
            break;

        case WM_TIMER:
            {
                switch ( SHORT1FROMMP( mp1 ) )
                {
                    case 2:
                    {
                        if ( !tws->bPressed )
                        {
                            POINTL ptl;
                            WinQueryPointerPos( HWND_DESKTOP, &ptl );
                            WinMapWindowPoints( HWND_DESKTOP, hwnd, &ptl, 1 );
                            MPARAM mp = MPFROM2SHORT( ptl.x, ptl.y );
                            for ( ULONG i = 0; i < tws->getSize(); i++ ) {
                                twsItem *ti = tws->get( i );
                                wrkMouseMove( tws->hab, hwnd, mp, ti );
                            }
                        }
                        break;
                    }

                    case 3:
                    {
                        if ( tws->bPressed )
                        {
                            POINTL ptl;
                            WinQueryPointerPos( HWND_DESKTOP, &ptl );
                            WinMapWindowPoints( HWND_DESKTOP, hwnd, &ptl, 1 );
                            MPARAM mp = MPFROM2SHORT( ptl.x, ptl.y );
                            for ( ULONG i = 0; i < tws->getSize(); i++ ) {
                                twsItem *ti = tws->get( i );
                                showPopup( tws, hwnd, mp, ti );
                            }
                        }
                        break;
                    }
                }
            }
            return (MRESULT)(FALSE);

        case WM_ERASEBACKGROUND:
            return (MRESULT)(FALSE);
    }
    return WinDefWindowProc( hwnd, msg, mp1, mp2 );
}


BOOL InitPMToolbarClass( HAB hab )
{
    return WinRegisterClass( hab, WC_ER_TOOLBAR, toolbarProc,
                             CS_SIZEREDRAW, sizeof( ULONG ) * 2 );
}

