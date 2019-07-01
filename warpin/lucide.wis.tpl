<!-- This is the profile for installing Lucide core and plugins. -->

<WARPIN
     OS="OS2_3x"
     CODEPAGE=850
>
<HEAD>

<!-- Every .WPI archive contains one or more packages. -->
<REXX NAME=ChkBldLvl>
    call RxFuncAdd 'SysLoadFuncs', 'REXXUTIL', 'SysLoadFuncs'
    call SysLoadFuncs
    /* based upon work from Doug Bissett */
    parse arg aFile " Package:" Package  
    name = filespec('N', aFile)
   /* clean up rxqueue */
    '@rxqueue /clear'
     val=0.0
     compval=6.3
     tag = 'VERSION'
   /* consider libpath search for libcx0.dll? */  
'@BLDLEVEL.EXE 'value('UNIXROOT',, 'OS2ENVIRONMENT')'\USR\LIB\'name' | RXQUEUE'

do while queued() > 0
  pull thisline
  if pos(tag,thisline)>0 then do
     foundval = strip(word(thisline,3))
     val = right(foundval,3) 
  end
end
if val > compval then do
   MsgStr = "" 
end
else MsgStr = 'REQUIRES="' || strip(Package) || '"'
    return MsgStr
</REXX>

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
langs = "EN,FR,DE,NL,ES,SV,IT,CS,DA,RU,ZH"
lang = translate(left(strip(value("LANG",,"OS2ENVIRONMENT")),2))
if pos(lang,langs) = 0 then lang = 'EN'
rc =WirexxPutEnv('prog','Lucide')
/*Make sure you change the help file object name when adding a new translation*/
select                                       
  when lang = 'FR' then do
                    /* Translate */
    rc =WirexxPutEnv('title','Lucide Afficheur de document')
    rc =WirexxPutEnv('uguide','Lucide User Guide')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('plug_gbm','Lucide GBM plugin')
    rc =WirexxPutEnv('readmetitle','LisezMoi')
    rc =WirexxPutEnv('welcome','Bienvenue dans l''installation du ')
    rc =WirexxPutEnv('accept','Veuillez prendre connaissance et accepter l''accord de licence suivant.')
    rc =WirexxPutEnv('target','Veuillez s‚lectionner le dossier de destination')
    rc =WirexxPutEnv('re_install','Si vous effectuez une mise … jour de SearchPlus, le dossier d''installation par d‚faut sera celui actuellement utilis‚ par l''ancienne version.')
    rc =WirexxPutEnv('ready','Veuillez confirmer les options d''installation.')
    rc =WirexxPutEnv('scfind','Modifications du fichier CONFIG.SYS pr‚vues: param‚trage de la variable SCFINDUTILITY … SearchPlus.exe pour en faire le programme de recherche du systŠme par d‚faut. Ces modifications n‚cessiteront un red‚marrage.')
    rc =WirexxPutEnv('over_write','Veuillez s‚lectionner de maniŠre … ‚craser tout fichier existant.')
    rc =WirexxPutEnv('install','~Install')
    rc =WirexxPutEnv('license','~J''accepte')
    rc =WirexxPutEnv('next','~Suivant')
    rc =WirexxPutEnv('nextText','Select "Suivant" to continue.')
    rc =WirexxPutEnv('cancelText','Select "Cancel" to abort installation.')
    rc =WirexxPutEnv('installText','Press "Install" in order to start installation of this archive.')
                    /* End Translate */
    rc =WirexxPutEnv('pkgnum','1033') 
                    /* Update us if this translation is added */
    rc =WirexxPutEnv('readme','readme_fr.txt')
    rc =WirexxPutEnv('lucidehelp','lucide_en.hlp+gbm_en.hlp')
    rc =WirexxPutEnv('fr_sel','SELECT DESELECT')
  end
  when lang = 'DE' then do
                    /* Translate */
    rc =WirexxPutEnv('title','Lucide Dokumentenbetrachter')
    rc =WirexxPutEnv('uguide','Lucide User Guide')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('plug_gbm','Lucide GBM plugin')
    rc =WirexxPutEnv('readmetitle','Lies mich!')
    rc =WirexxPutEnv('welcome','Willkommen zur Installation des ')
    rc =WirexxPutEnv('accept','Bitte lesen Sie den folgenden Text und akzeptieren Sie die Lizenzvereinbarung.')
    rc =WirexxPutEnv('target','W„hlen Sie bitte das Zielverzeichnis.')
    rc =WirexxPutEnv('re_install','Wenn dies ein Update ist, dann ist das Installationsverzeichnis das aktuelle Verzeichnis des Plugins.')
    rc =WirexxPutEnv('install','~Installieren')
    rc =WirexxPutEnv('license','St~imme zu')
    rc =WirexxPutEnv('next','W~eiter')
    rc =WirexxPutEnv('nextText','Zum Fortfahren "Weiter" ausw„hlen.')
    rc =WirexxPutEnv('cancelText','Zum Abbrechen "Cancel" ausw„hlen.')
    rc =WirexxPutEnv('installText','Bitte "Installieren" ausw„hlen, um die Installation des Archivs zu starten.')
                    /* End Translate */
    rc =WirexxPutEnv('pkgnum','1049')
                    /* Update us if this translation is added */
    rc =WirexxPutEnv('readme','readme_de.txt')
    rc =WirexxPutEnv('lucidehelp','lucide_en.hlp+gbm_en.hlp')
    rc =WirexxPutEnv('de_sel','SELECT DESELECT')
  end
  when lang = 'NL' then do
                    /* Translate */
    rc =WirexxPutEnv('title','Lucide Document Bekijker')
    rc =WirexxPutEnv('uguide','Lucide User Guide')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('plug_gbm','Lucide GBM plugin')
    rc =WirexxPutEnv('readmetitle','Lees mij')
    rc =WirexxPutEnv('welcome','Welcome to the installation of ')
    rc =WirexxPutEnv('accept','Please read and accept the following license-agreement.')
    rc =WirexxPutEnv('target','Please select target directory.')
    rc =WirexxPutEnv('re_install','If you are updating the Lucide, the default installation directory will be the current directory.')
    rc =WirexxPutEnv('install','~Install')
    rc =WirexxPutEnv('license','I ~accept')
    rc =WirexxPutEnv('next','~Next')
    rc =WirexxPutEnv('nextText','Select "Next" to continue.')
    rc =WirexxPutEnv('cancelText','Select "Cancel" to abort installation.')
    rc =WirexxPutEnv('installText','Press "Install" in order to start installation of this archive.')
                    /* End Translate */
    rc =WirexxPutEnv('pkgnum','1031')
                    /* Update us if this translation is added */
    rc =WirexxPutEnv('readme','readme_nl.txt')
    rc =WirexxPutEnv('lucidehelp','lucide_en.hlp+gbm_en.hlp')
    rc =WirexxPutEnv('nl_sel','SELECT DESELECT')
  end
  when lang = 'ES' Then Do
                    /* Translate */
    rc =WirexxPutEnv('title','Visor de documentos Lucide')
    rc =WirexxPutEnv('uguide','Manual del usuario de Lucide')
    rc =WirexxPutEnv('plug_pdf','M¢dulo PDF para Lucide')
    rc =WirexxPutEnv('plug_djvu','M¢dulo DjVu para Lucide')
    rc =WirexxPutEnv('plug_jpeg','M¢dulo JPEG para Lucide')
    rc =WirexxPutEnv('plug_gbm',' M¢dulo GBM para Lucide')
    rc =WirexxPutEnv('readmetitle','L‚ame')
    rc =WirexxPutEnv('welcome','Bienvenidos a la instalaci¢n de ')
    rc =WirexxPutEnv('accept','Por favor, lea y acepte el siguiente acuerdo de licencia.')
    rc =WirexxPutEnv('target','Por favor, seleccione el directorio de destino.')
    rc =WirexxPutEnv('re_install','Si est  actualizando Lucide, el directorio de instalaci¢n por omisi¢n ser  el directorio actual.')
    rc =WirexxPutEnv('install','~Instalar')
    rc =WirexxPutEnv('license','~Acepto')
    rc =WirexxPutEnv('next','~Siguiente')
    rc =WirexxPutEnv('nextText','Seleccione ®Siguiente¯ para continuar.')
    rc =WirexxPutEnv('cancelText','Seleccione ®Cancelar¯ para abortar la instalaci¢n.')
    rc =WirexxPutEnv('installText','Pulse ®Instalar¯ para iniciar la instalaci¢n de este archivo.')
                    /* End Translate */
    rc =WirexxPutEnv('pkgnum','1034')
                    /* Update us if this translation is added */
    rc =WirexxPutEnv('readme','readme_es.txt')
    rc =WirexxPutEnv('lucidehelp','lucide_es.hlp+gbm_es.hlp')
    rc =WirexxPutEnv('es_sel','SELECT DESELECT')
  end
  when lang = 'SV' Then Do
                    /* Translate */
    rc =WirexxPutEnv('title','Lucide Dokumentvisare')
    rc =WirexxPutEnv('uguide','Lucide User Guide')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('plug_gbm','Lucide GBM plugin')
    rc =WirexxPutEnv('readmetitle','L„s mig')
    rc =WirexxPutEnv('welcome','Welcome to the installation of ')
    rc =WirexxPutEnv('accept','Please read and accept the following license-agreement.')
    rc =WirexxPutEnv('target','Please select target directory.')
    rc =WirexxPutEnv('re_install','If you are updating the Lucide, the default installation directory will be the current directory.')
    rc =WirexxPutEnv('install','~Install')
    rc =WirexxPutEnv('license','I ~accept')
    rc =WirexxPutEnv('next','~Next')
    rc =WirexxPutEnv('nextText','Select "Next" to continue.')
    rc =WirexxPutEnv('cancelText','Select "Cancel" to abort installation.')
    rc =WirexxPutEnv('installText','Press "Install" in order to start installation of this archive.')
                    /* End Translate */
    rc =WirexxPutEnv('pkgnum','1')
                    /* Update us if this translation is added */
    rc =WirexxPutEnv('readme','readme')
    rc =WirexxPutEnv('lucidehelp','lucide_en.hlp+gbm_en.hlp')
    rc =WirexxPutEnv('sv_sel','SELECT DESELECT')
  end
  when lang = 'IT' Then Do
                    /* Translate */
    rc =WirexxPutEnv('title','Lucide Document Viewer')
    rc =WirexxPutEnv('uguide','Lucide User Guide')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('plug_gbm','Lucide GBM plugin')
    rc =WirexxPutEnv('readmetitle','ReadMe')
    rc =WirexxPutEnv('welcome','Welcome to the installation of the Lucide!')
    rc =WirexxPutEnv('accept','Please read and accept the following license-agreement.')
    rc =WirexxPutEnv('target','Please select target directory.')
    rc =WirexxPutEnv('re_install','If you are updating the Lucide, the default installation directory will be the current directory.')
    rc =WirexxPutEnv('install','~Install')
    rc =WirexxPutEnv('license','I ~accept')
    rc =WirexxPutEnv('next','~Next')
    rc =WirexxPutEnv('nextText','Select "Next" to continue.')
    rc =WirexxPutEnv('cancelText','Select "Cancel" to abort installation.')
    rc =WirexxPutEnv('installText','Press "Install" in order to start installation of this archive.')
                    /* End Translate */
    rc =WirexxPutEnv('pkgnum','1039')
                    /* Update us if this translation is added */
    rc =WirexxPutEnv('readme','readme_it.txt')
    rc =WirexxPutEnv('lucidehelp','lucide_en.hlp+gbm_en.hlp')
    rc =WirexxPutEnv('it_sel','SELECT DESELECT')
  end
  when lang = 'CS' Then Do
                    /* Translate */
    rc =WirexxPutEnv('title','Lucide Document Viewer')
    rc =WirexxPutEnv('uguide','Lucide User Guide')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('plug_gbm','Lucide GBM plugin')
    rc =WirexxPutEnv('readmetitle','ReadMe')
    rc =WirexxPutEnv('welcome','Welcome to the installation of the Lucide!')
    rc =WirexxPutEnv('accept','Please read and accept the following license-agreement.')
    rc =WirexxPutEnv('target','Please select target directory.')
    rc =WirexxPutEnv('re_install','If you are updating the Lucide, the default installation directory will be the current directory.')
    rc =WirexxPutEnv('install','~Install')
    rc =WirexxPutEnv('license','I ~accept')
    rc =WirexxPutEnv('next','~Next')
    rc =WirexxPutEnv('nextText','Select "Next" to continue.')
    rc =WirexxPutEnv('cancelText','Select "Cancel" to abort installation.')
    rc =WirexxPutEnv('installText','Press "Install" in order to start installation of this archive.')
                    /* End Translate */
    rc =WirexxPutEnv('pkgnum','1041')
                    /* Update us if this translation is added */
    rc =WirexxPutEnv('readme','readme_cs.txt')
    rc =WirexxPutEnv('lucidehelp','lucide_en.hlp+gbm_en.hlp')
    rc =WirexxPutEnv('cz_sel','SELECT DESELECT')
  end
  when lang = 'DA' Then Do
                    /* Translate */
    rc =WirexxPutEnv('title','Lucide Document Viewer')
    rc =WirexxPutEnv('uguide','Lucide User Guide')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('plug_gbm','Lucide GBM plugin')
    rc =WirexxPutEnv('readmetitle','ReadMe')
    rc =WirexxPutEnv('welcome','Welcome to the installation of the Lucide!')
    rc =WirexxPutEnv('accept','Please read and accept the following license-agreement.')
    rc =WirexxPutEnv('target','Please select target directory.')
    rc =WirexxPutEnv('re_install','If you are updating the Lucide, the default installation directory will be the current directory.')
    rc =WirexxPutEnv('install','~Install')
    rc =WirexxPutEnv('license','I ~accept')
    rc =WirexxPutEnv('next','~Next')
    rc =WirexxPutEnv('nextText','Select "Next" to continue.')
    rc =WirexxPutEnv('cancelText','Select "Cancel" to abort installation.')
    rc =WirexxPutEnv('installText','Press "Install" in order to start installation of this archive.')
                    /* End Translate */
    rc =WirexxPutEnv('pkgnum','1')
                    /* Update us if this translation is added */
    rc =WirexxPutEnv('readme','readme')
    rc =WirexxPutEnv('lucidehelp','lucide_en.hlp+gbm_en.hlp')
    rc =WirexxPutEnv('da_sel','SELECT DESELECT')
  end
  when lang = 'RU' Then Do
                    /* Translate */
    rc =WirexxPutEnv('title','Lucide Document Viewer')
    rc =WirexxPutEnv('uguide','Lucide User Guide')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('plug_gbm','Lucide GBM plugin')
    rc =WirexxPutEnv('readmetitle','ReadMe')
    rc =WirexxPutEnv('welcome','Welcome to the installation of the Lucide!')
    rc =WirexxPutEnv('accept','Please read and accept the following license-agreement.')
    rc =WirexxPutEnv('target','Please select target directory.')
    rc =WirexxPutEnv('re_install','If you are updating the Lucide, the default installation directory will be the current directory.')
    rc =WirexxPutEnv('install','~Install')
    rc =WirexxPutEnv('license','I ~accept')
    rc =WirexxPutEnv('next','~Next')
    rc =WirexxPutEnv('nextText','Select "Next" to continue.')
    rc =WirexxPutEnv('cancelText','Select "Cancel" to abort installation.')
    rc =WirexxPutEnv('installText','Press "Install" in order to start installation of this archive.')
                    /* End Translate */
    rc =WirexxPutEnv('pkgnum','1')
                    /* Update us if this translation is added */
    rc =WirexxPutEnv('readme','readme')
    rc =WirexxPutEnv('lucidehelp','lucide_en.hlp+gbm_en.hlp')
    rc =WirexxPutEnv('ru_sel','SELECT DESELECT')
  end
  when lang = 'ZH' Then Do
                    /* Translate */
    rc =WirexxPutEnv('title','Lucide Document Viewer')
    rc =WirexxPutEnv('uguide','Lucide User Guide')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('plug_gbm','Lucide GBM plugin')
    rc =WirexxPutEnv('readmetitle','ReadMe')
    rc =WirexxPutEnv('welcome','Welcome to the installation of the Lucide!')
    rc =WirexxPutEnv('accept','Please read and accept the following license-agreement.')
    rc =WirexxPutEnv('target','Please select target directory.')
    rc =WirexxPutEnv('re_install','If you are updating the Lucide, the default installation directory will be the current directory.')
    rc =WirexxPutEnv('install','~Install')
    rc =WirexxPutEnv('license','I ~accept')
    rc =WirexxPutEnv('next','~Next')
    rc =WirexxPutEnv('nextText','Select "Next" to continue.')
    rc =WirexxPutEnv('cancelText','Select "Cancel" to abort installation.')
    rc =WirexxPutEnv('installText','Press "Install" in order to start installation of this archive.')
                    /* End Translate */
    rc =WirexxPutEnv('pkgnum','1')
                    /* Update us if this translation is added */
    rc =WirexxPutEnv('readme','readme')
    rc =WirexxPutEnv('lucidehelp','lucide_en.hlp+gbm_en.hlp')
    rc =WirexxPutEnv('tw_sel','SELECT DESELECT')
  end
  otherwise do
    rc =WirexxPutEnv('title','Lucide Document Viewer')
    rc =WirexxPutEnv('uguide','Lucide User Guide')
    rc =WirexxPutEnv('plug_pdf','Lucide PDF plugin')
    rc =WirexxPutEnv('plug_djvu','Lucide DjVu plugin')
    rc =WirexxPutEnv('plug_jpeg','Lucide JPEG plugin')
    rc =WirexxPutEnv('plug_gbm','Lucide GBM plugin')
    rc =WirexxPutEnv('readmetitle','ReadMe')
    rc =WirexxPutEnv('welcome','Welcome to the installation of the Lucide!')
    rc =WirexxPutEnv('accept','Please read and accept the following license-agreement.')
    rc =WirexxPutEnv('target','Please select target directory.')
    rc =WirexxPutEnv('re_install','If you are updating the Lucide, the default installation directory will be the current directory.')
    rc =WirexxPutEnv('install','~Install')
    rc =WirexxPutEnv('license','I ~accept')
    rc =WirexxPutEnv('next','~Next')
    rc =WirexxPutEnv('nextText','Select "Next" to continue.')
    rc =WirexxPutEnv('cancelText','Select "Cancel" to abort installation.')
    rc =WirexxPutEnv('installText','Press "Install" in order to start installation of this archive.')
    rc =WirexxPutEnv('pkgnum','1')
    rc =WirexxPutEnv('readme','readme')
    rc =WirexxPutEnv('lucidehelp','lucide_en.hlp+gbm_en.hlp')
    rc =WirexxPutEnv('en_sel','SELECT DESELECT')
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
     TITLE="=("get_env title")"
     WRITEPROFILE="USER\Lucide\Path|$(1)"
     CLEARPROFILE="USER\Lucide\Path"
     =("ChkREQ LIBC066.DLL Package:netlabs-rel\libc\0\6\6\38")
     =("ChkREQ GCC492.DLL Package:netlabs-rel\libgcc-fwd\4\9\2\1\3")
     =("ChkREQ LIBCX0.DLL Package:netlabs-rel\libcx\0\6\3\1")
     SELECT
     CONFIGSYS="SET HELP=$(1); | ADDRIGHT"
     CONFIGSYS="SET BOOKSHELF=$(1); | ADDRIGHT"
     CONFIGSYS="SET LUCIDEINSTALLPATH=$(1) | UNIQUE"
     CONFIGSYS="SET LUCIDEHELP==("get_env lucidehelp") | UNIQUE"
     >=("get_env title").</PCK>

