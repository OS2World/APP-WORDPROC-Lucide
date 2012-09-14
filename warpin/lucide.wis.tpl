<!-- This is the profile for installing Lucide core and plugins. -->

<WARPIN
     OS="OS2_3x"
     CODEPAGE=850
>
<HEAD>

<!-- Every .WPI archive contains one or more packages. -->
<REXX NAME=ChkREQ>
    call RxFuncAdd 'SysLoadFuncs', 'REXXUTIL', 'SysLoadFuncs'
    call SysLoadFuncs
    /* based upon work from Dmitriy Kuminov */
    parse arg aFile " Package:" Package
    name = filespec('N', aFile)
    ext = translate(right(name, 4))
    search_path = ""
    select
      when (ext == '.DLL') then do
        config_sys = SysBootDrive()'\CONFIG.SYS'
        do while lines(config_sys)
          line = strip(linein(config_sys))
          if (left(line, 8) == 'LIBPATH=') then do
            search_path = substr(line, 9)
            leave
          end
        end
        call lineout config_sys
        search_path = SysQueryExtLibPath('B')';'search_path';'SysQueryExtLibPath('E')
      end
      when (ext == '.EXE') then search_path = value('PATH',, 'OS2ENVIRONMENT')
      when (ext == '.HLP') then search_path = value('BOOKSHELF',, 'OS2ENVIRONMENT')
      otherwise search_path = ''
    end
    if (search_path \= '') then do
      ok = value('CHKREQ_SEARCH_PATH', search_path, 'OS2ENVIRONMENT')
      real_file = SysSearchPath('CHKREQ_SEARCH_PATH', name)
      ok = value('CHKREQ_SEARCH_PATH', '', 'OS2ENVIRONMENT')
    end
    else real_file = ""

    /* generate the message string to return */
    if real_file <> "" then MsgStr = ""; else MsgStr = 'REQUIRES="' || strip(Package) || '"'
    return MsgStr
</REXX>


