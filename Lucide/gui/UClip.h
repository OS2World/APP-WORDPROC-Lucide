

#ifndef __UCLIP_H__
#define __UCLIP_H__

#include "os2all.h"

#ifndef WIN32API
#define WIN32API __stdcall
#endif
#ifdef VCL
#define BOOL PM_BOOL
#endif
#ifndef HANDLE
#define HANDLE ULONG
#endif

#ifdef __cplusplus
extern "C" {
#endif

BOOL APIENTRY UWinCloseClipbrd (HAB hab);
BOOL APIENTRY UWinEmptyClipbrd (HAB hab);
BOOL APIENTRY UWinOpenClipbrd (HAB hab);
ULONG APIENTRY UWinQueryClipbrdData (HAB hab, ULONG fmt);
BOOL APIENTRY UWinSetClipbrdData (HAB hab, ULONG ulData, ULONG fmt, ULONG rgfFmtInfo);

BOOL 	WIN32API OpenClipboard(HWND hwnd);
BOOL	WIN32API EmptyClipboard(void);
HANDLE 	WIN32API SetClipboardData(UINT uFormat, HANDLE hClipObj);
HANDLE 	WIN32API GetClipboardData(UINT uFormat);
BOOL 	WIN32API CloseClipboard(void);

#ifdef __cplusplus
}
#endif

/* Predefined Clipboard Formats */
#define UCLIP_CF_TEXT              1
#define UCLIP_CF_BITMAP            2
#define UCLIP_CF_METAFILEPICT      3
#define UCLIP_CF_SYLK              4
#define UCLIP_CF_DIF               5
#define UCLIP_CF_TIFF              6
#define UCLIP_CF_OEMTEXT           7
#define UCLIP_CF_DIB               8
#define UCLIP_CF_PALETTE           9
#define UCLIP_CF_PENDATA          10
#define UCLIP_CF_RIFF             11
#define UCLIP_CF_WAVE             12
#define UCLIP_CF_UNICODETEXT      13
#define UCLIP_CF_ENHMETAFILE      14
#define UCLIP_CF_HDROP            15
#define UCLIP_CF_LOCALE           16
#define UCLIP_CF_DIBV5            17
#define UCLIP_CF_MAX              18

#define UCLIP_CF_OWNERDISPLAY     0x0080
#define UCLIP_CF_DSPTEXT          0x0081
#define UCLIP_CF_DSPBITMAP        0x0082
#define UCLIP_CF_DSPMETAFILEPICT  0x0083
#define UCLIP_CF_DSPENHMETAFILE   0x008E

/* "Private" formats don't get GlobalFree()'d */
#define UCLIP_CF_PRIVATEFIRST     0x0200
#define UCLIP_CF_PRIVATELAST      0x02FF

/* "GDIOBJ" formats do get DeleteObject()'d */
#define UCLIP_CF_GDIOBJFIRST      0x0300
#define UCLIP_CF_GDIOBJLAST       0x03FF

#endif // __UCLIP_H__

