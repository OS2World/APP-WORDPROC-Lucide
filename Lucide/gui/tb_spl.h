#ifndef __TB_SPL_H
#define __TB_SPL_H

/*
 *  PM Splitter and Toolbar interface.
 *  by Eugene Romanenko
 *
 *  This code is in the public domain and has no copyright.
 */

// Toolbar and splitter definitions

/*****************************************************/
/*                   Splitter                        */
/*****************************************************/

// ��������� ����� Splitter
BOOL InitPMSplitterClass( HAB hab );

#define WC_ER_SPLITTER "er.splitter.class"

// Splitter window style definitions
#define SBS_VSPLIT          0x00000001L   // Vertical splitter
#define SBS_HSPLIT          0x00000002L   // Horizontal splitter
#define SBS_FIRSTFIXED      0x00000004L   // First window with fixed size
#define SBS_SECONDFIXED     0x00000008L   // Second window with fixed size
#define SBS_FIXED           (SBS_FIRSTFIXED|SBS_SECONDFIXED) // both fixed

// Splitter messages

// SetWindows - 㪠�뢠�� ���� ����� ���� ࠧ������ ᯫ���஬
#define SBM_SETWINDOWS      (WM_USER+1)
// HWND firstWindow;
// HWND secondWindow;
// (BOOL)WinSendMsg( hwnd, SBM_SETWINDOWS,
//              MPFROMHWND( firstWindow ), MPFROMHWND( secondWindow ) );

// SetSplitterPos - 㪠�뢠�� ������ ᯫ����
#define SBM_SETSPLITTERPOS  (WM_USER+2)
// SHORT splitterPos;
// (BOOL)WinSendMsg( hwnd, SBM_SETSPLITTERPOS,
//                   MPFROMSHORT( splitterPos ), MPVOID );

// GetSplitterPos - �����頥� ������ ᯫ����
#define SBM_GETSPLITTERPOS  (WM_USER+3)
// (SHORT)WinSendMsg( hwnd, SBM_GETSPLITTERPOS, MPVOID, MPVOID );

// SetPointers - 㪠���� �ᯮ��㥬� ��設� �������.
//               �� 㬮�砭�� �ᯮ�������
//               ��⥬�� SPTR_SIZEWE � SPTR_SIZENS
#define SBM_SETPOINTERS     (WM_USER+4)
// HPOINTER ptrWE;
// HPOINTER ptrNS;
// (BOOL)WinSendMsg( hwnd, SBM_SETPOINTERS, (MPARAM)ptrWE, (MPARAM)ptrNS );

// SetFixedSize - 㪠���� 䨪�஢���� ࠧ���
#define SBM_SETFIXEDSIZE    (WM_USER+5)
// SHORT size;
// (BOOL)WinSendMsg( hwnd, SBM_SETFIXEDSIZE, MPFROMSHORT( size ), MPVOID );

// Control notification code, splitter pos changed
// MP1 - (id, SBN_POSITIONCHANGED)  MP2 - (newpos, oldpos)
#define SBN_POSITIONCHANGED	1

/*****************************************************/
/*                   Toolbar                         */
/*****************************************************/

// ��������� ����� Toolbar

BOOL InitPMToolbarClass( HAB hab );

#define WC_ER_TOOLBAR "er.toolbar.class"

#define DEFAULT_PICTSIZE        20
//#define DEFAULT_PICTSIZE        40
#define TOOLBAR_HEIGHT_ADD      8


// Toolbar messages

// AddButton - �������� ������ �� �㫡��
#define TBM_ADDBUTTON       (WM_USER+1)
// AddBtnStruct *bs;
// WinSendMsg( hwnd, TBM_ADDBUTTON, (MPARAM)bs, MPVOID );

// AddSeparator - �������� ������/ࠧ����⥫� �� �㫡��
#define TBM_ADDSEPARATOR    (WM_USER+2)
// WinSendMsg( hwnd, TBM_ADDSEPARATOR, MPVOID, MPVOID );

// QueryCheck - �஢����, ����� �� ������
#define TBM_QUERYCHECK      (WM_USER+3)
// USHORT cmd;
// (BOOL)WinSendMsg( hwnd, TBM_QUERYCHECK, MPFROMSHORT(cmd), MPVOID );

