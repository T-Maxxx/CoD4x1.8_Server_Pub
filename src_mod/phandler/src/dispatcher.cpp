#include "dispatcher.hpp"
#include "macro.hpp"
#include <compiletime/ctcrc32.hpp>
#include "PluginHandler.hpp"
#include <cstring>

BEGIN_EXTERN_C
#include <core/qcommon_io.h>
#include <core/qcommon_mem.h>
#include <core/server.h>
#include <core/cmd.h>
END_EXTERN_C

using namespace phandler;

#define VARG(num, type) ((type)(((int*)&CodeHash_)[1 + num]))

void SysCallDispatcher(const unsigned int CodeHash_, ...)
{
    switch(CodeHash_)
    {
        case CRC32("Com_Printf"):
        {
            Com_Printf(VARG(0, const char*));
            break;
        }

        case CRC32("Com_Error"):
        {
            Com_Error(0, VARG(0, const char*));
            break;
        }

        case CRC32("Com_PrintError"):
        {
            Com_PrintError(VARG(0, const char*));
            break;
        }

        case CRC32("Com_DPrintf"):
        {
            Com_DPrintf(VARG(0, const char*));
            break;
        }

        case CRC32("Com_PrintWarning"):
        {
            Com_PrintWarning(VARG(0, const char*));
            break;
        }

        case CRC32("Cbuf_AddText"):
        {
            Cbuf_AddText(VARG(0, const char*));
            break;
        }

        case CRC32("SV_SetConfigString"):
        {
            SV_SetConfigstring(VARG(0, int), VARG(1, const char*));
            break;
        }

        case CRC32("SV_GetConfigString"):
        {
            SV_GetConfigstring(VARG(0, int), VARG(1, char*), VARG(2, int));
            break;
        }

        case CRC32("SV_GetStat"):
        {
            int* result = VARG(2, int*);
            *result = SV_GetClientStat(VARG(0, int), VARG(1, int));
            break;
        }

        case CRC32("SV_SetStat"):
        {
            SV_SetClientStat(VARG(0, int), VARG(1, int), VARG(2, int));
            break;
        }

        case CRC32("MemAlloc"):
        {
            int iSize = VARG(0, int);
            void** ppAddress = VARG(1, void**);
            *ppAddress = Z_Malloc(iSize);
            if (*ppAddress)
                GetPluginHandler()->CurrentPlugin()->SaveMemoryAddress(*ppAddress, iSize);

            break;
        }

        case CRC32("MemFree"):
        {
            void* pAddress = VARG(0, void*);
            Z_Free(pAddress);
            if (pAddress)
                GetPluginHandler()->CurrentPlugin()->DeleteMemoryAddress(pAddress);

            break;
        }

        case CRC32("Cmd_Argc"):
        {
            int* pArgc = VARG(0, int*);
            *pArgc = Cmd_Argc();
            break;
        }

        case CRC32("Cmd_Argv"):
        {
            const char** pChar = VARG(1, const char**);
            *pChar = Cmd_Argv(VARG(0, int));
            break;
        }

        case CRC32("Cmd_Args"):
        {
            Cmd_Args(VARG(0, char*), VARG(1, int));
            break;
        }

        case CRC32("Cmd_AddCommand"):
        {
            GetPluginHandler()->CurrentPlugin()->AddConsoleCommand(VARG(0, const char*), VARG(1, xfunction_t));
            break;
        }
        
        case CRC32("Cmd_RemoveCommand"):
        {
            GetPluginHandler()->CurrentPlugin()->DeleteConsoleCommand(VARG(0, const char*));
            break;
        }

        case CRC32("Cvar_Get_String"):
        {
            const char* const cvarName = VARG(0, const char* const);
            char* const buffer = VARG(1, char* const);
            unsigned int size = VARG(2, unsigned int);
            buffer[0] = '\0';
            strcat_s(buffer, size, Cvar_GetVariantString(cvarName));
            break;
        }

        case CRC32("Cvar_Get_Int"):
        {
            const char* const cvarName = VARG(0, const char* const);
            int* value = VARG(1, int*);
            *value = Cvar_GetInt(cvarName);
            break;
        }

        case CRC32("Cvar_Get_Bool"):
        {
            const char* const cvarName = VARG(0, const char* const);
            qboolean* value = VARG(1, qboolean*);
            *value = Cvar_GetBool(cvarName);
            break;
        }

        case CRC32("Cvar_Get_Float"):
        {
            const char* const cvarName = VARG(0, const char* const);
            float* value = VARG(1, float*);
            *value = Cvar_GetFloat(cvarName);
            break;
        }

        case CRC32("Cvar_Set_String"):
        {
            const char* const cvarName = VARG(0, const char* const);
            const char* const value = VARG(1, const char* const);
            Cvar_Set(cvarName, value);
            break;
        }

        case CRC32("Cvar_Set_Int"):
        {
            const char* const cvarName = VARG(0, const char* const);
            int value = VARG(1, int);
            Cvar_SetIntByName(cvarName, value);
            break;
        }

        case CRC32("Cvar_Set_Bool"):
        {
            const char* const cvarName = VARG(0, const char* const);
            qboolean value = VARG(1, qboolean);
            Cvar_SetBoolByName(cvarName, value);
            break;
        }

        case CRC32("Cvar_Set_Float"):
        {
            const char* const cvarName = VARG(0, const char* const);
            float* value = VARG(1, float*);
            Cvar_SetFloatByName(cvarName, *value);
            break;
        }

        default: 
            Com_Error(0, "Unknown system call hash: 0x%X", CodeHash_);
    }
}