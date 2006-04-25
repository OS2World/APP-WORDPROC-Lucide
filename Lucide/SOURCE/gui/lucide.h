#ifndef __LUCIDE_H
#define __LUCIDE_H

extern const char *appName;
extern HAB hab;
extern char deffont[];
extern int deffontlen;

class LuDocument;

class Lucide
{
	public:
		static bool dontSwitchPage;
		
		static void setDocument( LuDocument *_doc );
		static void checkNavigationMenus();
		static void checkZoomMenus();
		static void checkMenus();
		static void goToPage( long page );
		static void setZoom( double zoom );
		static void enableCopy( bool enable );
};

#endif // __LUCIDE_H