<REXX NAME=nls>
call RxFuncAdd 'SysLoadFuncs', 'REXXUTIL', 'SysLoadFuncs'
call SysLoadFuncs
langs = "EN,FR,DE,NL,ES,SV"
lang = translate(left(strip(value("LANG",,"OS2ENVIRONMENT")),2))
if pos(lang,langs) = 0 then lang = 'EN'
rc =WirexxPutEnv('prog','Lucide')
rc =WirexxPutEnv('brand','eCS (OS/2)')
select
  when lang = 'FR' then do
    rc =WirexxPutEnv('title','Lucide - Afficheur de document')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('welcome','Bienvenue dans l''installation du ')
    rc =WirexxPutEnv('accept','Veuillez prendre connaissance et accepter l''accord de licence suivant.')
    rc =WirexxPutEnv('target','Veuillez sÇlectionner le dossier de destination')
    rc =WirexxPutEnv('re_install','Si vous effectuez une mise Ö jour de SearchPlus, le dossier d''installation par dÇfaut sera celui actuellement utilisÇ par l''ancienne version.')
    rc =WirexxPutEnv('ready','Veuillez confirmer les options d''installation.')
    rc =WirexxPutEnv('scfind','Modifications du fichier CONFIG.SYS prÇvues: paramÇtrage de la variable SCFINDUTILITY Ö SearchPlus.exe pour en faire le programme de recherche du systäme par dÇfaut. Ces modifications nÇcessiteront un redÇmarrage.')
    rc =WirexxPutEnv('over_write','Veuillez sÇlectionner de maniäre Ö Çcraser tout fichier existant.')
    rc =WirexxPutEnv('install','~Install')
    rc =WirexxPutEnv('license','~J''accepte')
    rc =WirexxPutEnv('next','~Suivant')
    rc =WirexxPutEnv('fr_sel','SELECT DESELECT')
    rc =WirexxPutEnv('nextText','Select "Suivant" to continue.')
    rc =WirexxPutEnv('cancelText','Select "Cancel" to abort installation.')
    rc =WirexxPutEnv('installText','Press "Install" in order to start installation of this archive.')
  end
  when lang = 'DE' then do
    rc =WirexxPutEnv('title','Lucide - Dokumentenbetrachter')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('welcome','Willkommen zur Installation des ')
    rc =WirexxPutEnv('accept','Bitte lesen Sie den folgenden Text und akzeptieren Sie die Lizenzvereinbarung.')
    rc =WirexxPutEnv('target','WÑhlen Sie bitte das Zielverzeichnis.')
    rc =WirexxPutEnv('re_install','Wenn dies ein Update ist, dann ist das Installationsverzeichnis das aktuelle Verzeichnis des Plugins.')
    rc =WirexxPutEnv('install','~Installieren')
    rc =WirexxPutEnv('license','St~imme zu')
    rc =WirexxPutEnv('next','W~eiter')
    rc =WirexxPutEnv('de_sel','SELECT DESELECT')
    rc =WirexxPutEnv('nextText','Zum Fortfahren "Weiter" auswÑhlen.')
    rc =WirexxPutEnv('cancelText','Zum Abbrechen "Cancel" auswÑhlen.')
    rc =WirexxPutEnv('installText','Bitte "Installieren" auswÑhlen, um die Installation des Archivs zu starten.')
  end
  when lang = 'NL' then do
    rc =WirexxPutEnv('title','Lucide - Document Bekijker')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('welcome','Welcome to the installation of ')
    rc =WirexxPutEnv('accept','Please read and accept the following license-agreement.')
    rc =WirexxPutEnv('target','Please select target directory.')
    rc =WirexxPutEnv('re_install','If you are updating the Lucide for NetDrive, the default installation directory will be the current directory.')
    rc =WirexxPutEnv('install','~Install')
    rc =WirexxPutEnv('license','I ~accept')
    rc =WirexxPutEnv('next','~Next')
    rc =WirexxPutEnv('nl_sel','SELECT DESELECT')
    rc =WirexxPutEnv('nextText','Select "Next" to continue.')
    rc =WirexxPutEnv('cancelText','Select "Cancel" to abort installation.')
    rc =WirexxPutEnv('installText','Press "Install" in order to start installation of this archive.')
  end
  when lang = 'ES' Then Do
    rc =WirexxPutEnv('title','Lucide - Visor de documentos')
    rc =WirexxPutEnv('plug_pdf','Plugin PDF para Lucide')
    rc =WirexxPutEnv('plug_djvu','Plugin DjVu para Lucide')
    rc =WirexxPutEnv('plug_jpeg','Plugin JPEG para Lucide')
    rc =WirexxPutEnv('welcome','Welcome to the installation of ')
    rc =WirexxPutEnv('accept','Please read and accept the following license-agreement.')
    rc =WirexxPutEnv('target','Please select target directory.')
    rc =WirexxPutEnv('re_install','If you are updating the Lucide for NetDrive, the default installation directory will be the current directory.')
    rc =WirexxPutEnv('install','~Install')
    rc =WirexxPutEnv('license','I ~accept')
    rc =WirexxPutEnv('next','~Next')
    rc =WirexxPutEnv('es_sel','SELECT DESELECT')
    rc =WirexxPutEnv('nextText','Select "Next" to continue.')
    rc =WirexxPutEnv('cancelText','Select "Cancel" to abort installation.')
    rc =WirexxPutEnv('installText','Press "Install" in order to start installation of this archive.')
  end
  when lang = 'SV' Then Do
    rc =WirexxPutEnv('title','Lucide - Dokumentvisare')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('welcome','Welcome to the installation of ')
    rc =WirexxPutEnv('accept','Please read and accept the following license-agreement.')
    rc =WirexxPutEnv('target','Please select target directory.')
    rc =WirexxPutEnv('re_install','If you are updating the Lucide for NetDrive, the default installation directory will be the current directory.')
    rc =WirexxPutEnv('install','~Install')
    rc =WirexxPutEnv('license','I ~accept')
    rc =WirexxPutEnv('next','~Next')
    rc =WirexxPutEnv('sv_sel','SELECT DESELECT')
    rc =WirexxPutEnv('nextText','Select "Next" to continue.')
    rc =WirexxPutEnv('cancelText','Select "Cancel" to abort installation.')
    rc =WirexxPutEnv('installText','Press "Install" in order to start installation of this archive.')
  end
  otherwise do
    rc =WirexxPutEnv('title','Lucide - Document Viewer')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('welcome','Welcome to the installation of the Lucide for NetDrive!')
    rc =WirexxPutEnv('accept','Please read and accept the following license-agreement.')
    rc =WirexxPutEnv('target','Please select target directory.')
    rc =WirexxPutEnv('re_install','If you are updating the Lucide for NetDrive, the default installation directory will be the current directory.')
    rc =WirexxPutEnv('install','~Install')
    rc =WirexxPutEnv('license','I ~accept')
    rc =WirexxPutEnv('next','~Next')
    rc =WirexxPutEnv('en_sel','SELECT DESELECT')
    rc =WirexxPutEnv('nextText','Select "Next" to continue.')
    rc =WirexxPutEnv('cancelText','Select "Cancel" to abort installation.')
    rc =WirexxPutEnv('installText','Press "Install" in order to start installation of this archive.')
  end
