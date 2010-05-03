
<!-- This is the profile for installing Lucide core and plugins. -->

<WARPIN
     OS="OS2_3x"
     CODEPAGE=850
>

<!-- Every .WPI archive contains one or more packages. -->

<HEAD>
<TITLE>=("title")</TITLE>
<REXX NAME=title>
Call Rxfuncadd 'SysLoadFuncs','RexxUtil','SysLoadFuncs'
Call SysLoadFuncs
/* get boot drive language */
_lang = Value('lang',,'os2environment')
_id = Translate(Left(_lang,2))
If _id = 'ZH' Then Do
 _id = Translate(Substr(_lang,3,2))
 If _id = 'CN' Then _id = 'CX'
End
Select
 When _id = 'DE' Then Do
  _title = 'Lucide - Document Viewer'
  _folder = 'Lucide for eCS'
  _prog = 'Lucide'
  _readme = 'Lucide Readme'
  _change = 'Lucide Change Log'
  _plug_pdf = 'Lucide PDF plugin'
  _plug_djvu = 'Lucide DjVu plugin'
  _plug_jpeg = 'Lucide JPEG plugin'
 End
 When _id = 'NL' Then Do
  _title = 'Lucide - Document Bekijker'
  _folder = 'Lucide for eCS'
  _prog = 'Lucide'
  _readme = 'Lucide Readme'
  _change = 'Lucide Change Log'
  _plug_pdf = 'Lucide PDF plugin'
  _plug_djvu = 'Lucide DjVu plugin'
  _plug_jpeg = 'Lucide JPEG plugin'
 End
 When _id = 'FR' Then Do
  _title = 'Lucide - Afficheur de document'
  _folder = 'Lucide for eCS'
  _prog = 'Lucide'
  _readme = 'Lucide Readme'
  _change = 'Lucide Change Log'
  _plug_pdf = 'Lucide PDF plugin'
  _plug_djvu = 'Lucide DjVu plugin'
  _plug_jpeg = 'Lucide JPEG plugin'
 End
 When _id = 'ES' Then Do
  _title = 'Lucide - Visor de documentos'
  _folder = 'Lucide para eCS'
  _prog = 'Lucide'
  _readme = 'L�eme de Lucide'
  _change = 'Lucide Change Log'
  _plug_pdf = 'Plugin PDF para Lucide'
  _plug_djvu = 'Plugin DjVu para Lucide'
  _plug_jpeg = 'Plugin JPEG para Lucide'
 End
 When _id = 'SV' Then Do
  _title = 'Lucide - Dokumentvisare'
  _folder = 'Lucide for eCS'
  _prog = 'Lucide'
  _readme = 'Lucide Readme'
  _change = 'Lucide Change Log'
  _plug_pdf = 'Lucide PDF plugin'
  _plug_djvu = 'Lucide DjVu plugin'
  _plug_jpeg = 'Lucide JPEG plugin'
 End
 Otherwise Do
  _title = 'Lucide - Document Viewer'
  _folder = 'Lucide for eCS'
  _prog = 'Lucide'
  _readme = 'Lucide Readme'
  _change = 'Lucide Change Log'
  _plug_pdf = 'Lucide PDF plugin'
  _plug_djvu = 'Lucide DjVu plugin'
  _plug_jpeg = 'Lucide JPEG plugin'
 End
End
rc = WirexxPutEnv('title',_title)
rc = WirexxPutEnv('folder',_folder)
rc = WirexxPutEnv('prog',_prog)
rc = WirexxPutEnv('readme',_readme)
rc = WirexxPutEnv('change',_change)
rc = WirexxPutEnv('plug_pdf',_plug_pdf)
rc = WirexxPutEnv('plug_djvu',_plug_djvu)
rc = WirexxPutEnv('plug_jpeg',_plug_jpeg)
Return _title
</REXX>
<REXX NAME=folder>
Return WirexxGetEnv('folder')
</REXX>
<REXX NAME=prog>
ans = WirexxShowMessage(WirexxGetEnv('title'),'Make Lucide the default program for PDF files?',4)
If ans = 6 Then Do
 /* clear any previous associations */
 Call SysIni 'USER','PMWP_ASSOC_FILTER','*.PDF','DELETE:'
 Call SysIni 'USER','PMWP_ASSOC_FILTER','*PDF','DELETE:'
 Call SysIni 'USER','PMWP_ASSOC_TYPE','Acrobat Document','DELETE:'
