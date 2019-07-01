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
#include <mmioos2.h>

#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <algorithm>

#include <ludoc.xh>

#include "Lucide.h"
#include "luutils.h"

#define LUTHUMB_SIZE_X  256
#define LUTHUMB_SIZE_Y  256
static const char * const LUTHUMB_EA_NAME = "LUCIDE_THUMBNAIL";


static bool loadMMIOFuncs();

static HMODULE mmioHndl = NULLHANDLE;
static bool mmioFuncsLoaded = loadMMIOFuncs();

static void freeMmio()
{
    if ( mmioHndl != NULLHANDLE ) {
        DosFreeModule( mmioHndl );
    }
}

HMMIO  APIENTRY (*pMmioOpen)(PSZ,PMMIOINFO,ULONG);
LONG   APIENTRY (*pMmioWrite)(HMMIO,PCHAR,LONG);
ULONG  APIENTRY (*pMmioSetHeader)(HMMIO,PVOID,LONG,PLONG,ULONG,ULONG);
USHORT APIENTRY (*pMmioClose)(HMMIO,USHORT);
ULONG  APIENTRY (*pMmioIdentifyFile)(PSZ,PMMIOINFO,PMMFORMATINFO,PFOURCC,ULONG,ULONG);
ULONG  APIENTRY (*pMmioQueryHeaderLength)(HMMIO,PLONG,ULONG,ULONG);
ULONG  APIENTRY (*pMmioGetHeader)(HMMIO,PVOID,LONG,PLONG,ULONG,ULONG);
LONG   APIENTRY (*pMmioRead)(HMMIO,PCHAR,LONG);

static bool loadMMIOFuncs()
{
    bool res = false;
    do
    {
        if ( DosLoadModule( NULL, 0, "MMIO", &mmioHndl ) != 0 )
            break;
        if ( DosQueryProcAddr( mmioHndl, 0, "mmioOpen", (PFN *)&pMmioOpen ) != 0 )
            break;
        if ( DosQueryProcAddr( mmioHndl, 0, "mmioWrite", (PFN *)&pMmioWrite ) != 0 )
            break;
        if ( DosQueryProcAddr( mmioHndl, 0, "mmioSetHeader", (PFN *)&pMmioSetHeader ) != 0 )
            break;
        if ( DosQueryProcAddr( mmioHndl, 0, "mmioClose", (PFN *)&pMmioClose ) != 0 )
            break;
        if ( DosQueryProcAddr( mmioHndl, 0, "mmioIdentifyFile", (PFN *)&pMmioIdentifyFile ) != 0 )
            break;
        if ( DosQueryProcAddr( mmioHndl, 0, "mmioQueryHeaderLength", (PFN *)&pMmioQueryHeaderLength ) != 0 )
            break;
        if ( DosQueryProcAddr( mmioHndl, 0, "mmioGetHeader", (PFN *)&pMmioGetHeader ) != 0 )
            break;
        if ( DosQueryProcAddr( mmioHndl, 0, "mmioRead", (PFN *)&pMmioRead ) != 0 )
            break;

        res = true;
    } while (0);

    atexit( freeMmio );

    return res;
}


