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
                               vypl�ov�n� formul���, tisk ve form�tu PostScript

         DJVU                  Zm�na velikosti, tisk ve form�tu PostScript

         JPG                   -
  --------------------------------------------------------------------------

:: Srovn�n� s n�strojem qPDFView ::

N�stroje Lucide i qPDFView oba vyu��vaj� k vykreslov�n� soubor� PDF knihovnu
poppler. Vnit�n� rozd�ly mezi ob�ma programy zp�sobuj� rychlej� vykreslov�n�
n�kter�ch soubor� v jednom z obou program� ne� v druh�m. Celkov� se poci�ujeme,
�e Lucide m� u�ivatelsk� rozhran� bli�� (p�irozen�j�) pro syst�m OS/2 a je
pro pou�it� pod t�mto syst�mem vhodn�j�. Ka�d� u�ivatel si m��e zvolit, kter�
z obou n�stroj� l�pe vyhovuje jeho pot�eb�m.


:: Po�adavky ::

K nainstalov�n� v�eho pot�ebn�ho najednou z n�stroje Arca Noe Package Manager
zkop�rujte n�sleduj�c� �et�zec do dialogov�ho okna rychl� instalace (Quick
install):

    libc libgcc1 libgcc-fwd poppler poppler-data uclip

Pokud d�v�te p�ednost pou��v�n� n�stroje yum z p��kazov� ��dky, napi�te pros�m

    yum install libc libgcc1 libgcc-fwd poppler poppler-data libjpeg djvulibre uclip

a stiskn�te <Enter>.


Program Lucide konkr�tn� vy�aduje n�sleduj�c� bal�ky:

  - libc 0.6.6:
  - http://rpm.netlabs.org/release/00/zip/libc-0_6_6-38_oc00.zip (form�t zip)
    nebo ftp://ftp.netlabs.org/pub/gcc/libc-0_6_6-csd6.wpi (form�t WarpIn)
      nebo "yum install libc" (z �lo�i�t� netlabs-rel)
  - libcx 0.6.3
    - http://rpm.netlabs.org/release/00/zip/libcx-0_6_4-1_oc00.zip (form�t zip)
       or "yum install libcx" (z �lo�i�t� netlabs-rel)
  - gcc492.dll:
    - ftp://ftp.netlabs.org/pub/gcc/gcc4core-1_3_1.wpi (form�t WarpIn)
      nebo "yum install libgcc1 libgcc-fwd" (z �lo�i�t� netlabs-rel)

Pro zobrazov�n� soubor� PDF pot�ebuje p��slu�n� modul Lucide n�sleduj�c�:

    - poppler 0.59.0:
    - "yum install poppler" (z �lo�i�t� netlabs-rel)

Pro zobrazov�n� obr�zk� JPEG pot�ebuje p��slu�n� modul Lucide n�sleduj�c�:

    - libjpeg 8c:
    - "yum install libjpeg" (z �lo�i�t� netlabs-rel)

Pro zobrazov�n� soubor� DjVu pot�ebuje p��slu�n� modul Lucide n�sleduj�c�:

    - djvulibre 3.5.22:
    - "yum install djvulibre" (z �lo�i�t� netlabs-rel)


Voliteln�: chcete-li uschovat ve schr�nce text v k�dov�n� unicode ve form�tu
kompatibiln�m s bal�kem OpenOffice.org, mus�te nainstalovat bal�k UClip
(roz��en� podpora schr�nky syst�mu OS/2, standardn� sou��st syst�mu
eComStation verze 2.0 RC1 a vy�� a tak� ArcaOS Blue Lion):

  - http://hobbes.nmsu.edu/cgi-bin/h-search?key=UClip
    nebo "yum install uclip" (z �lo�i�t� netlabs-rel)
  
Voliteln�: chcete-li pou��vat japonsk� fonty, pot�ebujete bal��ek poppler-data.

  - "yum install poppler-data" (z �lo�i�t� netlabs-rel)


Tisk ve form�tu PostScript vy�aduje tisk�rnu podporuj�c� tento standard
(pscript.drv nebo psprint.drv).


�pln� seznam funkcionalit a roz��en� najdete v syst�mu TRAC pro Lucide na:

  https://trac.netlabs.org/lucide/

Najdete-li jak�koli chyby, zaregistrujte je tak� v syst�mu TRAC - viz:

  https://trac.netlabs.org/lucide/newticket

Pros�m, ov��te si, �e jste pro sv�j z�znam vybrali odpov�daj�c� verzi
a komponentu.


:: Zn�m� probl�my/omezen� ::

Viz: https://trac.netlabs.org/lucide/report/1


:: Moduly t�et�ch stran ::

GBM (Generalised Bitmap Module) je knihovna pro pr�ci s mnoha r�zn�mi form�ty
soubor� pro bitov� mapy. P�ich�z� se sadou u�ite�n�ch n�stroj� pro manipulace
s bitov�mi mapami a konverze form�t� z p��kazov� ��dky. V t�to verzi je nav�c
obsa�en� podpora form�t� BMP, JPG, JP2, PNG, TIF, PBM, PGM, PPM, PNM, XPM, JBG
a RAW.

http://hobbes.nmsu.edu/h-search.php?key=gbmos2pm160_gbm176_lu143_moz147_bin_wpi

Pozn�mka: Pokud pro vykreslov�n� obr�zk� JPG pou��v�te GBM, je vhodn� zabr�nit
konflikt�m zak�z�n�m modulu JPG dod�van�ho s Lucide (viz tiket #236). Toho lze
snadno dos�hnout p�ejmenov�n� souboru lujpeg.dll v adres��i programu Lucide
na lujpeg.dl_ ve chv�li, kdy Lucide nebا�. Pro op�tovn� povolen� obsa�en�ho
modulu JPG jednodu�e p�ejmenujte soubor na jeho p�vodn� jm�no a nastartujte
Lucide.


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


:: Licence do verze 1.21 (v�etn�) ::

Prohl��e� Lucide verze 1.21 a ni�� je licencov�n pouze pro pou�it� se syst�mem
eComStation. Produkt nesm� b�t distribuov�n jeho ukl�d�n�m na ve�ejn� servery
s�t� Internet ani zve�ej�ovat ho jin�m zp�sobem.


:: Licence verze 1.3.0 a vy�� ::

Po��naje verz� 1.3.0 odsouhlasily firmy Mensys BV a Serenity Systems
International p�echod programu Lucide do re�imu open source, p�i�em�
do produktu i nad�le investuj�.
Organizace Netlabs.org by za to cht�la firm�m Mensys BV a Serenity Systems
International pod�kovat.

Od verze 1.3.6 d�le se rozhodla firma Arca Noae, LLC podpo�it v�voj Lucide.
Lucide z�st�v� v re�imu open source a pod dvoj� licenc�.

Od verze 1.3.0 je program Lucide uvoln�n a distribuov�n pod licenc� CDDL/LGPL.


:: Licence pro moduly ::

Moduly jsou uvoln�n� pod licenc� CDDL/LGPL nebo GPL v z�vislosti na jednotliv�m
modulu. Viz http://svn.netlabs.org/lucide/ pro dal� informace a zdrojov� k�d.


:: Odkazy ::

http://www.netlabs.org
https://www.arcanoae.com


:: Copyright ::

(c) 2006-2007 Eugene Romanenko, netlabs.org
(c) 2010-2011 Dmitriy Kuminov, netlabs.org
    ve spolupr�ci se Serenity Systems International
(c) 2016-2019 netlabs.org
    ve spolupr�ci s Arca Noae, LLC