end
return ''
</REXX>
<REXX NAME=get_env>
Parse Arg subject .
Return WirexxGetEnv(subject)
</REXX>
<REXX NAME=set_assoc>
ans = WirexxShowMessage(WirexxGetEnv('title'),'Make Lucide the default program for PDF files?',4)
If ans = 6 Then Do
  /* clear any previous associations */
  Call SysIni 'USER','PMWP_ASSOC_FILTER','*.PDF','DELETE:'
  Call SysIni 'USER','PMWP_ASSOC_FILTER','*PDF','DELETE:'
  Call SysIni 'USER','PMWP_ASSOC_TYPE','Acrobat Document','DELETE:'
  Call SysIni 'USER','PMWP_ASSOC_TYPE','Adobe Portable Document Format','DELETE:'
End
Return ''
</REXX>
<REXX NAME=readme_xx>
readme = "readme.txt"
return readme
</REXX>

<TITLE>=("get_env title")</TITLE>
<PCK INDEX=1
     PACKAGEID="netlabs.org\Lucide\Lucide core\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(WARPIN_DEFAULTAPPSPATH)\Lucide"
     BASE
     =("nls")
     =("set_assoc")
     TITLE="=("get_env title")"
     WRITEPROFILE="USER\Lucide\Path|$(1)"
     CLEARPROFILE="USER\Lucide\Path"
     =("ChkREQ LIBC065.DLL Package:netlabs.org\kLIBC\LIBC 0.6 Runtime\0\6\5")
     =("ChkREQ GCC446.DLL Package:netlabs.org\GCC4\Core\1\2\0")
     =("ChkREQ STDCPP.DLL Package:netlabs.org\GCC4\Core\1\2\1")
     SELECT
     >=("get_env title").</PCK>

<PCK INDEX=2
     PACKAGEID="netlabs.org\Lucide\Lucide plugin PDF\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="=("get_env plug_pdf")"
     REQUIRES=1
     SELECT | FIXED
     >=("get_env plug_pdf")</PCK>

<PCK INDEX=3
     PACKAGEID="netlabs.org\Lucide\Lucide plugin DJVU\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="=("get_env plug_djvu")"
     REQUIRES=1
     SELECT | FIXED
     >=("get_env plug_djvu")</PCK>

<PCK INDEX=4
     PACKAGEID="netlabs.org\Lucide\Lucide plugin JPEG\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="=("get_env plug_jpeg")"
     REQUIRES=1
     SELECT | FIXED
     >=("get_env plug_jpeg")</PCK>
<PCK INDEX=5
     PACKAGEID="netlabs.org\Lucide\english\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="English"
     CREATEOBJECT='WPFolder|=("get_env prog") for =("get_env brand")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env prog") for =("get_env brand");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT='WPProgram|ReadMe|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_README>;TITLE=ReadMe;PROGTYPE=PM;PARAMETERS=$(1)\readme;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Changelog|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Changelog;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env en_sel")
     >English</PCK>
<PCK INDEX=6
     PACKAGEID="netlabs.org\Lucide\francais\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="Francais"
     CREATEOBJECT='WPFolder|=("get_env prog") pour =("get_env brand")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env prog") pour =("get_env brand");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT='WPProgram|Lucide LisezMoi|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_README>;TITLE=Lisez Moi;PROGTYPE=PM;PARAMETERS=$(1)\readme_fr.txt;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Change Log|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Change Log;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env fr_sel")
     >Francais</PCK>
<PCK INDEX=7
     PACKAGEID="netlabs.org\Lucide\deutsch\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="Deutsch"
     CREATEOBJECT='WPFolder|=("get_env prog") fÅr =("get_env brand")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env prog") fÅr =("get_env brand");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT='WPProgram|Lies mich!|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_README>;TITLE=Lies mich!;PROGTYPE=PM;PARAMETERS=$(1)\readme_de.txt;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Entwicklungsgeschichte|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Entwicklungsgeschichte;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env de_sel")
     >Deutsch</PCK>
<PCK INDEX=8
     PACKAGEID="netlabs.org\Lucide\dutch\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="Dutch"
     CREATEOBJECT='WPFolder|=("get_env prog") voor =("get_env brand")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env prog") voor =("get_env brand");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT='WPProgram|Lees mij|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_README>;TITLE=Lees mij;PROGTYPE=PM;PARAMETERS=$(1)\readme_nl.txt;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Changelog|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Changelog;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env nl_sel")
     >Dutch</PCK>
