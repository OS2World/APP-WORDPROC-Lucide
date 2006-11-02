.autodepend

CC=wcl386

CFLAGS=-zq -zp=4 -bm -ot -ox -sg -I..\include -DOS2 -DFT2_BUILD_LIBRARY

LIBS=ft2lib.lib

OBJS1 = autofit.obj ftbase.obj ftinit.obj ftglyph.obj ftsystem.obj \
        ftbitmap.obj ftbdf.obj fttype1.obj bdf.obj ftcache.obj cff.obj \
        type1cid.obj ftgzip.obj ftlzw.obj otvalid.obj pcf.obj pfr.obj

OBJS2 = psaux.obj pshinter.obj psnames.obj raster.obj sfnt.obj smooth.obj \
        truetype.obj type1.obj type42.obj winfnt.obj gxvalid.obj


all: $(LIBS)

$(LIBS): $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4)
    rm -f $(LIBS)
    wlib -b -q $@ + $(OBJS1)
    wlib -b -q $@ + $(OBJS2)

.c.obj:
    $(CC) $(CFLAGS) -c $<

.cc.obj:
    $(CC) $(CFLAGS) -c $<

    
autofit.obj:       autofit\autofit.c
ftbase.obj:        base\ftbase.c
ftinit.obj:        base\ftinit.c
ftglyph.obj:       base\ftglyph.c
ftsystem.obj:      base\ftsystem.c
ftbitmap.obj:      base\ftbitmap.c
ftbdf.obj:         base\ftbdf.c
fttype1.obj:       base\fttype1.c
bdf.obj:           bdf\bdf.c
ftcache.obj:       cache\ftcache.c
cff.obj:           cff\cff.c
type1cid.obj:      cid\type1cid.c
gxvalid.obj:       gxvalid\gxvalid.c
ftgzip.obj:        gzip\ftgzip.c
ftlzw.obj:         lzw\ftlzw.c
otvalid.obj:       otvalid\otvalid.c
pcf.obj:           pcf\pcf.c
pfr.obj:           pfr\pfr.c
psaux.obj:         psaux\psaux.c
pshinter.obj:      pshinter\pshinter.c
psnames.obj:       psnames\psnames.c
raster.obj:        raster\raster.c
sfnt.obj:          sfnt\sfnt.c
smooth.obj:        smooth\smooth.c
truetype.obj:      truetype\truetype.c
type1.obj:         type1\type1.c
type42.obj:        type42\type42.c
winfnt.obj:        winfonts\winfnt.c