<PCK INDEX=2
     PACKAGEID="netlabs.org\Lucide\Lucide plugin PDF\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="=("get_env plug_pdf")"
     REQUIRES=1
     =("ChkREQ POPPLE70.DLL Package:netlabs-rel\poppler\0\59\0\3")
     SELECT | FIXED
     >=("get_env plug_pdf")</PCK>

<PCK INDEX=3
     PACKAGEID="netlabs.org\Lucide\Lucide plugin DJVU\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="=("get_env plug_djvu")"
     REQUIRES=1
     =("ChkREQ DJVULI21.DLL Package:netlabs-rel\djvulibre\3\5\27\3")
     SELECT | FIXED
     >=("get_env plug_djvu")</PCK>

<PCK INDEX=5
     PACKAGEID="netlabs.org\Lucide\Lucide plugin GBM\1\4\4\0"
     TARGET="$(1)"
     TITLE="=("get_env plug_gbm")"
     REQUIRES=1
     SELECT | FIXED
     =("ChkREQ GBM.DLL Package:netlabs-rel\GBMDLL\1\76\1")
     >=("get_env plug_gbm")</PCK>

     <GROUP TITLE="Optional components">

<PCK INDEX=4
     PACKAGEID="netlabs.org\Lucide\Lucide plugin JPEG\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="=("get_env plug_jpeg")"
     REQUIRES=1
     FIXED
     =("ChkREQ JPEG8.DLL Package:netlabs-rel\libjpeg-turbo\1\5\1\1")
     >=("get_env plug_jpeg")</PCK>

