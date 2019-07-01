:userdoc.
:docprof toc=123456.
:title.Generalised Bitmap Plugin for Lucide
.* rev 2016-09-22-001
.* ----------------------------------------------------------------------------
:h1 res=10001 name=gbm_intro
    x=left y=bottom width=100% height=100%.About the GBM plugin for Lucide
.*:artwork align=center name='lucidelogo.bmp'.
:p.The Generalised Bitmap Module (GBM) plugin for :hp2.Lucide:ehp2. is an
extension which provides access to all bitmap formats supported by :link
reftype=hd res=10004.GBM:elink.. The following :hp2.Lucide:ehp2. features are
currently supported by the plugin:

:ul compact.
:li.Read all bitmap formats supported by :link reftype=hd
res=10004.GBM.DLL:elink.
:li.Save loaded single-page bitmap in any format supported by :link reftype=hd
res=10004.GBM:elink.
:li.Multi-page bitmap files may be navigated within :hp2.Lucide:ehp2.
:li.Scaled bitmap preview
:li.Rotated bitmap preview
:li.Document information
:li.Thumbnail creation
:li.Selectable quality scaling algorithms for improved appearance vs
performance
:li.Background rendering for Multi-page images 
:eul.

:p.To use the plgin, the following prerequisites must be met&colon.

:ul compact.
:li.:hp2.Lucide:ehp2. 1.20 or higher
:li.:link reftype=hd res=10004.GBM.DLL:elink. (GBM Bitmap Format Handler)
version 1.50 or higher
:eul.

:nt.:link reftype=hd res=10004.GBM.DLL:elink. version 1.41 must not be used as
it contains a compiler optimization issue which reduces stability. When used
together with the GBM plugin for :hp2.Lucide:ehp2., :hp2.Lucide:ehp2. will
crash when opening JPEG bitmaps. Please upgrade to :link reftype=hd
res=10004.GBM.DLL:elink. version 1.50 or higher. Using the latest available
version is recommended.
:ent.

:p.:ul compact.
:li.:link reftype=hd res=10002.License:elink.
:li.:link reftype=hd res=10003.Installation:elink.
:li.:link reftype=hd res=10004.About GBM:elink.
:li.:link reftype=hd res=10005.Configuring GBM for Lucide:elink.
:li.:link reftype=hd res=10110.Notices:elink.
:eul.
:p.

.* ............................................................................
:h2 res=10002 name=gbm_license
    x=left y=bottom width=100% height=100%.License

:p.Copyright &bx0012. 2006-2012 Heiko Nitzsche

:p.This software is provided 'as-is', without any express or
implied warranty. In no event will the author be held liable for any damages
arising from the use of this software.

:p.Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

:dl tsize=3 break=none.
:dt.1. 
:dd.The origin of this software must not be misrepresented; you must not claim
that you wrote the original software. If you use this software in a product, an
acknowledgment in the product documentation would be appreciated but is not
required.
:dt.2. 
:dd.Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
:dt.3. 
:dd.This notice may not be removed or altered from any source distribution.
:edl.

.* ............................................................................
:h2 res=10003 name=gbm_installation
    x=left y=bottom width=100% height=100%.Installation

:p.Simply copy lugbm.dll into the :hp2.Lucide:ehp2. installation directory.
Please check the requirements listed for :link reftype=hd
res=10004.GBM.DLL:elink. above. Copy :link reftype=hd res=10004.GBM.DLL:elink.
either into the :hp2.Lucide:ehp2.installation directory beside lugbm.dll or put
it somewhere in LIBPATH (defined in CONFIG.SYS). The last option is recommended
if gbm.dll is also required by other programs.

:note text='Note 1'. :hp2.Lucide:ehp2. contains a bug in handling plugins which
provide the same document format support. It can be prevented by ensuring that
only one of these plugins is loaded, otherwise strange effects when navigating
between documents will occur. One prominent example is lujpeg.dll (which comes
with :hp2.Lucide:ehp2. and provides JPEG support) and lugbm.dll (which also
provides JPEG support). In short, when you want to use lugbm.dll please rename
lujpeg.dll to, for instance, lujpeg.dll_, so that :hp2.Lucide:ehp2. does not
load it. You can check the loaded plugins in the Lucide Document menu.

:note text='Note 2'. The zoom quality used by the plugin to display images, as
well as other settings, may be customized via the configuration file:
lugbm.cfg. Simply create the configuration file right beside the plugin DLL
(lugbm.dll) using your favorite ASCII text editor, and set the options. There
is also an example file included in the package. You may use the &numsign. sign
to start a comment. Everything after this sign is ignored on this line. If the
configuration file does not exist, the plugin will use the default options. 


