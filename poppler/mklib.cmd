@echo off
if exist poppler.lib del poppler.lib
wlib poppler.lib + mypoppler\goo\libgoo.lib mypoppler\splash\libsplash.lib mypoppler\fofi\libfofi.lib mypoppler\poppler\libpoppler.lib freetype2\src\ft2lib.lib fc-emulate-os2\fontconfig\libfcos2.lib
