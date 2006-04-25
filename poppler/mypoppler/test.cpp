#include <stdio.h>
#include "config.h"

#include <goo/gmem.h>
#include <splash/SplashTypes.h>
#include <splash/SplashBitmap.h>
#include "Object.h"
#include "SplashOutputDev.h"
#include "GfxState.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "ErrorCodes.h"

//------------------------------------------------------------------------

#define xOutMaxRGBCube 6	// max size of RGB color cube

//------------------------------------------------------------------------
// Constants and macros
//------------------------------------------------------------------------

#define xoutRound(x) ((int)(x + 0.5))


static int view_load( const char *filename )
{
  PDFDoc *newDoc;
  int err;
  GooString *filename_g;
  int w, h;

  filename_g = new GooString (filename);

  // open the PDF file
  newDoc = new PDFDoc(filename_g, 0, 0);

  delete filename_g;
  
  if (!newDoc->isOk())
    {
      err = newDoc->getErrorCode();
      delete newDoc;
      return err;
    }

  printf("pages: %d\n", newDoc->getNumPages() );
    
  newDoc->saveAs( new GooString("my.pdf") );

  return errNone;
}


int main()
{
  
  globalParams = new GlobalParams("/etc/xpdfrc");
  
      int err = view_load("test.pdf");

      if (err != errNone)
        printf("Error loading document!\n");
      
  delete globalParams;
  
  return 0;
}
