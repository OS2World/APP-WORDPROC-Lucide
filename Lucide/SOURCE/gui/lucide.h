#ifndef __LUCIDE_H
#define __LUCIDE_H

extern const char *appName;
extern HAB hab;
extern char deffont[];
extern int deffontlen;

class LuDocument;

enum ViewMode { SinglePage, Continuous };

class Lucide
{
    private:
        static void setOfPages( long pages );
        static void enableZoomMenus();
        static void setZoomChecks( SHORT cmd, SHORT cbind, double zoom );

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
};

#endif // __LUCIDE_H

