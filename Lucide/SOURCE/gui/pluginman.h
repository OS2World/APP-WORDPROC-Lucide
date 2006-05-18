#ifndef __PLUGINMAN_H
#define __PLUGINMAN_H

#include <vector>
#include <string>


class LuDocument;

struct PluginInfo
{
    HMODULE handle;
    std::string name;
    std::string extensions;
    std::string description;
};

typedef std::vector<PluginInfo> PluginInfoList;

class PluginManager
{
    private:
        PluginInfoList *plugins;
        void loadPlugin( const char *dllname );
    public:
        PluginManager();
        ~PluginManager();
        PluginInfoList *getPluginsList() { return plugins; }
        LuDocument *createDocumentForExt( const char *ext, bool checkOnly );
        std::string getExtsMask();
};


extern PluginManager *pluginMan;

#endif // __PLUGINMAN_H
