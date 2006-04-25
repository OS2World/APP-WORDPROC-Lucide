#ifndef __PLUGINVIEWDLG_H
#define __PLUGINVIEWDLG_H

#include "pluginman.h"


class PluginViewDlg
{
    public:
        PluginViewDlg( HWND hWndFrame, PluginInfoList *plist );
        virtual ~PluginViewDlg();

        // Once a dialog object is created, either delete it again, or
        // call doDialog. doDialog will run the object and delete it when done
        void doDialog();

        // Internal stuffs
    private:

        static MRESULT EXPENTRY pluginViewDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );

        HWND hFrame;
        PluginInfoList *plugins;
        
        // columns titles
        PSZ pname, suppexts, pdesc;
};

#endif // __PLUGINVIEWDLG_H
