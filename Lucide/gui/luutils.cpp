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

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>

#if defined(__WATCOM__)
#include <strstrea.h>
#else
#include <sstream>
#include <algorithm>
#endif

#include "luutils.h"
#include "messages.h"

static bool initCountryInfo();

static COUNTRYINFO CtryInfo;
static bool countryInfoLoaded = initCountryInfo();


afbuf::afbuf( unsigned int s )
{
    size = s;
    buffer = new char[ s ];
    memset( buffer, 0, s );
}


BOOL CreateGraphicsBuffer( HAB hab, PRECTL prectl, HPS hps,
                           HPS *phpsBuffer, HDC *phdcBuffer )
{
    LONG cPlanes;
    LONG cBitCount;
    ULONG ulFlags;
    HBITMAP hbm;
    BITMAPINFOHEADER bmp;
    SIZEL sizl;
    FONTMETRICS fm;
    FATTRS fat;
    SIZEF sizf;
    HPS hpsBuffer;
    HDC hdc, hdcBuffer;
    hdc = GpiQueryDevice( hps );
    ulFlags = GpiQueryPS( hps, &sizl );

    hdcBuffer = DevOpenDC( hab, OD_MEMORY, "*",  0L, NULL, hdc );
    if ( hdcBuffer )
    {
        sizl.cx = sizl.cy = 0;

        hpsBuffer = GpiCreatePS( hab, hdcBuffer, &sizl, ulFlags | GPIA_ASSOC );

        *phpsBuffer = hpsBuffer;
        *phdcBuffer = hdcBuffer;

        DevQueryCaps( hdc, CAPS_COLOR_PLANES, 1L, &cPlanes );
        DevQueryCaps( hdc, CAPS_COLOR_BITCOUNT, 1L, &cBitCount );

        bmp.cbFix     = sizeof( BITMAPINFOHEADER );
        bmp.cx        = (SHORT)( prectl->xRight - prectl->xLeft );
        bmp.cy        = (SHORT)( prectl->yTop - prectl->yBottom );
        bmp.cPlanes   = (SHORT)cPlanes;
        bmp.cBitCount = (SHORT)cBitCount;

        hbm = GpiCreateBitmap( hpsBuffer, (PBITMAPINFOHEADER2)&bmp,
                               0x0000, NULL, NULL );
        if ( hbm )
        {
            GpiSetBitmap( hpsBuffer, hbm );
            GpiQueryFontMetrics( hps, sizeof( FONTMETRICS ), &fm );

            memset( &fat, 0, sizeof( fat ) );

            fat.usRecordLength = sizeof( FATTRS );
            fat.lMatch = fm.lMatch;
            strcpy( fat.szFacename, fm.szFacename );

            GpiDeleteSetId( hpsBuffer, 1L );
            GpiCreateLogFont( hpsBuffer, 0, 1L, &fat );
            GpiSetCharSet( hpsBuffer, 1L );

            sizf.cx = MAKEFIXED( fm.lEmInc, 0 );
            sizf.cy = MAKEFIXED( fm.lMaxBaselineExt, 0 );
            GpiSetCharBox( hpsBuffer, &sizf );

            return TRUE;
        }

        GpiDestroyPS( hpsBuffer );
        DevCloseDC( hdcBuffer );
        hpsBuffer = hdcBuffer = NULLHANDLE;
    }

    return FALSE;
}

void BlitGraphicsBuffer( HPS hps, HPS hpsBuffer, PRECTL prclPaint )
{
    POINTL aptl[ 3 ];

    aptl[ 0 ].x = prclPaint->xLeft;
    aptl[ 0 ].y = prclPaint->yBottom;
    aptl[ 1 ].x = prclPaint->xRight;
    aptl[ 1 ].y = prclPaint->yTop;
    aptl[ 2 ].x = prclPaint->xLeft;
    aptl[ 2 ].y = prclPaint->yBottom;

    GpiBitBlt( hps, hpsBuffer, 3L, aptl, ROP_SRCCOPY, BBO_IGNORE );
}

