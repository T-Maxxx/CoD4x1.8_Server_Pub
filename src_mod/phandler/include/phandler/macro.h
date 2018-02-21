#pragma once

#undef BEGIN_EXTERN_C
#undef END_EXTERN_C
#ifdef __cplusplus
    #define BEGIN_EXTERN_C extern "C" {
    #define END_EXTERN_C }
#else
    #define BEGIN_EXTERN_C
    #define END_EXTERN_C
#endif

#ifndef FUNCTION_NAME
#ifdef WIN32   //WINDOWS
#define FUNCTION_NAME (__FUNCTION__)
#else          //*NIX
#define FUNCTION_NAME (__func__)
#endif
#endif

#define THREAD_UNSAFE_RET(retVal) \
do { \
    if (Sys_IsMainThread() == qfalse) \
    { \
        Com_PrintError("Attempting to execute non thread safe function '%s'\n", FUNCTION_NAME); \
        return retVal; \
    } \
} while(0)

#define THREAD_UNSAFE() THREAD_UNSAFE_RET(;)

#define DURING_EVENT_ONLY_RET(retVal) \
    do { \
        if (!m_CurrentPlugin) \
        { \
            Com_PrintError("Attempt to call function '%s' outside of plugin event\n", FUNCTION_NAME); \
            return retVal; \
        } \
    } while(0)

#define DURING_EVENT_ONLY() DURING_EVENT_ONLY_RET(;)

#define NO_COPY_CLASS(className) \
    public: \
    className(const className&) = delete; \
    void operator=(const className&) = delete

#ifdef WIN32
#define CDECL __cdecl
#else
#define CDECL __attribute__((__cdecl__))
#endif