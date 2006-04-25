#ifndef __FONTSINFODLG_H
#define __FONTSINFODLG_H


class LuDocument;


class FontsInfoDlg
{
    public:
        FontsInfoDlg( HWND hWndFrame, LuDocument *_doc );
        virtual ~FontsInfoDlg();

        // Once a dialog object is created, either delete it again, or
        // call doDialog. doDialog will run the object and delete it when done
        void doDialog();

        // Internal stuffs
    private:

    	void loadList();
        static MRESULT EXPENTRY fontsInfoDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
        static void loadthread( void *p );

        HWND hFrame;
        HWND hDialog;
        HWND hContainer;
        LuDocument *doc;
        
        // columns titles
        PSZ name, type, embed;
};

#endif // __FONTSINFODLG_H
