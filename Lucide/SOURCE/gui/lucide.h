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


#ifndef __LUCIDE_H
#define __LUCIDE_H

extern const char *appName;
extern const char *appVersion;
extern HAB hab;
extern char deffont[];
extern int deffontlen;

class LuDocument;
class ProgressDlg;

enum PgLayout { SinglePage = 0, Continuous = 1 };

struct LuWindowPos
{
    SWP    Swp;
    USHORT XRestore;
    USHORT YRestore;
    USHORT CXRestore;
    USHORT CYRestore;
    USHORT XMinimize;
    USHORT YMinimize;
};

class Lucide
{
    private:
    
		static ProgressDlg *loadProgressDlg;
		static char docName[ CCHMAXPATH ];
		static bool docLoaded;
		static char *loadError;
		static bool isFullscreen;
		static LuWindowPos winPos;
    
        static void setOfPages( long pages );
        static void enableZoomMenus();
        static void setZoomChecks( SHORT cmd, SHORT cbind, double zoom );
        static void loadthread( void *p );

    public:
        static bool dontSwitchPage;
        static SHORT splitterPos;
        static bool showIndex;
        
        static void openDocument();
        static void loadDocument( const char *fn );
        static void setDocument( LuDocument *_doc );
        static void checkNavigationMenus();
        static void checkZoomMenus();
        static void checkMenus();
        static void checkNavpane();
        static void goToPage( long page );
        static void setZoom( double zoom );
        static void enableCopy( bool enable );
        static void setPageLayout( PgLayout layout );
        static void toggleFullscreen();
};

#endif // __LUCIDE_H