<PCK INDEX=7
     PACKAGEID="netlabs.org\Lucide\AltIcons\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)\Alticons"
     TITLE="AltIcons"
     REQUIRES=1
     FIXED
     >This package contains alternative icons for Lucide.</PCK>
     
<PCK INDEX=8
     PACKAGEID="netlabs.org\Lucide\Debug\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="Debug symbols"
     REQUIRES=1
     FIXED
     >This package contains debug symbols for Lucide.</PCK>     
     
     </GROUP>
     <!-- Language support packages  -->

    <GROUP TITLE="Language Support Packages selected based on system language">
    
/*Make sure you change the help file object name when adding a new translation*/
/*Readme objects are all different*/

<PCK INDEX=6
     PACKAGEID="netlabs.org\Lucide\english\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="English"
     CREATEOBJECT='WPFolder|=("get_env title")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env title");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT="REPLACE WPProgram|=("get_env uguide")|<LUCIDEFOLDER>|EXENAME=view.exe;OBJECTID=<LUCIDEFOLDER_GUIDE>;TITLE==("get_env uguide");PROGTYPE=PM;PARAMETERS==("get_env lucidehelp");STARTUPDIR=$(1);"
     CREATEOBJECT='WPProgram|=("get_env readmetitle")|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_README>;TITLE==("get_env readmetitle");PROGTYPE=PM;PARAMETERS=$(1)\readme;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Changelog|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Changelog;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env en_sel")
     >English</PCK>