// SetCheck - ��ॢ���� ������ � ����⮥/�⦠⮥ ���ﭨ�
#define TBM_SETCHECK        (WM_USER+4)
// USHORT cmd;
// BOOL checked;
// WinSendMsg( hwnd, TBM_SETCHECK, MPFROMSHORT(cmd), (MPARAM)checked );

// EnableItem - ࠧ�蠥�/����頥� ������
#define TBM_ENABLEITEM      (WM_USER+5)
// USHORT cmd;
// BOOL enable;
// WinSendMsg( hwnd, TBM_ENABLEITEM, MPFROMSHORT(cmd), (MPARAM)enable );

// SetBubbleText - ��⠭�������� �ᯫ뢠���� ���᪠���
#define TBM_SETBUBBLETEXT   (WM_USER+6)
// USHORT cmd;
// PCSZ text;
// WinSendMsg( hwnd, TBM_SETBUBBLETEXT, MPFROMSHORT(cmd), MPFROMP(text) );

// SetPictSize - ��⠭�������� ࠧ��� �ᯮ��㥬�� ��⬠���,
//               �� 㬮�砭�� 20 (���⨭�� �������)
#define TBM_SETPICTSIZE     (WM_USER+7)
// USHORT sz;
// WinSendMsg( hwnd, TBM_SETPICTSIZE, MPFROMSHORT( sz ), MPVOID );

// AddControl - �������� �ந������ ����஫ �� �㫡��
#define TBM_ADDCONTROL      (WM_USER+8)
// AddCtrlStruct *cs;
// WinSendMsg( hwnd, TBM_ADDCONTROL, (MPARAM)cs, MPVOID );

// �������, �ᯮ��㥬�� �� ���������� ������ �� �㫡��
// ���ᯮ��㥬� ���� ������ ���� ��������� ���祭��� 0 (NULL)
struct AddBtnStruct
{
    USHORT cmd; // �������
    // �ᯫ뢠�騩 ⥪��. ���� 㪠��⥫� �� ��ப� (bubbleText),
    // ���� ��ப� � ������ (bubbleRes � bubbleHmod)
    PSZ bubbleText;
    USHORT bubbleRes;
    HMODULE bubbleHmod;
    // ��⬠� � ������
    USHORT pictRes;
    HMODULE pictHmod;
    // �᫨ �� ����⨨ �� ������ ������ ������ ����
    USHORT menuRes;
    HMODULE menuHmod;

    BOOL checked; // ����� �� ������
    BOOL enabled; // ����襭� �� ������
};

// �������, �ᯮ��㥬�� �� ���������� ����஫�� �� �㫡��
// ���ᯮ��㥬� ���� ������ ���� ��������� ���祭��� 0 (NULL)
struct AddCtrlStruct
{
    HWND ctrlHandle; // HWND ����஫�
    SHORT cx;        // ��ਭ� ����஫�
    SHORT cy;        // ���� ���� ���祭�� ����� ���
                     // �᫨ <0 - � ����஫ �㤥� �த�� ���� (for combobox)
    // �ᯫ뢠�騩 ⥪��. ���� 㪠��⥫� �� ��ப� (bubbleText),
    // ���� ��ப� � ������ (bubbleRes � bubbleHmod)
    PSZ bubbleText;
    USHORT bubbleRes;
    HMODULE bubbleHmod;
};

//
// �ਬ�砭��:
//
// - �� �ᮢ���� ��⬠�� ���� ������ ���ᥫ� ������ �஧��� 梥�.
//
// - �� �������� ����� ������ࠩ���� �ᮢ���� � �஧�筮����
//   �� ࠡ�⠥�. ���⨭�� ���� ��ୠ�, ���� ��� �஧�筮��, ����
//   ��⥬� ��蠥���. � �⮬ ��砥 ������� � CONFIG.SYS ��ப�
//   SET ERTOOLBARSAFEDRAW=1 - �㤥� �ᯮ�짮������ ���������
//   �����ᥫ쭮� �ᮢ����. �� SDD/SNAP �ᮢ���� � �஧�筮����
//   �ᥣ�� ࠡ�⠥� ���४⭮.
//

#endif //__TB_SPL_H

