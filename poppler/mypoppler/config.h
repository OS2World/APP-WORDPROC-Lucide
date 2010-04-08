/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Default to A4 paper. */
#define A4_PAPER 1

/* Use libjpeg instead of builtin jpeg decoder. */
#define ENABLE_LIBJPEG  1
//#undef ENABLE_LIBJPEG

/* Use zlib instead of builtin zlib decoder. */
#undef ENABLE_ZLIB

/* Use cairo for rendering. */
#undef HAVE_CAIRO

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'. */
#if defined(__WATCOMC__)
#undef HAVE_DIRENT_H
#else
#define HAVE_DIRENT_H 1
#endif

#define HAVE_DIRECT_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#undef HAVE_DLFCN_H

/* Have FreeType2 include files */
#define HAVE_FREETYPE_H 1

/* Define to 1 if you have the `fseek64' function. */
#undef HAVE_FSEEK64

/* Define to 1 if fseeko (and presumably ftello) exists and is declared. */
#undef HAVE_FSEEKO

/* Define to 1 if you have the `ftell64' function. */
#undef HAVE_FTELL64

/* Defines if gettimeofday is available on your system */
#undef HAVE_GETTIMEOFDAY

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `z' library (-lz). */
#undef HAVE_LIBZ

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `mkstemp' function. */
#define HAVE_MKSTEMP 1

/* Define to 1 if you have the `mkstemps' function. */
#undef HAVE_MKSTEMPS

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
#undef HAVE_NDIR_H

/* Define to 1 if you have the `popen' function. */
#undef HAVE_POPEN

/* Use splash for rendering. */
#define HAVE_SPLASH 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
#undef HAVE_SYS_DIR_H

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
#undef HAVE_SYS_NDIR_H

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <zlib.h> header file. */
#undef HAVE_ZLIB_H

/* Enable multithreading support. */
#undef MULTITHREADED

/* Generate OPI comments in PS output. */
#undef OPI_SUPPORT

/* Name of package */
#undef PACKAGE

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT

/* Define to the full name of this package. */
#undef PACKAGE_NAME

/* Define to the full name and version of this package. */
#undef PACKAGE_STRING

/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME

/* Define to the version of this package. */
#undef PACKAGE_VERSION

/* Define to 1 if you have the ANSI C header files. */
#undef STDC_HEADERS

/* Full path for the system-wide xpdfrc file. */
#undef SYSTEM_XPDFRC

/* Enable word list support. */
#undef TEXTOUT_WORD_LIST

/* Use fixed point arithmetic */
#undef USE_FIXEDPOINT

/* Version number of package */
#undef VERSION

/* Define to 1 if the X Window System is missing or not being used. */
#define X_DISPLAY_MISSING 1

/*
 * jpeg.h needs HAVE_BOOLEAN, when the system uses boolean in system
 * headers and I'm too lazy to write a configure test as long as only
 * unixware is related
 */
#ifdef _UNIXWARE
#define HAVE_BOOLEAN
#endif


/* Number of bits in a file offset, on hosts where this is settable. */
#undef _FILE_OFFSET_BITS

/* Define to 1 to make fseeko visible on some hosts (e.g. glibc 2.2). */
#undef _LARGEFILE_SOURCE

/* Define for large files, on AIX-style hosts. */
#undef _LARGE_FILES

#define POPPLER_DATADIR "."

#define HAVE_GETTIMEOFDAY 1
