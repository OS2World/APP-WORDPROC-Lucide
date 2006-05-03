@echo off
if exist poppler.lib del poppler.lib
wlib poppler.lib + mypoppler\goo\libgoo.lib mypoppler\splash\libsplash.lib mypoppler\fofi\libfofi.lib mypoppler\poppler\libpoppler.lib fontconfig-2.3.2-os2\src\fontconfig.lib expat-1.95.8\lib\expat.lib freetype-2.1.10\src\ft2lib.lib
