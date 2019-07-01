; -----------------
; LUGBM.DLL exports
; -----------------

;
; Generalised Bitmap Module Lucide adapter
;
; Copyright (C) 2006-2012 Heiko Nitzsche
;
;   This software is provided 'as-is', without any express or implied
;   warranty.  In no event will the author be held liable for any damages
;   arising from the use of this software.
;
;   Permission is granted to anyone to use this software for any purpose,
;   including commercial applications, and to alter it and redistribute it
;   freely, subject to the following restrictions:
;
;   1. The origin of this software must not be misrepresented; you must not
;      claim that you wrote the original software. If you use this software
;      in a product, an acknowledgment in the product documentation would be
;      appreciated but is not required.
;   2. Altered source versions must be plainly marked as such, and must not be
;      misrepresented as being the original software.
;   3. This notice may not be removed or altered from any source distribution.

LIBRARY LUGBM INITINSTANCE TERMINSTANCE

DATA MULTIPLE NONSHARED READWRITE
CODE PRELOAD EXECUTEREAD

DESCRIPTION  '@#Arca Noae:${VERSION}_${BUILD}#@##1## ${VERSIONDATE} ${VERSIONTIME}      ${BUILDMACHINE}::EN:US:0:M:@@ GBM plugin for Lucide (LUGBM,GCC) Copyright (c) 2017 netlabs/Arca Noae 2006-2012 Heiko Nitzsche All rights reserved'

EXPORTS
  LuGbmDocumentNewClass
  LuGbmDocumentClassData=_LuGbmDocumentClassData
  LuGbmDocumentCClassData=_LuGbmDocumentCClassData
  createObject
  getSupportedExtensions
  getDescription
  isFileSupported


