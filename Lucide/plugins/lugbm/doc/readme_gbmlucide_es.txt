M¢dulo GBM para Lucide 1.44
---------------------------

GBM es el acr¢nimo de Generalised Bitmap Module.

Nos gustar°a agradecer a Heiko Nitzsche, el desarrollador original de este
programa, permitirnos incluirlo con Lucide e integrarlo en el marco de
desarrollo de Lucide.

êste es un m¢dulo para el visor de documentos Lucide, disponible para ArcaOS,
eComStation y OS/2, que extiende sus capacidades para poder leer los formatos
de imagen soportados por GBM.DLL.

Funciones soportadas:
* informaci¢n del documento
* cargar todos los formatos soportados por GBM
* guardar la imagen cargada si s¢lo tiene una p†gina
* ver im†genes multip†gina (archivos con varias im†genes)
* cargar p†gina de imagen a petici¢n
* escalado y rotaci¢n
* creaci¢n de miniaturas de archivo
* algoritmo de escalado de alta calidad
* representaci¢n en segundo plano configurable para cambio de p†ginas r†pido
y desplazamiento entre p†ginas continuo

Para poder usarlo, se necesita lo siguiente:
- Lucide RC1 o posterior
- GBM.DLL versi¢n 1.42 o posterior (Manipulador de im†genes de GBM)
  (las versiones anteriores funcionar†n pero fallar†n las solicitudes de
   n£mero de im†genes en el archivo, no se da soporte a GBM.DLL 1.41)
- Le recomendamos instalar GBMDLL 1.76 del repositorio RPM Netlabs-rel
  mediante el mandato Æyum install GBMDLLØ o utilizando GPAN (ANPM).

Encontrar† m†s informaci¢n sobre este paquete y GBM en general en
http://heikon.home.tlink.de o la informaci¢n inclu°da. M†s informaci¢n sobre
Lucide en http://svn.netlabs.org/lucide/
All° encontrar† tambiÇn el c¢digo fuente de este m¢dulo.


Instalar GBM para Lucide
------------------------
Use el instalador WarpIN de Lucide y seleccione instalar el paquete
correspondiente. Aseg£rese de que gbm.dll queda instalado en su LIBPATH (ver
m†s arriba y el archivo lÇame de Lucide).

Licencia
--------

Copyright ∏ 2006-2012 Heiko Nitzsche
          ∏ 2017-2018 netlabs.org en colaboraci¢n con Arca Noae, LLC

  Este programa se suministra Ætal cualØ, sin ninguna garant°a expresa o
  impl°cita. Bajo ninguna circunstancia se exigir† al autor responsabilidad
  por ning£n da§o que pueda resultar del uso de este programa.

  Se concede permiso a cualquiera a utilizar este programa para cualquier
  prop¢sito, incluidas aplicaciones comerciales y alterarlo y redistribuirlo
  libremente, con las siguientes restricciones:

  1. Se prohibe distorsionar el origen de este programa; no puede vd. afirmar
     que escribi¢ el programa original. Si lo utiliza en un producto propio,
     se agradecer°a un reconocimiento en la documentaci¢n, aunque no se exige.
  2. Las versiones alteradas del c¢digo fuente deben denominarse como tales sin
     ambages, y se prohibe presentarlas como la versi¢n original del programa.
  3. No se puede retirar o alterar este aviso en ninguna distribuci¢n del c¢digo
     fuente.


Contacto
--------
https://trac.netlabs.org/lucide/

Informes de errores
https://trac.netlabs.org/lucide/newticket

Consulte el archivo lÇame de Lucide para m†s opciones de contacto.


Historial de versiones (en espa§ol s¢lo desde la v. 1.42.)
----------------------------------------------------------

27-Jun-2006  <b>NEW:</b> GBM plugin for Lucide (LUGBM.DLL version 1.0 beta 1)
             * Initial public beta

30-Jun-2006  GBM plugin for Lucide (LUGBM.DLL version 1.0 beta 2)
             * Fixes for the most urgent issues
               - file extension list too long for file dialog (only keep the first extension)
                 which causes a cutted list of shown file extensions and a crash on pressing
                 Cancel in the file dialog (buffer overflow in Lucide)
             * Add error message reporting to load_file())

16-Jul-2006  GBM for Lucide 1.00 (LUGBM.DLL version 1.00 final)
             - It requires Lucide 1.2 due to plugin API changes
             - Added document info
             - Added rotated rendering
             - Added delayed loading of bitmap data (on user request)
             - Support transparent caching for fast scrolling of a scaled view

31-Jul-2006  GBM for Lucide 1.10 (LUGBM.DLL)
             - Save loaded bitmap in any GBM supported format if it has only one page
               (GBM does not support multipage save, requires Lucide beta 2.1)
             - Remove code for rendering to a buffer, rendering is now always via HPS
             - Sync to latest common code shared with the Mozilla plugin
               updated common code
             - Now supports dynamic lookup of GBM.DLL either via LIBPATH
               or look into the directory where lugbm.dll is located.

