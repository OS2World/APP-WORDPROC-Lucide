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


#include "messages.h"

// Dynamic menu items
extern const char *MENU_CLEAR_LIST = "MENU_CLEAR_LIST";

// Toolbar hints
const char *TBHINT_OPEN          = "TBHINT_OPEN";
const char *TBHINT_PRINT         = "TBHINT_PRINT";
const char *TBHINT_SHOW_NAV_PANE = "TBHINT_SHOW_NAV_PANE";
const char *TBHINT_FIRST_PAGE    = "TBHINT_FIRST_PAGE";
const char *TBHINT_PREV_PAGE     = "TBHINT_PREV_PAGE";
const char *TBHINT_NEXT_PAGE     = "TBHINT_NEXT_PAGE";
const char *TBHINT_LAST_PAGE     = "TBHINT_LAST_PAGE";
const char *TBHINT_ACTUAL_SIZE   = "TBHINT_ACTUAL_SIZE";
const char *TBHINT_FIT_WINDOW    = "TBHINT_FIT_WINDOW";
const char *TBHINT_FIT_WIDTH     = "TBHINT_FIT_WIDTH";
const char *TBHINT_FIND          = "TBHINT_FIND";
const char *TBHINT_FINDAGAIN     = "TBHINT_FINDAGAIN";
const char *TBHINT_ZOOM_IN_OUT   = "TBHINT_ZOOM_IN_OUT";
const char *TBHINT_BACK          = "TBHINT_BACK";
// toolbar's page number
const char *TB_PAGENUM           = "TB_PAGENUM";


// Lucide messages
const char *MSGS_MAIN_WIN_TITLE           = "MSGS_MAIN_WIN_TITLE";
const char *MSGS_NO_SUIT_PLUG             = "MSGS_NO_SUIT_PLUG";
const char *MSGS_FILE_LOAD_ERROR          = "MSGS_FILE_LOAD_ERROR";
const char *MSGS_LOADING_DOCUMENT         = "MSGS_LOADING_DOCUMENT";
const char *MSGS_CREATING_THUMBNAIL       = "MSGS_CREATING_THUMBNAIL";
const char *MSGS_WARNING                  = "MSGS_WARNING";
const char *MSGS_OVERWRITE_FILE           = "MSGS_OVERWRITE_FILE";
const char *MSGS_FILE_SAVE_ERROR          = "MSGS_FILE_SAVE_ERROR";
const char *MSGS_PAGE                     = "MSGS_PAGE";
const char *MSGS_ERROR_STARTING_BROWSER   = "MSGS_ERROR_STARTING_BROWSER";
const char *MSGS_CLOSE_MODIFIED_DOCUMENT  = "MSGS_CLOSE_MODIFIED_DOCUMENT";
const char *MSGS_FILE_COPY_SUFFIX         = "MSGS_FILE_COPY_SUFFIX";
const char *MSGS_TEMP_FILE_LOAD_ERROR     = "MSGS_TEMP_FILE_LOAD_ERROR";
const char *MSGS_TEMP_FILE_SAVE_ERROR     = "MSGS_TEMP_FILE_SAVE_ERROR";
const char *MSGS_NO_TEMP_DIR_ERROR        = "MSGS_NO_TEMP_DIR_ERROR";
const char *MSGS_NO_PRINTER_FOUND_ERROR   = "MSGS_NO_PRINTER_FOUND_ERROR";
const char *MSGS_HELP_INSTANCE_FAILED     = "MSGS_HELP_INSTANCE_FAILED";

const char *MSGS_LDERR                    = "MSGS_LDERR";
const char *MSGS_LDERR_OUT_OF_MEMORY      = "MSGS_LDERR_OUT_OF_MEMORY";
const char *MSGS_LDERR_OPEN_ERROR         = "MSGS_LDERR_OPEN_ERROR";
const char *MSGS_LDERR_READ_ERROR         = "MSGS_LDERR_READ_ERROR";
const char *MSGS_LDERR_DAMAGED            = "MSGS_LDERR_DAMAGED";
const char *MSGS_LDERR_WRONG_FORMAT       = "MSGS_LDERR_WRONG_FORMAT";
const char *MSGS_LDERR_ENCRYPTED          = "MSGS_LDERR_ENCRYPTED";