<PCK INDEX=1033
     PACKAGEID="netlabs.org\Lucide\francais\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="Francais"
     CREATEOBJECT='WPFolder|=("get_env title")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env title");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT="REPLACE WPProgram|=("get_env uguide")|<LUCIDEFOLDER>|EXENAME=view.exe;OBJECTID=<LUCIDEFOLDER_GUIDE>;TITLE==("get_env uguide");PROGTYPE=PM;PARAMETERS=$(1)\Lucide_en.hlp;STARTUPDIR=$(1);"
     CREATEOBJECT='WPProgram|=("get_env readmetitle")|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_READMEFR>;TITLE==("get_env readmetitle");PROGTYPE=PM;PARAMETERS=$(1)\readme_fr.txt;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Change Log|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Change Log;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env fr_sel")
     >Francais</PCK>

<PCK INDEX=1049
     PACKAGEID="netlabs.org\Lucide\deutsch\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="Deutsch"
     CREATEOBJECT='WPFolder|=("get_env title")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env title");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT="REPLACE WPProgram|=("get_env uguide")|<LUCIDEFOLDER>|EXENAME=view.exe;OBJECTID=<LUCIDEFOLDER_GUIDE>;TITLE==("get_env uguide");PROGTYPE=PM;PARAMETERS==("get_env lucidehelp");STARTUPDIR=$(1);" 
     CREATEOBJECT='WPProgram|=("get_env readmetitle")|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_READMEDE>;TITLE==("get_env readmetitle");PROGTYPE=PM;PARAMETERS=$(1)\readme_de.txt;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Entwicklungsgeschichte|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Entwicklungsgeschichte;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env de_sel")
     >Deutsch</PCK>

