:: Acerca de Lucide ::

Lucide es un visor de documentos con arquitectura modular que soporta distintos
formatos de archivo.

La arquitectura de estos m�dulos o �plugins� est� basada en SOM, lo que permite
a terceros programadores a�adir f�cilmente soporte para m�s formatos.


:: M�dulos ::

   Tipos de archivo soportados  Funciones disponibles
  --------------------------------------------------------------------------
         PDF                    Escalado, rotaci�n, navegaci�n, selecci�n de
                                texto, b�squeda, representaci�n as�ncrona,
                                cumplimentado de formularios, impresi�n
                                PostScript

         DJVU                   Escalado, impresi�n PostScript

         JPG                    Escalado
  --------------------------------------------------------------------------

:: Comparaci�n con qPDFView ::

Tanto Lucide como qPDFView utilizan la misma biblioteca de ejecuci�n �poppler�
para mostrar los archivos PDF. Las diferencias internas entre los dos pogramas
pueden dar como resultado que un archivo determinado se abra con mayor rapidez
en un programa o en el otro. Tenemos la sensaci�n de que, en general, la
interfaz de Lucide tiene un estilo m�s parecido al de OS/2 -o nativo-, y encaja
mejor en el sistema operativo. Por supuesto, queda a la entera discreci�n del
usuario la elecci�n final de cu�l se ajusta mejor a sus necesidades.


:: Requisitos ::

Para instalar todos los prerrequesitos de Lucide en una sola operaci�n desde el
Gestor de Paquetes de Arca Noae, simplemente copie la siguiente lista de
paquetes y p�guela en el di�logo �Instalaci�n r�pida�:

libc libgcc1 libgcc-fwd libstdc++6 libsupc++6 poppler poppler-data libjpeg
djvulibre uclip

Si prefiere hacerlo desde el indicador de mandatos de yum, por favor teclee

yum install libc libgcc1 libgcc-fwd libstdc++6 libsupc++6 poppler poppler-data
libjpeg djvulibre uclip

y pulse Enter.


Espec�ficamente, Lucide requiere lo siguiente:

  - libc 0.6.6:
    - http://rpm.netlabs.org/release/00/zip/libc-0_6_6-38_oc00.zip (formato zip)
      o ftp://ftp.netlabs.org/pub/gcc/libc-0_6_6-csd6.wpi (formato WarpIn)
      o �yum install libc� (desde el repositorio netlabs-rel)
  - libcx 0.6.3
    - http://rpm.netlabs.org/release/00/zip/libcx-0_6_4-1_oc00.zip (formato zip)
       o �yum install libcx� (desde el repositorio netlabs-rel)
  - gcc492.dll:
    - ftp://ftp.netlabs.org/pub/gcc/gcc4core-1_3_1.wpi (formato WarpIn)
      o �yum install libgcc1 libgcc-fwd� (desde el repositorio netlabs-rel)

El m�dulo que permite a Lucide mostrar PDFs requiere lo siguiente:

    - poppler 0.59.0:
    - �yum install poppler� (desde el repositorio netlabs-rel)

Para mostrar los archivos DjVu, el m�dulo correspondiente necesita:

    - djvulibre 3.5.27:
    - �yum install djvulibre� (desde el repositorio netlabs-rel)

Para mostrar diversos formatos de imagen mapa de bits, el m�dulo
GBM necesita:

    - GBMDLL 1.76:
    - �yum install GBMDLL� (desde el repositorio netlabs-rel)
    - Instalado por omisi�n en ArcaOS 5.0.3 o m�s reciente
  
El m�dulo para JPEGs requiere:

    - libjpeg 8d:
    - �yum install libjpeg� (desde el repositorio netlabs-rel)
    - S�lo se necesita para el m�dulo JPG; GBM ya da soporte a JPG
    - No deber�a instalar JPG y GBM a la vez. (Se recomienda GBM.)

Opcional: para poner en el portapapeles texto unicode en formato compatible con
OpenOffice.org, necesita instalar el paquete UClip (soporte mejorado de
portapapeles para OS/2, instalado por omisi�n en eComStation 2.0 RC1 y
posteriores, as� como en ArcaOS Blue Lion):

  - http://hobbes.nmsu.edu/cgi-bin/h-search?key=UClip
    o �yum install uclip� (desde el repositorio netlabs-rel)

