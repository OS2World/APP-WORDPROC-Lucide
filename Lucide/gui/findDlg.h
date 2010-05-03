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


#ifndef __FINDDLG_H
#define __FINDDLG_H


class FindDlg
{
    public:
        FindDlg( HWND hWndFrame );
        virtual ~FindDlg();

        ULONG showDialog();
        char *getSearchString() { return searchString; }
        bool isCaseSensitive() { return caseSensitive; }
        bool doFindBack() { return findBack; }

    private:

        static MRESULT EXPENTRY findDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );

        HWND hFrame;
        char *searchString;
        bool caseSensitive;
        bool findBack;
};

class GotoDlg
{
    public:
        GotoDlg( HWND hWndFrame, long _pages, long _curpage );
        virtual ~GotoDlg();

        ULONG showDialog();
        long getPage() { return page; }

    private:

        static MRESULT EXPENTRY gotoDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );

        HWND hFrame;
        long page;
        long pages;
        long curpage;
};

#endif // __FINDDLG_H
