#ifndef __DOCINFODLG_H
#define __DOCINFODLG_H


struct LuDocumentInfo;


class DocInfoDlg
{
    public:
        DocInfoDlg( HWND hWndFrame, LuDocumentInfo *_dinfo );
        virtual ~DocInfoDlg();

        // Once a dialog object is created, either delete it again, or
        // call doDialog. doDialog will run the object and delete it when done
        void doDialog();

        // Internal stuffs
    private:

		void insertPair( HWND cntr, const char *key, const char *value );
    	void loadValues( HWND cntr );
        static MRESULT EXPENTRY docInfoDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );

        HWND hFrame;
        LuDocumentInfo *dinfo;
};

#endif // __DOCINFODLG_H
