.autodepend

TEST=1
VERSION=Beta 2.1

!if $(TEST)==1
	BMODE=os2v2
!else
	BMODE=os2v2_pm
!endif

OBJDIR = ..\..\OBJS
EXEDIR = ..\..\BIN

.path.obj = $(OBJDIR)
.path.res = $(OBJDIR)
.path.exe = $(EXEDIR)
.path.dll = $(EXEDIR)


.CPP.OBJ:
     WPP386 @make.cfg -fo$@ $<

.C.OBJ:
     WPP386 @make.cfg -fo$@ $<

.idl.xh:
    sc -c -s"xc;xih;xh" ..\plugins\ludoc $<


all: make.cfg Lucide.exe
   DEL MAKE.CFG

OBJS = Lucide.obj luutils.obj clipbrd.obj pmsplitter.obj pmtoolbar.obj \
       toolbar.obj pluginman.obj pluginViewDlg.obj docViewer.obj \
       linklab.obj wwbtn.obj intern.obj messages.obj indexWindow.obj \
       fontsInfoDlg.obj docInfoDlg.obj findDlg.obj progressDlg.obj \
       aboutDlg.obj settingsDlg.obj lusettings.obj printDlg.obj \
       print.obj

Lucide.exe: $(OBJS) Lucide.res
  copy &&|
option quiet
system $(BMODE)
option map=$(OBJDIR)\lucide
option statics
file $(OBJDIR)\Lucide.obj
file $(OBJDIR)\luutils.obj
file $(OBJDIR)\clipbrd.obj
file $(OBJDIR)\pmsplitter.obj
file $(OBJDIR)\pmtoolbar.obj
file $(OBJDIR)\toolbar.obj
file $(OBJDIR)\pluginman.obj
file $(OBJDIR)\pluginViewDlg.obj
file $(OBJDIR)\fontsInfoDlg.obj
file $(OBJDIR)\docInfoDlg.obj
file $(OBJDIR)\findDlg.obj
file $(OBJDIR)\progressDlg.obj
file $(OBJDIR)\aboutDlg.obj
file $(OBJDIR)\printDlg.obj
file $(OBJDIR)\print.obj
file $(OBJDIR)\settingsDlg.obj
file $(OBJDIR)\lusettings.obj
file $(OBJDIR)\docViewer.obj
file $(OBJDIR)\indexWindow.obj
file $(OBJDIR)\linklab.obj
file $(OBJDIR)\wwbtn.obj
file $(OBJDIR)\intern.obj
file $(OBJDIR)\messages.obj
name $(EXEDIR)\Lucide
lib ..\plugins\ludoc\ludoc
lib somtk

| tmpmake.lnk >NUL
    wlink @tmpmake.lnk
    RC -n $(OBJDIR)\Lucide.RES $(EXEDIR)\Lucide.exe >NUL
    del tmpmake.lnk
    

Lucide.res: Lucide.rc dialogs.rc
    RC -n -r Lucide.rc $(OBJDIR)\Lucide.res


Lucide.cpp: ..\plugins\ludoc\ludoc.xh

Lucide.obj:         Lucide.cpp         makefile
luutils.obj:        luutils.cpp
clipbrd.obj:        clipbrd.cpp
pmsplitter.obj:     pmsplitter.cpp
pmtoolbar.obj:      pmtoolbar.cpp
toolbar.obj:        toolbar.cpp
pluginman.obj:      pluginman.cpp
pluginViewDlg.obj:  pluginViewDlg.cpp
fontsInfoDlg.obj:   fontsInfoDlg.cpp
docInfoDlg.obj:     docInfoDlg.cpp
findDlg.obj:        findDlg.cpp
progressDlg.obj:    progressDlg.cpp
aboutDlg.obj:       aboutDlg.cpp
printDlg.obj:       printDlg.cpp
print.obj:          print.cpp
settingsDlg.obj:    settingsDlg.cpp
lusettings.obj:     lusettings.cpp
docViewer.obj:      docViewer.cpp
indexWindow.obj:    indexWindow.cpp
intern.obj:         intern.cpp
messages.obj:       messages.cpp
linklab.obj:        linklab.c
wwbtn.obj:          wwbtn.c


MAKE.CFG: makefile
  copy &&|
-zq
-zp=4
-bm
-xs
-sg
-DVERSION="$(VERSION)"  
!if $(TEST)==1
-D__TEST__
!endif
-I..\sominc
-I..\plugins\ludoc
-DOS2
| MAKE.CFG >NUL