End
Return WirexxGetEnv('prog')
</REXX>
<REXX NAME=readme>
Return WirexxGetEnv('readme')
</REXX>
<REXX NAME=change>
Return WirexxGetEnv('change')
</REXX>
<REXX NAME=plug_pdf>
Return WirexxGetEnv('plug_pdf')
</REXX>
<REXX NAME=plug_djvu>
Return WirexxGetEnv('plug_djvu')
</REXX>
<REXX NAME=plug_jpeg>
Return WirexxGetEnv('plug_jpeg')
</REXX>
<PCK INDEX=1
     PACKAGEID="netlabs.org\Lucide\Lucide core\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(WARPIN_DEFAULTAPPSPATH)\Lucide"
     BASE
     TITLE="=("title")"
     CREATEOBJECT='WPFolder|=("folder")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='REPLACE WPProgram|=("prog")|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT='REPLACE WPProgram|=("readme")|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_README>;PROGTYPE=PM;PARAMETERS=$(1)\readme;STARTUPDIR=$(1);'
     CREATEOBJECT='REPLACE WPProgram|=("change")|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     WRITEPROFILE="USER\Lucide\Path|$(1)"
     CLEARPROFILE="USER\Lucide\Path"
     REQUIRES="netlabs.org\kLIBC\LIBC 0.6 Runtime\0\6\3"
     REQUIRES="netlabs.org\GCC4\Runtime\4\4\2\20091204"
     SELECT
     >=("title").</PCK>

<PCK INDEX=2
     PACKAGEID="netlabs.org\Lucide\Lucide plugin PDF\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="=("plug_pdf")"
     REQUIRES=1
     SELECT | FIXED
     >=("plug_pdf")</PCK>

<PCK INDEX=3
     PACKAGEID="netlabs.org\Lucide\Lucide plugin DJVU\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="=("plug_djvu")"
     REQUIRES=1
     SELECT | FIXED
     >=("plug_djvu")</PCK>

<PCK INDEX=4
     PACKAGEID="netlabs.org\Lucide\Lucide plugin JPEG\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="=("plug_jpeg")"
     REQUIRES=1
     SELECT | FIXED
     >=("plug_jpeg")</PCK>

</HEAD>

<!-- Here come the different pages. They are linked by
     the <NEXTBUTTON> tags, which must have a target.
     Each page must have a TYPE= attribute, which tells
     WarpIn what will be visible on that page. -->

<BODY>

<!-- The TYPE_README will show a README text in a multi-line entry field. -->

<PAGE INDEX=1 TYPE=README>
<NEXTBUTTON TARGET=2>~Next</NEXTBUTTON>
<TEXT>
Select "Next" to continue.
Select "Cancel" to abort installation.
</TEXT>

<README FORMAT=HTML>
<B>Lucide for eComStation, version ${VERSION} ${BUILD}</B>
<P>
Lucide is a plugin based document viewer for eComStation. In its first incarnation
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
For further details please visit the Lucide project homepage:<BR>
http://svn.netlabs.org/lucide/
<BR>
</README>
</PAGE>

<PAGE INDEX=2 TYPE=README>
<NEXTBUTTON TARGET=3>~Next</NEXTBUTTON>
<TEXT>
The following list describes what is new in this version of Lucide.
</TEXT>
<README FORMAT=PLAIN EXTRACTFROMPCK="1">changelog</README>
</PAGE>

<PAGE INDEX=3 TYPE=README>
<NEXTBUTTON TARGET=4>~I agree</NEXTBUTTON>
<TEXT>
By pressing the "I agree" button, you agree to all terms and conditions to the below licence agreement.
</TEXT>
<README FORMAT=HTML>
<B>LICENSE</B>
<P>
Starting with version 1.3.0 Mensys BV and Serenity Systems International
have agreed in opensourcing Lucide, while still investing in the product.
Netlabs.org would like to express it's gratitude toward Mensys BV and
Serenity Systems International.</P>
<P>
Lucide as of version 1.3.0 is released and distributed under CDDL/LGPL.</P>
<P>
The plugins are released under CDDL/LGPL or GPL, depending on the plugin. See
http://svn.netlabs.org/lucide/ for more information and source code.</P>
</README>
</PAGE>

<!-- The TYPE=CONTAINER will list the packages which can be installed. -->

<PAGE INDEX=4 TYPE=CONTAINER>
<NEXTBUTTON TARGET=6>~Next</NEXTBUTTON>
<TEXT>
Please select the packages which are to be installed. You may change the target paths for the packages.
</TEXT>
</PAGE>


<!-- The TYPE=CONFIGURE will allow the user to set the CONFIG.SYS and
     WPS classes/objects stuff.

     NOTE that we skip this target since 1.32 to avoid inconsistency that could
     happen should the user deselect creation of WPS objects (see ticket:128
     for details). -->

<PAGE INDEX=5 TYPE=CONFIGURE>
<NEXTBUTTON TARGET=6>~Next</NEXTBUTTON>
<TEXT>

Please select additional configuration that WarpIN should perform after installing this archive.

</TEXT>
</PAGE>

<!-- Here's another TYPE=TEXT page before we install.
     The special target "0" indicates that after this page we
     should start installation.
     Note that the TYPE=INSTALL page (which we had in Alpha #3)
     is no longer supported. -->

<PAGE INDEX=6 TYPE=TEXT>
<NEXTBUTTON TARGET=0>I~nstall</NEXTBUTTON>
<TEXT>



Press "Install" to begin installing this archive.</TEXT>
</PAGE>
</BODY>
</WARPIN>