void DestroyGraphicsBuffer( HPS hpsBuffer, HDC hdcBuffer )
{
    if( hpsBuffer && hdcBuffer )
    {
        HBITMAP hbm = GpiSetBitmap( hpsBuffer, NULLHANDLE );

        if ( hbm != NULLHANDLE ) {
            GpiDeleteBitmap( hbm );
        }

        GpiDestroyPS( hpsBuffer );
        DevCloseDC( hdcBuffer );

        hpsBuffer = hdcBuffer = NULLHANDLE;
    }
}


char *newstrdup( const char *s )
{
    if ( s == NULL ) {
        return NULL;
    }
    char *temp = new char[ strlen( s ) + 1 ];
    strcpy( temp, s );
    return temp;
}


struct ER_WINDOW_POS
{
    SWP    Swp;
    USHORT XRestore;
    USHORT YRestore;
    USHORT CXRestore;
    USHORT CYRestore;
    USHORT XMinimize;
    USHORT YMinimize;
};


BOOL PMRestoreWindowPos( PCSZ pIniName, PCSZ pAppName, PCSZ pKeyName,
                         HWND hwnd, BOOL activate, BOOL chkCoord,
                         BOOL min, BOOL max, BOOL hide )
{
    HINI          hini;
    ER_WINDOW_POS wp;
    ULONG         ulWpSize = sizeof( ER_WINDOW_POS );
    ULONG         SwpOptions = SWP_MOVE | SWP_SIZE | SWP_SHOW;
    BOOL          rval = FALSE;

    if ( activate && !hide ) {
        SwpOptions |= SWP_ACTIVATE;
    }

    if ( pIniName == NULL ) { // ��襬 � user profile
        hini = HINI_USER;
    }
    else {
        hini = PrfOpenProfile( WinQueryAnchorBlock( hwnd ), pIniName );
    }

    if ( hini != NULLHANDLE )
    {
        if ( PrfQueryProfileData( hini, pAppName, pKeyName, &wp, &ulWpSize ) )
        {
            if ( wp.Swp.fl & SWP_MAXIMIZE ) {
                SwpOptions |= SWP_MAXIMIZE;
            }
            else if ( wp.Swp.fl & SWP_MINIMIZE ) {
                SwpOptions |= SWP_MINIMIZE;
            }

            if ( min ) {
                SwpOptions &= ~SWP_MAXIMIZE;
                SwpOptions |= SWP_MINIMIZE;
            }
            if ( max ) {
                SwpOptions &= ~SWP_MINIMIZE;
                SwpOptions |= SWP_MAXIMIZE;
            }
            if ( hide ) {
                SwpOptions &= ~SWP_SHOW;
                SwpOptions |= SWP_HIDE;
            }

            if ( chkCoord )
            {
                LONG sx, sy;
                sx = WinQuerySysValue( HWND_DESKTOP, SV_CXSCREEN );
                sy = WinQuerySysValue( HWND_DESKTOP, SV_CYSCREEN );

                if ( wp.Swp.x > sx ) {
                    wp.Swp.x = sx - wp.Swp.cx;
                }
                if ( wp.Swp.y > sy ) {
                    wp.Swp.y = sy - wp.Swp.cy;
                }
            }

            WinSetWindowPos( hwnd, NULLHANDLE,
                             wp.Swp.x, wp.Swp.y, wp.Swp.cx, wp.Swp.cy,
                             SwpOptions );

            WinSetWindowUShort( hwnd, QWS_XRESTORE,  wp.XRestore );
            WinSetWindowUShort( hwnd, QWS_YRESTORE,  wp.YRestore );
            WinSetWindowUShort( hwnd, QWS_CXRESTORE, wp.CXRestore );
            WinSetWindowUShort( hwnd, QWS_CYRESTORE, wp.CYRestore );
            WinSetWindowUShort( hwnd, QWS_XMINIMIZE, wp.XMinimize );
            WinSetWindowUShort( hwnd, QWS_YMINIMIZE, wp.YMinimize );
            rval = TRUE;
        }

        if ( pIniName != NULL ) {
            PrfCloseProfile( hini );
        }
    }
    return rval;
}

