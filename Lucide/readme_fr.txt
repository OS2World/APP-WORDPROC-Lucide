:: · propos de Lucide ::

Lucide est un afficheur de documents, bas‚ sur des composants
enfichables, prenant en charge divers formats de fichiers. 

Il offre une architecture d'extension bas‚e sur SOM permettant … des
programmeurs tiers d'ajouter ais‚ment de nouveaux composants. 


:: Composants ::

   Type de fichiers            Fonctionnalit‚s prise en charge
  --------------------------------------------------------------------------
         PDF                   Mise … l'‚chelle, rotation, navigation,
                               s‚lectction, recherche, rendu asynchrone,
                               impression PostScript

         DJVU                  Mise … l'‚chelle, impression PostScript

         JPG                   Mise … l'‚chelle
  --------------------------------------------------------------------------


:: Pr‚requis ::

Lucide n‚cessite : 

  - libc 0.6.4:
    - ftp://ftp.netlabs.org/pub/gcc/libc-0.6.4-csd4.zip (format zip)
      ou ftp://ftp.netlabs.org/pub/gcc/libc-0.6.3-csd4.wpi (format WarpIn)
  - gcc446.dll:
    - ftp://ftp.netlabs.org/pub/gcc/gcc4core-1_2_1.wpi (format WarpIn)


En option : pour pouvoir placer du texte Unicode dans le presse-papiers
            dans un format compatible avec OpenOffice.org, vous devrez
installer la distribution UClip ("enhanced OS/2 clipboard support" ou
"prise en charge du presse-papiers am‚lior‚", install‚e par d‚faut dans
les versions 2.0 RC1 et ult‚rieures de eComStation) : 

  - http://hobbes.nmsu.edu/cgi-bin/h-search?key=UClip


L'impression PostScript n‚cessite une imprimante PostScript (utilisant
pscript.drv). 


Pour obtenir une liste plus exhaustive des fonctionnalit‚s et
des am‚liorations, consultez le "TRAC" de Lucide : 

  http://svn.netlabs.org/lucide/

Si vous rencontrez un bug, enregistrez-les aussi dans le "TRAC". Voir : 

  http://svn.netlabs.org/lucide/newticket

Veuillez vous assurer de s‚lectionner la version correcte du composant
pour l'‚tablissement de votre ticket. 


:: ProblŠmes connus/limitations ::

G‚n‚ral : la s‚lection de pages paires/impaires est indisponible pour
          l'impression Postscript.
          ( http://svn.netlabs.org/lucide/ticket/87#comment:4 )


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
http://www.ecomstation.com


:: Copyright ::

(c) 2006-2007 par Eugene Romanenko, netlabs.org
(c) 2010-2011 par Dmitriy Kuminov, netlabs.org
    en coop‚ration avec Serenity Systems International

Traduction fran‡aise du 2011-03-08 par Guillaume Gay <guillaume.gay@bigfoot.com>