<PCK INDEX=1031
     PACKAGEID="netlabs.org\Lucide\dutch\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     TITLE="Dutch"
     CREATEOBJECT='WPFolder|=("get_env title")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env title");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT="REPLACE WPProgram|=("get_env uguide")|<LUCIDEFOLDER>|EXENAME=view.exe;OBJECTID=<LUCIDEFOLDER_GUIDE>;TITLE==("get_env uguide");PROGTYPE=PM;PARAMETERS==("get_env lucidehelp");STARTUPDIR=$(1);" 
     CREATEOBJECT='WPProgram|=("get_env readmetitle")|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_READMENL>;TITLE==("get_env readmetitle");PROGTYPE=PM;PARAMETERS=$(1)\readme_nl.txt;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Changelog|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Changelog;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env nl_sel")
     >Dutch</PCK>

<PCK INDEX=1034
     PACKAGEID="netlabs.org\Lucide\espanol\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     FIXED
     TITLE="Espanol"
     CREATEOBJECT='WPFolder|=("get_env title")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env title");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT="REPLACE WPProgram|=("get_env uguide")|<LUCIDEFOLDER>|EXENAME=view.exe;OBJECTID=<LUCIDEFOLDER_GUIDEES>;TITLE==("get_env uguide");PROGTYPE=PM;PARAMETERS==("get_env lucidehelp");STARTUPDIR=$(1);" 
     CREATEOBJECT='WPProgram|=("get_env readmetitle")|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_READMEES>;TITLE==("get_env readmetitle");PROGTYPE=PM;PARAMETERS=$(1)\readme_es.txt;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Change Log|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Changelog;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env es_sel")
     >Espanol</PCK>

