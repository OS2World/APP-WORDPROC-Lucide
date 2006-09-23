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


#define INCL_DOS
#include <os2.h>

#include <string.h>
#include <process.h>

//
// Lcd.exe sets BEGINLIBPATH to directory where Lucide resides
// and executes Lucide.exe
//

char lucideDir[ CCHMAXPATH ] = "";
char lucideExe[ CCHMAXPATH ] = "";

int main( int argc, char *argv[] )
{
    char *last_slash;

    // fill lucide dir
    strcpy( lucideDir, argv[0] );
    if ( ( last_slash = strrchr( lucideDir, '\\' ) ) == NULL ) {
        return 1;
    }
    else {
        *last_slash = 0;
    }
    // fill lucide exe
    strcpy( lucideExe, lucideDir );
    strcat( lucideExe, "\\Lucide.exe" );

    // set beginlibpath
    DosSetExtLIBPATH( lucideDir, BEGIN_LIBPATH );

    // execute lucide
    execvp( lucideExe, (char const **)argv );

    return 0;
}

