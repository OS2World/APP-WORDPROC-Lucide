:: �ber Lucide ::

Lucide ist ein Plugin-basierter Dokumentenbetrachter der verschiedene Dateiformate unterst�tzt.

Es bietet eine Plugin-Architektur basierend auf SOM, die es Fremdanbietern erlaubt,
relativ einfach Plugins f�r die Darstellung weiterer Dateitypen hinzuzuf�gen.


:: Plugins::

   Unterst�tzte Dateitypen Unterst�tzte Funktionen
  ------------------------ --------------------------------------------------
         PDF               Skalierung, Drehung, Navigation, Textauswahl
                           Suchen, Asynchrones Rendering,
                           Ausf�llen von Formularen, PostScript-Druck

         DJVU              Skalierung, PostScript-Druck

         JPG               Skalierung
  ------------------------ --------------------------------------------------

:: Abgrenzung zu qPDFView ::

Sowohl Lucide als auch qPDFView verwenden die poppler-Bibliothek zur Darstellung
von PDF-Dateien. Aufgrund interner Unterschiede der beiden Programme ist die
Anzeige mal beim einen und mal beim anderen Programm schneller. Insgesamt ist
unserer Meinung nach Lucide �hnlicher zu anderen OS/2 Programmen und besser mit
dem Betriebssystem integriert.
Die Entscheidung liegt aber beim Anwender. Er sollte das Programm verwenden, das
seine Anforderungen am besten erf�llt.


:: Voraussetzungen::

Um alle ben�tigten Komponenten in einem Schritt zu installieren, starten
sie bitte den Arca Noae Package Manager und kopieren sie den folgenden Text
in den 'Schnellinstallation-Dialog' (YUM -> Schnellinstallation...)

    libc libgcc1 libgcc-fwd poppler poppler-data libjpeg djvulibre uclip

Sollten sie lieber mit yum auf der Befehlszeile arbeiten, dann k�nnen sie folgendes eingeben:

    yum install libc libgcc1 libgcc-fwd poppler poppler-data libjpeg djvulibre uclip

Anschlie�end best�tigen sie die Eingabe mit <Enter>.


Im Einzelnen ben�tigt Lucide die folgenden Komponenten:

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

F�r die Darstellung von PDF Dateien ben�tigt Lucide:

    - poppler 0.59.0:
    - "yum install poppler" (vom netlabs-rel repository)

F�r die Darstellung von DjVu-Dateien ben�tigt Lucide:

    - djvulibre 3.5.27:
    - "yum install djvulibre" (vom netlabs-rel repository)

F�r die Darstellung s�mtlicher Formate des GBM-Plugins ben�tigt Lucide:

    - GBMDLL 1.76:
    - "yum install GBMDLL" (vom arcanoae-rel repository)
    
F�r die Darstellung von JPEG Bildern ben�tigt Lucide:

    - libjpeg 8d:
    - "yum install libjpeg" (vom netlabs-rel repository) 
    - Only needed if you install the JPG plugin GBM provides JPG support
    - You should not install  JPG and GBM at the same time. (GBM is recommended)

Optional: Um Unicode-Text in die Zwischenablage im OpenOffice.org-kompatiblen
Format kopieren zu k�nnen, m�ssen Sie das UClip-Paket (Enhanced OS/2
Unterst�tzung der Zwischenablage) installieren (dieses Paket ist standardm��ig
bei eComStation 2.0 RC1 und h�her oder ArcaOS Blue Lion installiert):

  - http://hobbes.nmsu.edu/cgi-bin/h-search?key=UClip
    oder "yum install uclip" (vom netlabs-rel repository)

Optional: Wenn Sie mit japanischen Schriften arbeiten, ben�tigen Sie das
poppler-Daten-Paket.

  - "yum install poppler-data" (vom netlabs-rel repository)


Der PostScript-Druck erfordert einen PostScript-f�higen Drucker (PSCRIPT.DRV).


Eine vollst�ndige Liste der Funktionen und Verbesserungen finden sie unter:

  https://trac.netlabs.org/lucide/

F�r Fehlermeldungen verwenden sie bitte:

  https://trac.netlabs.org/lucide/newticket