const char *MSGS_RERR_OUT_OF_MEMORY       = "MSGS_RERR_OUT_OF_MEMORY";
const char *MSGS_RERR_CORRUPTED_PAGE_DATA = "MSGS_RERR_CORRUPTED_PAGE_DATA";
const char *MSGS_RERR_FONT_NOT_FOUND      = "MSGS_RERR_FONT_NOT_FOUND";


// Settings dialog
const char *SD_SINGLE_PAGE = "SD_SINGLE_PAGE";
const char *SD_CONTINUOUS  = "SD_CONTINUOUS";

// Plugins List columns titles
const char *PLUGLIST_PLUGIN_NAME = "PLUGLIST_PLUGIN_NAME";
const char *PLUGLIST_SUPP_EXTS   = "PLUGLIST_SUPP_EXTS";
const char *PLUGLIST_PLUGIN_DESC = "PLUGLIST_PLUGIN_DESC";

// 'Fonts Info' List columns titles
const char *FONTINFO_NAME     = "FONTINFO_NAME";
const char *FONTINFO_TYPE     = "FONTINFO_TYPE";
const char *FONTINFO_EMBEDDED = "FONTINFO_EMBEDDED";
const char *FONTINFO_SUBNAME  = "FONTINFO_SUBNAME";
// 'Fonts Info' Embedded types
const char *FONTINFO_EMBED_NOT_EMBEDDED    = "FONTINFO_EMBED_NOT_EMBEDDED";
const char *FONTINFO_EMBED_EMBEDDED        = "FONTINFO_EMBED_EMBEDDED";
const char *FONTINFO_EMBED_EMBEDDED_SUBSET = "FONTINFO_EMBED_EMBEDDED_SUBSET";


// "Document info" dialog,  Document info keys
const char *DOCINFO_TITLE         = "DOCINFO_TITLE";
const char *DOCINFO_FORMAT        = "DOCINFO_FORMAT";
const char *DOCINFO_AUTHOR        = "DOCINFO_AUTHOR";
const char *DOCINFO_SUBJECT       = "DOCINFO_SUBJECT";
const char *DOCINFO_KEYWORDS      = "DOCINFO_KEYWORDS";
const char *DOCINFO_CREATOR       = "DOCINFO_CREATOR";
const char *DOCINFO_PRODUCER      = "DOCINFO_PRODUCER";
const char *DOCINFO_CREATION_DATE = "DOCINFO_CREATION_DATE";
const char *DOCINFO_MOD_DATE      = "DOCINFO_MOD_DATE";
const char *DOCINFO_NAME = "DOCINFO_NAME";

// "Find" dialog, other 'find'-related messages
const char *FIND_SEARCH_PAGE_OF = "FIND_SEARCH_PAGE_OF";
const char *FIND_NOT_FOUND      = "FIND_NOT_FOUND";

// 'Go to page' dialog
const char *GTP_OF = "GTP_OF";

// Print dialog
const char *PD_RANGE_EVEN_ODD           = "PD_RANGE_EVEN_ODD";
const char *PD_RANGE_ODD                = "PD_RANGE_ODD";
const char *PD_RANGE_EVEN               = "PD_RANGE_EVEN";
// Printing, other 'print'-related messages
const char *PD_WRONG_MARGINS            = "PD_WRONG_MARGINS";
const char *PRINT_PRINTING_PAGE_OF      = "PRINT_PRINTING_PAGE_OF";
const char *PRINT_GENERATING_POSTSCRIPT = "PRINT_GENERATING_POSTSCRIPT";
const char *PRINT_SPOOLING_POSTSCRIPT   = "PRINT_SPOOLING_POSTSCRIPT";
const char *PRINT_FAILED                = "PRINT_FAILED";

// Open file dialog
const char *FDLG_NO_PREVIEW_AVAILABLE = "FDLG_NO_PREVIEW_AVAILABLE";
const char *FDLG_ALL_SUPPORTED_TYPES  = "FDLG_ALL_SUPPORTED_TYPES";

// Help file title
const char *HLP_TITLE = "HLP_TITLE";
