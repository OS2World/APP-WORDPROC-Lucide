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

#include <string.h>
#include <process.h>
#include <stdlib.h>

#include "Lucide_res.h"


static const char *pipeName    = "\\PIPE\\LUCIDE";

// Commands
static const char *cmPrev       = "$prev";
static const char *cmNext       = "$next";
static const char *cmMinimize   = "$minimize";
static const char *cmFullScreen = "$switchfullscreen";
static const char *cmRotate     = "$rotate";
static const char *cmZoomIn     = "$zoomin";
static const char *cmZoomOut    = "$zoomout";
static const char *cmZoomOrig   = "$zoomoriginal";


static void pipeMonitor( void *p )
{
    HWND hWndFrame = (HWND)p;

    HAB thab = WinInitialize( 0 );
    HMQ hmq = WinCreateMsgQueue( thab, 0 );

    char buf[ 100 ]  = "";
    HPIPE PipeHandle = NULLHANDLE;
    ULONG Readed     = 0;

    if ( DosCreateNPipe( pipeName, &PipeHandle,
                         NP_ACCESS_INBOUND | NP_NOINHERIT,
                         NP_WAIT | NP_TYPE_MESSAGE | NP_READMODE_MESSAGE | 0x01,
                         0, sizeof( buf ), 0 ) == 0 )
    {
        while ( true )
        {
            Readed = 0;
            if ( DosConnectNPipe( PipeHandle ) != 0 ) {
                break;
            }
            if ( DosRead( PipeHandle, buf, sizeof( buf ) - 1, &Readed ) == 0 )
            {
                if ( Readed != 0 )
                {
                    buf[ Readed ] = '\0';

                    if ( strnicmp( buf, cmPrev, strlen( cmPrev ) ) == 0 )
                    {
                        WinPostMsg( hWndFrame, WM_COMMAND, MPFROMSHORT( CM_PREVPAGE ),
                                    MPFROM2SHORT( CMDSRC_OTHER, TRUE ) );
                    }
                    else if ( strnicmp( buf, cmNext, strlen( cmNext ) ) == 0 )
                    {
                        WinPostMsg( hWndFrame, WM_COMMAND, MPFROMSHORT( CM_NEXTPAGE ),
                                    MPFROM2SHORT( CMDSRC_OTHER, TRUE ) );
                    }
                    else if ( strnicmp( buf, cmMinimize, strlen( cmMinimize ) ) == 0 )
                    {
                        WinPostMsg( hWndFrame, WM_COMMAND, MPFROMSHORT( CM_MINIMIZE ),
                                    MPFROM2SHORT( CMDSRC_OTHER, TRUE ) );
                    }
                    else if ( strnicmp( buf, cmFullScreen, strlen( cmFullScreen ) ) == 0 )
                    {
                        WinPostMsg( hWndFrame, WM_COMMAND, MPFROMSHORT( CM_TOFULLSCREEN ),
                                    MPFROM2SHORT( CMDSRC_OTHER, TRUE ) );
                    }
                    else if ( strnicmp( buf, cmRotate, strlen( cmRotate ) ) == 0 )
                    {
                        WinPostMsg( hWndFrame, WM_COMMAND, MPFROMSHORT( CM_ROTATE90CW ),
                                    MPFROM2SHORT( CMDSRC_OTHER, TRUE ) );
                    }
                    else if ( strnicmp( buf, cmZoomIn, strlen( cmZoomIn ) ) == 0 )
                    {
                        WinPostMsg( hWndFrame, WM_COMMAND, MPFROMSHORT( CM_ZOOM_IN ),
                                    MPFROM2SHORT( CMDSRC_OTHER, TRUE ) );
                    }
                    else if ( strnicmp( buf, cmZoomOut, strlen( cmZoomOut ) ) == 0 )
                    {
                        WinPostMsg( hWndFrame, WM_COMMAND, MPFROMSHORT( CM_ZOOM_OUT ),
                                    MPFROM2SHORT( CMDSRC_OTHER, TRUE ) );
                    }
                    else if ( strnicmp( buf, cmZoomOrig, strlen( cmZoomOrig ) ) == 0 )
                    {
                        WinPostMsg( hWndFrame, WM_COMMAND, MPFROMSHORT( CM_ACTSIZE ),
                                    MPFROM2SHORT( CMDSRC_OTHER, TRUE ) );
                    }
                }
            }
            DosDisConnectNPipe( PipeHandle );
        }

        DosClose( PipeHandle );
    }

    WinDestroyMsgQueue( hmq );
    WinTerminate( thab );
}


static int pmTid = -1;

void initPipeMon( HWND hWndFrame )
{
    if ( pmTid == -1 ) {
        pmTid = _beginthread( pipeMonitor, NULL, 32768, (void *)hWndFrame );
    }
}

void unInitPipeMon()
{
    if ( pmTid != -1 ) {
        TID tid = pmTid;
        DosKillThread( tid );
        DosWaitThread( &tid, DCWW_WAIT );
    }
}

