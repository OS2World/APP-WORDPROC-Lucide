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


all: make.cfg lujpeg.dll
   DEL MAKE.CFG


lujpeg.dll: lujpeg.obj jpscale.obj ..\ludoc\ludoc.lib
  copy &&|
option quiet
system os2v2 dll initinstance terminstance
option map=$(OBJDIR)\lujpeg
option statics
file $(OBJDIR)\lujpeg.obj
file $(OBJDIR)\jpscale.obj
name $(EXEDIR)\lujpeg
lib ..\..\..\..\libjpeg\libjpeg.lib
lib ..\ludoc\ludoc
lib somtk 
export LuJpegDocumentNewClass
export LuJpegDocumentClassData
export LuJpegDocumentCClassData
export createObject
export getSupportedExtensions
export getDescription
export getCheckStruct
| tmpmake.lnk >NUL
    wlink @tmpmake.lnk
    del tmpmake.lnk
    

lujpeg.obj: lujpeg.cpp lujpeg.xh

lujpeg.cpp: lujpeg.idl


MAKE.CFG: makefile
  copy &&|
-zq 
-zp=4
-bm
-ot
-ox
-xs
-xr
-I..\..\sominc
-I..\ludoc
-I..\..\..\..\libjpeg
-DOS2
| MAKE.CFG >NUL