<PCK INDEX=1046
     PACKAGEID="netlabs.org\Lucide\sverige\${WPIVERSION}\${WPIBUILD}"
     TARGET="$(1)"
     FIXED
     TITLE="Sverige"
     CREATEOBJECT='WPFolder|=("get_env title")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env title");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT="REPLACE WPProgram|=("get_env uguide")|<LUCIDEFOLDER>|EXENAME=view.exe;OBJECTID=<LUCIDEFOLDER_GUIDE>;TITLE==("get_env uguide");PROGTYPE=PM;PARAMETERS==("get_env lucidehelp");STARTUPDIR=$(1);" 
     CREATEOBJECT='WPProgram|=("get_env readmetitle")|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_READMESV>;TITLE==("get_env readmetitle");PROGTYPE=PM;PARAMETERS=$(1)\readme;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Changelog|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Changelog;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env sv_sel")
     >Sverige</PCK>

<PCK INDEX=1039
     PACKAGEID="netlabs.org\Lucide\Italian\${WPIVERSION}\${WPIBUILD"
     TITLE="Italian"
     TARGET="$(1)"
     FIXED
     CREATEOBJECT='WPFolder|=("get_env title")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env title");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT="REPLACE WPProgram|=("get_env uguide")|<LUCIDEFOLDER>|EXENAME=view.exe;OBJECTID=<LUCIDEFOLDER_GUIDE>;TITLE==("get_env uguide");PROGTYPE=PM;PARAMETERS==("get_env lucidehelp");STARTUPDIR=$(1);" 
     CREATEOBJECT='WPProgram|=("get_env readmetitle")|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_READMEIT>;TITLE==("get_env readmetitle");PROGTYPE=PM;PARAMETERS=$(1)\readme;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Changelog|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Changelog;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env it_sel")
     >Italian language support files for Lucide.</PCK>

