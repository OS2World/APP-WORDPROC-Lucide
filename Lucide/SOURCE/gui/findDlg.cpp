#define INCL_WIN
#include <os2.h>

#include "findDlg.h"
#include "Lucide_res.h"
#include "luutils.h"

#define MAXSEARCHLENGTH 100

FindDlg::FindDlg( HWND hWndFrame )
{
    hFrame        = hWndFrame;
    searchString  = newstrdup( "" );
    caseSensitive = false;
}

FindDlg::~FindDlg()
{
    delete searchString;
}

ULONG FindDlg::showDialog()
{
    return WinDlgBox( HWND_DESKTOP, hFrame, findDlgProc,
                      NULLHANDLE, IDD_FIND, this );
}



MRESULT EXPENTRY FindDlg::findDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    // This is a static method, so we don't know which instantiation we're
    // dealing with. But we can get a pseudo-this from the parameter to
    // WM_INITDLG, which we therafter store with the window and retrieve
    // as follows:
    FindDlg *_this = (FindDlg *)WinQueryWindowULong( hwnd, QWL_USER );

    switch (msg)
    {

        // Dialog has just been created
        case WM_INITDLG:
        {
            // Save the mp2 into our user data so that subsequent calls have
            // access to the parent C++ object
            WinSetWindowULong( hwnd, QWL_USER, (ULONG)mp2 );
            _this = (FindDlg *)mp2;
            localizeDialog( hwnd );
            centerWindow( _this->hFrame, hwnd );

            WinSendDlgItemMsg( hwnd, IDC_FINDFIELD, EM_SETTEXTLIMIT,
                               MPFROMSHORT( MAXSEARCHLENGTH ), MPVOID );
            WinSetDlgItemText( hwnd, IDC_FINDFIELD, _this->searchString );
            WinCheckButton( hwnd, IDC_FINDMATCHCASE, _this->caseSensitive );

            return (MRESULT)FALSE;
        }

        case WM_COMMAND:
            switch (SHORT1FROMMP(mp1))
            {
                case DID_OK:
                    {
                        char buf[ MAXSEARCHLENGTH + 1 ];
                        WinQueryDlgItemText( hwnd, IDC_FINDFIELD, sizeof( buf ), buf );
                        delete _this->searchString;
                        _this->searchString = newstrdup( buf );
                        _this->caseSensitive = WinQueryButtonCheckstate( hwnd, IDC_FINDMATCHCASE );
                        WinDismissDlg( hwnd, DID_OK );
                    }
                    return (MRESULT)FALSE;

                case DID_CANCEL:
                    WinDismissDlg( hwnd, DID_CANCEL );
                    return (MRESULT)FALSE;
            };
            return (MRESULT)FALSE;
    }
    return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}