<PCK INDEX=9
     PACKAGEID="netlabs.org\Lucide\espanol\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="Espanol"
     CREATEOBJECT='WPFolder|=("get_env prog") para =("get_env brand")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env prog") para =("get_env brand");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT='WPProgram|LÇeme de Lucide|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_README>;TITLE=LÇeme de Lucide;PROGTYPE=PM;PARAMETERS=$(1)\readme_es.txt;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Change Log|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Changelog;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env es_sel")
     >Espanol</PCK>
<PCK INDEX=10
     PACKAGEID="netlabs.org\Lucide\sverige\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="Sverige"
     CREATEOBJECT='WPFolder|=("get_env prog") fîr =("get_env brand")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env prog") fîr =("get_env brand");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT='WPProgram|LÑs mig|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_README>;TITLE=LÑs mig;PROGTYPE=PM;PARAMETERS=$(1)\readme;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Changelog|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Changelog;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env sv_sel")
     >Sverige</PCK>
</HEAD>

<!-- Here come the different pages. They are linked by
     the <NEXTBUTTON> tags, which must have a target.
     Each page must have a TYPE= attribute, which tells
     WarpIn what will be visible on that page. -->

<BODY>	

<!-- The TYPE_README will show a README text in a multi-line entry field. -->

<PAGE INDEX=1 TYPE=README>
<NEXTBUTTON TARGET=2>=("get_env next")</NEXTBUTTON>
<TEXT>
=("get_env nextText")
=("get_env cancelText")
</TEXT>

<README FORMAT=HTML>
<B>=("get_env welcome")=("get_env title"), version ${VERSION}.${WPIBUILD}</B>

<P>
=("get_env prog") is a plugin based document viewer for eComStation. In its first incarnation
it supports PDF, DjVu and JPEG files but new document types can easily be added to it.
<P>
<P>
<BR>
Features:
<UL>
  <LI>PDF, DjVu and JPEG Support
  <LI>Drag and Drop Support
  <LI>Fast and small
</UL>
<P>
<BR>
For further details please visit the =("get_env prog") project homepage:<BR>
<U><a href="http://svn.netlabs.org/lucide/">http://svn.netlabs.org/lucide/</a></U>
<BR>
</README>
</PAGE>

<PAGE INDEX=2 TYPE=README>
<NEXTBUTTON TARGET=3>=("get_env next")</NEXTBUTTON>
<TEXT>
The following list describes what is new in this version of =("get_env prog").
</TEXT>
<README FORMAT=PLAIN EXTRACTFROMPCK="1">changelog</README>
</PAGE>

<PAGE INDEX=3 TYPE=README>
<NEXTBUTTON TARGET=4>=("get_env license")</NEXTBUTTON>
<TEXT>
=("get_env accept")
</TEXT>
<README FORMAT=HTML>
<B>LICENSE</B>
<P>
Starting with version 1.3.0 Mensys BV and Serenity Systems International
have agreed in opensourcing Lucide, while still investing in the product.
Netlabs.org would like to express it's gratitude toward Mensys BV and
Serenity Systems International.</P>
<P>
Lucide as of version 1.3.0 is released and distributed under <U><a href="http://opensource.org/licenses/cddl1.php">CDDL</a></U>/<U><a href="http://www.gnu.org/licenses/lgpl.html">LGPL</a></U>.</P>
<P>
The plugins are released under CDDL/LGPL or GPL, depending on the plugin. See
<U><a href="http://svn.netlabs.org/lucide/">http://svn.netlabs.org/lucide/</a></U> for more information and source code.</P>
</README>
</PAGE>

<!-- The TYPE=CONTAINER will list the packages which can be installed. -->

<PAGE INDEX=4 TYPE=CONTAINER>
<NEXTBUTTON TARGET=6>=("get_env next")</NEXTBUTTON>
<TEXT>
=("get_env target")
</TEXT>
</PAGE>


<!-- The TYPE=CONFIGURE will allow the user to set the CONFIG.SYS and
     WPS classes/objects stuff.

     NOTE that we skip this target since 1.32 to avoid inconsistency that could
     happen should the user deselect creation of WPS objects (see ticket:128
     for details). -->

<PAGE INDEX=5 TYPE=CONFIGURE>
<NEXTBUTTON TARGET=6>=("get_env next")</NEXTBUTTON>
<TEXT>

Please select additional configuration that WarpIN should perform after installing this archive.

</TEXT>
</PAGE>

<PAGE INDEX=6 TYPE=TEXT>
<NEXTBUTTON TARGET=0>=("get_env install")</NEXTBUTTON>
<TEXT>


=("get_env installText")</TEXT>
</PAGE>
</BODY>
</WARPIN>
