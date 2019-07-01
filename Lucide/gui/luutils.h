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


#ifndef __LUUTILS_H
#define __LUUTILS_H

#include <string>

// Auto-free buffer
class afbuf
{
	protected:
		unsigned int size;
	public:
		char *buffer;
		afbuf( unsigned int s );
		~afbuf() { delete[] buffer; }
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
SHORT setZoomValues( HWND lbox );
double convZoom( SHORT v );

typedef bool (* PENUMCNTRFN)( HWND hwndCntr, PRECORDCORE pRec, void *pUser );
void enumCntrRecords( HWND hwndCntr, PENUMCNTRFN pFn, void *pUser );
void enumCntrEmphasis( HWND hwndCntr, USHORT fEmphasisMask,
                       PENUMCNTRFN pFn, void *pUser );
#endif


char *newstrdup( const char *s );
char *getTmpDir( char *buf );

// Internationalization/Localization
void loadLang();
#ifdef INCL_WIN
void localizeMenu( HWND hmenu );
void localizeDialog( HWND hdlg );
#endif
void getLocalizedString( const char *key, LONG maxLen, char *buf );
char *newstrdupL( const char *key );
std::string getLocalizedString( const char *t );
std::string str( double n );
std::string time2string( unsigned long time );

extern "C" int startBrowser( const char *url );


#endif // __LUUTILS_H

