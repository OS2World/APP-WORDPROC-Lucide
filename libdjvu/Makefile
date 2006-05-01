.autodepend

AR=ar rc
RANLIB=ranlib
CC=g++

CFLAGS=-O3 -s -Zomf -Zmtd -DHAVE_CONFIG_H=1 -Wno-deprecated

LIBS=libdjvu.a

OBJS1 = DjVuGlobal.o DjVuGlobalMemory.o GOS.o GException.o GContainer.o \
    GString.o GThreads.o GRect.o GSmartPointer.o  MMX.o Arrays.o \
    GBitmap.o GPixmap.o GScaler.o DjVuPalette.o ByteStream.o
OBJS2 = IFFByteStream.o BSByteStream.o BSEncodeByteStream.o ZPCodec.o \
    JB2Image.o JB2EncodeCodec.o IW44Image.o IW44EncodeCodec.o \
    MMRDecoder.o JPEGDecoder.o DataPool.o GURL.o DjVuFileCache.o
OBJS3 = DjVuPort.o GMapAreas.o DjVuAnno.o GIFFManager.o DjVuText.o \
    DjVuInfo.o DjVuFile.o DjVuImage.o DjVuDocument.o \
    DjVmDir.o DjVmDoc.o DjVmDir0.o DjVmNav.o DjVuNavDir.o
OBJS4 = DjVuErrorList.o DjVuDocEditor.o DjVuToPS.o DjVuDumpHelper.o \
    DjVuMessageLite.o DjVuMessage.o GUnicode.o UnicodeByteStream.o \
    XMLParser.o XMLTags.o miniexp.o ddjvuapi.o debug.o

       
all: $(LIBS) libdjvu.dll

$(LIBS): $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4)
	rm -f $(LIBS)	
	wlib -b -q $@ + $(OBJS1)
	wlib -b -q $@ + $(OBJS2)
	wlib -b -q $@ + $(OBJS3)
	wlib -b -q $@ + $(OBJS4)


#	rm -f $(LIBS)
#	$(AR) $@ $(OBJS1)
#	$(AR) $@ $(OBJS2)
#	$(AR) $@ $(OBJS3)
#	$(AR) $@ $(OBJS4)
#	$(RANLIB) $(LIBS)

libdjvu.dll: $(LIBS)
  g++ -s -Zomf -Zdll -Zmtd ddjvuapi.o ddjvuapi.def -llibdjvu
  implib ddjvuapi ddjvuapi.dll

.cpp.o:
	$(CC) $(CFLAGS) -c $<
