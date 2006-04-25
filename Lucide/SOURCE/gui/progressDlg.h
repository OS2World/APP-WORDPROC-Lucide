#ifndef __PROGRESSDLG_H
#define __PROGRESSDLG_H


typedef void (*progressThreadFn)( void *data );
typedef void (*progressBrkFn)( void *data );


class ProgressDlg
{
    public:
        ProgressDlg( HWND hWndFrame );
        virtual ~ProgressDlg();

        void show( progressThreadFn _threadFn, void *_threadData );
        void hide();
        
        void setBreakFunc( progressBrkFn _fn, void *_data );
        void setText( const char *_text );

    private:

		void drawShape( HPS hps, PRECTL r );
    	void wmPaintBar( HWND hwnd );

        static MRESULT EXPENTRY progressDlgProc( HWND hwnd, ULONG msg,
                                                 MPARAM mp1, MPARAM mp2 );
        static MRESULT EXPENTRY progressBarProc( HWND hwnd, ULONG msg,
                                                 MPARAM mp1, MPARAM mp2 );

        HWND hFrame;
        HWND hDialog;
        char *text;
        progressThreadFn threadFn;
        void *threadData;
        progressBrkFn fn;
        void *data;
        PFNWP pOldBarProc;
		HPS hpsBuffer;
		HDC hdcBuffer;
		LONG startPos;
};

#endif // __PROGRESSDLG_H