.* ............................................................................
:h2 res=10004 name=gbm_about
    x=left y=bottom width=100% height=100%.About GBM

:p.:hp2.Overview:ehp2.

:p.The Generalised Bitmap Module (GBM) is a library capable of loading and
saving bitmap files in a variety of popular bitmap file formats. Programs may
be written to use this library, and thus be able to access a variety of file
formats without actually knowing in what format the pictures are, or any
details about file format itself.

:p.Additionally, the GBM package contains of a number of other components:

:ul compact.
:li.For all platforms&colon.
:ul compact.
:li.Some pieces of code that perform common operations on bitmap data such as
reflection, X-Y transposition, rotation, cropping, scaling, halftoning,
error-diffusing, palette mapping, and colour space mapping. These operations
are available as ready to use C libraries.
:li.Some command line programs which use the above code.
:eul.
:li.For OS/2, eComStation, ArcaOS, and Windows only&colon.
:ul compact.
:li.Plugin for the web browsers Netscape, Mozilla, Firefox, and SeaMonkey.
:eul.
:li.For OS/2, eComStation, and ArcaOS only&colon.
:ul compact.
:li.REXX libraries for loading and saving bitmap formats, scaling, reflecting,
rotating and colour conversions.
:li.A PM bitmap viewer and an editor supporting all the above functionality.
:li.Plugin for the Lucide Document Viewer
:eul.
:eul.

:p.:hp2.Platforms:ehp2.

:p.GBM is available for several platforms, namely OS/2, Windows, Linux, DOS,
and AIX.

:nt.The current version is so far only supported on OS/2 (32bit), Windows
(32/64bit) and Linux (32/64bit), though it shouldn't be a problem to compile it
for other x86/X64 platforms as it uses pure ANSI C/C++ code. You can get
versions for other platforms supporting a smaller feature set on the homepage
of the initial author Andy Key.
:ent.

:p.:hp2.Enhancements:ehp2.

:p.Many enhancements have been applied compared to the original version
provided by Andy Key&colon.

:p.:hp5.GBM format handler library:ehp5.

:ul compact.
:li.PNG (new codec)
:ul compact.
:li.based on latest Libpng + APNG patch
:li.supports all RGB/Gray color depths (1,2,4,8,16,24,32,48,64bpp)
:li.supports transparency and alpha channel
:li.supports PNG provided and custom backgrounds
:li.supports reading animated PNGs
:eul.
:li.TIF (replacement codec)
:ul compact.
:li.based on latest Libtiff
:li.supports multipage bitmaps
:li.supports most RGB/Gray color depths (1,2,4,8,16,24,32,48,64bpp), partly
CMYK (8/16bpp)
:li.supports alpha channel (with rendering against a custom background)
:li.Compression schemes&colon. LZW, PackBits, ThunderScan, NeXT, JPEG, CCITT,
Deflate, Adobe Deflate, JBIG
:eul.
:li.PBM (new codec)
:ul compact.
:li.reads and writes 1bpp black/white bitmaps
:li.supports format types P1 (ASCII) and P4 (binary)
:li.supports multipage P4 bitmaps
:eul.
:li.PGM (enhanced codec)
:ul compact.
:li.reads and writes 8 and 16bpp grey bitmaps
:li.supports format types P2 (ASCII) and P5 (binary)
:li.supports multipage P5 bitmaps
:eul.
:li.PPM (replacement codec)
:ul compact.
:li.reads and writes 24 and 48bpp RGB bitmaps
:li.supports format types P3 (ASCII) and P6 (binary)
:li.supports multipage P6 bitmaps
:eul.
:li.PNM (new codec)
:ul compact.
:li.PNM consolidates the formats PBM, PGM and PPM under one extension
:li.supports format types P1,P2,P3 (ASCII) and P4,P5,P6 (binary)
:li.supports multipage P4,P5 and P6 bitmaps
:eul.
:li.BMP (enhanced codec)
:ul compact.
:li.reads also RLE24 encoded OS/2 bitmaps
:li.reads also Windows MultiMedia bitmaps (RGB, BITFIELDS&colon. 16bpp, 32bpp)
:li.handles now 1bpp color bitmaps rather than always mapping them to
black/white
:eul.
:li.JPEG (enhanced codec)
:ul compact.
:li.updated to latest IJG JPEG library
:li.reads also YCCK and CMYK encoded JPEGs
:li.writes also grayscale JPEGs (8bpp)
:li.some new write options are available like smoothing and optimizing
:eul.
:li.JPEG2000 (new codec)
:ul compact.
:li.based on latest OpenJPEG library
:li.supports RGB/YUV/Gray color depths (8,16,24,48 bpp)
:li.writes images with lossless or lossy compression
:eul.
:li.TGA (enhanced codec)
:ul compact.
:li.reads also horizontally flipped TGAs
:li.reads TGAs with 1 bpp and 4 bpp
:li.reads TGAs with alpha channel (32 bpp)
:li.writes TGAs with alpha channel (32 bpp)
:li.writes TGAs with RLE compression
:eul.
:li.XPM (new codec)
:ul compact.
:li.reads and writes XPM2 and XPM3 formats without extensions (no XPM1, XPM2C)
:li.supports RGB files with hex or X11 symbolic coded colours (4,8,12,16 bit
per R,G or B)
:li.supports transparency
:eul.
:li.JBIG (new codec)
:ul compact.
:li.based on latest JBIG-Kit library
:li.supports also Gray color depths (1,8 bpp)
:eul.
:li.RAW (new codec)
:ul compact.
:li.based on latest LibRaw library
:li.reads almost all dcraw supported RAW formats including DNG (but no Foveon
support)
:li.supports many dcraw import parameters for RAW conversion
:eul.
:li.Many fixes and some API enhancements (e.g. query page count)
:li.REXX adapter DLL available for OS/2 (GBMRX)
:eul.

