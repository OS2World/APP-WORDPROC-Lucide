#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>

extern "C" LONG APIENTRY GpiDrawBits(HPS hps,
                                   PVOID pBits,
                                   PBITMAPINFO2 pbmiInfoTable,
                                   LONG lCount,
                                   PPOINTL aptlPoints,
                                   LONG lRop,
                                   ULONG flOptions);

#include <goo/gmem.h>
#include <splash/SplashTypes.h>
#include <splash/SplashBitmap.h>
#include "Object.h"
#include "SplashOutputDev.h"
#include "GfxState.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "ErrorCodes.h"

HAB   hab;
HWND  hWndFrame;
HWND  hWndClient;
PDFDoc *doc;
SplashOutputDev *out;

static int pdfload( const char *filename )
{
  int err;
  GooString *filename_g;
  int w, h;

  filename_g = new GooString(filename);
  // open the PDF file
  doc = new PDFDoc(filename_g, 0, 0);
  delete filename_g;

  if (!doc->isOk()) {
      err = doc->getErrorCode();
      delete doc;
      return err;
  }

  SplashColor sc;
  sc[0] = 255;
  sc[1] = 255;
  sc[2] = 255;
  out = new SplashOutputDev(splashModeBGR8, 4, gFalse, sc );

  out->startDoc(doc->getXRef());
  doc->displayPage(out, 1, 120, 120, 0, gFalse, gTrue, gTrue);

  return errNone;
}


static MRESULT EXPENTRY wndProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch ( msg )
    {
        case WM_ERASEBACKGROUND:
            return (MRESULT)TRUE;

        case WM_PAINT:
            {
                RECTL rcl;
                HPS hps = WinBeginPaint( hwnd , 0L , 0L );
                WinQueryWindowRect( hwnd , &rcl );
                //WinDrawText( hps , -1 , "test" , &rcl , CLR_BLACK, CLR_PALEGRAY,
                //             DT_CENTER | DT_VCENTER | DT_ERASERECT );

                BITMAPINFO2  pbmi;
                // target and source rectangles
                pbmi.cbFix = 16L;
                pbmi.cx = out->getBitmapWidth();
                pbmi.cy = out->getBitmapHeight();
                pbmi.cPlanes = 1;
                pbmi.cBitCount = 24;
                //POINTL aptlPoints[4]={ 0, 0, pbmi.cx, pbmi.cy, 0, 0, pbmi.cx, pbmi.cy };

                printf( "cx/cy: %d/%d\n", pbmi.cx, pbmi.cy );

                void *dptr = out->getBitmap()->getDataPtr();
                for ( int i = 0; i < pbmi.cy; i++ )
                {
                    POINTL aptlPoints[4]={ 0, rcl.yTop-i-1, pbmi.cx, rcl.yTop-i, 0, i, pbmi.cx, i+1 };
                    GpiDrawBits(hps, dptr, &pbmi, 4L,
                                aptlPoints, ROP_SRCCOPY, BBO_IGNORE);
                }

                //GpiDrawBits(hps, out->getBitmap()->getDataPtr(), &pbmi, 4L,
                //               aptlPoints, ROP_SRCCOPY, BBO_IGNORE);

                WinEndPaint( hps );
            }
            break;
    }
    return WinDefWindowProc( hwnd, msg, mp1, mp2 );
}



void main( int argc, char *argv[] )
{
    PPIB pib;
    PTIB tib;
    DosGetInfoBlocks(&tib, &pib);
    pib->pib_ultype = 3;

    if ( argc < 2 )
    {
        printf("No file name given!\n");
        return;
    }

    globalParams = new GlobalParams(".");

    int err = pdfload(argv[1]);
    if (err != errNone) {
        printf("Error loading document!\n");
        return;
    }

    HMQ   hmq;
    QMSG  qmsg;
    hab = WinInitialize( 0 );
    hmq = WinCreateMsgQueue( hab, 0 );

    // Создать главное окно
    ULONG ulFrameFlags = FCF_TITLEBAR | FCF_SIZEBORDER | FCF_SYSMENU |
                         FCF_MINMAX | FCF_TASKLIST | FCF_NOBYTEALIGN;
    hWndFrame = WinCreateStdWindow( HWND_DESKTOP, 0, &ulFrameFlags, NULL, "test",
                                    WS_SYNCPAINT|WS_VISIBLE, NULLHANDLE, 250, NULL );

    WinRegisterClass( hab, "my.test", wndProc, CS_SIZEREDRAW, sizeof( ULONG ) * 2 );

    // Невидимый фиксированный сплиттер

    // Рабочее окно программы
    hWndClient = WinCreateWindow( hWndFrame, "my.test", "",
                                  WS_VISIBLE, 0, 0, 0, 0, hWndFrame,
                                  HWND_TOP, FID_CLIENT, NULL, NULL );

    // Показать окно программы
    WinSetWindowPos( hWndFrame, HWND_TOP, 100, 100, 630, 400,
                     SWP_SIZE | SWP_MOVE | SWP_SHOW | SWP_ACTIVATE );

    // Messsage loop
    while ( WinGetMsg( hab, &qmsg, 0, 0, 0 ) ) {
        WinDispatchMsg( hab, &qmsg );
    }

    WinDestroyWindow( hWndFrame );
    WinDestroyMsgQueue( hmq );
    WinTerminate( hab );
}

