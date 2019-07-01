:: öber Lucide ::

Lucide ist ein Plugin-basierter Dokumentenbetrachter der verschiedene Dateiformate unterstÅtzt.

Es bietet eine Plugin-Architektur basierend auf SOM, die es Fremdanbietern erlaubt,
relativ einfach Plugins fÅr die Darstellung weiterer Dateitypen hinzuzufÅgen.


:: Plugins::

   UnterstÅtzte Dateitypen UnterstÅtzte Funktionen
  ------------------------ --------------------------------------------------
         PDF               Skalierung, Drehung, Navigation, Textauswahl
                           Suchen, Asynchrones Rendering,
                           AusfÅllen von Formularen, PostScript-Druck

         DJVU              Skalierung, PostScript-Druck

         JPG               Skalierung
  ------------------------ --------------------------------------------------

:: Abgrenzung zu qPDFView ::

Sowohl Lucide als auch qPDFView verwenden die poppler-Bibliothek zur Darstellung
von PDF-Dateien. Aufgrund interner Unterschiede der beiden Programme ist die
Anzeige mal beim einen und mal beim anderen Programm schneller. Insgesamt ist
unserer Meinung nach Lucide Ñhnlicher zu anderen OS/2 Programmen und besser mit
dem Betriebssystem integriert.
Die Entscheidung liegt aber beim Anwender. Er sollte das Programm verwenden, das
seine Anforderungen am besten erfÅllt.


:: Voraussetzungen::

Um alle benîtigten Komponenten in einem Schritt zu installieren, starten
sie bitte den Arca Noae Package Manager und kopieren sie den folgenden Text
in den 'Schnellinstallation-Dialog' (YUM -> Schnellinstallation...)

    libc libgcc1 libgcc-fwd poppler poppler-data libjpeg djvulibre uclip

Sollten sie lieber mit yum auf der Befehlszeile arbeiten, dann kînnen sie folgendes eingeben:

    yum install libc libgcc1 libgcc-fwd poppler poppler-data libjpeg djvulibre uclip

Anschlie·end bestÑtigen sie die Eingabe mit <Enter>.


Im Einzelnen benîtigt Lucide die folgenden Komponenten:

  - libc 0.6.6:
    - http://rpm.netlabs.org/release/00/zip/libc-0_6_6-38_oc00.zip (zip format)
      oder ftp://ftp.netlabs.org/pub/gcc/libc-0_6_6-csd6.wpi (WarpIn format)
      oder "yum install libc" (vom netlabs-rel repository)
  - libcx 0.6.3
    - http://rpm.netlabs.org/release/00/zip/libcx-0_6_4-1_oc00.zip (zip format)
       or "yum install libcx" (vom netlabs-rel repository)
  - gcc492.dll:
    - ftp://ftp.netlabs.org/pub/gcc/gcc4core-1_3_1.wpi (WarpIn format)
      oder "yum install libgcc1 libgcc-fwd" (vom netlabs-rel repository)

FÅr die Darstellung von PDF Dateien benîtigt Lucide:

    - poppler 0.59.0:
    - "yum install poppler" (vom netlabs-rel repository)

FÅr die Darstellung von DjVu-Dateien benîtigt Lucide:

    - djvulibre 3.5.27:
    - "yum install djvulibre" (vom netlabs-rel repository)

FÅr die Darstellung sÑmtlicher Formate des GBM-Plugins benîtigt Lucide:

    - GBMDLL 1.76:
    - "yum install GBMDLL" (vom arcanoae-rel repository)
    
FÅr die Darstellung von JPEG Bildern benîtigt Lucide:

    - libjpeg 8d:
    - "yum install libjpeg" (vom netlabs-rel repository) 
    - Only needed if you install the JPG plugin GBM provides JPG support
    - You should not install  JPG and GBM at the same time. (GBM is recommended)

Optional: Um Unicode-Text in die Zwischenablage im OpenOffice.org-kompatiblen
Format kopieren zu kînnen, mÅssen Sie das UClip-Paket (Enhanced OS/2
UnterstÅtzung der Zwischenablage) installieren (dieses Paket ist standardmÑ·ig
bei eComStation 2.0 RC1 und hîher oder ArcaOS Blue Lion installiert):

  - http://hobbes.nmsu.edu/cgi-bin/h-search?key=UClip
    oder "yum install uclip" (vom netlabs-rel repository)

Optional: Wenn Sie mit japanischen Schriften arbeiten, benîtigen Sie das
poppler-Daten-Paket.

  - "yum install poppler-data" (vom netlabs-rel repository)