:p.:hp5.Command line tools (not part of the plugin):ehp5.

:ul compact.
:li.gbmsize, gbmhdr, gbmref, gbmsub, gbmgamma
:ul compact.
:li.now also support 32, 48 and 64bpp (with/without alpha channel)
:eul.
:li.gbmsize now supports also multithreaded resampled scaling with several
filters
:ul compact.
:li.Nearest Neighbor, Bilinear, Bell, BSpline, Mitchell, Lanczos, Blackman,
Catmull/Rom, Quadratic, Gaussian, Kaiser
:eul.
:li.gbmconv added (format converter)
:li.gbmver added (helps analyzing all installed GBM DLLs and provides version
compatibility hints for users)
:li.enhanced command line parser to fix some issues when filenames with comma
where specified
:eul.


:p.More information about GBM may be found in the homepage&colon.
http&colon.//heikon.home.tlink.de/

.* ............................................................................
:h2 res=10005 name=gbm_config
    x=left y=bottom width=100% height=100%.Configuring the GBM plugin for Lucide

:p.The following configuration options may be set in lugbm.cfg&colon.


:p.:ul compact.
:li.:link reftype=hd res=10006.scaler:elink.
:li.:link reftype=hd res=10050.progressive_render_pages:elink.
:eul.
:p.

.* ............................................................................
:h3 res=10006 name=gbm_config_scaler
    x=left y=bottom width=100% height=100%.scaler

:p.:hp2.scaler:ehp2.

:p.This defines the scaling (sizing) algorithm

:p.By default, the simple scaler is used. This is the fastest scaler which uses
less resources compared to all other scalers while providing acceptable quality
for normal viewing.

:p.:hp2.Syntax&colon.:ehp2.

:xmp.
scaler&eq.{:link reftype=hd res=10010.simple:elink.|:link reftype=hd res=10011.nearestneighbor:elink.|:link reftype=hd res=10012.bilinear:elink.|:link reftype=hd res=10013.bell:elink.|:link reftype=hd res=10014.bspline:elink.|:link reftype=hd res=10015.quadratic:elink.|
           :link reftype=hd res=10016.gaussian:elink.|:link reftype=hd res=10017.mitchell:elink.|:link reftype=hd res=10018.catmullrom:elink.|:link reftype=hd res=10019.lanczos:elink.|:link reftype=hd res=10020.blackman:elink.|:link reftype=hd res=10021.kaiser:elink.}
:exmp.

:p.:hp2.Default&colon.:ehp2.

:xmp.
scaler&eq.simple
:exmp.


:p.Related&colon.

:p.:ul compact.
:li.:link reftype=hd res=10010.simple:elink.
:li.:link reftype=hd res=10011.nearestneighbor:elink.
:li.:link reftype=hd res=10012.bilinear:elink.
:li.:link reftype=hd res=10013.bell:elink.
:li.:link reftype=hd res=10014.bspline:elink.
:li.:link reftype=hd res=10015.quadratic:elink.
:li.:link reftype=hd res=10016.gaussian:elink.
:li.:link reftype=hd res=10017.mitchell:elink.
:li.:link reftype=hd res=10018.catmullrom:elink.
:li.:link reftype=hd res=10019.lanczos:elink.
:li.:link reftype=hd res=10020.blackman:elink.
:li.:link reftype=hd res=10021.kaiser:elink.
:eul.

