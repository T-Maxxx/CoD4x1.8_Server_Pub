///////////////////////////////////////////////////////////////////////////////
// phandler.h/cpp - Plugin handler C++ -> C bridge.
//      Allows you to call plugin handler C++ code from C code.
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "macro.hpp"

BEGIN_EXTERN_C
#include <core/q_shared_types.h>

CDECL void PHandler_Init();
CDECL void PHandler_Shutdown();
CDECL qboolean PHandler_ExecuteConsoleCommand(const char* const CmdName_);
END_EXTERN_C
