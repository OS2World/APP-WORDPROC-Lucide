#define INCL_WIN
#define INCL_DOS
#include <os2.h>

#include <string.h>
#include <malloc.h>
#include "cpconv.h"


#define kUnicodeMime "text/unicode"

inline ULONG RegisterClipboardFormat(PCSZ pcszFormat)
{
    ATOM atom = WinFindAtom(WinQuerySystemAtomTable(), pcszFormat);
    if (!atom) {
        atom = WinAddAtom(WinQuerySystemAtomTable(), pcszFormat);
    }
    return atom;
}

void initClipbrd()
{
    RegisterClipboardFormat( kUnicodeMime );
}

void textToClipbrd( HAB hab, const char *text )
{
    size_t len = 0;
    size_t olen = 0;
    const char *tsav = text;

    if ( WinOpenClipbrd( hab ) )
    {
        WinEmptyClipbrd( hab );

        len = strlen( text );
        olen = (len + 2)*2;

        void *memuni = NULL;

        // place to clipboard as unicode
        if ( DosAllocSharedMem( &memuni, NULL, olen ,
                                PAG_WRITE | PAG_COMMIT | OBJ_GIVEABLE ) == 0 )
        {
            memset( memuni, 0, olen );
            void *tmem = memuni;

            //cpconv c( 1208, 1200 );
            tsav = text;
            //c.conv( &text, &len, (char **)&memuni, &olen );
            cnvUTF8ToUni( &text, &len, (char **)&memuni, &olen );
            text = tsav;

            ULONG ulFormatID = RegisterClipboardFormat( kUnicodeMime );
            WinSetClipbrdData( hab, (ULONG)tmem, ulFormatID, CFI_POINTER );
        }

        len = strlen( text );
        olen = (len + 2)*2;
        void *memcp = NULL;

        // place to clipboard as current codepage
        if ( DosAllocSharedMem( &memcp, NULL, olen ,
                                PAG_WRITE | PAG_COMMIT | OBJ_GIVEABLE ) == 0 )
        {
            memset( memcp, 0, olen );
            void *tmem = memcp;

            //cpconv c( 1208 );
            tsav = text;
            //c.conv( &text, &len, (char **)&memcp, &olen );
            cnvUTF8ToSys( &text, &len, (char **)&memcp, &olen );
			text = tsav;

            WinSetClipbrdData( hab, (ULONG)tmem, CF_TEXT, CFI_POINTER );
        }


        WinCloseClipbrd( hab );
    }
}

