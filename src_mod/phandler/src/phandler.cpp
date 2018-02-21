#include "phandler.hpp"
#include "PluginHandler.hpp"
#include "cmds.hpp"

void PHandler_Init()
{
    SV_AddPluginHandlerConsoleCommands();
    GetPluginHandler()->Init();
}

void PHandler_Shutdown()
{
    GetPluginHandler()->Shutdown();
}

qboolean PHandler_ExecuteConsoleCommand(const char* const CmdName_)
{
    return GetPluginHandler()->ExecuteCustomConsoleCommand(CmdName_) ? qtrue : qfalse;
}
