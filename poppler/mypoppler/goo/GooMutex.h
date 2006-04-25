//========================================================================
//
// GooMutex.h
//
// Portable mutex macros.
//
// Copyright 2002-2003 Glyph & Cog, LLC
//
//========================================================================

#ifndef GMUTEX_H
#define GMUTEX_H

// Usage:
//
// GooMutex m;
// gInitMutex(&m);
// ...
// gLockMutex(&m);
//   ... critical section ...
// gUnlockMutex(&m);
// ...
// gDestroyMutex(&m);

#ifdef WIN32

#include <windows.h>

typedef CRITICAL_SECTION GooMutex;

#define gInitMutex(m) InitializeCriticalSection(m)
#define gDestroyMutex(m) DeleteCriticalSection(m)
#define gLockMutex(m) EnterCriticalSection(m)
#define gUnlockMutex(m) LeaveCriticalSection(m)

#elif defined(OS2)

#define INCL_DOS
#include <os2.h>

typedef HMTX GooMutex;

#define gInitMutex(m) DosCreateMutexSem(NULL,m,0,FALSE)
#define gDestroyMutex(m) DosCloseMutexSem(*m)
#define gLockMutex(m) DosRequestMutexSem(*m,SEM_INDEFINITE_WAIT)
#define gUnlockMutex(m) DosReleaseMutexSem(*m)


#else 
// assume pthreads

#include <pthread.h>

typedef pthread_mutex_t GooMutex;

#define gInitMutex(m) pthread_mutex_init(m, NULL)
#define gDestroyMutex(m) pthread_mutex_destroy(m)
#define gLockMutex(m) pthread_mutex_lock(m)
#define gUnlockMutex(m) pthread_mutex_unlock(m)

#endif

#endif
