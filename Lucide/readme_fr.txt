:: · propos de Lucide ::

Lucide est un afficheur de documents, bas‚ sur des composants
enfichables, prenant en charge divers formats de fichiers. 

Il offre une architecture d'extension bas‚e sur SOM permettant … des
programmeurs tiers d'ajouter ais‚ment de nouveaux composants. 


:: Composants ::

   Type de fichiers            Fonctionnalit‚s prise en charge
  --------------------------------------------------------------------------
         PDF                   Mise … l'‚chelle, rotation, navigation,
                               s‚lection, recherche, rendu asynchrone,
                               impression PostScript

         DJVU                  Mise … l'‚chelle, impression PostScript

         JPG                   Mise … l'‚chelle
  --------------------------------------------------------------------------


:: Comparaison avec qPDFView ::

Lucide et qPDFView utilisent tous les deux la bibliothŠque poppler pour
le rendu des fichiers PDF. Les diff‚rences de conceptions internes entre
les deux programmes r‚sultent en des rendus plus rapides dans l'un
programme que dans l'autre. Dans l'ensemble, nous trouvons que Lucide
pr‚sente une interface plus dans le style d'OS/2 (ou "native") et qu'il
est donc plus adapt‚ au systŠme d'exploitation. Le choix est laiss‚
entiŠrement … l'utilisateur pour ce qu'il pense ˆtre le mieux adapt‚ …
ses besoins. 


:: Pr‚requis ::

Pour installer tous les pr‚requis en une seule passe depuis Arca Noae 
Package Manager (Gestionnaire de paquetages Arca Noae), dans la boŒte de
dialogue "Installation rapide" copier et coller simplement la chaŒne
suivante : 

    libc libgcc1 libgcc-fwd poppler poppler-data uclip


Plus sp‚cifiquement, Lucide n‚cessite : 

  - libc 0.6.6 : 
    - http://rpm.netlabs.org/release/00/zip/libc-0_6_6-38_oc00.zip (format zip)
      ou ftp://ftp.netlabs.org/pub/gcc/libc-0_6_6-csd6.wpi (format WarpIn)
      ou "yum install libc" (depuis le d‚p“t netlabs-rel)
  - libcx 0.6.3
    - http://rpm.netlabs.org/release/00/zip/libcx-0_6_4-1_oc00.zip (format zip)
       or "yum install libcx" (depuis le d‚p“t netlabs-rel)
  - gcc492.dll : 
    - ftp://ftp.netlabs.org/pub/gcc/gcc4core-1_3_1.wpi (format WarpIn)
      ou "yum install libgcc1 libgcc-fwd" (depuis le d‚p“t netlabs-rel)

For rendering PDFs, Lucide's plugin requires the following:

    - librairie poppler 0.59.0 pour afficher les PDFs : 
    - "yum install poppler" (depuis le d‚p“t netlabs-rel)
    
For rendering DjVu files, Lucide's plugin requires the following:

    - djvulibre 3.5.27:
    - "yum install djvulibre" (from the netlabs-rel repository)
    
For rendering multiple bitmap format files (GBM), Lucide's plugin 
requires the following:

    - GBMDLL 1.76:
    - "yum install GBMDLL" (from the netlabs-rel repository)
    - Installed by default on ArcaOS 5.0.3 and higher

For rendering JPEGs, Lucide's plugin requires the following:

    - libjpeg 8d:
    - "yum install libjpeg" (from the netlabs-rel repository)
    - Only needed if you install the JPG plugin GBM provides JPG support
    - You should not install  JPG and GBM at the same time. (GBM is recommended)

En option : pour pouvoir placer du texte Unicode dans le presse-papiers
            dans un format compatible avec OpenOffice.org, vous devez
installer le paquetage UClip ("enhanced OS/2 clipboard support" ou
"prise en charge du presse-papiers am‚lior‚", install‚ par d‚faut dans
les version 2.0 RC1 ou ult‚rieures de eComStation, ainsi que dans ArcaOS
Blue Lion) : 

  - http://hobbes.nmsu.edu/cgi-bin/h-search?key=UClip
    ou "yum install uclip" (depuis le d‚p“t netlabs-rel)

En option : pour que les fontes japonaises fonctionnent, vous aurez
            besoin du paquetage poppler-data : 

  - "yum install poppler-data" (depuis le d‚p“t netlabs-rel)


