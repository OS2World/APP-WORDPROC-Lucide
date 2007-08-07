.autodepend

CC=wcl386

CFLAGS=-zq -zp=8 -bm -sg -ot -ox -oh -xs -xr -I.. -I..\..\freetype2\include -DOS2

LIBS=libsplash.lib

OBJS1 = Splash.obj SplashBitmap.obj SplashClip.obj SplashFont.obj \
        SplashFontEngine.obj SplashFontFile.obj SplashFontFileID.obj \
        SplashFTFont.obj SplashFTFontEngine.obj SplashFTFontFile.obj
OBJS2 = SplashPath.obj SplashPattern.obj SplashScreen.obj \
        SplashState.obj SplashT1Font.obj SplashT1FontEngine.obj \
        SplashT1FontFile.obj SplashXPath.obj SplashXPathScanner.obj
       
       
all: $(LIBS)

$(LIBS): $(OBJS1) $(OBJS2)
	rm -f $(LIBS)
	wlib -b -q $@ + $(OBJS1)
	wlib -b -q $@ + $(OBJS2)

.c.obj:
	$(CC) $(CFLAGS) -c $<

.cc.obj:
	$(CC) $(CFLAGS) -c $<
