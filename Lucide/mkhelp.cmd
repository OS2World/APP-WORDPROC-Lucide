/* mkhelp.cmd - compile helpfile */
PARSE ARG lang
IF lang == '' THEN DO
    locale = VALUE('LANG',,'OS2ENVIRONMENT')
    SELECT
        WHEN locale == 'zh_CN' THEN lang = 'cn'
        WHEN locale == 'zh_TW' THEN lang = 'tw'
        OTHERWISE PARSE VAR locale lang '_' .
    END
END
ELSE lang = LEFT( lang, 2 )

ipflangs = 'ARA BGR CAT CHT CZE DAN DEU ELL ENG ENU ESP FIN FRA FRC GBK GRK HEB HUN ITA JPN KOR LTU NLD NOR POL PRC PTB PTG RUS SLO SVE THI TRK'
langcode = 'ar  bg  en  tw  cz  da  de  el  en  en  es  fi  fr  fr  cn  el  he  hu  it  jp  ko  en  nl  no  po  cn  pt  pt  ru  en  sv  th  tr'
langpos  = WORDPOS( lang, langcode )
IF langpos == 0 THEN lsw = 'en'
ELSE lsw = WORD( ipflangs, langpos )

CALL VALUE 'IPFCARTWORK', 'gui\bitmaps', 'OS2ENVIRONMENT'
'ipfc -l:'lsw 'lng\lucide_'lang'.ipf Lucide_'lang'.hlp'

RETURN rc