<PCK INDEX=1421
     PACKAGEID="netlabs.org\Lucide\Czech\${WPIVERSION}\${WPIBUILD"
     TITLE="Czech"
     TARGET="$(1)"
     FIXED
     CREATEOBJECT='WPFolder|=("get_env title")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env title");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT="REPLACE WPProgram|=("get_env uguide")|<LUCIDEFOLDER>|EXENAME=view.exe;OBJECTID=<LUCIDEFOLDER_GUIDE>;TITLE==("get_env uguide");PROGTYPE=PM;PARAMETERS==("get_env lucidehelp");STARTUPDIR=$(1);"
     CREATEOBJECT='WPProgram|=("get_env readmetitle")|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_READMECS>;TITLE==("get_env readmetitle");PROGTYPE=PM;PARAMETERS=$(1)\readme;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Changelog|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Changelog;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env cz_sel")
     >Czech language support files for Lucide.</PCK>

<PCK INDEX=1045
     PACKAGEID="netlabs.org\Lucide\Danish\${WPIVERSION}\${WPIBUILD"
     TITLE="Danish"
     TARGET="$(1)"
     FIXED
     CREATEOBJECT='WPFolder|=("get_env title")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env title");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT="REPLACE WPProgram|=("get_env uguide")|<LUCIDEFOLDER>|EXENAME=view.exe;OBJECTID=<LUCIDEFOLDER_GUIDE>;TITLE==("get_env uguide");PROGTYPE=PM;PARAMETERS==("get_env lucidehelp");STARTUPDIR=$(1);" 
     CREATEOBJECT='WPProgram|=("get_env readmetitle")|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_READMEDA>;TITLE==("get_env readmetitle");PROGTYPE=PM;PARAMETERS=$(1)\readme;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Changelog|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Changelog;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env da_sel")
     >Danish language support files for Lucide.</PCK>

