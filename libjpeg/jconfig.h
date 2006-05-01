/* jconfig.wat --- jconfig.h for Watcom C/C++ on MS-DOS or OS/2. */
/* see jconfig.doc for explanations */

#define HAVE_PROTOTYPES 1
#define HAVE_UNSIGNED_CHAR 1
#define HAVE_UNSIGNED_SHORT 1
/* #define void char */
/* #define const */
#define CHAR_IS_UNSIGNED 1
#define HAVE_STDDEF_H 1
#define HAVE_STDLIB_H 1
#undef NEED_BSD_STRINGS
#undef NEED_SYS_TYPES_H
#undef NEED_FAR_POINTERS	/* Watcom uses flat 32-bit addressing */
#undef NEED_SHORT_EXTERNAL_NAMES
#undef INCOMPLETE_TYPES_BROKEN

#ifdef JPEG_INTERNALS

#undef RIGHT_SHIFT_IS_UNSIGNED

#endif /* JPEG_INTERNALS */

#ifdef JPEG_CJPEG_DJPEG

#define BMP_SUPPORTED	1	/* BMP image file format */
#define GIF_SUPPORTED	1	/* GIF image file format */
#define PPM_SUPPORTED	1	/* PBMPLUS PPM/PGM image file format */
#undef RLE_SUPPORTED		/* Utah RLE image file format */
#define TARGA_SUPPORTED	1	/* Targa image file format */

#undef TWO_FILE_COMMANDLINE	/* optional */
#define USE_SETMODE	1	/* Needed to make one-file style work in Watcom */
#undef NEED_SIGNAL_CATCHER	/* Define this if you use jmemname.c */
#undef DONT_USE_B_MODE
#undef PROGRESS_REPORT		/* optional */


#endif /* JPEG_CJPEG_DJPEG */
