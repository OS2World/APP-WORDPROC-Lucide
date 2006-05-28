CC=wcl386

CFLAGS=-zq -zp=4 -bm -ox -sg -I.. -DOS2

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
