:: Lucide ::

Lucide e' un visualizzatore di documenti basato su plugin, con supporto per molteplici formati di files.

Fornisce un'architettura plugin basata su SOM che consente a programmatori di terze parti di aggiungere
facilmente ulteriori plugins.


:: Plugins ::

   Estensioni supportate         Caratteristiche supportate
  --------------------------------------------------------------------------
         PDF                   Ridimensionamento, Rotazione, Navigazione,
                               Selezione testo, Ricerca, Rendering asincrono,
                               Stampa PostScript

         DJVU                  Ridimensionamento, Stampa PostScript

         JPG                   Ridimensionamento
  --------------------------------------------------------------------------


:: Requisiti ::

Lucide richiede i seguenti pacchetti per il suo funzionamento:

  - libc 0.6.4:
    - ftp://ftp.netlabs.org/pub/gcc/libc-0.6.4-csd4.zip (format zip)
      or ftp://ftp.netlabs.org/pub/gcc/libc-0..6.4-csd4.wpi (formato WarpIn)
  - gcc446.dll:
    - ftp://ftp.netlabs.org/pub/gcc/gcc4core-1_2_1.wpi (formato WarpIn)

Opzionale: per inserire testo unicode dagli appunti in formato compatibile
Openoffice.org, e' necessario installare il pacchetto UClip (supporto appunti
avanzato per OS/2, installato automaticamente in eComStation 2.0 RC1 e successive):

  - http://hobbes.nmsu.edu/cgi-bin/h-search?key=UClip

La stampa PostScript richiede una stampante abilitata alla gestione di dati 
PostScript (pscript.drv).

Per vedere una lista completa di tutte le caratteristiche supportate, consultare 
il servizio TRAC per Lucide all'indirizzo web:

  http://svn.netlabs.org/lucide/

Per segnalare un eventuale bug riscontrato, comunicarlo utilizzando il servizio 
TRAC, vedere:

  http://svn.netlabs.org/lucide/newticket

Assicuratevi di selezionare la versione corretta ed il componente esatto per il
vostro ticket!.



:: Problemi conosciuti/limitazioni ::

Generale: stampa pagine pari/dispari non disponibile per stampanti postscript.
          ( http://svn.netlabs.org/lucide/ticket/87#comment:4 )


:: Comandi Pipe ::

La prima istanza di Lucide crea una named pipe chiamata \PIPE\LUCIDE. 
E' possibile inviare i seguenti comandi a tale pipe:

$prev              - vai alla pagina precedente
$next              - vai alla pagina successiva
$presentation      - vai a tutto schermo (anche se minimizzato)
$minimize          - minimizza Lucide (anche se a tutto schermo)
$rotate            - ruota 90 gradi in senso orario
$zoomin            - ingrandisci vista
$zoomout           - riduci vista
$zoomoriginal      - zoom al livello originale

Questi comandi possono essere utili per il controllo remoto di una
presentazione.


:: Licenza fino alla versione 1.21 ::

La licenza di Lucide 1.21 e precedenti ne consente l'utilizzo solo con eComStation. 
Non e' consentita la distribuzione del prodotto su servers Internet aperti al
pubblico o tramite analogo altro sistema disponibile.


:: Licenza dalla versione 1.3.0 e successive ::

A partire dalla versione 1.3.0, Mensys BV e Serenity Systems International 
hanno acconsentito a pubblicare Lucide sotto licenza opensource, pur continuando
ad investire nel prodotto.
Netlabs.org esprime gratitudine a Mensys BV and Serenity Systems International.

Lucide dalla versione 1.3.0 e' rilasciato e distribuito con licenza CDDL/LGPL.


:: Licenza plugin ::

Le estensioni sono rilasciate sotto licenza CDDL/LGPL o GPL, a seconda del plugin.
Vedere http://svn.netlabs.org/lucide/ per ulteriori informazioni e per ottenere
il codice sorgente.


:: Links ::

http://www.netlabs.org
http://www.ecomstation.com


:: Copyright ::

(c) 2006-2007 by Eugene Romanenko, netlabs.org
(c) 2010-2011 by Dmitriy Kuminov, netlabs.org
    in cooperazione con Serenity Systems International

