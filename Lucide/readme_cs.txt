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
                               vyplåov n¡ formul ý…, tisk ve form tu PostScript

         DJVU                  ZmØna velikosti, tisk ve form tu PostScript

         JPG                   -
  --------------------------------------------------------------------------

:: Srovn n¡ s n strojem qPDFView ::

N stroje Lucide i qPDFView oba vyu§¡vaj¡ k vykreslov n¡ soubor… PDF knihovnu
poppler. Vnitýn¡ rozd¡ly mezi obØma programy zp…sobuj¡ rychlejç¡ vykreslov n¡
nØkterìch soubor… v jednom z obou program… ne§ v druh‚m. CelkovØ se pociœujeme,
§e Lucide m  u§ivatelsk‚ rozhran¡ bli§ç¡ (pýirozenØjç¡) pro syst‚m OS/2 a je
pro pou§it¡ pod t¡mto syst‚mem vhodnØjç¡. Ka§dì u§ivatel si m…§e zvolit, kterì
z obou n stroj… l‚pe vyhovuje jeho potýeb m.


:: Po§adavky ::

K nainstalov n¡ vçeho potýebn‚ho najednou z n stroje Arca Noe Package Manager
zkop¡rujte n sleduj¡c¡ ýetØzec do dialogov‚ho okna rychl‚ instalace (Quick
install):

    libc libgcc1 libgcc-fwd poppler poppler-data uclip

Pokud d v te pýednost pou§¡v n¡ n stroje yum z pý¡kazov‚ ý dky, napiçte pros¡m

    yum install libc libgcc1 libgcc-fwd poppler poppler-data libjpeg djvulibre uclip

a stisknØte <Enter>.


Program Lucide konkr‚tnØ vy§aduje n sleduj¡c¡ bal¡ky:

  - libc 0.6.6:
  - http://rpm.netlabs.org/release/00/zip/libc-0_6_6-38_oc00.zip (form t zip)
    nebo ftp://ftp.netlabs.org/pub/gcc/libc-0_6_6-csd6.wpi (form t WarpIn)
      nebo "yum install libc" (z £lo§içtØ netlabs-rel)
  - libcx 0.6.3
    - http://rpm.netlabs.org/release/00/zip/libcx-0_6_4-1_oc00.zip (form t zip)
       or "yum install libcx" (z £lo§içtØ netlabs-rel)
  - gcc492.dll:
    - ftp://ftp.netlabs.org/pub/gcc/gcc4core-1_3_1.wpi (form t WarpIn)
      nebo "yum install libgcc1 libgcc-fwd" (z £lo§içtØ netlabs-rel)

Pro zobrazov n¡ soubor… PDF potýebuje pý¡sluçnì modul Lucide n sleduj¡c¡:

    - poppler 0.59.0:
    - "yum install poppler" (z £lo§içtØ netlabs-rel)

Pro zobrazov n¡ obr zk… JPEG potýebuje pý¡sluçnì modul Lucide n sleduj¡c¡:

    - libjpeg 8c:
    - "yum install libjpeg" (z £lo§içtØ netlabs-rel)

Pro zobrazov n¡ soubor… DjVu potýebuje pý¡sluçnì modul Lucide n sleduj¡c¡:

    - djvulibre 3.5.22:
    - "yum install djvulibre" (z £lo§içtØ netlabs-rel)


Voliteln‚: chcete-li uschovat ve schr nce text v k¢dov n¡ unicode ve form tu
kompatibiln¡m s bal¡kem OpenOffice.org, mus¡te nainstalovat bal¡k UClip
(rozç¡ýen  podpora schr nky syst‚mu OS/2, standardn¡ souŸ st syst‚mu
eComStation verze 2.0 RC1 a vyçç¡ a tak‚ ArcaOS Blue Lion):

  - http://hobbes.nmsu.edu/cgi-bin/h-search?key=UClip
    nebo "yum install uclip" (z £lo§içtØ netlabs-rel)
  
