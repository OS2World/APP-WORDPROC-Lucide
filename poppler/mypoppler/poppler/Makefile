.autodepend

CC=wcl386

CFLAGS=-zq -zp=4 -bm -sg -ox -xs -xr -I.. -I..\..\freetype-2.1.10\include -I..\..\fontconfig-2.3.2-os2 -DOS2 -DUSE_ANNOTS_VIEW

LIBS=libpoppler.lib

OBJS1 = SplashOutputDev.obj Annot.obj Array.obj BuiltinFont.obj \
        BuiltinFontTables.obj Catalog.obj CharCodeToUnicode.obj \
        CMap.obj Decrypt.obj Dict.obj Error.obj FontEncodingTables.obj
OBJS2 = FontInfo.obj Function.obj Gfx.obj GfxFont.obj GfxState.obj \
        GlobalParams.obj JArithmeticDecoder.obj JBIG2Stream.obj \
        JPXStream.obj Lexer.obj Link.obj NameToCharCode.obj Object.obj
OBJS3 = Outline.obj OutputDev.obj Page.obj Parser.obj PDFDoc.obj \
        PDFDocEncoding.obj ProfileData.obj PSTokenizer.obj Stream.obj \
        UnicodeMap.obj UnicodeTypeTable.obj XRef.obj PSOutputDev.obj
OBJS4 = TextOutputDev.obj PageLabelInfo.obj SecurityHandler.obj \
        XpdfPluginAPI.obj UGooString.obj

all: $(LIBS)

$(LIBS): $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4)
	rm -f $(LIBS)
	wlib -b -q $@ + $(OBJS1)
	wlib -b -q $@ + $(OBJS2)
	wlib -b -q $@ + $(OBJS3)
	wlib -b -q $@ + $(OBJS4)

.c.obj:
	$(CC) $(CFLAGS) -c $<

.cc.obj:
	$(CC) $(CFLAGS) -c $<
