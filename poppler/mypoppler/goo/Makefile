CC=wcl386

CFLAGS=-zq -zp=4 -bm -ot -ox -xs -xr -sg -I.. -DOS2
CFLAGS_C=-zq -zp=4 -bm -ot -ox -sg -I.. -DOS2

LIBS=libgoo.lib

OBJS = FixedPoint.obj gfile.obj gmempp.obj GooHash.obj GooList.obj \
       GooString.obj GooTimer.obj gmem.obj
       
       
all: $(LIBS)

$(LIBS): $(OBJS)
	rm -f $(LIBS)
	wlib $@ + $(OBJS)

.c.obj:
	$(CC) $(CFLAGS_C) -c $<

.cc.obj:
	$(CC) $(CFLAGS) -c $<
