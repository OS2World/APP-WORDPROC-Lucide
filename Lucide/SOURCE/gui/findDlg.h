#ifndef __FINDDLG_H
#define __FINDDLG_H


class FindDlg
{
    public:
        FindDlg( HWND hWndFrame );
        virtual ~FindDlg();

        ULONG showDialog();
        char *getSearchString() { return searchString; }
        bool isCaseSensitive() { return caseSensitive; }

    private:

        static MRESULT EXPENTRY findDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );

        HWND hFrame;
        char *searchString;
        bool caseSensitive;
};

#endif // __FINDDLG_H