<PCK INDEX=1007
     PACKAGEID="netlabs.org\Lucide\Russian\${WPIVERSION}\${WPIBUILD"
     TITLE="Russian"
     TARGET="$(1)"
     FIXED
     CREATEOBJECT='WPFolder|=("get_env title")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env title");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT="REPLACE WPProgram|=("get_env uguide")|<LUCIDEFOLDER>|EXENAME=view.exe;OBJECTID=<LUCIDEFOLDER_GUIDE>;TITLE==("get_env uguide");PROGTYPE=PM;PARAMETERS==("get_env lucidehelp");STARTUPDIR=$(1);"
     CREATEOBJECT='WPProgram|=("get_env readmetitle")|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_READMERU>;TITLE==("get_env readmetitle");PROGTYPE=PM;PARAMETERS=$(1)\readme;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Changelog|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Changelog;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env ru_sel")
     >Russian language support files for Lucide.</PCK>

<PCK INDEX=1088
     PACKAGEID="netlabs.org\Lucide\Chinese (TW)\${WPIVERSION}\${WPIBUILD"
     TITLE="Chinese (TW)"
     TARGET="$(1)"
     FIXED
     CREATEOBJECT='WPFolder|=("get_env title")|<WP_DESKTOP>|OBJECTID=<LUCIDEFOLDER>;TITLE==("get_env title");ICONFILE=$(1)\lucide_fldr_1.ico;ICONNFILE=1,$(1)\lucide_fldr_2.ico;OPEN=DEFAULT;ALWAYSSORT=YES;'
     CREATEOBJECT='WPProgram|Lucide|<LUCIDEFOLDER>|EXENAME=$(1)\lucide.exe;OBJECTID=<LUCIDEFOLDER_LUCIDEEXE>;TITLE==("get_env prog");PROGTYPE=PM;STARTUPDIR=$(1);ASSOCFILTER=*.PDF,*.DJVU;ASSOCTYPE=Acrobat Document;CCVIEW=YES;'
     CREATEOBJECT="REPLACE WPProgram|=("get_env uguide")|<LUCIDEFOLDER>|EXENAME=view.exe;OBJECTID=<LUCIDEFOLDER_GUIDE>;TITLE==("get_env uguide");PROGTYPE=PM;PARAMETERS==("get_env lucidehelp");STARTUPDIR=$(1);" 
     CREATEOBJECT='WPProgram|=("get_env readmetitle")|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_READMETW>;TITLE==("get_env readmetitle");PROGTYPE=PM;PARAMETERS=$(1)\readme;STARTUPDIR=$(1);'
     CREATEOBJECT='WPProgram|Changelog|<LUCIDEFOLDER>|EXENAME=e.exe;OBJECTID=<LUCIDEFOLDER_CHANGELOG>;TITLE=Changelog;PROGTYPE=PM;PARAMETERS=$(1)\changelog;STARTUPDIR=$(1);'
     =("get_env tw_sel")
     >Chinese (TW) language support files for Lucide.</PCK>

    </GROUP>

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
<README FORMAT=PLAIN EXTRACTFROMPCK="=("get_env pkgnum")">=("get_env readme")</README>
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
<README FORMAT=PLAIN EXTRACTFROMPCK="1">LICENSE.CDDL</README>
</PAGE>

<PAGE INDEX=4 TYPE=README>
<NEXTBUTTON TARGET=5>=("get_env license")</NEXTBUTTON>
<TEXT>
=("get_env accept")
</TEXT>
<README FORMAT=PLAIN EXTRACTFROMPCK="1">LICENSE.LGPL</README>
</PAGE>

<!-- The TYPE=CONTAINER will list the packages which can be installed. -->

<PAGE INDEX=5 TYPE=CONTAINER>
<NEXTBUTTON TARGET=7>=("get_env next")</NEXTBUTTON>
<TEXT>
=("get_env target")
</TEXT>
</PAGE>


<!-- The TYPE=CONFIGURE will allow the user to set the CONFIG.SYS and
     WPS classes/objects stuff.

     NOTE that we skip this target since 1.32 to avoid inconsistency that could
     happen should the user deselect creation of WPS objects (see ticket:128
     for details). -->

<PAGE INDEX=6 TYPE=CONFIGURE>
<NEXTBUTTON TARGET=7>=("get_env next")</NEXTBUTTON>
<TEXT>

Please select additional configuration that WarpIN should perform after installing this archive.

</TEXT>
</PAGE>

<PAGE INDEX=7 TYPE=TEXT>
<NEXTBUTTON TARGET=0>=("get_env install")</NEXTBUTTON>
<TEXT>


=("get_env installText")</TEXT>
</PAGE>
</BODY>
</WARPIN>