void PMStoreWindowPosI( HINI ini, PCSZ pAppName, PCSZ pKeyName, HWND hwnd )
{
    ER_WINDOW_POS wp;

    WinQueryWindowPos( hwnd, &wp.Swp );
    wp.XRestore  = WinQueryWindowUShort( hwnd, QWS_XRESTORE );
    wp.YRestore  = WinQueryWindowUShort( hwnd, QWS_YRESTORE );
    wp.CXRestore = WinQueryWindowUShort( hwnd, QWS_CXRESTORE );
    wp.CYRestore = WinQueryWindowUShort( hwnd, QWS_CYRESTORE );
    wp.XMinimize = WinQueryWindowUShort( hwnd, QWS_XMINIMIZE );
    wp.YMinimize = WinQueryWindowUShort( hwnd, QWS_YMINIMIZE );

    PrfWriteProfileData( ini, pAppName, pKeyName, &wp, sizeof( wp ) );
}

BOOL PMStoreWindowPos( PCSZ pIniName, PCSZ pAppName, PCSZ pKeyName, HWND hwnd )
{
    HAB           hab = WinQueryAnchorBlock( hwnd );
    HINI          hini;
    BOOL          rval = FALSE;

    if ( pIniName == NULL )
    {
        PMStoreWindowPosI( HINI_USER, pAppName, pKeyName, hwnd );
        rval = TRUE;
    }
    else
    {
        if ( ( hini = PrfOpenProfile( hab, pIniName ) ) != NULLHANDLE )
        {
            PMStoreWindowPosI( hini, pAppName, pKeyName, hwnd );
            PrfCloseProfile( hini );
            rval = TRUE;
        }
    }
    return rval;
}


SHORT getStringPixSize( HPS hps, PCSZ str )
{
    POINTL ptl[ 3 ] = { 0 };
    GpiQueryTextBox( hps, strlen( str ), (PSZ)str, 3, ptl );
    return (SHORT)( ptl[ 2 ].x - ptl[ 0 ].x );
}


#if defined(__WATCOM__)
static void end_zeros_trim( char *s )
{
    size_t l = strlen( s );
    char *end_str = ( s + l ) - 1;

    while ( *end_str == '0' ) {
        *end_str-- = 0;
    }

    if ( *end_str == '.' ) {
        *end_str = 0;
    }
}
#endif

std::string str( double n )
{
#if defined(__WATCOM__)
    char *pt;
    char buf[ 60 ];
    memset( buf, 0, sizeof buf );

    ostrstream o( buf, sizeof buf );
    o.flags( ios::dec | ios::showpoint | ios::fixed );
    o << n;
    end_zeros_trim( buf );

    return buf;
#else
    std::basic_ostringstream< char > o;
    o.flags( std::ios::dec | std::ios::showpoint | std::ios::fixed );
    o << n;
    std::string ret = o.str();
    std::string::iterator it = ret.end();
    while ( it != ret.begin() && *--it == '0' )
        it = ret.erase(it);
    if ( *it == '.')
        ret.erase(it);
    return ret;
#endif
}


void centerWindow( HWND parent, HWND hwnd )
{
    SWP swpf;
    WinQueryWindowPos( parent, &swpf );
    SWP swp;
    WinQueryWindowPos( hwnd, &swp );
    POINTL ptl = { ( swpf.cx - swp.cx ) / 2, ( swpf.cy - swp.cy ) / 2 };
    WinMapWindowPoints( parent, HWND_DESKTOP, &ptl, 1 );
    WinSetWindowPos( hwnd, HWND_TOP, ptl.x, ptl.y, 0, 0, SWP_MOVE );
}


