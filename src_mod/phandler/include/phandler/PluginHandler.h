#pragma once
#include <map>
#include <string>
#include "Plugin.hpp"

namespace phandler
{
////////////////////////
// CoD4X plugin handler.
class CPluginHandler 
{
    NO_COPY_CLASS(CPluginHandler);

public:

    CPluginHandler();
    ~CPluginHandler();

    ////////////////////////////////
    // Plugin handler management. //
    ////////////////////////////////

    //////////////////////////////
    // Initializes plugin handler.
    void Init();

    ///////////////////////////////////////////////////////////////////////////
    // Shut plugin handler down and free all resources.
    void Shutdown();

    ////////////////////////
    // Plugin management. //
    ////////////////////////

    ///////////////////////////////////
    // Loads plugin by its LibName_.
    void LoadPlugin(const char *LibName_);

    ///////////////////////////////////
    // Unload plugin by name LibName_.
    void UnloadPlugin(const char *LibName_);

    ///////////////////////////////////////////////
    // Prints info about plugin with name LibName_.
    void PrintPluginInfo(const char *LibName_);

    //////////////////////////////////////////
    // Prints all plugins summary information.
    void PrintPluginsSummary();

    /////////////////////
    // Fire plugin event.
    template <class... TParms>
    void Event(const unsigned int EventHashCode_, TParms... Params)
    {
        for (auto &plugin : m_Plugins)
        {
            CPlugin* pOldPlugin = SetCurrentPlugin(&plugin.second);
            m_CurrentPlugin->Event(EventHashCode_, Params...);
            SetCurrentPlugin(pOldPlugin);
        }
    }
    
    /////////////////////////
    // Return current plugin.
    CPlugin* CurrentPlugin() const;

    //////////////////////
    // Set current plugin.
    CPlugin* SetCurrentPlugin(CPlugin* const pPlugin_);

    ///////////////////////////////////////////////////////
    // Return true if CmdName_ is registered in any plugin.
    bool IsCustomConsoleCommandExist(const char* const CmdName_) const;

    //////////////////////////////////////////////
    // Executes registered plugin console command.
    bool ExecuteCustomConsoleCommand(const char* const CmdName_) const;

  private:
    ////////////////////////////////////////////////////////////////
    // Returns true if plugin with name LibName_ has known checksum.
    bool isLegacyPlugin(const std::string &LibPath_) const;

    ////////////////////////////
    // Returns plugin file path.
    std::string getPluginFilePath(const std::string& strPluginName_) const;

    bool m_Initialized;
    std::map<std::string, CPlugin> m_Plugins;
    CPlugin *m_CurrentPlugin;
};
} // end of namespace phandler

phandler::CPluginHandler* GetPluginHandler();
