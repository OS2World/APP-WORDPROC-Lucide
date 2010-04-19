/*
 * Script to set up the build environment for Lucide
 */

'@echo off'
trace off
signal on error name OnError

parse source . . ScriptFile

parse arg aArgs

rc = rxFuncAdd('SysLoadFuncs', 'REXXUTIL', 'SysLoadFuncs')
rc = SysLoadFuncs()

if (EnvGet('LUCIDE_ENV_CMD_DONE') == 1) then do
    say
    say 'Lucide build environment is already set up.'
    exit 0
end

/* include LocalEnv.cmd */
LocalEnv_cmd = filespec('D', ScriptFile)||filespec('P', ScriptFile)'LocalEnv.cmd'
LocalEnv = charin(LocalEnv_cmd,, chars(LocalEnv_cmd))
LocalEnv = translate(LocalEnv, ';;', '0D0A'x)
interpret LocalEnv

/* process arguments */
if (arg(1) == 'debug') then do
    call EnvSet 'BUILD_TYPE', 'debug'
    aArgs = subword(aArgs, 2)
end
else if (arg(1) == 'release') then do
    call EnvSet 'BUILD_TYPE', 'release'
    aArgs = subword(aArgs, 2)
end

/* fix the outdated kBuild setting in GCC environment */
if (EnvGet('BUILD_PLATFORM') == 'OS2') then
    call EnvSet 'BUILD_PLATFORM', 'os2'

/* setup kBuild */
cmdline = 'call' G.PATH_TOOL_KBUILD'\envos2.cmd'
cmdline
drop cmdline

/* setup GCC */
if (G.PATH_TOOL_GCC442 \== '') then do
cmdline = 'call' G.PATH_TOOL_GCC442'\gcc442.cmd @'
cmdline
drop cmdline
end

/* fix the outdated kBuild setting in GCC environment */
if (EnvGet('BUILD_PLATFORM') == 'OS2') then
    call EnvSet 'BUILD_PLATFORM', 'os2'

/* setup variables for Config.kmk/kBuild */

