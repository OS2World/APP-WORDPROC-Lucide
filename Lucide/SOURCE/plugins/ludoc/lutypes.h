#ifndef lutypes_h
#define lutypes_h


struct LuRectangle
{ 
	double x1;
	double y1;
	double x2;
	double y2; 
};


#define LU_LINK_TYPE_TITLE         0
#define LU_LINK_TYPE_PAGE          1
#define LU_LINK_TYPE_EXTERNAL_URI  2


struct LuLink
{
	char *title;
	char *uri;
	long type;
	long page;
};


struct LuLinkMapping
{
	LuLink link;
	LuRectangle area;
};


struct LuFontInfo
{
	char *name;
	char *type;
	char *embedded;
};

	
#define LU_DOCUMENT_LAYOUT_SINGLE_PAGE       0
#define LU_DOCUMENT_LAYOUT_ONE_COLUMN        1
#define LU_DOCUMENT_LAYOUT_TWO_COLUMN_LEFT   2
#define LU_DOCUMENT_LAYOUT_TWO_COLUMN_RIGHT  3
#define LU_DOCUMENT_LAYOUT_TWO_PAGE_LEFT     4
#define LU_DOCUMENT_LAYOUT_TWO_PAGE_RIGHT    5

	
#define LU_DOCUMENT_MODE_NONE             0
#define LU_DOCUMENT_MODE_USE_OC           1
#define LU_DOCUMENT_MODE_USE_THUMBS       2
#define LU_DOCUMENT_MODE_FULL_SCREEN      3
#define LU_DOCUMENT_MODE_USE_ATTACHMENTS  4
#define LU_DOCUMENT_MODE_PRESENTATION     LU_DOCUMENT_MODE_FULL_SCREEN


#define LU_DOCUMENT_UI_HINT_HIDE_TOOLBAR       0x0001
#define LU_DOCUMENT_UI_HINT_HIDE_MENUBAR       0x0002
#define LU_DOCUMENT_UI_HINT_HIDE_WINDOWUI      0x0004
#define LU_DOCUMENT_UI_HINT_FIT_WINDOW         0x0008
#define LU_DOCUMENT_UI_HINT_CENTER_WINDOW      0x0010
#define LU_DOCUMENT_UI_HINT_DISPLAY_DOC_TITLE  0x0020
#define LU_DOCUMENT_UI_HINT_DIRECTION_RTL      0x0040



#define LU_DOCUMENT_PERMISSIONS_OK_TO_PRINT      0x0001
#define LU_DOCUMENT_PERMISSIONS_OK_TO_MODIFY     0x0002
#define LU_DOCUMENT_PERMISSIONS_OK_TO_COPY       0x0004
#define LU_DOCUMENT_PERMISSIONS_OK_TO_ADD_NOTES  0x0008
#define LU_DOCUMENT_PERMISSIONS_FULL  (LU_DOCUMENT_PERMISSIONS_OK_TO_PRINT|LU_DOCUMENT_PERMISSIONS_OK_TO_MODIFY|LU_DOCUMENT_PERMISSIONS_OK_TO_COPY|LU_DOCUMENT_PERMISSIONS_OK_TO_ADD_NOTES)


#define LU_DOCUMENT_INFO_TITLE          0x0001
#define LU_DOCUMENT_INFO_FORMAT         0x0002
#define LU_DOCUMENT_INFO_AUTHOR         0x0004
#define LU_DOCUMENT_INFO_SUBJECT        0x0008
#define LU_DOCUMENT_INFO_KEYWORDS       0x0010
#define LU_DOCUMENT_INFO_LAYOUT         0x0020
#define LU_DOCUMENT_INFO_CREATOR        0x0040
#define LU_DOCUMENT_INFO_PRODUCER       0x0080
#define LU_DOCUMENT_INFO_CREATION_DATE  0x0100
#define LU_DOCUMENT_INFO_MOD_DATE       0x0200
#define LU_DOCUMENT_INFO_LINEARIZED     0x0400
#define LU_DOCUMENT_INFO_START_MODE     0x0800
#define LU_DOCUMENT_INFO_UI_HINTS       0x1000
#define LU_DOCUMENT_INFO_PERMISSIONS    0x2000
#define LU_DOCUMENT_INFO_N_PAGES        0x4000
#define LU_DOCUMENT_INFO_SECURITY       0x8000


struct LuDocumentInfo
{
	char *title;
	char *format; /* eg, "pdf-1.5" */
	char *author;
	char *subject;
	char *keywords;
	char *creator;
	char *producer;
	long security;
	long linearized;
	unsigned long creation_date;
	unsigned long modified_date;
	unsigned long layout;
	unsigned long mode;
	unsigned long ui_hints;
	unsigned long permissions;
	long n_pages;

	// Mask of all valid fields
	unsigned long fields_mask;
};

#ifndef __SOMIDL__
typedef long (_System *_asynchCallbackFn)( void *data );
//typedef _asynchCallbackFn *asynchCallbackFn;
#endif

#endif // lutypes_h