static bool saveToImage( char *pszFileName, char *format,
                         ULONG width, ULONG height, ULONG row_size,
                         ULONG bpp, char* src_buf )
{
    bool              ret = false;
    MMIOINFO          mmioinfoTarget;
    HMMIO             hmmioTarget;
    PBYTE             pbBuffer = NULL;
    ULONG             cbBuffer,cbBitmapInfo, rl;
    ULONG             rc;
    MMIMAGEHEADER     mmImgHdr;
    BITMAPINFO2       bmp;
    FOURCC            saveas;

    rl = ( ( bpp * width + 31 ) / 32 ) * 4;
    cbBuffer = rl * height;

    if ( !format ) {
        return ret;
    }

    saveas = mmioFOURCC( format[0], format[1], format[2], format[3] );

    // fill bmp
    memset( &bmp, 0, sizeof( bmp ) );
    bmp.cbFix         = sizeof( bmp );
    bmp.cx            = width;
    bmp.cy            = height;
    bmp.cPlanes       = 1;
    bmp.cBitCount     = bpp;
    bmp.ulCompression = 0;
    bmp.cbImage       = cbBuffer;

    cbBitmapInfo = sizeof( bmp );

    memset( &mmioinfoTarget, 0L, sizeof( MMIOINFO ) );
    mmioinfoTarget.fccIOProc = saveas;
    mmioinfoTarget.ulTranslate = MMIO_TRANSLATEHEADER | MMIO_TRANSLATEDATA;
    hmmioTarget = pMmioOpen( pszFileName, &mmioinfoTarget, MMIO_CREATE | MMIO_WRITE |
                                                        MMIO_DENYWRITE | MMIO_NOIDENTIFY );
    if ( hmmioTarget )
    {
        ULONG ulBytesWritten;

        memset( &mmImgHdr, 0, sizeof( MMIMAGEHEADER ) );
        mmImgHdr.ulHeaderLength = sizeof(MMIMAGEHEADER);
        mmImgHdr.ulContentType = MMIO_IMAGE_UNKNOWN;
        mmImgHdr.ulMediaType = MMIO_MEDIATYPE_IMAGE;
        mmImgHdr.mmXDIBHeader.XDIBHeaderPrefix.ulMemSize = cbBuffer;
        mmImgHdr.mmXDIBHeader.XDIBHeaderPrefix.ulPelFormat = ( bpp < 24 ) ?
                        mmioFOURCC('p','a','l','b') : mmioFOURCC('r','g','b','b');

        mmImgHdr.mmXDIBHeader.XDIBHeaderPrefix.usTransType = 0;
        mmImgHdr.mmXDIBHeader.XDIBHeaderPrefix.ulTransVal = 0;
        memcpy( &mmImgHdr.mmXDIBHeader.BMPInfoHeader2, &bmp, cbBitmapInfo );
        rc = pMmioSetHeader( hmmioTarget, &mmImgHdr, sizeof(MMIMAGEHEADER),
                                    (PLONG)&ulBytesWritten, 0L, 0L);
        if ( rc == MMIO_SUCCESS )
        {
            for ( int k=0; k < height; k++ )
            {
                char *line = src_buf + ( k * row_size );

                ulBytesWritten = pMmioWrite( hmmioTarget, (char*)line, rl );

                if ( ( ulBytesWritten == MMIO_ERROR ) || ( ulBytesWritten == 0 ) ) {
                    break;
                }
            }

            if ( ( ulBytesWritten != MMIO_ERROR ) && ( ulBytesWritten != 0 ) ) {
                ret = true;
            }
        }

        pMmioClose( hmmioTarget, 0L );
    }

    return ret;
}