Voliteln‚: chcete-li pou§¡vat japonsk‚ fonty, potýebujete bal¡Ÿek poppler-data.

  - "yum install poppler-data" (z £lo§içtØ netlabs-rel)


Tisk ve form tu PostScript vy§aduje tisk rnu podporuj¡c¡ tento standard
(pscript.drv nebo psprint.drv).


éplnì seznam funkcionalit a rozç¡ýen¡ najdete v syst‚mu TRAC pro Lucide na:

  https://trac.netlabs.org/lucide/

Najdete-li jak‚koli chyby, zaregistrujte je tak‚ v syst‚mu TRAC - viz:

  https://trac.netlabs.org/lucide/newticket

Pros¡m, ovØýte si, §e jste pro sv…j z znam vybrali odpov¡daj¡c¡ verzi
a komponentu.


:: Zn m‚ probl‚my/omezen¡ ::

Viz: https://trac.netlabs.org/lucide/report/1


:: Moduly týet¡ch stran ::

GBM (Generalised Bitmap Module) je knihovna pro pr ci s mnoha r…znìmi form ty
soubor… pro bitov‚ mapy. Pýich z¡ se sadou u§iteŸnìch n stroj… pro manipulace
s bitovìmi mapami a konverze form t… z pý¡kazov‚ ý dky. V t‚to verzi je nav¡c
obsa§en  podpora form t… BMP, JPG, JP2, PNG, TIF, PBM, PGM, PPM, PNM, XPM, JBG
a RAW.

http://hobbes.nmsu.edu/h-search.php?key=gbmos2pm160_gbm176_lu143_moz147_bin_wpi

Pozn mka: Pokud pro vykreslov n¡ obr zk… JPG pou§¡v te GBM, je vhodn‚ zabr nit
konflikt…m zak z n¡m modulu JPG dod van‚ho s Lucide (viz tiket #236). Toho lze
snadno dos hnout pýejmenov n¡ souboru lujpeg.dll v adres ýi programu Lucide
na lujpeg.dl_ ve chv¡li, kdy Lucide nebØ§¡. Pro opØtovn‚ povolen¡ obsa§en‚ho
modulu JPG jednoduçe pýejmenujte soubor na jeho p…vodn¡ jm‚no a nastartujte
Lucide.


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


:: Licence do verze 1.21 (vŸetnØ) ::

Prohl¡§eŸ Lucide verze 1.21 a ni§ç¡ je licencov n pouze pro pou§it¡ se syst‚mem
eComStation. Produkt nesm¡ bìt distribuov n jeho ukl d n¡m na veýejn‚ servery
s¡tØ Internet ani zveýejåovat ho jinìm zp…sobem.


:: Licence verze 1.3.0 a vyçç¡ ::

PoŸ¡naje verz¡ 1.3.0 odsouhlasily firmy Mensys BV a Serenity Systems
International pýechod programu Lucide do re§imu open source, pýiŸem§
do produktu i nad le investuj¡.
Organizace Netlabs.org by za to chtØla firm m Mensys BV a Serenity Systems
International podØkovat.

Od verze 1.3.6 d le se rozhodla firma Arca Noae, LLC podpoýit vìvoj Lucide.
Lucide z…st v  v re§imu open source a pod dvoj¡ licenc¡.

Od verze 1.3.0 je program Lucide uvolnØn a distribuov n pod licenc¡ CDDL/LGPL.


:: Licence pro moduly ::

Moduly jsou uvolnØn‚ pod licenc¡ CDDL/LGPL nebo GPL v z vislosti na jednotliv‚m
modulu. Viz http://svn.netlabs.org/lucide/ pro dalç¡ informace a zdrojovì k¢d.


:: Odkazy ::

http://www.netlabs.org
https://www.arcanoae.com


:: Copyright ::

(c) 2006-2007 Eugene Romanenko, netlabs.org
(c) 2010-2011 Dmitriy Kuminov, netlabs.org
    ve spolupr ci se Serenity Systems International
(c) 2016-2019 netlabs.org
    ve spolupr ci s Arca Noae, LLC