static bool initCountryInfo()
{
    static const char *pmnkey = "PM_National";

    memset( &CtryInfo, 0, sizeof( COUNTRYINFO ) );
    COUNTRYCODE Country   = {0};
    ULONG       ulInfoLen = 0;

    DosQueryCtryInfo( sizeof( CtryInfo ), &Country, &CtryInfo, &ulInfoLen );

    char buf[ 10 ];
    PrfQueryProfileString( HINI_USERPROFILE, pmnkey, "sDate",
                           CtryInfo.szDateSeparator, buf, sizeof( buf ) );
    CtryInfo.szDateSeparator[ 0 ] = buf[ 0 ];
    PrfQueryProfileString( HINI_USERPROFILE, pmnkey, "sTime",
                           CtryInfo.szTimeSeparator, buf, sizeof( buf ) );
    CtryInfo.szTimeSeparator[ 0 ] = buf[ 0 ];
    PrfQueryProfileString( HINI_USERPROFILE, pmnkey, "sDecimal",
                           CtryInfo.szDecimal, buf, sizeof( buf ) );
    CtryInfo.szDecimal[ 0 ] = buf[ 0 ];
    PrfQueryProfileString( HINI_USERPROFILE, pmnkey, "sThousand",
                           CtryInfo.szThousandsSeparator, buf, sizeof( buf ) );
    CtryInfo.szThousandsSeparator[ 0 ] = buf[ 0 ];
    PrfQueryProfileString( HINI_USERPROFILE, pmnkey, "sList",
                           CtryInfo.szDataSeparator, buf, sizeof( buf ) );
    CtryInfo.szDataSeparator[ 0 ] = buf[ 0 ];

    return true;
}


static const char *format01 = "%02d%s%02d%s%04d";
static const char *format23 = "%04d%s%02d%s%02d";

static void dateToStr( struct tm *tmbuf, char *buf, int buflen )
{
    switch ( CtryInfo.fsDateFmt )
    {
        case 0:
            snprintf( buf, buflen, format01,
                      tmbuf->tm_mon + 1, CtryInfo.szDateSeparator, tmbuf->tm_mday,
                      CtryInfo.szDateSeparator, tmbuf->tm_year + 1900 );
            break;
        case 1:
            snprintf( buf, buflen, format01,
                      tmbuf->tm_mday, CtryInfo.szDateSeparator, tmbuf->tm_mon + 1,
                      CtryInfo.szDateSeparator, tmbuf->tm_year + 1900 );
            break;
        case 2:
            snprintf( buf, buflen, format23,
                      tmbuf->tm_year + 1900, CtryInfo.szDateSeparator,
                      tmbuf->tm_mon + 1, CtryInfo.szDateSeparator, tmbuf->tm_mday );
            break;
        case 3:
            snprintf( buf, buflen, format23,
                      tmbuf->tm_year + 1900, CtryInfo.szDateSeparator,
                      tmbuf->tm_mday, CtryInfo.szDateSeparator, tmbuf->tm_mon + 1 );
            break;
    }
}

static const char *format0 = "%d%s%02d%s%02d %s";
static const char *format1 = "%02d%s%02d%s%02d";

static void timeToStr( struct tm *tmbuf, char *buf, int buflen )
{
    switch ( CtryInfo.fsTimeFmt )
    {
        case 0:
            snprintf( buf, buflen, format0,
                      (int)( ( tmbuf->tm_hour > 12 ) ? ( tmbuf->tm_hour - 12 ) :
                                                         tmbuf->tm_hour ),
                      CtryInfo.szTimeSeparator, (int)tmbuf->tm_min,
                      CtryInfo.szTimeSeparator, (int)tmbuf->tm_sec,
                      (char *)( ( tmbuf->tm_hour < 12 ) ? "AM" : "PM" ) );
            break;
        case 1:
            snprintf( buf, buflen, format1, tmbuf->tm_hour,
                      CtryInfo.szTimeSeparator, tmbuf->tm_min,
                      CtryInfo.szTimeSeparator, tmbuf->tm_sec );
            break;
    }
}

std::string time2string( unsigned long time )
{
    struct tm tmbuf = { 0 };
#if defined(__WATCOM__)
    _localtime( &time, &tmbuf );
#else
    time_t t = time;
    localtime_r(&t, &tmbuf );
#endif
    char datbuf[ 16 ] = "";
    char timbuf[ 16 ] = "";
    dateToStr( &tmbuf, datbuf, sizeof( datbuf ) );
    timeToStr( &tmbuf, timbuf, sizeof( timbuf ) );

    std::string s = datbuf;
    s += "  ";
    s += timbuf;

    return s;
}