static BOOL set_ea( const char *file_name, const char *ea_name,
                    const char *ea_data, int ea_data_len )
{
    APIRET rc = 0;
    EAOP2  op;

    char *databuf = new char[(64*2*1024)+1024]; // twice 64K for EA data + 1024 for any case

    op.fpGEA2List = (PGEA2LIST)0;
    op.fpFEA2List = (PFEA2LIST)databuf;

    int  ea_name_len = strlen( ea_name );
    if ( ea_name_len > 255 ) {
        delete[] databuf;
        return FALSE;
    }

    char *databufp = databuf + sizeof( long );
    *((long*)databufp) = 0; // Next field offset is zero - just one field here
    databufp += sizeof(long);
    *databufp++ = 0; // not critical
    *databufp++ = (char)ea_name_len;
    *((short*)databufp) = (short)ea_data_len;
    databufp += sizeof(short);
    memcpy( databufp, ea_name, ea_name_len+1 ); // with trailing zero
    databufp += ea_name_len+1;

    // set the ea type and length
    *((short*)databufp) = EAT_BINARY;
    databufp += sizeof(short);
    *((short*)databufp) = (short)ea_data_len;
    databufp += sizeof(short);

    memcpy( databufp, ea_data, ea_data_len ); // with trailing zero
    databufp += ea_data_len;

    *((long*)databuf) = databufp-databuf; // Size of all that stuff

    // HPFS386 workaround
    // Save timestamp (setting EA drops timestamp on HPFS386)
    APIRET qpirc = 0;
    FILESTATUS3 fs = { 0 };
    qpirc = DosQueryPathInfo( file_name, FIL_STANDARD, &fs, sizeof( fs ) );

    // Write EA
    rc = DosSetPathInfo( file_name, FIL_QUERYEASIZE, &op, sizeof(op), 0);
    delete[] databuf;

    // Restore timestamp
    if ( qpirc == 0 ) {
        DosSetPathInfo( file_name, FIL_STANDARD, &fs, sizeof( fs ), DSPI_WRTTHRU );
    }

    if ( rc != 0 ) {
        return FALSE;
    }

    return TRUE;
}

bool Lucide::isThumbNeeded( const char *fn )
{
    // First, check if mmio is available
    if ( !mmioFuncsLoaded ) {
        return false;
    }

    // Second, check if file is writeable
    if ( access( fn, W_OK ) != 0 ) {
        // Isn't writable, do not waste time to render thumbnail
        return false;
    }

    // Third, check if thumbnail EA already present
    UCHAR    EnumBuf[200] = {0};      // Data Buffer
    ULONG    ulEnumCnt    = 0;        // Count of entries to return
    FEA2     *ptr         = NULL;     // Pointer to data items returned
    ULONG    ulTemp       = 0;
    APIRET   rc           = 0;

    ulEnumCnt = (ULONG)-1; // Request as many attributes as will fit in buffer

    rc = DosEnumAttribute( ENUMEA_REFTYPE_PATH, (PVOID)fn, 1L, &EnumBuf, sizeof( EnumBuf ),
                           &ulEnumCnt, ENUMEA_LEVEL_NO_VALUE );

    if ( rc != 0 ) {
        // error look for EA names, return 'false' to prevent EA creation
        // as if enum failed, creation may also fail
        return false;
    }

    ptr = (FEA2 *)EnumBuf; // Mask the buffer pointer to an FEA2 structure

    for ( ULONG i = 0; i < ulEnumCnt; i++ )
    {
        if ( strcmp( ptr->szName, LUTHUMB_EA_NAME ) == 0 ) {
            return false; // Thumbnail already present
        }
        /// increment the ptr with the value in oNextEntryOffset
        ulTemp = ptr->oNextEntryOffset + (ULONG)ptr;
        ptr = (FEA2 *)ulTemp;
    }
    return true;
}


