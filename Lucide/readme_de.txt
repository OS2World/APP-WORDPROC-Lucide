:: šber Lucide:

Lucide ist ein Plugin-basierter Dokumenten-Betrachter mit Untersttzung fr verschiedene Dateiformate.

Es bietet eine Plugin-Architektur basierend auf SOM, die es 3rd-Party-Programmierern erlaubt
relative einfach erm”glich weitere Plugins hinzuzufgen.


:: Plugins::

   Untersttzte Dateitypen Untersttzte Funktionen
  ------------------------ --------------------------------------------------
         PDF               Skalierung, Drehung, Navigation, Text
                           Auswahl, Suchen, Asynchron-Rendering,
                           PostScript-Druck

         DJVU              Skalierung, PostScript-Druck

         JPG               Skalierung
  ------------------------ --------------------------------------------------


:: Voraussetzungen::

Lucide erfordert Folgendes:

  - Libc 0.6.3:
    - ftp://ftp.netlabs.org/pub/gcc/libc-0.6.3-csd3.zip (zip-Format)
      oder ftp://ftp.netlabs.org/pub/gcc/libc-0_6_3-csd3.wpi (WarpIn-Format)
  - Gcc442.dll:
    - http://download.smedley.info/gcc442.zip (zip-Format)
      oder ftp://ftp.netlabs.org/pub/qt4/gcc-lib-4_4_2-20091204.wpi (WarpIn-Format)


Optional: Um Unicode-Text in die Zwischenablage im OpenOffice.org-kompatiblen
Format kopieren zu k”nnen, mssen Sie das UClip Paket (Enhanced OS/2
Untersttzung der Zwischenablage installieren, standardm„áig installiert in 
eComStation 2.0 RC1 und h”her):

  - http://hobbes.nmsu.edu/cgi-bin/h-search?key=UClip

Optional: Wenn Sie mit japanische Fonts arbeiten, brauchen Sie das 
poppler-Daten-Paket.

  - Entpacken Sie die 4 Verzeichnisse aus dem Paket auf http://poppler.freedesktop.org
    in Ihre %unixroot%/usr/local/share/poppler oder direkt in Verzeichnis von Lucide.exe
  - Achten Sie darauf, dass die "Times New Roman WT J" Schrift installiert ist. Diese Schrift wird verwendet,
    als Fallback
    
PostScript-Druck erfordert einen PostScript-f„higen Drucker (PSCRIPT.DRV).


Um eine vollst„ndige Liste der Funktionen und Verbesserungen konsultieren Lucide TRAC unter:

  http://svn.netlabs.org/lucide/

Wenn Sie Fehler melden m”chten, k”nnen Sie das in TRAC sowie unter:

  http://svn.netlabs.org/lucide/newticket

Bitte stellen Sie sicher, dass Sie die richtige Version und Komponenten fr 
Ihr Ticket angeben.


:: Bekannte Probleme / Einschr„nkungen:

Allgemein: Gerade / ungerade Drucken ist nicht verfgbar fr PostScript-Druck.
          (Http://svn.netlabs.org/lucide/ticket/87 # comment: 4)


:: Pipe-Befehle:

Die erste Instanz der Lucide ”ffnet eine Named Pipe "\PIPE\Lucide.
Sie k”nnen Lucide mit folgenden Befehlen ber diese Pipe fernsteuern:

$ Prev -, um zur vorherigen Seite wechseln
$ Next - wird auf der n„chsten Seite wechseln
$ Pr„sentation - Pr„sentation wechseln wird (auch wenn minimiert)
$ Minimieren - wird mimimize Lucide (auch wenn Vollbild)
$ Drehen - werden mit 90 ø zu drehen, CW
$ ZoomIn - zoomt in
$ ZoomOut - verkleinert
$ Zoomoriginal - wird von den tats„chlichen Gr”áe vergr”áern

Dies kann ntzlich sein fr Pr„sentationen mit einer Fernbedienung.


:: Lizenz bis Version 1.21:

Lucide Version 1.21 und frher sind fr den Einsatz mit eComStation lizenziert.
Sie sind nicht berechtigt, das Produkt durch Hochladen auf ”ffentliche verteilen
Internet-Servern oder ”ffentlich zug„nglich machen auf eine andere Weise.


:: Lizenz fr Version 1.3.0 und besser::

Beginnend mit Version 1.3.0 Mensys BV und Serenity Systems International
haben in opensourcing Lucide, w„hrend noch die Investition in das Produkt 
vereinbart. Netlabs.org m”chte es Dankbarkeit gegenber Mensys BV und 
Serenity Systems International ausdrcken.

Lucide ab der Version 1.3.0 ist freigegeben und verteilt unter CDDL / LGPL.


:: Plugin-Lizenz:
Die Plugins sind unter CDDL / LGPL oder GPL ver”ffentlicht, je nach dem Plugin. Siehe
http://svn.netlabs.org/lucide/ fr weitere Informationen und Quellcode.


:: Links::

http://www.netlabs.org
http://www.ecomstation.com


:: Copyright::

(C) 2006-2007 von Eugene Romanenko, netlabs.org
(C) 2010 von Dmitri A. Kuminov, netlabs.org
    in Kooperation mit Serenity Systems International

