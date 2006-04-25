#ifndef __PLUGINMAN_H
#define __PLUGINMAN_H

#include <vector>
#include <string>
using namespace std;


class LuDocument;

struct PluginInfo
{
    HMODULE handle;
    std::string name;
    std::string extensions;
    std::string description;
};

typedef vector<PluginInfo> PluginInfoList;

class PluginManager
{
    private:
        PluginInfoList *plugins;
        void loadPlugin( const char *dllname );
    public:
        PluginManager();
        ~PluginManager();
        PluginInfoList *getPluginsList() { return plugins; }
        LuDocument *createDocumentForExt( const char *ext );
        std::string getExtsMask();
};

#endif // __PLUGINMAN_H