Bitte stellen Sie sicher, da� Sie die richtige Version und Komponenten f�r
Ihr Ticket angeben.


:: Bekannte Probleme / Einschr�nkungen:

Eine aktuelle Liste finden sie unter: https://trac.netlabs.org/lucide/report/1


:: 3rd-Party Erweiterungen ::

Die Bibliothek GBM (Generalised Bitmap Module) unterst�tzt die Darstellung von
vielen verschiedenen Bitmap-Dateien. Sie enth�lt au�erdem eine Reihe von n�tzlichen
Dienstprogrammen f�r die Befehlszeile, die verschiedenen Ver�nderungen und Formatumwandlungen
durchf�hren k�nnen. Die aktuelle Version unterst�tzt BMP, JPG, JP2, PNG, TIF,
PBM, PGM, PPM, PNM, XPM, JBG und RAW-Dateien.

http://hobbes.nmsu.edu/h-search.php?key=gbmos2pm160_gbm176_lu143_moz147_bin_wpi

Achtung: Wenn sie GBM zur Darstellung von JPG-Bilddateienen verwenden wollen, dann sollten
sie das JPG Plugin von Lucide deaktivieren um Konflikte zu vermeiden (ticket #236).
Zur Deaktivierung benennen sie einfach die Datei lujpeg.dll im Lucide-Programmverzeichnis
in lujpeg.dl_ um (Lucide darf daf�r nicht gestartet sein). Imdem sie den Datei wieder in
lujpeg.dll umbenennen und Lucide neu starten, k�nnen sie das Plugin wieder aktivieren.


:: Pipe-Befehle:

Die erste gestartete Instanz von Lucide �ffnet eine benannte Pipe mit dem Namen "\PIPE\Lucide".
Sie k�nnen Lucide mit folgenden Befehlen �ber diese Pipe fernsteuern:

$prev              - zur vorherigen Seite wechseln
$next              - zur n�chsten Seite wechseln
$presentation      - schaltet in den Pr�sentationsmodus (auch wenn Lucide minimiert ist)
$minimize          - minimiert Lucide (auch aus dem Vollbild-Modus)
$rotate            - dreht die Anzeige um 90� im Uhrzeigersinn
$zoomin            - vergr��ern
$zoomout           - verkleinern
$zoomoriginal      - die Orginalgr��e f�r die Darstellung verwenden

Diese Befehle k�nnen z.B. bei der Verwendung einer Fernbedienung n�tzlich sein.


:: Lizenz bis einschlie�lich Version 1.21:

Die Lucide Versionen 1.21 und �lter sind ausschlie�lich f�r den Einsatz mit eComStation lizenziert.
Sie sind nicht berechtigt, das Produkt durch Hochladen auf Internet-Server �ffentlich zu verteilen
oder auf andere Weise �ffentlich zug�nglich machen.


:: Lizenz f�r Version 1.3.0 und besser::

Beginnend mit Version 1.3.0 haben Mensys BV und Serenity Systems International
der Ver�ffentlichung Lucide von Lucide als Open Source zugestimmt. Gleichzeitig
wird weiter in das Produkt investiert.
Netlabs.org bedankt sich daf�r bei Mensys BV und Serenity Systems International.

Arca Noae, LLC hat sich bereit erkl�rt, die Weiterentwicklung von Lucide ausgehend von
der Version 1.3.6 zu unterst�tzen. Lucide bleibt Open Source, und wurde dual lizenziert.

Lucide ab der Version 1.3.0 ist unter der CDDL und der LGPL freigegeben.


:: Plugin-Lizenz:

Die Plugins sind unter CDDL / LGPL oder GPL ver�ffentlicht, je nach dem Plugin. Siehe
http://svn.netlabs.org/lucide/ f�r weitere Informationen und Quellcode.


:: Links::

http://www.netlabs.org
https://www.arcanoae.com


:: Copyright::

(C) 2006-2007 von Eugene Romanenko, netlabs.org
(C) 2010 von Dmitri A. Kuminov, netlabs.org
    in Kooperation mit Serenity Systems International
(c) 2016-2019 von netlabs.org
    in Kooperation mit Arca Noae, LLC
