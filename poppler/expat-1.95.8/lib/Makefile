CC=wcl386

CFLAGS=-zq -zp=4 -bm -ox -I.. -DOS2 -DHAVE_MEMMOVE

LIBS=expat.lib

OBJS = xmlparse.obj xmlrole.obj xmltok.obj
       
       
all: $(LIBS)

$(LIBS): $(OBJS)
	rm -f $(LIBS)
	wlib $@ + $(OBJS)

.c.obj:
	$(CC) $(CFLAGS) -c $<

.cc.obj:
	$(CC) $(CFLAGS) -c $<
