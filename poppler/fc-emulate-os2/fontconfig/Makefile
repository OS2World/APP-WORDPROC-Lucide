.autodepend

CC=wpp386
CFLAGS=-zq -zp=4 -bm -sg -ot -ox -xs -xr -I..\..\freetype2\include -DOS2

LIBS=libfcos2.lib

OBJS1 = fontconfig.obj

all: $(LIBS)

$(LIBS): $(OBJS1)
	rm -f $(LIBS)
	wlib -b -q $@ + $(OBJS1)


.c.obj:
	$(CC) $(CFLAGS) $<

.cpp.obj:
	$(CC) $(CFLAGS) $<
