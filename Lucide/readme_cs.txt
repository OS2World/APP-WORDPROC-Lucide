:: O prohl¡§eŸi Lucide ::

Lucide je prohl¡§eŸ dokument… zalo§enì na modulech podporuj¡c¡ r…zn‚ form ty
soubor….

Poskytuje modul rn¡ architekturu zalo§enou na rozhran¡ SOM, co§ umo§åuje dalç¡m
program tor…m jednoduçe pýid vat dalç¡ moduly.


:: Moduly ::

   Podporovanì typ soubor…     Podporovan‚ funkcionality
  --------------------------------------------------------------------------
         PDF                   ZmØna velikosti, rotace, navigace, vìbØr
                               textu, hled n¡, asynchronn¡ vykreslov n¡,
                               tisk ve form tu PostScript

         DJVU                  ZmØna velikosti, tisk ve form tu PostScript

         JPG                   -
  --------------------------------------------------------------------------

:: Po§adavky ::

Program Lucide vy§aduje n sleduj¡c¡ bal¡ky:

  - libc 0.6.4:
  - ftp://ftp.netlabs.org/pub/gcc/libc-0.6.4-csd4.zip (form t zip)
    nebo ftp://ftp.netlabs.org/pub/gcc/libc-0.6.4-csd4.wpi (form t WarpIn)

  - gcc446.dll:
    - ftp://ftp.netlabs.org/pub/gcc/gcc4core-1_2_1.wpi (form t WarpIn)


Voliteln‚: chcete-li uschovat ve schr nce text v k¢dov n¡ unicode ve form tu
kompatibiln¡m s bal¡em OpenOffice.org, mus¡te nainstalovat bal¡k UClip
(rozç¡ýen  podpora schr nky syst‚mu OS/2, standardn¡ souŸ st syst‚mu
eComStation verze 2.0 RC1 a vyçç¡):

  - http://hobbes.nmsu.edu/cgi-bin/h-search?key=UClip
  
Voliteln‚: chcete-li pou§¡vat Japonsk‚ fonty, potýebujete bal¡Ÿek poppler-data.

  - Rozbalte 4 adres ýe z bal¡Ÿku dostupn‚ho na http://poppler.freedesktop.org
    do adres ýe %unixroot%/usr/local/share/poppler nebo do adres ýe
    obsahuj¡c¡ho nainstalovanì soubor lucide.exe.
  - Zkontrolujte, §e m te nainstalovanì font "Times New Roman WT J". Tento font
    je pou§itì jako z lo§n¡ varianta.

Tisk ve form tu PostScript vy§aduje tisk rnu podporuj¡c¡ tento standard
(pscript.drv).


éplnì seznam funkcionalit a rozç¡ýen¡ najdete v syst‚mu TRAC pro Lucide na:

  http://svn.netlabs.org/lucide/

Najdete-li jak‚koli chyby, zaregistrujte je tak‚ v syst‚mu TRAC - viz:

  http://svn.netlabs.org/lucide/newticket

Pros¡m, ovØýte si, §e jste pro sv…j z znam vybrali odpov¡daj¡c¡ verzi
a komponentu.


:: Zn m‚ probl‚my/omezen¡ ::

Obecn‚: Tisk sudìch/lichìch str nek nen¡ k dispozici pro tisk ve form tu
        PostScript.
          ( http://svn.netlabs.org/lucide/ticket/87#comment:4 )


:: Pý¡kazy pýes rouru ::

Prvn¡ instance prohl¡§eŸe Lucide vytvoý¡ pojmenovanou rouru \PIPE\LUCIDE. Do
roury m…§ete poslat n sleduj¡c¡ pý¡kazy:

$prev              - pýepne na pýedchoz¡ str nku
$next              - pýepne na dalç¡ str nku
$presentation      - pýepne do prezentaŸn¡ho re§imu (i v pý¡padØ minimalizace)
$minimize          - mimimalizuje prohl¡§eŸ Lucide (i z cel‚ obrazovky)
$rotate            - otoŸ¡ zobrazen¡ o 90ø doprava
$zoomin            - zvØtç¡ zobrazen¡
$zoomout           - zmenç¡ zobrazen¡
$zoomoriginal      - pýepne na skuteŸnou velikost

Toto m…§e bìt u§iteŸn‚ pro prezentace s d lkovìm ovl d n¡m.


:: Licence do verze 1.21 ::

Prohl¡§eŸ Lucide verze 1.21 a ni§ç¡ je licencov n pouze pro pou§it¡ se syst‚mem
eComStation. Produkt nesm¡ bìt distribuov n jeho ukl d n¡m na veýejn‚ servery
s¡tØ Internet ani zveýejåovat ho jinìm zp…sobem.


:: Licence verze 1.3.0 a vyçç¡ ::

PoŸ¡naje verz¡ 1.3.0 odsouhlasily firmy Mensys BV a Serenity Systems
International pýechod programu Lucide do re§imu open source, pýiŸem§
do produktu i nad le investuj¡.
Organizace Netlabs.org by za to chtØla firm m Mensys BV a Serenity Systems
International podØkovat.

Od verze 1.3.0 je program Lucide uvolnØn a distribuov n pod licenc¡ CDDL/LGPL.


:: Licence pro moduly ::

Moduly jsou uvolnØn‚ pod licenc¡ CDDL/LGPL nebo GPL v z vislosti na jednotliv‚m
modulu. Viz http://svn.netlabs.org/lucide/ pro dalç¡ informace a zdrojovì k¢d.


:: Odkazy ::

http://www.netlabs.org
http://www.ecomstation.com


:: Copyright ::

(c) 2006-2007 Eugene Romanenko, netlabs.org
(c) 2010-2011 Dmitriy Kuminov, netlabs.org
    ve spolupr ci se Serenity Systems International