bool Lucide::createThumbnail( LuDocument *doc )
{
    //if ( !doc->isScalable( ev ) ) {
    //    return;
    //}

    // render first page if there is one
    if ( doc->getPageCount( ev ) <= 0 )
        return FALSE;
    double width = 0, height = 0;
    doc->getPageSize( ev, 0, &width, &height );
    if ( width <= 0 || height <= 0 )
        return FALSE;
    double zoom = std::min( (double)LUTHUMB_SIZE_X / width, (double)LUTHUMB_SIZE_Y / height );
    short bpp = doc->getBpp( ev );

    long rx = width * zoom;
    long ry = height * zoom;
    LuPixbuf *pixbuf = new LuPixbuf( ev, rx, ry, bpp );
    if ( !doc->renderPageToPixbuf(ev, 0, 0, 0, rx, ry, zoom, 0, pixbuf,
                                  NULL, NULL ) ) {
        delete pixbuf;
        return TRUE;
    }
    char *tmpgif = new char[ CCHMAXPATH ];
    getTmpDir( tmpgif );
    strcat( tmpgif, "LUTHUMB.TMP" );

    // Workaround: GIF mmio proc hangs on 32-bit images, convert to 24 bit
    if ( bpp == 4 )
    {
        LuPixbuf *pb = new LuPixbuf( ev, rx, ry, 3 );

        char *src = (char *)pixbuf->getDataPtr( ev );
        char *dst = (char *)pb->getDataPtr( ev );
        int src_rowstride = pixbuf->getRowSize( ev );
        int dst_rowstride = pb->getRowSize( ev );

        int i, j, l, m;
        for ( i = 0; i < ry; i++ )
        {
            char *src_line = src + ( i * src_rowstride );
            char *dst_line = dst + ( i * dst_rowstride );

            // source 4 Bpp, dest 3 Bpp
            for ( j = 0, l = 0, m = 0; j < rx; j++ ) {
                dst_line[ l++ ] = src_line[ m++ ];
                dst_line[ l++ ] = src_line[ m++ ];
                dst_line[ l++ ] = src_line[ m++ ];
                m++;
            }
        }

        delete pixbuf;
        pixbuf = pb;
        bpp = 3;
    }

    bool saved = saveToImage( tmpgif, "GIFC", rx, ry, pixbuf->getRowSize( ev ),
                              bpp * 8, (char *)pixbuf->getDataPtr( ev ) );
    delete pixbuf;
    if ( saved )
    {
        // If image file saved, read file content into
        // thumbnailData buffer, to be able write it into EA
        // when document will be closed
        int h = open( tmpgif, O_RDONLY | O_BINARY | O_NOINHERIT );
        if ( h != -1 )
        {
            long flen = filelength( h );
            if ( flen > 0 )
            {
                thumbnailData = new char[ flen ];
                thumbnailDataLen = flen;
                if ( read( h, thumbnailData, flen ) != flen ) {
                    delete thumbnailData;
                    thumbnailData = NULL;
                    thumbnailDataLen = 0;
                }
            }
            close( h );
        }
    }
    // if tmp file exist - delete it
    if ( access( tmpgif, F_OK ) == 0 ) {
        unlink( tmpgif );
    }
    delete[] tmpgif;
    return TRUE;
}

void Lucide::writeThumbnail( const char *fn )
{
    if ( ( thumbnailData == NULL ) || ( thumbnailDataLen == 0 ) ) {
        return;
    }

    set_ea( fn, LUTHUMB_EA_NAME, (const char *)thumbnailData, thumbnailDataLen );
    delete thumbnailData;
    thumbnailData = NULL;
    thumbnailDataLen = 0;
}