16-Aug-2006  GBM for Lucide 1.20 (LUGBM.DLL)
             - Adapt makefiles to use now the patched SOM header files
               part of the Lucide plugindev pack.
             - Fix for issue that GBM.DLL is not found when LIBPATHSTRICT (or RUN!)
               is used. Thanks to Rich Walsh for the background info about the root cause.
             - Add bldlevel info
             - Makefiles now support activating debug compile without editing them.
               Just use nmake or wmake with parameter debug=on

31-Aug-2006  Version 1.21
             - When reporting an extended error message after a loading error
               sprintf reads from an illegal address due to wrong parameter
               (int instead char pointer)

08-Sep-2006  Version 1.22
             - 1bpp bitmaps were shown inverted (colors swapped)

28-Nov-2006  Version 1.23
             - Improved detection of bitmap file formats
             - Adapt loadFile() and renderToPS() for Lucide 1.0 API
               (error reporting added to the API)
             - OpenWatcom 1.6 is now supported
               Note: In the Lucide plugin linker description file the exports have to be adapted
                     if OpenWatcom before 1.6 is used for compile (see the remarks in the file
                     lugbm.lnk)

20-Jan-2007  Version 1.24
             - Some fixes for upcoming Lucide RC1
             - Protect getPageSize() against writing to width or height
               for the unusual case they're NULL.
             - Don't write to error/errorCode pointer if it is NULL.
               This is a bit strange as one would expect that they
               would be always valid.

06-Sep-2007  Version 1.30
             - Add support for Lucide 1.02 API extension isFileSupported()
               to allow file format detection via file content
             - Add support for creating thumbnails in EAs
             - Report all available extensions again as the issue with
               Lucide file dialog has been resolved since Lucide 1.10.
               So this plugin version should not be used with older Lucide!
             - 8bpp grayscale and true color images are now scaled with a high quality
               algorithm to improve appearance.

04-Nov-2007  Version 1.31
             - Resampling scaler with improved accuracy

27-Jan-2008  Version 1.32
             - Resampling scaler now supports all grayscale bitmaps <=8bpp

08-Feb-2008  Version 1.33
             - Move HPS rendering code to common package GbmRenderer
               to save memory (now renders directly from cache buffer)
               without temporary subrectangle buffer
             - Allocate memory from high memory for bitmap data to
               stretch limit for out-of-memory errors
               (requires kernel with high memory support)
             - Custom settings definable in lugbm.cfg file
               (so far scaler={simple,nearestneighbor,bilinear,bell,bspline,mitchell,lanczos})
               The default scaler is simple to allow fast scaling on less powerful systems.

03-Jun-2008  Version 1.34
             - Wrong cache preparation for 1bpp bitmaps when simple scaler is active
               (no upconversion to 8bpp as for resampling scaler required)
             - New user configurable background rendering (option progressive_render_pages)

28-Aug-2008  Version 1.35
             - New user configurable background rendering (option progressive_render_pages)
               -> Improves continous scrolling/page switching performance, especially when
                  using high quality scaler. On dual-core systems the performance gain
                  will be much higher than on single-core systems.
               -> Always progressive_render_pages/2 pages backward and forward will
                  be calculated in background.
             - For lengthy operations now the hourglas mouse pointer is shown
             - The size and color depth of the current page is shown behind the format
               name in the document information dialog
             - Fix potential write to const memory object when building extension list

21-Sep-2008  Version 1.36
             - changes for GCC compile support

27-Sep-2008  Version 1.37
             Enforce struct padding to 4 byte for compiler independent compatibility

22-Feb-2009  Version 1.38
             Fix some incompatibilites with new OpenWatcom 1.8 compiler

21-May-2009  Version 1.39
             - Fix rendering of B&W bitmaps as PM needs special data ordering for it.

22-Apr-2010  Version 1.40
             - Fix huge memory consumption when doing background rendering
               of multiple pages that have a big size difference.

20-Aug-2010  Version 1.41
             - Quality fine tuning of resampling scalers
               (flat colour areas are now preserved to get better quality)
             - Some minor internal changes on the core classes shared with Mozilla
               plugin for the Windows port
             - Fix output size shift which lead to slightly distorted drawings
             - Fix wrong size calculation in background rendering of multiple pages
               which causes uneffective prefetching

02-Nov-2010  Versi¢n 1.42
             - A§adidos filtros de escalado con re-muestreo:
               * blackman, catmullrom, cuadr†tico, gaussiano, k†iser
             - Soluci¢n final al muarÇ generado por errores de redondeo en los
               c†lculos de contribuci¢n.

28-Oct-2012  Versi¢n 1.43
             * Integrada gbmmthrd.lib actualizada (ver doc de gbm)

11-Mar-2017  Versi¢n 1.44 Compilada por Netlabs (Gregg Young)
             - Cambio a cabeceras SOM del juego de herramientas de IBM
             - Cambio a la versi¢n actual de ludoc.lib
             - Cambio a cabeceras del juego de herramientas de desarrollo de IBM
             - Compilada con Kbuild y GCC 4.92
