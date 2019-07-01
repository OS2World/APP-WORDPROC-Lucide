/* ***** BEGIN LICENSE BLOCK *****
 * Version: CDDL 1.0/LGPL 2.1
 *
 * The contents of this file are subject to the COMMON DEVELOPMENT AND
 * DISTRIBUTION LICENSE (CDDL) Version 1.0 (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at http://www.sun.com/cddl/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Initial Developer of the Original Code is
 * Eugene Romanenko, netlabs.org.
 * Portions created by the Initial Developer are Copyright (C) 2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the LGPL are applicable instead of those
 * above. If you wish to allow use of your version of this file only under the
 * terms of the LGPL, and not to allow others to use your version of this file
 * under the terms of the CDDL, indicate your decision by deleting the
 * provisions above and replace them with the notice and other provisions
 * required by the LGPL. If you do not delete the provisions above, a recipient
 * may use your version of this file under the terms of any one of the CDDL
 * or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */


#include "os2all.h"

#include <stdio.h>
#include <string.h>
#include <process.h>

//#define INCL_LOADEXCEPTQ
//#include "exceptq.h"
//
// Lcd.exe sets BEGINLIBPATH to directory where Lucide resides
// and executes Lucide.exe
//

typedef APIRET (APIENTRY *LMain)(int argc, char **argv);

int main( int argc, char *argv[] )
{
    int result = 1;
    char *last_slash;
    char buf[ CCHMAXPATH + 15 /*";%BEGINLIBPATH%"*/ ] = { 0 };
    HMODULE hmod = NULLHANDLE;
    APIRET rc = 0;
    //EXCEPTIONREGISTRATIONRECORD exRegRec;

#ifdef __TEST__
    PPIB pib;
    PTIB tib;
    //LoadExceptq(&exRegRec, "I", "Lucide "VERSION);
    DosGetInfoBlocks(&tib, &pib);
    pib->pib_ultype = 3;
#else
    //LoadExceptq(&exRegRec, "I", "Lucide "VERSION);
#endif

    // fill lucide dir
    strcpy( buf, argv[0] );
    if ( ( last_slash = strrchr( buf, '\\' ) ) == NULL )
    {
        //UninstallExceptq(&exRegRec);
        return 1;
    }
    else
    {
        *last_slash = 0;
    }
    // retain the previous BEGINLIBPATH setting
    strcat( buf, ";%BEGINLIBPATH%" );

    // set beginlibpath
    DosSetExtLIBPATH( buf, BEGIN_LIBPATH );

    rc = DosLoadModule( buf, sizeof( buf ), "Lucide1", &hmod );
    if ( rc == 0 )
    {
        PFN pfn = NULL;
        if ( DosQueryProcAddr( hmod, 0, "LucideMain", &pfn ) == 0 )
        {
            LMain LucideMain = (LMain)pfn;
            result = LucideMain( argc, argv );
        }
        DosFreeModule( hmod );
    }
    else
    {
        HAB hab;
        HMQ hmq;
        char msg[ 256 ];

        hab = WinInitialize( 0 );
        hmq = WinCreateMsgQueue( hab, 0 );

        if ( buf[0] == 0 ) { // No modulename
            snprintf( msg, sizeof( msg ), "Error loading Lucide1.dll: SYS%04u", rc );
        }
        else {
            snprintf( msg, sizeof( msg ),
                      "Error loading Lucide1.dll: can't find module '%s' (SYS%04u)",
                      buf, rc );
        }
        WinMessageBox( HWND_DESKTOP, NULLHANDLE, msg, NULL, 1, MB_OK | MB_MOVEABLE );

        WinDestroyMsgQueue( hmq );
        WinTerminate( hab );
    }
    //UninstallExceptq(&exRegRec);
    return result;
}

