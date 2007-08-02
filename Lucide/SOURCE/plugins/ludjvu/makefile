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


all: make.cfg ludjvu.dll
   DEL MAKE.CFG


ludjvu.dll: ludjvu.obj ..\ludoc\ludoc.lib
  copy &&|
option quiet
system os2v2 dll initinstance terminstance
option map=$(OBJDIR)\ludjvu
option statics
file $(OBJDIR)\ludjvu.obj
name $(EXEDIR)\ludjvu
lib ..\..\..\..\libdjvu\ddjvuapi.lib
lib ..\ludoc\ludoc
lib somtk 
export LuDjvuDocumentNewClass
export _LuDjvuDocumentClassData
export _LuDjvuDocumentCClassData
export LuDjvuDocumentClassData=_LuDjvuDocumentClassData
export LuDjvuDocumentCClassData=_LuDjvuDocumentCClassData
export createObject
export getSupportedExtensions
export getDescription
export getCheckStruct
| tmpmake.lnk >NUL
    wlink @tmpmake.lnk
    del tmpmake.lnk
    

ludjvu.obj: ludjvu.cpp ludjvu.xh

ludjvu.cpp: ludjvu.idl


MAKE.CFG: makefile
  copy &&|
-zq 
-zp=4
-bm
-ox
-xs
-xr
-I..\..\sominc
-I..\ludoc
-I..\..\..\..\libdjvu
-DOS2
| MAKE.CFG >NUL
