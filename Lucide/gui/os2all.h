#ifndef __OS2ALL_H
#define __OS2ALL_H

/*
 *  Include this instead of <os2.h>
 */

#if defined(__EMX__)
#define OS2EMX_PLAIN_CHAR
#endif
#define INCL_BASE
#define INCL_PM
#include <os2.h>

#if defined(__GNUC__)
// make GCC 4.x happy
#undef FIELDOFFSET
#define FIELDOFFSET(t,f)  ((SHORT)(LONG)&(((t *)0)->f))
#endif

#endif //__OS2ALL_H

