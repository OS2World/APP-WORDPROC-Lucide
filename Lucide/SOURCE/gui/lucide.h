#ifndef __LUCIDE_H
#define __LUCIDE_H

extern const char *appName;
extern const char *appVersion;
extern HAB hab;
extern char deffont[];
extern int deffontlen;

class LuDocument;
class ProgressDlg;

enum ViewMode { SinglePage, Continuous };

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
        static void setViewMode( ViewMode mode );
        static void toggleFullscreen();
};

#endif // __LUCIDE_H

