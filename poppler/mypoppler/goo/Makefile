CC=wcl386

CFLAGS=-zq -zp=8 -bm -ot -ox -xs -oh -xr -sg -5 -fp5 -I.. -DOS2
CFLAGS_C=-zq -zp=8 -bm -ot -ox -oh -sg -5 -fp5 -I.. -DOS2

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