call EnvSet 'PATH_SDK_SOM', translate(G.PATH_SDK_SOM, '/', '\')

/* setup OpenWatcom (not necessary any more) */
/*
if (G.PATH_TOOL_OPENWATCOM \== '') then do
    call EnvAddFront 'PATH', G.PATH_TOOL_OPENWATCOM'\binp'
    call EnvAddFront 'BEGINLIBPATH', G.PATH_TOOL_OPENWATCOM'\binp\dll'
    call EnvAddFront 'INCLUDE', G.PATH_TOOL_OPENWATCOM'\h;'G.PATH_TOOL_OPENWATCOM'\h\os2'
end
*/

/* setup OS/2 Toolkit (not necessary any more) */
/*
if (G.PATH_OS2_TOOLKIT \== '') then do
    call EnvAddEnd 'PATH', G.PATH_OS2_TOOLKIT'\som\bin'
    call EnvAddEnd 'BEGINLIBPATH', G.PATH_OS2_TOOLKIT'\som\lib'
    call EnvAddEnd 'INCLUDE', G.PATH_OS2_TOOLKIT'\h'
    call EnvAddEnd 'LIB', G.PATH_OS2_TOOLKIT'\som\lib'
    call EnvAddEnd 'SMINCLUDE', G.PATH_OS2_TOOLKIT'\idl;'G.PATH_OS2_TOOLKIT'\som\include'
end
*/

/* final mark */
call EnvSet 'LUCIDE_ENV_CMD_DONE', 1

if (aArgs \== '') then do
    /* Start the program */
    prg = translate(word(aArgs, 1))
    isCmd = 0
    realPrg = SysSearchPath(PATH, prg)
    if (realPrg == '') then realPrg = SysSearchPath(PATH, prg'.EXE')
    if (realPrg == '') then realPrg = SysSearchPath(PATH, prg'.COM')
    if (realPrg == '') then realPrg = SysSearchPath(PATH, prg'.CMD')
    if (realPrg \== '') then do
        if (right(realPrg, 4) == '.CMD') then isCmd = 1
    end
    if (isCmd) then 'call' aArgs
    else aArgs
end
else if (EnvGet('SE_CMD_RUNNING') == '') then do
    /* Print some information about the environment */
    say
    say 'Lucide build environment is set up.'
end
exit

/*----------------------------------------------------------------------------*/

/**
 * Add sToAdd in front of sEnvVar. sToAdd may be a list.
 *
 * See EnvAddFrontOrBack for details.
 */
EnvAddFront: procedure
    parse arg sEnvVar, sToAdd, sSeparator
    return EnvAddFrontOrBack(1, 0, sEnvVar, sToAdd, sSeparator);


/**
 * Add sToAdd to the end of sEnvVar. sToAdd may be a list.
 *
 * See EnvAddFrontOrBack for details.
 */
EnvAddEnd: procedure
    parse arg sEnvVar, sToAdd, sSeparator
    return EnvAddFrontOrBack(0, 0, sEnvVar, sToAdd, sSeparator);

/**
 * Remove all occurences of sToRemove from sEnvVar. sToRemove may be a list.
 *
 * See EnvAddFrontOrBack for details.
 */
EnvRemove: procedure
    parse arg sEnvVar, sToRemove, sSeparator
    return EnvAddFrontOrBack(0, 1, sEnvVar, sToRemove, sSeparator);

/**
 * Add sToAdd in front or at the end of sEnvVar. sToAdd may be a list.
 *
 * Note: This function will remove leading and trailing semicolons, as well
 * as duplcate semicolons somewhere in the middle. See
 *
 *   http://gcc.gnu.org/onlinedocs/gcc-4.4.2/gcc/Environment-Variables.html
 *
 * (CPLUS_INCLUDE_PATH and friends) for the explaination why it is necessary to
 * do. If you want to specifially mean the current working directory, use "."
 * instead of an empty path element.
 */
EnvAddFrontOrBack: procedure
    parse arg fFront, fRM, sEnvVar, sToAdd, sSeparator

    /* sets default separator if not specified. */
    if (sSeparator = '') then sSeparator = ';';

    /* get rid of extra ';' */
    sToAdd = strip(sToAdd,, sSeparator);
    sToAddClean = ''
    do i = 1 to length(sToAdd)
        ch = substr(sToAdd, i, 1);
        if (ch == sSeparator & right(sToAddClean, 1) == sSeparator) then
            iterate
        sToAddClean = sToAddClean||ch
    end

    /* Get original variable value */
    sOrgEnvVar = EnvGet(sEnvVar);

    /* loop thru sToAddClean */
    rc = 0;
    i = length(sToAddClean);
    do while (i > 0 & rc = 0)
        j = lastpos(sSeparator, sToAddClean, i);
        sOne = substr(sToAddClean, j+1, i - j);
        cbOne = length(sOne);
        /* Remove previous sOne if exists. (Changing sOrgEnvVar). */
        s1 = 1;
        do while (s1 <= length(sOrgEnvVar))
            s2 = pos(sSeparator, sOrgEnvVar, s1);
            if (s2 == 0) then
                s2 = length(sOrgEnvVar) + 1;
            if (translate(substr(sOrgEnvVar, s1, s2 - s1)) == translate(sOne)) then do
                sOrgEnvVar = delstr(sOrgEnvVar, s1, s2 - s1 + 1 /*+sep*/);
                s1 = s1 + 1;
            end
            else do
                s1 = s2 + 1;
            end
        end
        sOrgEnvVar = strip(sOrgEnvVar,, sSeparator);

        i = j - 1;
    end

    /* set environment */
    if (fRM) then
        return EnvSet(sEnvVar, sOrgEnvVar);

    /* add sToAddClean in necessary mode */
    if (fFront) then
    do
        if (sOrgEnvVar \== '' & left(sOrgEnvVar, 1) \== sSeparator) then
            sOrgEnvVar = sSeparator||sOrgEnvVar;
        sOrgEnvVar = sToAddClean||sOrgEnvVar;
    end
    else
    do
        if (sOrgEnvVar \== '' & right(sOrgEnvVar, 1) \== sSeparator) then
            sOrgEnvVar = sOrgEnvVar||sSeparator;
        sOrgEnvVar = sOrgEnvVar||sToAddClean;
    end

    return EnvSet(sEnvVar, sOrgEnvVar);


/**
 * Sets sEnvVar to sValue.
 */
EnvSet: procedure
    parse arg sEnvVar, sValue

    sEnvVar = translate(sEnvVar);

    /*
     * Begin/EndLibpath fix:
     *      We'll have to set internal these using both commandline 'SET'
     *      and internal VALUE in order to export it and to be able to
     *      get it (with EnvGet) again.
     */
    if ((sEnvVar = 'BEGINLIBPATH') | (sEnvVar = 'ENDLIBPATH')) then
    do
        if (length(sValue) >= 1024) then
            say 'Warning: 'sEnvVar' is too long,' length(sValue)' char.';
        return SysSetExtLibPath(sValue, substr(sEnvVar, 1, 1));
    end

    if (length(sValue) >= 1024) then
    do
        say 'Warning: 'sEnvVar' is too long,' length(sValue)' char.';
        say '    This may make CMD.EXE unstable after a SET operation to print the environment.';
    end
    sRc = VALUE(sEnvVar, sValue, 'OS2ENVIRONMENT');
    return 0;

/**
 * Gets the value of sEnvVar.
 */
EnvGet: procedure
    parse arg sEnvVar
    if ((translate(sEnvVar) = 'BEGINLIBPATH') | (translate(sEnvVar) = 'ENDLIBPATH')) then
        return SysQueryExtLibPath(substr(sEnvVar, 1, 1));
    return value(sEnvVar,, 'OS2ENVIRONMENT');

OnError:
    if (rc \= 0 & symbol('cmdline') == 'VAR') then
        say 'ERROR: Executing "'cmdline'" failed with code' rc'.'
	exit rc


