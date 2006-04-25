.autodepend

OBJDIR = D:\Projects\Lucide\OBJS
EXEDIR = D:\Projects\Lucide\BIN

.path.obj = $(OBJDIR)
.path.res = $(OBJDIR)
.path.exe = $(EXEDIR)
.path.dll = $(EXEDIR)


.CPP.OBJ:
     WPP386 @make.cfg -fo$@ $<

.idl.xh:
    sc -c -s"xc;xih;xh" -I..\ludoc $<
     

all: make.cfg lupplr.dll
   DEL MAKE.CFG
    
lupplr.dll: lupoppler.obj ..\ludoc\ludoc.lib
  copy &&|
option quiet
system os2v2 dll initinstance terminstance
option map=$(OBJDIR)\lupplr
option statics
file $(OBJDIR)\lupoppler.obj
name $(EXEDIR)\lupplr
lib D:\Projects\poppler\mypoppler\poppler.lib
lib D:\Projects\poppler\mypoppler\ft2lib.lib
lib ..\ludoc\ludoc
lib somtk 
export LuPopplerDocumentNewClass
export LuPopplerDocumentClassData
export LuPopplerDocumentCClassData
export createObject
export getSupportedExtensions
export getDescription
| tmpmake.lnk >NUL
    wlink @tmpmake.lnk
    del tmpmake.lnk

    
lupoppler.obj: lupoppler.cpp lupoppler.xh

lupoppler.cpp: lupoppler.idl

MAKE.CFG: makefile
  copy &&|
-zq 
-zp=4
-bm
-ox
-xs
-xr
-I..\ludoc
-ID:\Projects\poppler\mypoppler
-ID:\Projects\poppler\mypoppler\poppler
-ID:\Projects\poppler\fontconfig-2.3.2-os2
-DOS2
| MAKE.CFG >NUL
