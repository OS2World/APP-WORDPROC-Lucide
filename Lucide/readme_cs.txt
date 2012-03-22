:: O prohl��e�i Lucide ::

Lucide je prohl��e� dokument� zalo�en� na modulech podporuj�c� r�zn� form�ty
soubor�.

Poskytuje modul�rn� architekturu zalo�enou na rozhran� SOM, co� umo��uje dal�m
program�tor�m jednodu�e p�id�vat dal� moduly.


:: Moduly ::

   Podporovan� typ soubor�     Podporovan� funkcionality
  --------------------------------------------------------------------------
         PDF                   Zm�na velikosti, rotace, navigace, v�b�r
                               textu, hled�n�, asynchronn� vykreslov�n�,
                               tisk ve form�tu PostScript

         DJVU                  Zm�na velikosti, tisk ve form�tu PostScript

         JPG                   -
  --------------------------------------------------------------------------

:: Po�adavky ::

Program Lucide vy�aduje n�sleduj�c� bal�ky:

  - libc 0.6.4:
  - ftp://ftp.netlabs.org/pub/gcc/libc-0.6.4-csd4.zip (form�t zip)
    nebo ftp://ftp.netlabs.org/pub/gcc/libc-0.6.4-csd4.wpi (form�t WarpIn)

  - gcc446.dll:
    - ftp://ftp.netlabs.org/pub/gcc/gcc4core-1_2_1.wpi (form�t WarpIn)


Voliteln�: chcete-li uschovat ve schr�nce text v k�dov�n� unicode ve form�tu
kompatibiln�m s bal�em OpenOffice.org, mus�te nainstalovat bal�k UClip
(roz��en� podpora schr�nky syst�mu OS/2, standardn� sou��st syst�mu
eComStation verze 2.0 RC1 a vy��):

  - http://hobbes.nmsu.edu/cgi-bin/h-search?key=UClip
  
Voliteln�: chcete-li pou��vat Japonsk� fonty, pot�ebujete bal��ek poppler-data.

  - Rozbalte 4 adres��e z bal��ku dostupn�ho na http://poppler.freedesktop.org
    do adres��e %unixroot%/usr/local/share/poppler nebo do adres��e
    obsahuj�c�ho nainstalovan� soubor lucide.exe.
  - Zkontrolujte, �e m�te nainstalovan� font "Times New Roman WT J". Tento font
    je pou�it� jako z�lo�n� varianta.

Tisk ve form�tu PostScript vy�aduje tisk�rnu podporuj�c� tento standard
(pscript.drv).


�pln� seznam funkcionalit a roz��en� najdete v syst�mu TRAC pro Lucide na:

  http://svn.netlabs.org/lucide/

Najdete-li jak�koli chyby, zaregistrujte je tak� v syst�mu TRAC - viz:

  http://svn.netlabs.org/lucide/newticket

Pros�m, ov��te si, �e jste pro sv�j z�znam vybrali odpov�daj�c� verzi
a komponentu.


:: Zn�m� probl�my/omezen� ::

Obecn�: Tisk sud�ch/lich�ch str�nek nen� k dispozici pro tisk ve form�tu
        PostScript.
          ( http://svn.netlabs.org/lucide/ticket/87#comment:4 )


:: P��kazy p�es rouru ::

Prvn� instance prohl��e�e Lucide vytvo�� pojmenovanou rouru \PIPE\LUCIDE. Do
roury m��ete poslat n�sleduj�c� p��kazy:

$prev              - p�epne na p�edchoz� str�nku
$next              - p�epne na dal� str�nku
$presentation      - p�epne do prezenta�n�ho re�imu (i v p��pad� minimalizace)
$minimize          - mimimalizuje prohl��e� Lucide (i z cel� obrazovky)
$rotate            - oto�� zobrazen� o 90� doprava
$zoomin            - zv�t� zobrazen�
$zoomout           - zmen� zobrazen�
$zoomoriginal      - p�epne na skute�nou velikost

Toto m��e b�t u�ite�n� pro prezentace s d�lkov�m ovl�d�n�m.


:: Licence do verze 1.21 ::

Prohl��e� Lucide verze 1.21 a ni�� je licencov�n pouze pro pou�it� se syst�mem
eComStation. Produkt nesm� b�t distribuov�n jeho ukl�d�n�m na ve�ejn� servery
s�t� Internet ani zve�ej�ovat ho jin�m zp�sobem.


:: Licence verze 1.3.0 a vy�� ::

Po��naje verz� 1.3.0 odsouhlasily firmy Mensys BV a Serenity Systems
International p�echod programu Lucide do re�imu open source, p�i�em�
do produktu i nad�le investuj�.
Organizace Netlabs.org by za to cht�la firm�m Mensys BV a Serenity Systems
International pod�kovat.

Od verze 1.3.0 je program Lucide uvoln�n a distribuov�n pod licenc� CDDL/LGPL.


:: Licence pro moduly ::

Moduly jsou uvoln�n� pod licenc� CDDL/LGPL nebo GPL v z�vislosti na jednotliv�m
modulu. Viz http://svn.netlabs.org/lucide/ pro dal� informace a zdrojov� k�d.


:: Odkazy ::

http://www.netlabs.org
http://www.ecomstation.com


:: Copyright ::

(c) 2006-2007 Eugene Romanenko, netlabs.org
(c) 2010-2011 Dmitriy Kuminov, netlabs.org
    ve spolupr�ci se Serenity Systems International