.* ............................................................................
:h4 res=10010 name=gbm_config_scaler_simple
    x=left y=bottom width=100% height=100%.simple

:p.The simple scaling algorithm uses pixel skipping and/or replication to
re-size the current image. This is the least-resource-intensive scaling option
and is the default. No resampling is performed.

.* ............................................................................
:h4 res=10011 name=gbm_config_scaler_nearestneighbor
    x=left y=bottom width=100% height=100%.nearestneighbor


.* ............................................................................
:h4 res=10012 name=gbm_config_scaler_bilinear
    x=left y=bottom width=100% height=100%.bilinear


.* ............................................................................
:h4 res=10013 name=gbm_config_scaler_bell
    x=left y=bottom width=100% height=100%.bell


.* ............................................................................
:h4 res=10014 name=gbm_config_scaler_bspline
    x=left y=bottom width=100% height=100%.bspline
    

.* ............................................................................
:h4 res=10015 name=gbm_config_scaler_quadratic
    x=left y=bottom width=100% height=100%.quadratic

.* ............................................................................
:h4 res=10016 name=gbm_config_scaler_gaussian
    x=left y=bottom width=100% height=100%.gaussian

.* ............................................................................
:h4 res=10017 name=gbm_config_scaler_mitchell
    x=left y=bottom width=100% height=100%.mitchell

.* ............................................................................
:h4 res=10018 name=gbm_config_scaler_catmullrom
    x=left y=bottom width=100% height=100%.catmullrom

.* ............................................................................
:h4 res=10019 name=gbm_config_scaler_lanczos
    x=left y=bottom width=100% height=100%.lanczos

.* ............................................................................
:h4 res=10020 name=gbm_config_scaler_blackman
    x=left y=bottom width=100% height=100%.blackman

.* ............................................................................
:h4 res=10021 name=gbm_config_scaler_kaiser
    x=left y=bottom width=100% height=100%.kaiser

.* ............................................................................
:h3 res=10050 name=gbm_config_progressive_render_pages
    x=left y=bottom width=100% height=100%.progressive_render_pages

:p.:hp2.progressive_render_pages:ehp2.

:p.This defines the number of pages of a multi-page image which should be
calculated in the background for faster drawing (at the cost of more memory).
This figure &divide. 2 (progressive_render_pages/2) &eq. the number of pages
before and after to be calculated in the background. If not specified, no
progressive rendering will be used (at the cost of speed).

:p.:hp2.Syntax&colon.:ehp2.

:xmp.
progressive_render_pages&eq.:hp1.an integer:ehp1.
:exmp.

:p.:hp2.Default&colon.:ehp2.

:xmp.
progressive_render_pages&eq.2
:exmp.

.* ............................................................................
:h2 res=10110 name=notices
    x=left y=bottom width=100% height=100%.Notices

:p.JBIG support (extension to base version)

:p.The Open Source (GPL) library JBIG-Kit 2.0 can be used to build GBM with
JBIG support. Try looking for the library at&colon.

:p.http&colon.//www.cl.cam.ac.uk/~mgk25/jbigkit/

:p.I (Heiko Nitzsche) have donated gbmjbg.c to GBM. This file allows GBM to use
the JBIG-Kit 2.0 library.

:p.GBM may be compiled up either with or without JBIG support. If you use the
JBIG enabled variety of GBM in your project, please beware of the patenting
issues&colon.

:p.Users of Non-GPL compatible software linking against GBM.DLL should study
potential licensing issues. GBM.DLL can be built without JBIG support by
disabling it in the main GBM makefile (e.g. gbm\makefile.xxx\makefile.yyy) if
necessary.

:p.This code has been tested on OS/2, Linux and Windows.

:p.JPEG support

:p.The Independant JPEG Group have generously allowed others to use their
source code to their JPEG handling library. The only condition of use is that
the IJG must be credited for their work. Try looking for this library at&colon.

:p.http&colon.//www.ijg.org/files/jpegsr8d.zip.

:p.Martin Lisowski has generously donated his gbmjpg.c to GBM. This file allows
GBM to use the IJG 8d library. I (Heiko Nitzsche) implemented some
enhancements.

:p.GBM may be compiled up either with or without JPEG support. If you use the
JPEG enabled variety of GBM in your project, you must credit the IJG. This code
has been tested on OS/2, Linux and Windows.

