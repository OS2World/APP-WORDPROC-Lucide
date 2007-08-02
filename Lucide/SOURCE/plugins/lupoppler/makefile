.autodepend

OBJDIR = ..\..\..\OBJS
EXEDIR = ..\..\..\BIN

.path.obj = $(OBJDIR)
.path.res = $(OBJDIR)
.path.exe = $(EXEDIR)
.path.dll = $(EXEDIR)


.CPP.OBJ:
     WPP386 @make.cfg -fo$@ $<

.idl.xh:
    sc -c -s"xc;xih;xh" -I..\ludoc $<
    ..\..\sominc\cnvsomex.cmd $@


all: make.cfg lupplr.dll
   DEL MAKE.CFG
    
lupplr.dll: lupoppler.obj ..\ludoc\ludoc.lib ..\..\..\..\poppler\poppler.lib
  copy &&|
option quiet
system os2v2 dll initinstance terminstance
option map=$(OBJDIR)\lupplr
option statics
file $(OBJDIR)\lupoppler.obj
name $(EXEDIR)\lupplr
lib ..\..\..\..\poppler\poppler.lib
lib ..\..\..\..\libjpeg\libjpeg.lib
lib ..\ludoc\ludoc
lib somtk 
lib libconv
lib libuls
export LuPopplerDocumentNewClass
export LuPopplerDocumentClassData
export LuPopplerDocumentCClassData
export createObject
export getSupportedExtensions
export getDescription
export getCheckStruct
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
-ot
-ox
-xs
-xr
-sg
-I..\..\sominc
-I..\ludoc
-I..\..\..\..\poppler\mypoppler
-I..\..\..\..\poppler\mypoppler\poppler
-I..\..\..\..\poppler\fc-emulate-os2
-DOS2
| MAKE.CFG >NUL
