CC=wcl386

CFLAGS=-zq -zp=8 -bm -ot -ox -oh -sg -5 -fp5 -I.. -DOS2

LIBS=libfofi.lib

OBJS = FoFiBase.obj FoFiEncodings.obj FoFiTrueType.obj FoFiType1.obj \
       FoFiType1C.obj
       
       
all: $(LIBS)

$(LIBS): $(OBJS)
	rm -f $(LIBS)
	wlib $@ + $(OBJS)

.c.obj:
	$(CC) $(CFLAGS) -c $<

.cc.obj:
	$(CC) $(CFLAGS) -c $<