L'impression PostScript n‚cessite une imprimante PostScript (utilisant
pscript.drv ou psprint.drv). 


Pour obtenir une liste plus exhaustive des fonctionnalit‚s et
des am‚liorations, consultez le "TRAC" de Lucide : 

  http://svn.netlabs.org/lucide/

Si vous rencontrez un bug, enregistrez-les aussi dans le "TRAC". Voir : 

  http://svn.netlabs.org/lucide/newticket

Veuillez vous assurer de s‚lectionner la version correcte du composant
pour l'‚tablissement de votre ticket. 


:: ProblŠmes connus/limitations ::

Voir : https://trac.netlabs.org/lucide/report/1


:: Third-Party plugins ::

GBM (Generalised Bitmap Module) est une bibliothŠque pour la manipulation
de plusieurs formats de fichiers d'image diff‚rents. Il est fourni avec
un ensemble d'outils en ligne de commandes trŠs utiles permettant
d'effectuer des manipulations sur les images et des conversion de
formats. Dans cette version est inclue la prise en charge des BMP, JPG,
JP2, PNG, TIF, PBM, PGM, PPM, PNM, XPM, JBG et RAW. 

http://hobbes.nmsu.edu/h-search.php?key=gbmos2pm160_gbm176_lu143_moz147_bin_wpi

Remarque : si vous voulez utiliser GBM pour le rendu d'images JPG, il
est recommand‚ de d‚sactiver le composant enfichable JPG fourni avec
Lucide pour ‚viter les conflits (voir le ticket #236). Cela s'effectue
simplement en renommant le fichier lujpeg.dll, situ‚ dans le r‚pertoire
d'installation de Lucide, en lujpeg.dl_ lorsque Lucide n'est pas en
cours d'ex‚cution. Pour r‚activer le composant enfichable JPG inclus,
renommez simplement le fichier pour lui rendre son nom original, puis
lancez Lucide. 


:: Commandes Pipe ::

La premiŠre instance de Lucide cr‚e un tube nomm‚ ("named pipe")
\PIPE\LUCIDE. Vous pouvez alors y envoyer les commandes suivantes : 

$prev              - bascule vers la page pr‚c‚dente
$next              - bascule … la page suivante
$presentation      - bascule en mode pr‚sentation (mˆme si r‚duit)
$minimize          - r‚duit Lucide (mˆme si affich‚ en plein ‚cran)
$rotate            - rotation … 90ø vers la droite
$zoomin            - agrandit (loupe)
$zoomout           - r‚duit (loupe)
$zoomoriginal      - affiche … la taille normale

Cela peut ˆtre utile pour des pr‚sentations pilot‚es … la t‚l‚commande. 


:: Licence jusqu'… la version 1.21 ::

Les versions 1.21 de Lucide et pr‚c‚dentes sont licenci‚es pour un
usage avec eComStation uniquement. 
Vous n'ˆtes pas autoris‚s … distribuer le produit en le mettant …
disposition sur des serveurs Internet publics, ou le rendre disponible
publiquement par n'importe quel autre moyen que ce soit. 


:: Licence pour les versions 1.3.0 et ult‚rieures ::

· partir de la version 1.3.0, Mensys BV et Serenity Systems International 
se sont accord‚s pour rendre Lucide opensource, tout en continuant …
investir dans le produit. 
Netlabs.org tient … exprimer toute sa gratitude envers Mensys BV et
Serenity Systems International. 

Lucide, depuis la version 1.3.0, est donc publi‚ et distribu‚ sous
licence CDDL/LGPL. 


:: Licence pour les composants ::

Les composants enfichables sont publi‚s sous licence CDDL/LGPL ou GPL,
en fonction du composant. Consulter http://svn.netlabs.org/lucide/
pour plus d'informations et le code source. 


:: Liens ::

http://www.netlabs.org
https://www.arcanoae.com


:: Copyright ::

(c) 2006-2007 par Eugene Romanenko, netlabs.org
(c) 2010-2011 par Dmitriy Kuminov, netlabs.org
    en coop‚ration avec Serenity Systems International
(c) 2016-2019 par netlabs.org
    en coop‚ration avec Arca Noae, LLC

Traduction fran‡aise du 2016-08-09 par Guillaume Gay <guillaume.gay@bigfoot.com>
