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

#define IDI_MAIN_ICON 1

#define IDP_HAND  10

#define IDB_OPEN		20
#define IDB_PRINT		21
#define IDB_NAVPANE		22
#define IDB_FIRSTPAGE	23
#define IDB_PREVPAGE	24
#define IDB_NEXTPAGE	25
#define IDB_LASTPAGE	26
#define IDB_100PERC		27
#define IDB_FITPAGE		28
#define IDB_FITWIDTH	29
#define IDB_FIND		30

#define IDM_MAINMENU    100
#define IDA_MAINACCEL	101

#define CM_OPEN			101
#define CM_SAVEAS		102
#define CM_EXPORTTOPS	103
#define CM_PAGESETUP	104
#define CM_PRINT		105
#define CM_PLUGINSLIST	106
#define CM_EXIT			107

#define CM_COPY			201
#define CM_SELECTALL	202
#define CM_FIND			203
#define CM_FINDAGAIN	204

#define CM_FIRSTPAGE	301
#define CM_PREVPAGE		302
#define CM_NEXTPAGE		303
#define CM_LASTPAGE		304
#define CM_GOTOPAGE		305

#define CM_FITWINDOW	401
#define CM_ACTSIZE		402
#define CM_FITWIDTH		403
#define CM_ROTATE90CW	404
#define CM_ROTATE90CCW	405
#define CM_SINGLEPAGE	406
#define CM_CONTINUOUS	407
#define CM_DOCINFO		408
#define CM_FONTSINFO	409

#define CM_NAVPANE		501
#define CM_FULLSCREEN	502

#define CM_PRODINFO		601

#define TBID_PAGENUM	1
#define TBID_OFPAGES	2
#define TBID_ZOOM		3

#define IDD_VIEWPLUGINS		1000
#define IDC_PLUGINSLIST		10

#define IDD_FONTINFO		1001
#define IDC_FONTSLIST		10
#define IDC_ENUMLABEL		11

#define IDD_DOCINFO			1002
#define IDC_PROPSLIST		10

#define IDD_FIND			1003
#define IDC_FINDFIELD		10
#define IDC_FINDMATCHCASE	11

#define IDD_PROGRESS		1004
#define IDC_PTEXT			10
#define IDC_PBAR			11

#define IDD_ABOUT			1005
#define IDT_LUCIDEVERSION	10
#define IDC_COPYRIGHTS		11
#define IDC_NETLABSURL		12

#endif // __LUCIDE_RES_H
