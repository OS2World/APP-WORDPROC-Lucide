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

// Регистрация класса Splitter
BOOL InitPMSplitterClass( HAB hab );

#define WC_ER_SPLITTER "er.splitter.class"

// Splitter window style definitions
#define SBS_VSPLIT          0x00000001L   // Vertical splitter
#define SBS_HSPLIT          0x00000002L   // Horizontal splitter
#define SBS_FIRSTFIXED      0x00000004L   // First window with fixed size
#define SBS_SECONDFIXED     0x00000008L   // Second window with fixed size
#define SBS_FIXED           (SBS_FIRSTFIXED|SBS_SECONDFIXED) // both fixed

// Splitter messages

// SetWindows - указывает окна которые будут разделены сплиттером
#define SBM_SETWINDOWS      (WM_USER+1)
// HWND firstWindow;
// HWND secondWindow;
// (BOOL)WinSendMsg( hwnd, SBM_SETWINDOWS,
//              MPFROMHWND( firstWindow ), MPFROMHWND( secondWindow ) );

// SetSplitterPos - указывает позицию сплиттера
#define SBM_SETSPLITTERPOS  (WM_USER+2)
// SHORT splitterPos;
// (BOOL)WinSendMsg( hwnd, SBM_SETSPLITTERPOS,
//                   MPFROMSHORT( splitterPos ), MPVOID );

// GetSplitterPos - возвращает позицию сплиттера
#define SBM_GETSPLITTERPOS  (WM_USER+3)
// (SHORT)WinSendMsg( hwnd, SBM_GETSPLITTERPOS, MPVOID, MPVOID );

// SetPointers - указать используемые мышиные поинтеры.
//               по умолчанию используются
//               системные SPTR_SIZEWE и SPTR_SIZENS
#define SBM_SETPOINTERS     (WM_USER+4)
// HPOINTER ptrWE;
// HPOINTER ptrNS;
// (BOOL)WinSendMsg( hwnd, SBM_SETPOINTERS, (MPARAM)ptrWE, (MPARAM)ptrNS );

// SetFixedSize - указать фиксированный размер
#define SBM_SETFIXEDSIZE    (WM_USER+5)
// SHORT size;
// (BOOL)WinSendMsg( hwnd, SBM_SETFIXEDSIZE, MPFROMSHORT( size ), MPVOID );

// Control notification code, splitter pos changed
// MP1 - (id, SBN_POSITIONCHANGED)  MP2 - (newpos, oldpos)
#define SBN_POSITIONCHANGED	1

/*****************************************************/
/*                   Toolbar                         */
/*****************************************************/

// Регистрация класса Toolbar

BOOL InitPMToolbarClass( HAB hab );

#define WC_ER_TOOLBAR "er.toolbar.class"

#define DEFAULT_PICTSIZE        20
//#define DEFAULT_PICTSIZE        40
#define TOOLBAR_HEIGHT_ADD      8


// Toolbar messages

// AddButton - добавляет кнопку на тулбар
#define TBM_ADDBUTTON       (WM_USER+1)
// AddBtnStruct *bs;
// WinSendMsg( hwnd, TBM_ADDBUTTON, (MPARAM)bs, MPVOID );

// AddSeparator - добавляет полоску/разделитель на тулбар
#define TBM_ADDSEPARATOR    (WM_USER+2)
// WinSendMsg( hwnd, TBM_ADDSEPARATOR, MPVOID, MPVOID );

// QueryCheck - проверяет, нажата ли кнопка
#define TBM_QUERYCHECK      (WM_USER+3)
// USHORT cmd;
// (BOOL)WinSendMsg( hwnd, TBM_QUERYCHECK, MPFROMSHORT(cmd), MPVOID );

// SetCheck - переводит кнопку в нажатое/отжатое состояние
#define TBM_SETCHECK        (WM_USER+4)
// USHORT cmd;
// BOOL checked;
// WinSendMsg( hwnd, TBM_SETCHECK, MPFROMSHORT(cmd), (MPARAM)checked );

// EnableItem - разрешает/запрещает кнопку
#define TBM_ENABLEITEM      (WM_USER+5)
// USHORT cmd;
// BOOL enable;
// WinSendMsg( hwnd, TBM_ENABLEITEM, MPFROMSHORT(cmd), (MPARAM)enable );

// SetBubbleText - устанавливает всплывающую подсказку
#define TBM_SETBUBBLETEXT   (WM_USER+6)
// USHORT cmd;
// PCSZ text;
// WinSendMsg( hwnd, TBM_SETBUBBLETEXT, MPFROMSHORT(cmd), MPFROMP(text) );

// SetPictSize - устанавливает размер используемых битмапов,
//               по умолчанию 20 (картинки квадратные)
#define TBM_SETPICTSIZE     (WM_USER+7)
// USHORT sz;
// WinSendMsg( hwnd, TBM_SETPICTSIZE, MPFROMSHORT( sz ), MPVOID );

// AddControl - добавляет произвольный контрол на тулбар
#define TBM_ADDCONTROL      (WM_USER+8)
// AddCtrlStruct *cs;
// WinSendMsg( hwnd, TBM_ADDCONTROL, (MPARAM)cs, MPVOID );

// Структура, используемая при добавлении кнопок на тулбар
// Неиспользуемые поля должны быть заполнены значением 0 (NULL)
struct AddBtnStruct
{
    USHORT cmd; // Команда
    // Всплывающий текст. Либо указатель на строку (bubbleText),
    // либо строка в ресурсах (bubbleRes и bubbleHmod)
    PSZ bubbleText;
    USHORT bubbleRes;
    HMODULE bubbleHmod;
    // Битмап в ресурсах
    USHORT pictRes;
    HMODULE pictHmod;
    // Если при нажатии на кнопку должно появлятся меню
    USHORT menuRes;
    HMODULE menuHmod;

    BOOL checked; // Нажата ли кнопка
    BOOL enabled; // Разрешена ли кнопка
};

// Структура, используемая при добавлении контролов на тулбар
// Неиспользуемые поля должны быть заполнены значением 0 (NULL)
struct AddCtrlStruct
{
    HWND ctrlHandle; // HWND контрола
    SHORT cx;        // Ширина контрола
    SHORT cy;        // ноль либо значение меньше нуля
                     // если <0 - то контрол будет продлён вниз (for combobox)
    // Всплывающий текст. Либо указатель на строку (bubbleText),
    // либо строка в ресурсах (bubbleRes и bubbleHmod)
    PSZ bubbleText;
    USHORT bubbleRes;
    HMODULE bubbleHmod;
};

//
// Примечания:
//
// - При рисовании битмапа левый нижний пиксель задаёт прозрачный цвет.
//
// - На некоторых старых видеодрайверах рисование с прозрачностью
//   не работает. Картинка либо чёрная, либо без прозрачности, либо
//   система вешается. В этом случае добавьте в CONFIG.SYS строку
//   SET ERTOOLBARSAFEDRAW=1 - будет использоваться медленное
//   попиксельное рисование. На SDD/SNAP рисование с прозрачностью
//   всегда работает корректно.
//

#endif //__TB_SPL_H

