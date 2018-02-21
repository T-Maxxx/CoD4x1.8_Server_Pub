#include "Plugin.hpp"
#include "dispatcher.hpp"
#include "PluginHandler.hpp"
#include <algorithm>
#include <cassert>
#include <compiletime/ctcrc32.hpp>

BEGIN_EXTERN_C
#include <core/qcommon.h>
#include <core/cmd.h>
END_EXTERN_C

using namespace std;

namespace phandler
{

CPlugin::CPlugin() 
    : m_LibHandle(INVALID_LIB_HANDLE)
    , m_pEventDispatcher(nullptr)
    , m_Initialized(false)
{

}

CPlugin::~CPlugin()
{
    assert(!m_Initialized && "You have to call Unload() before deleting object");
}

CPlugin::CPlugin(CPlugin&& From_)
    : CPlugin()
{
    // I am newly created CPlugin instance but I didn't hit my constructor.
    if (m_Initialized)
        Unload();

    // Always TODO: If you adding fields to this class, do not forget to add it here.
    m_Initialized = false;
    m_LibHandle = From_.m_LibHandle;

    From_.m_Initialized = false;
    From_.m_LibHandle = INVALID_LIB_HANDLE;
}

bool CPlugin::LoadFromFile(const std::string &LibPath_)
{
    // We can't rely on filename, only it's hash.
    // That's why CPlugin not holds plugin name.
    // Plugin handler does that.

    Com_DPrintf("Loading plugin from file '%s'\n", LibPath_.c_str());
    m_LibHandle = Sys_LoadLibrary(LibPath_.c_str());
    if (m_LibHandle == INVALID_LIB_HANDLE)
    {
        Com_PrintError("Error: plugin file not found\n");
        return false;
    }
    Com_DPrintf("Plugin binary file loaded successfully\n");


    Com_DPrintf("Setting up plugin syscall dispatchers\n");
    void* pPluginEntry = Sys_GetProcedure(m_LibHandle, "pluginEntry");
    if (!pPluginEntry)
    {
        Com_PrintError("Error: plugin entry point not found\n");
        return false;
    }
    m_pEventDispatcher = ((TSysCall(*)(const TSysCall))pPluginEntry)(SysCallDispatcher);
    Com_DPrintf("Syscall dispatcher has been set successfully\n");

    return true;
}

void CPlugin::Unload()
{
    /*
    if (pluginFunctions.plugins[id].exports != 0)
    { // Library-plugins cannot be unloaded, see plugins/readme.txt
        Com_PrintError("PHandler_Unload: Cannot unload a library plugin!\n");
        return;
    }
    */

    /* TODO: yes, we will be able ;D
    if (pluginFunctions.plugins[id].scriptfunctions != 0 || pluginFunctions.plugins[id].scriptmethods != 0)
    {
        // Script-library plugins cannot be unloaded, see plugins/readme.txt
        Com_PrintError("PHandler_Unload: Cannot unload a script-library plugin!\n");
        return;
    }
    */
    // Let plugin free its stuff.
    if (m_Initialized)
    {
        constexpr unsigned int hash = CRC32("OnPluginUnload");
        Event(hash);
        m_Initialized = false;
    }

    freeAllocatedMemory();
    removeCustomConsoleCommands();

    /*closeAllSockets();
    closeAllFiles();*/

    /*
    // Remove all server commands of the plugin
    for (i = 0; i < pluginFunctions.plugins[id].cmds; i++)
    {
        if (pluginFunctions.plugins[id].cmd[i].xcommand != NULL)
        {
            Com_DPrintf("Removing command \"%s\"...\n", pluginFunctions.plugins[id].cmd[i].name);
            Cmd_RemoveCommand(pluginFunctions.plugins[id].cmd[i].name);
        }
    }
    */
    // at end
    Sys_CloseLibrary(m_LibHandle);
    m_LibHandle = INVALID_LIB_HANDLE; // Prevent unloading from destructor.
}

void CPlugin::PrintPluginInfo() // const impossible because of "Event" call
{
    // We know, plugin has required events.
    SPluginInfo_t info;
    constexpr auto hash = CRC32("OnInfoRequest");
    Event(hash, &info);

    //Com_Printf("^2Plugin version:^7\n%d\n\n", ); // TODO: get back
    Com_Printf("^2Full plugin name:^7\n%s\n\n", info.fullName);
    Com_Printf("^2Short plugin description:^7\n%s\n\n", info.shortDescription);
    Com_Printf("^2Full plugin description:^7\n%s\n\n", info.longDescription);
    Com_Printf("^2Commands:^7 (total %d)\n\n", /*pluginFunctions.plugins[id].cmds*/ 0); // TODO
    /*
    for (i = 0; i < pluginFunctions.plugins[id].cmds; ++i)
        Com_Printf(" -%s\n", pluginFunctions.plugins[id].cmd[i].name);
    */
    Com_Printf("^2Script Functions:^7 (total %d)\n\n", /*pluginFunctions.plugins[id].scriptfunctions*/0);
    /*
    for (i = 0; i < pluginFunctions.plugins[id].scriptfunctions; ++i)
    {
        if (!pluginScriptCallStubs.s[id * MAX_SCRIPTFUNCTIONS + i].isMethod)
        {
            Com_Printf(" -%s\n", pluginScriptCallStubs.s[id * MAX_SCRIPTFUNCTIONS + i].name);
        }
    }
    */
    Com_Printf("^2Script Methods:^7 (total %d)\n\n", /*pluginFunctions.plugins[id].scriptmethods*/0); // TODO
    /*
    for (i = 0; i < pluginFunctions.plugins[id].scriptmethods; ++i)
    {
        if (pluginScriptCallStubs.s[id * MAX_SCRIPTFUNCTIONS + i].isMethod)
        {
            Com_Printf(" -%s\n", pluginScriptCallStubs.s[id * MAX_SCRIPTFUNCTIONS + i].name);
        }
    }
    */
}

bool CPlugin::IsInitialized() const
{
    return m_Initialized;
}

void CPlugin::SetInitialized(bool bInitialized_)
{
    m_Initialized = bInitialized_;
}

void CPlugin::SaveMemoryAddress(void* const Address_, const unsigned int Size_)
{
    if (m_mapMemAllocs.find(Address_) != m_mapMemAllocs.end())
    {
        assert(!"Self-check: Address already defined");
        return;
    }

    m_mapMemAllocs[Address_] = Size_;
}

void CPlugin::DeleteMemoryAddress(void* const Address_)
{
    if (m_mapMemAllocs.find(Address_) == m_mapMemAllocs.end())
    {
        assert(!"Self-check: Address not defined");
        return;
    }

    m_mapMemAllocs.erase(Address_);
}

void CPlugin::AddConsoleCommand(const char* const CmdName_, xfunction_t Callback_)
{
    if (GetPluginHandler()->IsCustomConsoleCommandExist(CmdName_))
    {
        assert(!"Command already exist");
        return;
    }
    
    if (!Callback_)
    {
        assert(Callback_ && "Can not add console command: callback is nullptr");
        return;
    }

    string cmdName = CmdName_;
    function<void()> cmdCallback = [this, Callback_]()
    {
        GetPluginHandler()->SetCurrentPlugin(this);
        Callback_();
        GetPluginHandler()->SetCurrentPlugin(nullptr);
    };

    m_mapConsoleCommands[cmdName] = cmdCallback;
}

bool CPlugin::IsConsoleCommandExist(const char* const CmdName_) const
{
    for (const auto& itCmd : m_mapConsoleCommands)
        if (itCmd.first == CmdName_)
            return true;

    return false;
}

void CPlugin::DeleteConsoleCommand(const char* const CmdName_)
{
    for (auto it = m_mapConsoleCommands.begin(), end = m_mapConsoleCommands.end(); it != end; ++it)
    {
        if (it->first == CmdName_)
        {
            m_mapConsoleCommands.erase(it);
            return;
        }
    }
    assert(!"Self-check: Command not exist in this plugin");
}

bool CPlugin::ExecuteConsoleCommand(const char* const CmdName_) const
{
    const auto& itCmd = m_mapConsoleCommands.find(string(CmdName_));
    if (itCmd == m_mapConsoleCommands.end())
        return false;
    
    // Execute command.
    itCmd->second();
    return true;
}

#if 0
void* CPlugin::Malloc(size_t Size_)
{
    /*if (!Size_) // Not an error, but worth mention.
    {
        Com_DPrintf("Attempt to allocate 0 bytes for plugin\n");
        return nullptr;
    }

    Com_DPrintf("Allocating %dB of memory for plugin...", Size_);
    void* mem = reinterpret_cast<void*>(malloc(Size_));
    if (!mem)
    {
        Com_DPrintf("failed: not enough memory\n");
        return nullptr;
    }
    m_MemStorage.push_back(mem);
    ++m_MemAllocs;
    m_AllocatedBytesCount += Size_;
    Com_DPrintf("done\n");
    return mem;*/
    return nullptr;
}

void CPlugin::Free(const void* Ptr_)
{
    /*if (!Ptr_)
    {
        Com_DPrintf("Attempt to free nullptr for plugin\n");
        return;
    }

    Com_DPrintf("Freeing plugin memory...");
    for (auto pMem : m_MemStorage) // pMem is void ptr so may use auto instead of auto&.
        if (pMem == Ptr_)
        {
            m_MemStorage.remove(pMem);
            free(pMem);
            Com_DPrintf("done\n");
            return;
        }
    Com_DPrintf("failed: unknown pointer");*/
}

void CPlugin::AddConsoleCommand(const char* const Name_, xcommand_t fpCallback_, int Power_ /*= 0*/)
{
    /*Com_DPrintf("Adding custom console command '%s' for plugin...", Name_);
    Cmd_AddPCommand(Name_, fpCallback_, Power_);
    m_CustomCmds.push_back(string(Name_));
    Com_DPrintf("done\n");*/
}

void CPlugin::RemoveConsoleCommand(const char* const Name_)
{
    /*Com_DPrintf("Removing custom console command '%s' from plugin...", Name_);
    string sName = Name_;*/
    /////////////////////////////////////////////
    // std::find issue.
    /*auto& itCmdName = std::find(m_CustomCmds.begin(), m_CustomCmds.end(), sName);
    if (itCmdName == m_CustomCmds.end())
    {
        Com_PrintError("Custom command '%s' not belongs to this plugin\n", Name_);
        return;
    }
    Cmd_RemoveCommand(Name_);
    m_CustomCmds.remove(itCmdName);
    */
    //////////////////////
    /*Com_DPrintf("done\n");*/
}

int CPlugin::TCP_Connect(const char* const Remote_, FPNetworkReceiveCallback ReceiveCallback_)
{
    /*Com_DPrintf("Opening new TCP connection to '%s'...", Remote_);

    int socket = NET_TcpClientConnect(Remote_);
    if (socket < 1)
    {
        Com_Printf("Failed to open TCP connection to server '%s'\n", Remote_);
        return SOCKET_ERROR;
    }
    SNetworkConnectionInfo info;
    info.ReceiveCallback = ReceiveCallback_;
    NET_StringToAdr(Remote_, &info.Remote, NA_UNSPEC);
    m_Sockets[socket] = info;

    Com_DPrintf("done\n");
    return socket;*/
    return 0;
}

unsigned int CPlugin::TCP_Send(const int Connection_, const void* const Data_, const unsigned int Size_) const
{
    /*if (!Data_ || !Size_)
    {
        Com_PrintError("Attempting to send NULL buffer\n");
        return SOCKET_ERROR;
    }

    if (m_Sockets.find(Connection_) == m_Sockets.end())
    {
        Com_PrintError("Unknown plugin socket\n");
        return SOCKET_ERROR;
    }

    char errMsg[256] = {'\0'};
    int sent = NET_TcpSendData(Connection_, Data_, Size_, errMsg, sizeof(errMsg));

    if (sent == NET_WANT_WRITE)
        return 0;

    if (sent == SOCKET_ERROR)
        Com_PrintError("Failed to send data to a TCP socket: %s\n", errMsg);

    return sent; // Count of sent bytes or SOCKET_ERROR.*/
    return 0;
}

unsigned int CPlugin::TCP_Receive(const int Connection_, void* const Buffer_, unsigned int Size_) const
{
    /*if (!Buffer_)
    {
        Com_PrintError("Output buffer must not be NULL\n");
        return SOCKET_ERROR;
    }

    if (!Size_) // Unknown buffer size. Nowhere to read to. Not an error but dev's mistake.
    {
        Com_PrintWarning("Zero length buffer size passed\n");
        return 0;
    }
    
    if (m_Sockets.find(Connection_) == m_Sockets.end())
    {
        Com_PrintError("Unknown socket for plugin\n");
        return SOCKET_ERROR;
    }
    
    char errormsg[256] = {'\0'};
    len = NET_TcpClientGetData(Connection_, Buffer_, Size_, errormsg, sizeof(errormsg));

    if (len == NET_WANT_READ)
        return 0;

    if (len == SOCKET_ERROR) // Something went wrong.
        Com_PrintError("Failed to receive data from TCP socket: %s\n", errormsg);
    
    return len; // Count of received bytes or SOCKET_ERROR*/
    return 0;
}

void CPlugin::TCP_Close(const int Connection_)
{
    /*Com_DPrintf("Closing TCP socket...");
    if (m_Sockets.find(Connection_) == m_Sockets.end())
    {
        Com_PrintWarning("Failed to close unknown connection socket\n");
        return;
    }

    NET_TcpCloseSocket(Connection_);
    m_Sockets.erase(Connection_);
    Com_DPrintf("done\n");*/
}

fileHandle_t CPlugin::FS_FOpen(const char* const FileName_, EFileLocation Location_, EFileOpenMode Mode_)
{
    /*fileHandle_t hFile = 0;
    if (Location_ == FL_Game)
    {
        switch(Mode_)
        {
            case FOM_Read:
                FS_FOpenFileRead(FileName_, &hFile);
                break;
            case FOM_Write:
                hFile = FS_FOpenFileWrite(FileName_);
                break;
            case FOM_Append:
                hFile = FS_FOpenFileAppend(FileName_);
                break;
            default: break;
        }
    }
    else if (Location_ == FL_Server)
    {
        switch(Mode_)
        {
            case FOM_Read:
                FS_SV_FOpenFileRead(FileName_, &hFile);
                break;
            case FOM_Write:
                hFile = FS_SV_FOpenFileWrite(FileName_);
                break;
            case FOM_Append:
                hFile = FS_SV_FOpenFileAppend(FileName_);
                break;
            default: break;
        }
    }
    // File was not opened.
    if (hFile == 0)
        return 0;

    m_Files.push_back(hFile);
    return hFile;*/
    return 0;
}

void CPlugin::FS_FClose(const fileHandle_t hFile_)
{
    /*Com_DPrintf("Closing previously opened file %d...", hFile_);
    bool found = false;
    for (auto itHFile = m_Files.begin(); itHFile != m_Files.end(); ++itHFile)
    {
        if (*itHFile == hFile)
        {
            m_Files.erase(itHFile);
            found = true;
            break;
        }
    }
    if (!found)
    {
        Com_PrintError("File %d not belongs to this plugin.\n", hFile_);
        return;
    }

    if (FS_FCloseFile(hFile_) != qtrue)
        Com_PrintError("Error closing file %d\n", hFile_);

    Com_DPrintf("done\n");*/
}
#endif

void CPlugin::freeAllocatedMemory()
{
    assert(!m_mapMemAllocs.size() && "Plugin-check: not all memory allocations was freed by plugin");

    for (const auto& itAddress : m_mapMemAllocs)
        free(reinterpret_cast<void*>(itAddress.first));

    m_mapMemAllocs.clear();
}

void CPlugin::removeCustomConsoleCommands()
{
    if (!m_mapConsoleCommands.size())
        return;

    assert(!"You forgot to remove custom console commands added by your plugin");
    m_mapConsoleCommands.clear();
}

#if 0
void CPlugin::closeAllSockets()
{
    /*for (auto& it : m_Sockets)
        NET_TcpCloseSocket(it.first);
    m_Sockets.clear();*/
}

void CPlugin::closeAllFiles()
{
    /*for (auto& it : m_Files)
        FS_FCloseFile(it);
    m_Files.clear();*/
}
#endif

} // end of namespace phandler
