/* ***** BEGIN LICENSE BLOCK *****
 * Version: CDDL 1.0/LGPL 2.1
 *
 * The contents of this file are subject to the COMMON DEVELOPMENT AND
 * DISTRIBUTION LICENSE (CDDL) Version 1.0 (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at http://www.sun.com/cddl/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Initial Developer of the Original Code is
 * Eugene Romanenko, netlabs.org.
 * Portions created by the Initial Developer are Copyright (C) 2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the LGPL are applicable instead of those
 * above. If you wish to allow use of your version of this file only under the
 * terms of the LGPL, and not to allow others to use your version of this file
 * under the terms of the CDDL, indicate your decision by deleting the
 * provisions above and replace them with the notice and other provisions
 * required by the LGPL. If you do not delete the provisions above, a recipient
 * may use your version of this file under the terms of any one of the CDDL
 * or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */


#ifndef __LUCIDE_RES_H
#define __LUCIDE_RES_H

#define IDI_MAIN_ICON   1
#define IDB_LOGO        2

#define IDP_HAND        10
#define IDP_ZOOM_IN		11
#define IDP_ZOOM_OUT	12

#define IDB_OPEN        20
#define IDB_PRINT       21
#define IDB_NAVPANE     22
#define IDB_FIRSTPAGE   23
#define IDB_PREVPAGE    24
#define IDB_NEXTPAGE    25
#define IDB_LASTPAGE    26
#define IDB_100PERC     27
#define IDB_FITPAGE     28
#define IDB_FITWIDTH    29
#define IDB_FIND        30
#define IDB_FINDAGAIN   31
#define IDB_MGLASS		32

#define IDM_MAINMENU    100
#define IDA_MAINACCEL   101

#define CM_NEW_WINDOW   101
#define CM_OPEN         102
#define CM_SAVEAS       103
#define CM_CLOSE        104
#define CM_PRINT        105
#define CM_PLUGINSLIST  106
#define CM_EXIT         107

#define CM_FILEFIRST    151
#define CM_FILEPREVIOUS 152
#define CM_FILENEXT     153
#define CM_FILELAST     154

#define CM_COPY         201
#define CM_SELECTALL    202
#define CM_FIND         203
#define CM_FINDAGAIN    204
#define CM_SETTINGS     205

#define CM_FIRSTPAGE    301
#define CM_PREVPAGE     302
#define CM_NEXTPAGE     303
#define CM_LASTPAGE     304
#define CM_GOTOPAGE     305

#define CM_FITWINDOW    401
#define CM_ACTSIZE      402
#define CM_FITWIDTH     403
#define CM_ZOOM_IN_OUT	404
#define CM_ZOOM_IN      405
#define CM_ZOOM_OUT     406
#define CM_ROTATE90CW   407
#define CM_ROTATE90CCW  408
#define CM_SINGLEPAGE   409
#define CM_CONTINUOUS   410
#define CM_DOCINFO      411
#define CM_FONTSINFO    412

#define CM_NAVPANE      501
#define CM_MAXVIEW      502
#define CM_FULLSCREEN   503

#define CM_PRODINFO     601

// No menuitems for this commands
#define CM_MINIMIZE     701
#define CM_TOFULLSCREEN 702
#define CM_SWITCHWINDOW 703

#define CM_RECENT       1000
#define CM_RECENTCLEAR  1099

#define TBID_PAGENUM    1
#define TBID_OFPAGES    2
#define TBID_ZOOM       3

#define IDD_VIEWPLUGINS     1000
#define IDC_PLUGINSLIST     10

#define IDD_FONTINFO        1001
#define IDC_FONTSLIST       10
#define IDC_ENUMLABEL       11

#define IDD_DOCINFO         1002
#define IDC_PROPSLIST       10

#define IDD_FIND            1003
#define IDC_FINDFIELD       10
#define IDC_FINDMATCHCASE   11

#define IDD_PROGRESS        1004
#define IDC_PTEXT           10
#define IDC_PBAR            11

#define IDD_ABOUT           1005
#define IDT_LUCIDEVERSION   10
#define IDC_COPYRIGHTS      11
#define IDC_NETLABSURL      12
#define IDC_LOGO            13

#define IDD_SETTINGS        1006
#define IDC_DEFPGLAYOUT     10
#define IDC_DEFZOOM         11

#define IDD_GOTOPAGE        1007
#define IDC_PAGE            10
#define IDC_PAGES           11

#define IDD_PRINT           1008
#define IDC_PNAME           10
#define IDC_JOBPROPERTIES   11
#define IDC_PDESCRIPTION    12
#define IDC_RANGEALL        13
#define IDC_RANGECURRENT    14
#define IDC_RANGEPAGES      15
#define IDC_LABELFROM       16
#define IDC_PGFROM          17
#define IDC_LABELTO         18
#define IDC_PGTO            19
#define IDC_COPIES			20
#define IDC_RANGE_EVEN_ODD_LABEL	21
#define IDC_RANGE_EVEN_ODD  22
#define IDC_TYPE_POSTSCRIPT	23
#define IDC_TYPE_ASIMAGE	24
#define IDC_PRINT_TO_FILE	25
#define IDC_HIGHER_IMAGE_QUALITY	26
#define IDC_PORTRAIT		27
#define IDC_LANDSCAPE		28
#define IDC_IGNMARGINS		29
#define IDC_MLEFT			30
#define IDC_MRIGHT			31
#define IDC_MTOP			32
#define IDC_MBOTTOM			33
#define IDC_SELECTED_FORM	34

#define IDD_PASSWORD        1009
#define IDC_PASSWORD        10

#define IDD_LCD_FILEDLG     1010
#define IDC_PREVIEW			5000


#endif // __LUCIDE_RES_H
