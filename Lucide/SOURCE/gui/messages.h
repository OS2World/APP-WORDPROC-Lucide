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


#ifndef __MESSAGES_H
#define __MESSAGES_H


// Toolbar hints
extern const char *TBHINT_OPEN;
extern const char *TBHINT_PRINT;
extern const char *TBHINT_SHOW_NAV_PANE;
extern const char *TBHINT_FIRST_PAGE;
extern const char *TBHINT_PREV_PAGE;
extern const char *TBHINT_NEXT_PAGE;
extern const char *TBHINT_LAST_PAGE;
extern const char *TBHINT_ACTUAL_SIZE;
extern const char *TBHINT_FIT_WINDOW;
extern const char *TBHINT_FIT_WIDTH;
extern const char *TBHINT_FIND;
extern const char *TBHINT_FINDAGAIN;
extern const char *TBHINT_ZOOM_IN_OUT;
// toolbar's page number
extern const char *TB_PAGENUM;

// Lucide messages
extern const char *MSGS_MAIN_WIN_TITLE;
extern const char *MSGS_NO_SUIT_PLUG;
extern const char *MSGS_FILE_LOAD_ERROR;
extern const char *MSGS_LOADING_DOCUMENT;
extern const char *MSGS_CREATING_THUMBNAIL;
extern const char *MSGS_WARNING;
extern const char *MSGS_OVERWRITE_FILE;
extern const char *MSGS_FILE_SAVE_ERROR;
extern const char *MSGS_PAGE;
extern const char *MSGS_ERROR_STARTING_BROWSER;

extern const char *MSGS_LDERR;
extern const char *MSGS_LDERR_OUT_OF_MEMORY;
extern const char *MSGS_LDERR_OPEN_ERROR;
extern const char *MSGS_LDERR_READ_ERROR;
extern const char *MSGS_LDERR_DAMAGED;
extern const char *MSGS_LDERR_WRONG_FORMAT;
extern const char *MSGS_LDERR_ENCRYPTED;

extern const char *MSGS_RERR_OUT_OF_MEMORY;
extern const char *MSGS_RERR_CORRUPTED_PAGE_DATA;
extern const char *MSGS_RERR_FONT_NOT_FOUND;


// Settings dialog
extern const char *SD_SINGLE_PAGE;
extern const char *SD_CONTINUOUS;

// Plugins List columns titles
extern const char *PLUGLIST_PLUGIN_NAME;
extern const char *PLUGLIST_SUPP_EXTS;
extern const char *PLUGLIST_PLUGIN_DESC;

// 'Fonts Info' List columns titles
extern const char *FONTINFO_NAME;
extern const char *FONTINFO_TYPE;
extern const char *FONTINFO_EMBEDDED;
// 'Fonts Info' Embedded types
extern const char *FONTINFO_EMBED_NOT_EMBEDDED;
extern const char *FONTINFO_EMBED_EMBEDDED;
extern const char *FONTINFO_EMBED_EMBEDDED_SUBSET;


// "Document info" dialog,  Document info keys
extern const char *DOCINFO_TITLE;
extern const char *DOCINFO_FORMAT;
extern const char *DOCINFO_AUTHOR;
extern const char *DOCINFO_SUBJECT;
extern const char *DOCINFO_KEYWORDS;
extern const char *DOCINFO_CREATOR;
extern const char *DOCINFO_PRODUCER;
extern const char *DOCINFO_CREATION_DATE;
extern const char *DOCINFO_MOD_DATE;

// "Find" dialog, other 'find'-related messages
extern const char *FIND_SEARCH_PAGE_OF;
extern const char *FIND_NOT_FOUND;

// 'Go to page' dialog
extern const char *GTP_OF;

// Printing, other 'print'-related messages
extern const char *PD_WRONG_MARGINS;
extern const char *PRINT_PRINTING_PAGE_OF;
extern const char *PRINT_GENERATING_POSTSCRIPT;
extern const char *PRINT_SPOOLING_POSTSCRIPT;
extern const char *PRINT_FAILED;


#endif // __MESSAGES_H
