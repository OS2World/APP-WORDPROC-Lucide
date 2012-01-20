:: Over Lucide:

Lucide is een plugin-based document viewer met ondersteuning voor verschillende bestandsformaten.

Het biedt een plug-in architectuur op basis van SOM, die het andere programmeurs het mogelijk maakt op relatief eenvoudige wijze meer plugins toe te voegen.


:: Plugins::

   Ondersteunde bestandstypen 	ondersteunde functies
  ------------------------ 	-------------------------- ------------------------
         PDF 			schalen, roteren, navigatie, tekst
                           	selectie, zoeken, asynchrone rendering
                           	PostScript afdrukken

         DJVU 			schalen, PostScript afdrukken

         JPG 			schal eig
  ------------------------ -------------------------- ------------------------


:: Eisen::

Lucide vereist het volgende:

  - Libc 0.6.4:
    - FTP://ftp.netlabs.org/pub/gcc/libc-0.6.4-csd4.zip (zip formaat)
      of ftp://ftp.netlabs.org/pub/gcc/libc-0.6.4-csd4.wpi (WarpIn formaat)
  - Gcc446.dll:
    - ftp://ftp.netlabs.org/pub/gcc/gcc4core-1_2_1.wpi (WarpIn formaat)


Optioneel: om unicode-tekst naar het klembord in het OpenOffice.org-compatibele formaat
te plaasten, moet u het pakket UClip (enhanced OS/2 clipboard support installeren, standaard 
geînstalleerd in eComStation 2.0 RC1 en hoger):

  - Http://hobbes.nmsu.edu / cgi-bin / h-search key = UClip?

Optioneel: als u gebruik wilt maken van Japanse lettertypen, heeft u het poppler-data pakket nodig.

  - Pak de vier directories van het pakket uit dat u gevonden heeft op: http://poppler.freedesktop.org
    in uw %unixroot%/usr/local/share/poppler of in de directory waaarin Lucide.exe is geïnstallerd,
  - zorg ervoor dat het "Times New Roman WT J" lettertype is geïnstalleerd. Dit lettertype wordt gebruikt
    om op terug te vallen
    
PostScript-afdrukken vereist een PostScript-printer (PSCRIPT.DRV).


Om een volledige lijst van functies en verbeteringen kijk op Lucide TRAC op:

  http://svn.netlabs.org/lucide/

Als u een fout tegen komt, leg ze ook vast in hde TRAC op:

  http://svn.netlabs.org/lucide/newticket

Zorg ervoor dat u de juiste versie en componenten voor
uw ticket te selecteert.


:: Bekende problemen / beperkingen ::

Algemeen: even en oneven afdrukken is niet beschikbaar voor PostScript-afdrukken.
          (Http://svn.netlabs.org/lucide/ticket/87#comment: 4)


:: Pipe commando's:

Het eerste voorbeeld van Lucide opent een pipe genaamd \PIPE\Lucide.
U kunt de volgende commando's naar deze pipe sturen:

$ Vorige 	 - om over te schakelen naar de vorige pagina
$ Volgende 	 - gaat naar de volgende pagina
$ Presentatie 	 - verander de presentatie (ook als deze geminimaliseerd is)
$ Minimaliseren  - minimaliseery Lucide (zelfs uit volledig scherm)
$ Draaien 	 - zal 90° draaien, CW
$ ZoomIn 	 - zoomt in
$ ZoomOut 	 - zoomt uit
$ Zoom origineel - zal zoomen naar de werkelijke grootte

Dit kan handig zijn voor presentaties met een afstandsbediening.


:: Licentie voor versie 1.21:

Lucide versie 1.21 en eerder zijn gelicentieerd voor gebruik met eComStation.
U bent niet gerechtigd om het product te distribueren door het te uploaden naar openbare
Internet servers, of het op een andere manier openbaar maken.


:: Licentie voor versie 1.3.0 en beter:

Beginnend met versie 1.3.0 hebben Mensys BV en Serenity Systems International 
toegestemd in de Open Sourcing van Lucide, onderwijl nog investerend in het product. 
Netlabs.org wil zijn dank uitspreken tegenover Mensys BV en Serenity Systems International.

Lucide wordt vanaf versie 1.3.0 vrijgegeven en gedistribueerd onder CDDL/LGPL.


:: Plugin Licentie:
De plugins zijn onder CDDL/LGPL of GPL, vrijgegeven afhankelijk van de plugin. Zie
http://svn.netlabs.org/lucide/ voor meer informatie en broncode.


:: Links::

http://www.netlabs.org
http://www.ecomstation.com


:: Copyright::

(C) 2006-2007 door Eugene Romanenko, netlabs.org
(C) 2010 door Dmitry A. Kuminov, netlabs.org
    in samenwerking met Serenity Systems International

