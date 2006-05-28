CC=wcl386

CFLAGS=-zq -zp=4 -bm -ox -sg -I.. -I..\..\expat-1.95.8\lib -I..\..\freetype-2.1.10\include -DOS2

LIBS=fontconfig.lib

OBJS = fcatomic.obj fcblanks.obj fccache.obj fccfg.obj fccharset.obj \
       fcdbg.obj fcdefault.obj fcdir.obj fcfreetype.obj fcfs.obj \
       fcinit.obj fclang.obj fclist.obj fcmatch.obj fcmatrix.obj \
       fcname.obj fcpat.obj fcstr.obj fcxml.obj


all: $(LIBS)

$(LIBS): $(OBJS)
	rm -f $(LIBS)
	wlib -b -q $@ + $(OBJS)

.c.obj:
	$(CC) $(CFLAGS) -c $<

.cc.obj:
	$(CC) $(CFLAGS) -c $<
