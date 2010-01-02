@echo off
REM *********************************************
REM Setup the environment to build lucide
REM for OS/2
REM Change the paths for WATCOM, GCC and
REM the toolkit
REM
REM RBRi 2009
REM *********************************************

REM ----------------------------------------------
REM Change here
REM ----------------------------------------------

SET WATCOM=d:\progs\develop\watcom_18
SET GCC=d:\progs\develop\gcc\usr
SET OS2_TK=d:\progs\develop\OS2TK45_2
SET TOOLS=D:\work\netlabs_svn\lucide\tools\b_make


REM ----------------------------------------------
REM - don't touch the rest -----------------------
REM ----------------------------------------------

SET PATH=%WATCOM%\BINP;%WATCOM%\BINW;%PATH%;%OS2_TK%\som\bin;
SET INCLUDE=.;%WATCOM%\H;%WATCOM%\H\OS2;%OS2_TK%\H
SET HELP=%WATCOM%\BINP\HELP;%HELP%
SET BOOKSHELF=%WATCOM%\BINP\HELP;%BOOKSHELF%
SET BEGINLIBPATH=%WATCOM%\BINP\DLL;%OS2_TK%\som\lib;
SET LIB=%OS2_TK%\som\lib;
SET SMINCLUDE=%OS2_TK%\idl;%OS2_TK%\som\include;

REM ----------------------------------------------
REM init gcc env
REM ----------------------------------------------
call %GCC%\bin\gccenv.cmd %GCC%

SET EMXOMFLD_TYPE=LINK386
SET EMXOMFLD_LINKER=link386.exe


REM ----------------------------------------------
REM add the borland make tool to the path
REM ----------------------------------------------
SET PATH=%TOOLS%;%PATH%