HBITMAP LoadBitmap( HAB hab, HDC hdc, HPS *hps, PSZ pszFileName )
{
    HBITMAP       hbm;
    MMIOINFO      mmioinfo;
    MMFORMATINFO  mmFormatInfo;
    HMMIO         hmmio;
    ULONG         ulImageHeaderLength;
    MMIMAGEHEADER mmImgHdr;
    ULONG         ulBytesRead;
    ULONG         dwNumRowBytes;
    PBYTE         pRowBuffer;
    ULONG         dwRowCount;
    SIZEL         ImageSize;
    ULONG         dwHeight, dwWidth;
    SHORT         wBitCount;
    FOURCC        fccStorageSystem;
    ULONG         dwPadBytes;
    ULONG         dwRowBits;
    ULONG         ulReturnCode;
    ULONG         dwReturnCode;
    HBITMAP       hbReturnCode;
    LONG          lReturnCode;
    FOURCC        fccIOProc;


    ulReturnCode = pMmioIdentifyFile( pszFileName, 0L, &mmFormatInfo,
                                      &fccStorageSystem, 0L, 0L );
    if ( ulReturnCode == MMIO_ERROR ) {
         return NULLHANDLE;
    }

    if( mmFormatInfo.fccIOProc == FOURCC_DOS ) {
         return NULLHANDLE;
    }

    if ( (mmFormatInfo.ulMediaType != MMIO_MEDIATYPE_IMAGE) ||
         ((mmFormatInfo.ulFlags & MMIO_CANREADTRANSLATED) == 0) ) {
         return NULLHANDLE;
    }
    else {
         fccIOProc = mmFormatInfo.fccIOProc;
    }

    memset( &mmioinfo, 0L, sizeof( MMIOINFO ) );
    mmioinfo.fccIOProc = fccIOProc;
    mmioinfo.ulTranslate = MMIO_TRANSLATEHEADER | MMIO_TRANSLATEDATA;

    hmmio = pMmioOpen( (PSZ)pszFileName, &mmioinfo,
                      MMIO_READ | MMIO_DENYWRITE | MMIO_NOIDENTIFY );

    if ( !hmmio ) {
         return NULLHANDLE;
    }

    dwReturnCode = pMmioQueryHeaderLength( hmmio, (PLONG)&ulImageHeaderLength, 0L, 0L );

    if ( ulImageHeaderLength != sizeof ( MMIMAGEHEADER ) ) {
         pMmioClose( hmmio, 0L );
         return NULLHANDLE;
    }

    ulReturnCode = pMmioGetHeader( hmmio, &mmImgHdr, sizeof( MMIMAGEHEADER ),
                                   (PLONG)&ulBytesRead, 0L, 0L );

    if ( ulReturnCode != MMIO_SUCCESS ) {
         pMmioClose( hmmio, 0L );
         return NULLHANDLE;
    }

    dwHeight = mmImgHdr.mmXDIBHeader.BMPInfoHeader2.cy;
    dwWidth = mmImgHdr.mmXDIBHeader.BMPInfoHeader2.cx;
    wBitCount = mmImgHdr.mmXDIBHeader.BMPInfoHeader2.cBitCount;
    dwRowBits = dwWidth * mmImgHdr.mmXDIBHeader.BMPInfoHeader2.cBitCount;
    dwNumRowBytes = dwRowBits >> 3;

    if ( dwRowBits % 8 ) {
         dwNumRowBytes++;
    }

    dwPadBytes = ( dwNumRowBytes % 4 );

    if ( dwPadBytes ) {
         dwNumRowBytes += 4 - dwPadBytes;
    }

    pRowBuffer = (PBYTE)malloc( dwNumRowBytes );

    ImageSize.cx = dwWidth;
    ImageSize.cy = dwHeight;

    *hps = GpiCreatePS( hab, hdc, &ImageSize,
                        PU_PELS | GPIF_DEFAULT | GPIT_MICRO | GPIA_ASSOC );

    if ( !*hps ) {
        free( pRowBuffer );
        pMmioClose( hmmio, 0L );
        return NULLHANDLE;
    }

    hbm = GpiCreateBitmap( *hps, &mmImgHdr.mmXDIBHeader.BMPInfoHeader2, 0L, NULL, NULL );

    if ( !hbm )
    {
        free( pRowBuffer );
        pMmioClose( hmmio, 0L );
        return NULLHANDLE;
    }

    hbReturnCode = GpiSetBitmap( *hps, hbm );

    for ( dwRowCount = 0; dwRowCount < dwHeight; dwRowCount++ )
    {
         ulBytesRead = pMmioRead( hmmio, pRowBuffer, dwNumRowBytes );

         if ( !ulBytesRead ) {
              break;
         }

         lReturnCode = GpiSetBitmapBits( *hps, dwRowCount, 1, pRowBuffer,
                                         (PBITMAPINFO2)&mmImgHdr.mmXDIBHeader.BMPInfoHeader2 );
    }

    pMmioClose( hmmio, 0L );
    free( pRowBuffer );

    return hbm;
}

