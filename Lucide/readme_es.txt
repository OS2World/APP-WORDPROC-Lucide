:: Acerca de Lucide ::

Lucide es un visor de documentos con arquitectura de plugins y soporte para
varios formatos de archivo.

Provee una arquitectura de plugins basada en SOM la que permite a programadores
de terceras partes a¤adir f cilmente m s plugins.


:: Plugins ::

   Tipo de archivo soportado   Caracter¡sticas soportadas
  --------------------------------------------------------------------------
         PDF                   Escalado, Rotaci¢n, Navegaci¢n, Selecci¢n de
                               texto, B£squedas, Renderizado as¡ncrono,
                               impresi¢n PostScript

         DJVU                  Escalado, impresi¢n PostScript

         JPG                   Escalado
  --------------------------------------------------------------------------


:: Requisitos ::

Lucide requiere lo siguiente:

  - libc 0.6.3:
    - ftp://ftp.netlabs.org/pub/gcc/libc-0.6.3-csd3.zip (formato zip)
      or ftp://ftp.netlabs.org/pub/gcc/libc-0_6_3-csd3.wpi (formato WarpIn)
  - gcc442.dll:
    - http://download.smedley.info/gcc442.zip (formato zip)
      or ftp://ftp.netlabs.org/pub/qt4/gcc-lib-4_4_2-20091204.wpi (formato WarpIn)


Opcional: para poner texto unicode en el portapapeles  en programas compatibles
con el formato de OpenOffice.org, necesita instalar el paquete UClip (soporte
mejorado de portapapeles para OS/2, instalado por defecto en eComStation 2.0
RC1 y superiores):

  - http://hobbes.nmsu.edu/cgi-bin/h-search?key=UClip

    
La impresi¢n PostScript requiere una impresora PostScript (pscript.drv).


Para ver una lista completa de caracter¡sticas y mejoras consulte el TRAC de
Lucide en:

  http://svn.netlabs.org/lucide/

Si encuentra fallos, reg¡strelos en el TRAC, vea:

  http://svn.netlabs.org/lucide/newticket

Por favor, aseg£rese de que selecciona la versi¢n y el componente correctos
para su ticket.


:: Problemas conocidos/limitaciones ::

General: la impresi¢n de pares/impares no est  disponible para impresi¢n
postscript.
          ( http://svn.netlabs.org/lucide/ticket/87#comment:4 )


:: Comandos de tuber¡a ::

La primera instancia de Lucide crear  una tuber¡a con nombre \PIPE\LUCIDE. 
Puede enviar los siguientes comandos a esa tuber¡a:

$prev              - cambiar  a la p gina anterior
$next              - cambiar  a la p gina siguiente
$presentation      - cambiar  a presentaci¢n (incluso minimizado)
$minimize          - minimizar  Lucide (incluso en pantalla completa)
$rotate            - rotar  90ø en el sentido de las agujas del reloj
$zoomin            - aumentar  el zoom
$zoomout           - disminuir  el zoom
$zoomoriginal      - ampliar  o reducir  al tama¤o normal

Esto puede ser £til para presentaciones con un control remoto.


:: Licencia hasta la versi¢n 1.21 ::

La versi¢n 1.21 y anteriores est n licenciadas para su uso exclusivo con
eComStation. No se le permite distribuir el producto subi‚ndolo a servidores
p£blicos de Internet o hacerlo disponible p£blicamente por otros medios.


:: Licencia para versi¢n 1.3.0 y superiores ::

Comenzando con la versi¢n 1.3.0, Mensys BV y Serenity Systems International
han llegado al acuerdo de abrir el c¢digo de Lucide, mientras siguen
invirtiendo en el producto. Netlabs.org desea expresar su gratitud hacia
Mensys BV y Serenity Systems International.

Lucide as of version 1.3.0 is released and distributed under CDDL/LGPL.


:: Licencia de plugins ::
Los plugins son distribuidos bajo licencias CDDL/LGPL o GPL, dependiendo del
plugin. Vea http://svn.netlabs.org/lucide/ para m s informaci¢n y c¢digo
fuente.


:: Enlaces ::

http://www.netlabs.org
http://www.ecomstation.com


:: Copyright ::

(c) 2006-2007 por Eugene Romanenko, netlabs.org
(c) 2010 por Dmitry A. Kuminov, netlabs.org
    en cooperaci¢n con Serenity Systems International