SHORT setZoomValues( HWND lbox )
{
    char *actsizetext = newstrdupL( TBHINT_ACTUAL_SIZE );
    char *fitwindtext = newstrdupL( TBHINT_FIT_WINDOW );
    char *fitwidthtext = newstrdupL( TBHINT_FIT_WIDTH );
    WinSetWindowText( lbox, actsizetext );
    WinInsertLboxItem( lbox, LIT_END, actsizetext );
    WinInsertLboxItem( lbox, LIT_END, fitwindtext );
    WinInsertLboxItem( lbox, LIT_END, fitwidthtext );
    WinInsertLboxItem( lbox, LIT_END, "12.5%" );
    WinInsertLboxItem( lbox, LIT_END, "25%" );
    WinInsertLboxItem( lbox, LIT_END, "50%" );
    WinInsertLboxItem( lbox, LIT_END, "100%" );
    WinInsertLboxItem( lbox, LIT_END, "125%" );
    WinInsertLboxItem( lbox, LIT_END, "150%" );
    WinInsertLboxItem( lbox, LIT_END, "200%" );
    WinInsertLboxItem( lbox, LIT_END, "300%" );
    WinInsertLboxItem( lbox, LIT_END, "400%" );
    WinInsertLboxItem( lbox, LIT_END, "800%" );
    WinInsertLboxItem( lbox, LIT_END, "1600%" );

    HPS hps = WinGetPS( lbox );
    SHORT actsizelen = getStringPixSize( hps, actsizetext );
    SHORT fitwindlen = getStringPixSize( hps, fitwindtext );
    SHORT fitwidthlen = getStringPixSize( hps, fitwidthtext );
    WinReleasePS( hps );

    delete fitwidthtext;
    delete fitwindtext;
    delete actsizetext;

    return std::max( actsizelen, std::max( fitwindlen, fitwidthlen ) );
}

double convZoom( SHORT v )
{
    double z = -3;
    switch ( v )
    {
        case 0:   z = 1;      break;
        case 1:   z = -2;     break;
        case 2:   z = -1;     break;
        case 3:   z = 0.125;  break;
        case 4:   z = 0.25;   break;
        case 5:   z = 0.5;    break;
        case 6:   z = 1;      break;
        case 7:   z = 1.25;   break;
        case 8:   z = 1.5;    break;
        case 9:   z = 2;      break;
        case 10:  z = 3;      break;
        case 11:  z = 4;      break;
        case 12:  z = 8;      break;
        case 13:  z = 16;     break;
    }
    return z;
}

void enumCntrRecords( HWND hwndCntr, PENUMCNTRFN pFn, void *pUser )
{
    PRECORDCORE rec = (PRECORDCORE) WinSendMsg( hwndCntr, CM_QUERYRECORD,
                                                0,
                                                MPFROM2SHORT( CMA_FIRST, CMA_ITEMORDER ) );
    while ( rec != NULL && rec != (PRECORDCORE)(-1) )
    {
        if ( !pFn( hwndCntr, rec, pUser ) )
            return;
        rec = (PRECORDCORE) WinSendMsg( hwndCntr, CM_QUERYRECORD,
                                        MPFROMP( rec ),
                                        MPFROM2SHORT( CMA_NEXT, CMA_ITEMORDER ) );
    }
}

void enumCntrEmphasis( HWND hwndCntr, USHORT fEmphasisMask,
                       PENUMCNTRFN pFn, void *pUser )
{
    PRECORDCORE rec = (PRECORDCORE) WinSendMsg( hwndCntr, CM_QUERYRECORDEMPHASIS,
                                                MPFROMP( CMA_FIRST ),
                                                MPFROMSHORT( fEmphasisMask ) );
    while ( rec != NULL && rec != (PRECORDCORE)(-1) )
    {
        if ( !pFn( hwndCntr, rec, pUser ) )
            return;
        rec = (PRECORDCORE) WinSendMsg( hwndCntr, CM_QUERYRECORDEMPHASIS,
                                        MPFROMP( rec ),
                                        MPFROMSHORT( fEmphasisMask ) );
    }
}

char *getTmpDir( char *buf )
{
    char *tmpenv = getenv( "TMP" );
    strcpy( buf, ( tmpenv == NULL ) ? ".\\" : tmpenv );
    if ( buf[ strlen( buf ) - 1 ] != '\\' ) {
        strcat( buf, "\\" );
    }
    return buf;
}