:p.JPEG2000 support (extension to base version)

:p.The Open Source library OpenJPEG 1.5.1 can be used to build GBM with
JPEG2000 support. Try looking for the library at&colon.

:p.http&colon.//www.openjpeg.org

:p.I (Heiko Nitzsche) have donated gbmj2k.c to GBM. This file allows GBM to use
the OpenJPEG 1.5.1 library.

:p.GBM may be compiled up either with or without JPEG2000 support. If you use
the JPEG2000 enabled variety of GBM in your project, you should credit the Open
Source project for OpenJPEG. This code has been tested on OS/2, Linux and
Windows.

:p.PNG support (extension to base version)

:p.The official Open Source reference libraries Libpng 1.5.13 and Zlib 1.2.7
can be used to build GBM with PNG support. In order to support animated PNGs
the APNG patch may be used. Try looking for these libraries at&colon.

:p.http&colon.//www.libpng.org
.br
http&colon.//www.zlib.org
.br
http&colon.//sourceforge.net/projects/libpng-apng/

:p.I (Heiko Nitzsche) have donated gbmpng.c and gbmmap.c to GBM. These files
allow GBM to use the Libpng 1.5.13 library.

:p.GBM may be compiled up either with or without PNG support. If you use the
PNG enabled variety of GBM in your project, you should credit the Open Source
projects for Libpng and Zlib. This code has been tested on OS/2, Linux and
Windows.

:p.TIF support (replacement of base version)

:p.The official Open Source reference library Libtiff 3.9.5 can be used to
build GBM with TIF support. Required are Zlib 1.2.7, the IJG Group lib IJG 8d
that is also used for standard JPEG support in GBM and the JBIG-Kit 2.0 library
that is also used for standard JBIG support in GBM. Try looking for these
libraries at&colon.

:p.http&colon.//www.remotesensing.org/libtiff
.br
http&colon.//www.zlib.org
.br
http&colon.//www.ijg.org/files/jpegsr8d.zip.
.br
http&colon.//www.cl.cam.ac.uk/~mgk25/jbigkit/

:p.I (Heiko Nitzsche) have donated gbmtif.c and gbmmap.c to GBM. These files
allow GBM to use the Libtiff 3.9.5 library.

:p.GBM may be compiled up either with or without TIF support. If you use the
TIF enabled variety of GBM in your project, you should credit the Open Source
projects for Libtiff, Zlib, IJG and JBIG-Kit. This code has been tested on
OS/2, Linux and Windows.

:p.PBM support (extension to base version)

:p.I (Heiko Nitzsche) have donated gbmpbm.c to GBM. This file allows GBM to
read and write black/white PBM (binary P4, ASCII P1) files. This code has been
tested on OS/2, Linux and Windows.

:p.PGM support (enhancement of base version)

:p.I (Heiko Nitzsche) have donated gbmpgm.c to GBM. This file allows GBM to
read and write 8bpp and 16bpp greyscale PGM (binary P5, ASCII P2) files. This
code has been tested on OS/2, Linux and Windows.

:p.PPM support (replacement of base version)

:p.I (Heiko Nitzsche) have donated gbmppm.c to GBM. This file allows GBM to
read and write unpalettised 24 and 48 bpp multipage RGB PPM (binary P6, ASCII
P3) files. This code has been tested on OS/2, Linux and Windows.

:p.PNM support (extension to base version)

:p.I (Heiko Nitzsche) have donated gbmpnm.c to GBM. This file allows GBM to
read and write PNM (binary P4,P5,P6, ASCII P1,P2,P3) files. This code has been
tested on OS/2, Linux and Windows.

:p.XPM support (extension to base version)

:p.I (Heiko Nitzsche) have donated gbmxpm.c and gbmxpmcn.c to GBM. These files
allow GBM to read and write XPM2 and XPM3 files. This code has been tested on
OS/2, Linux and Windows.

:p.Camera RAW support (extension to base version)

:p.The Open Source library LibRaw 0.14.7 can be used to build GBM with RAW
support. Try looking for this library at&colon.

:p.http&colon.//www.libraw.org

:p.I (Heiko Nitzsche) have donated gbmraw.c to GBM. This file allows GBM to use
the LibRaw 0.14.7 library.

:p.GBM may be compiled up either with or without RAW support. If you use the
RAW enabled variety of GBM in your project, you should credit the Open Source
project for LibRaw. LibRaw 0.14.7 is based on DCRAW 9.15 from Dave Coffin. This
code has been tested on OS/2, Linux and Windows.
:euserdoc.