Opcional: para que funcionen las fuentes japonesas necesita el paquete
poppler-data.

  - �yum install poppler-data� (desde el repositorio netlabs-rel)


La impresi�n PostScript requiere una impresora PostScript (pscript.drv o
psprint.drv).


Para ver una lista completa de caracter�sticas y mejoras consulte el sistema de
seguimiento del desarrollo de Netlabs (TRAC) para Lucide en:

  https://trac.netlabs.org/lucide/

Si encuentra fallos, reg�strelos tambi�n en TRAC; consulte:

  https://trac.netlabs.org/lucide/newticket

Por favor, aseg�rese de que selecciona la versi�n y el componente correctos
para su informe de incidencias.


:: Problemas conocidos/limitaciones ::

Consulte: https://trac.netlabs.org/lucide/report/1


:: M�dulos de terceros ::

GBM (Generalised Bitmap Module) es una biblioteca para manipular muchos
formatos de imagen diferentes. Incluye un conjunto de herramientas de indicador
de mandatos muy �tiles para manipular im�genes y convertir formatos. En esta
versi�n se incluye soporte adicional para BMP, JPG, JP2, PNG, TIF, PBM, PGM,
PPM, PNM, XPM, JBG y RAW.

http://hobbes.nmsu.edu/h-search.php?key=gbmos2pm160_gbm176_lu143_moz147_bin_wpi

N.B.: Si utiliza GBM para mostrar im�genes JPG, es aconsejable desactivar el
m�dulo para JPG incluido con Lucide para evitar conflictos (vea el ticket #236).
Esto se puede hacer sin m�s que renombrar lujpeg.dll en el directorio de Lucide
a lujpeg.dl_ cuando Lucide no se est� ejecutando. Para restaurar el m�dulo para
JPG que se incluye, simplemente vuelva a renombrar el archivo e inicie Lucide.

:: Canalizaci�n de mandatos ::

La primera instancia de Lucide crear� el canal de comunicaci�n \PIPE\LUCIDE.
Por �l puede enviar a Lucide las siguientes �rdenes:

$prev              - cambiar� a la p�gina anterior
$next              - cambiar� a la p�gina siguiente
$presentation      - cambiar� a modo presentaci�n (incluso minimizado)
$minimize          - minimizar� Lucide (incluso en pantalla completa)
$rotate            - rotar� 90� en sentido horario
$zoomin            - aumentar� el tama�o
$zoomout           - disminuir� el tama�o
$zoomoriginal      - cambiar� al tama�o real

Esto puede resultar �til para presentaciones con control remoto.


:: Licencia hasta la versi�n 1.21 ::

La versi�n 1.21 y anteriores se publicaron bajo licencia para su uso exclusivo
con eComStation. No se permite distribuir el producto carg�ndolo en servidores
p�blicos de Internet o haci�ndolo disponible p�blicamente por ning�n otro
medio.


:: Licencia para versi�n 1.3.0 y superiores ::

Comenzando con la versi�n 1.3.0, Mensys BV y Serenity Systems International
han llegado al acuerdo de liberar el c�digo de Lucide, mientras contin�an
invirtiendo en el producto. Netlabs.org desea expresar su gratitud hacia Mensys
BV y Serenity Systems International.

Arca Noae, LLC ha accedido a patrocinar el desarrollo de Lucide desde la
versi�n 1.3.6 en adelante. Lucide contin�a siendo c�digo abierto bajo licencia
dual.

Lucide, en su versi�n 1.3.0, se publica y distribuye bajo licencia CDDL/LGPL.


:: Licencia de los m�dulos ::

Los m�dulos se publican bajo licencia CDDL/LGPL o GPL, dependiendo de cada
caso. Consulte http://svn.netlabs.org/lucide/ para m�s informaci�n y acceder al
c�digo fuente.


:: Enlaces ::

http://www.netlabs.org/
http://www.arcanoae.com/


:: Derechos de copia ::

� 2006-2007 por Eugene Romanenko, netlabs.org
� 2010-2011 por Dmitriy Kuminov, netlabs.org
  en colaboraci�n con Serenity Systems International
� 2016-2019 por netlabs.org
  en colaboraci�n con Arca Noae, LLC


