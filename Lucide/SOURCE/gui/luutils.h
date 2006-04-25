#ifndef __LUUTILS_H
#define __LUUTILS_H


// Auto-free buffer
class afbuf
{
	protected:
		unsigned int size; 
	public:
		char *buffer;
		afbuf( unsigned int s );
		~afbuf() { delete buffer; }
		unsigned int getSize() { return size; }
    private:
        // dummy copy constructor and operator= to prevent copying
        afbuf( const afbuf& );
        afbuf& operator = ( const afbuf& );
};


#ifdef INCL_WIN
BOOL CreateGraphicsBuffer( HAB hab, PRECTL prectl, HPS hps, HPS *phpsBuffer, HDC *phdcBuffer );
void BlitGraphicsBuffer( HPS hps, HPS hpsBuffer, PRECTL prclPaint );
void DestroyGraphicsBuffer( HPS hpsBuffer, HDC hdcBuffer );
BOOL PMStoreWindowPos( PCSZ pIniName, PCSZ pAppName, PCSZ pKeyName, HWND hwnd );
void PMStoreWindowPosI( HINI ini, PCSZ pAppName, PCSZ pKeyName, HWND hwnd );
BOOL PMRestoreWindowPos( PCSZ pIniName, PCSZ pAppName, PCSZ pKeyName,
                         HWND hwnd, BOOL activate, BOOL chkCoord,
                         BOOL min, BOOL max, BOOL hide );
SHORT getStringPixSize( HPS hps, PCSZ str );
void textToClipbrd( HAB hab, const char *text );
void centerWindow( HWND parent, HWND hwnd );
#endif


char *newstrdup( const char *s );

// Internationalization/Localization
void loadLang();
#ifdef INCL_WIN
void localizeMenu( HWND hmenu );
void localizeDialog( HWND hdlg );
#endif
void getLocalizedString( const char *key, LONG maxLen, char *buf );
char *newstrdupL( const char *key );
#ifdef _STRING_INCLUDED
std::string getLocalizedString( const char *t );
std::string str( double n );
std::string time2string( unsigned long time );
#endif


#endif // __LUUTILS_H