Der PostScript-Druck erfordert einen PostScript-fÑhigen Drucker (PSCRIPT.DRV).


Eine vollstÑndige Liste der Funktionen und Verbesserungen finden sie unter:

  https://trac.netlabs.org/lucide/

FÅr Fehlermeldungen verwenden sie bitte:

  https://trac.netlabs.org/lucide/newticket

Bitte stellen Sie sicher, da· Sie die richtige Version und Komponenten fÅr
Ihr Ticket angeben.


:: Bekannte Probleme / EinschrÑnkungen:

Eine aktuelle Liste finden sie unter: https://trac.netlabs.org/lucide/report/1


:: 3rd-Party Erweiterungen ::

Die Bibliothek GBM (Generalised Bitmap Module) unterstÅtzt die Darstellung von
vielen verschiedenen Bitmap-Dateien. Sie enthÑlt au·erdem eine Reihe von nÅtzlichen
Dienstprogrammen fÅr die Befehlszeile, die verschiedenen VerÑnderungen und Formatumwandlungen
durchfÅhren kînnen. Die aktuelle Version unterstÅtzt BMP, JPG, JP2, PNG, TIF,
PBM, PGM, PPM, PNM, XPM, JBG und RAW-Dateien.

http://hobbes.nmsu.edu/h-search.php?key=gbmos2pm160_gbm176_lu143_moz147_bin_wpi

Achtung: Wenn sie GBM zur Darstellung von JPG-Bilddateienen verwenden wollen, dann sollten
sie das JPG Plugin von Lucide deaktivieren um Konflikte zu vermeiden (ticket #236).
Zur Deaktivierung benennen sie einfach die Datei lujpeg.dll im Lucide-Programmverzeichnis
in lujpeg.dl_ um (Lucide darf dafÅr nicht gestartet sein). Imdem sie den Datei wieder in
lujpeg.dll umbenennen und Lucide neu starten, kînnen sie das Plugin wieder aktivieren.


:: Pipe-Befehle:

Die erste gestartete Instanz von Lucide îffnet eine benannte Pipe mit dem Namen "\PIPE\Lucide".
Sie kînnen Lucide mit folgenden Befehlen Åber diese Pipe fernsteuern:

$prev              - zur vorherigen Seite wechseln
$next              - zur nÑchsten Seite wechseln
$presentation      - schaltet in den PrÑsentationsmodus (auch wenn Lucide minimiert ist)
$minimize          - minimiert Lucide (auch aus dem Vollbild-Modus)
$rotate            - dreht die Anzeige um 90¯ im Uhrzeigersinn
$zoomin            - vergrî·ern
$zoomout           - verkleinern
$zoomoriginal      - die Orginalgrî·e fÅr die Darstellung verwenden

Diese Befehle kînnen z.B. bei der Verwendung einer Fernbedienung nÅtzlich sein.


:: Lizenz bis einschlie·lich Version 1.21:

Die Lucide Versionen 1.21 und Ñlter sind ausschlie·lich fÅr den Einsatz mit eComStation lizenziert.
Sie sind nicht berechtigt, das Produkt durch Hochladen auf Internet-Server îffentlich zu verteilen
oder auf andere Weise îffentlich zugÑnglich machen.


:: Lizenz fÅr Version 1.3.0 und besser::

Beginnend mit Version 1.3.0 haben Mensys BV und Serenity Systems International
der Verîffentlichung Lucide von Lucide als Open Source zugestimmt. Gleichzeitig
wird weiter in das Produkt investiert.
Netlabs.org bedankt sich dafÅr bei Mensys BV und Serenity Systems International.

Arca Noae, LLC hat sich bereit erklÑrt, die Weiterentwicklung von Lucide ausgehend von
der Version 1.3.6 zu unterstÅtzen. Lucide bleibt Open Source, und wurde dual lizenziert.

Lucide ab der Version 1.3.0 ist unter der CDDL und der LGPL freigegeben.


:: Plugin-Lizenz:

Die Plugins sind unter CDDL / LGPL oder GPL verîffentlicht, je nach dem Plugin. Siehe
http://svn.netlabs.org/lucide/ fÅr weitere Informationen und Quellcode.


:: Links::

http://www.netlabs.org
https://www.arcanoae.com


:: Copyright::

(C) 2006-2007 von Eugene Romanenko, netlabs.org
(C) 2010 von Dmitri A. Kuminov, netlabs.org
    in Kooperation mit Serenity Systems International
(c) 2016-2019 von netlabs.org
    in Kooperation mit Arca Noae, LLC
