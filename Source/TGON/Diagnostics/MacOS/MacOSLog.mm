#include "PrecompiledHeader.h"

#include <string>
#include <cstdarg>
#include <mutex>
#include <AppKit/NSAlert.h>

#include "Misc/Algorithm.h"
#include "String/StringTraits.h"

#include "../Log.h"

namespace tgon
{
namespace
{

#if defined(_DEBUG) || !defined(NDEBUG)
std::mutex g_mutex;
#endif

} /* namespace */

TGON_API void Log(LogLevel logLevel, const char* formatStr, va_list vaList)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    if (formatStr == nullptr || formatStr[0] == '\0')
    {
        return;
    }

    thread_local static std::unique_ptr<char[]> strBuffer(new char[1024 * 8] {});
    
    vsprintf(strBuffer.get(), formatStr, vaList);
    
    std::lock_guard<std::mutex> lockGuard(g_mutex);

    if (logLevel == LogLevel::Debug)
    {
        NSLog(@"%s", strBuffer.get());
    }
    else if (logLevel == LogLevel::Warning)
    {
        NSAlert *alert = [[NSAlert alloc] init];
        [alert setMessageText:@""];
        [alert setInformativeText:[NSString stringWithUTF8String:strBuffer.get()]];
        [alert setAlertStyle:NSAlertStyleCritical];
        [alert runModal];
    }
#endif
}
    
TGON_API void Log(LogLevel logLevel, const char* formatStr, ...)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    std::va_list vaList;
    va_start(vaList, formatStr);
    Log(logLevel, formatStr, vaList);
#endif
}

void Assert(bool condition)
{
#if defined(_DEBUG) || ! defined(NDEBUG)
    if (condition == false)
    {
        Log(LogLevel::Warning, "Assertion Failed!");
        std::abort();
    }
#endif
}

void Assert(bool condition, const char* formatStr, ...)
{
#if defined(_DEBUG) || ! defined(NDEBUG)
    if (condition == false)
    {
        if (formatStr == nullptr || formatStr[0] == '\0')
        {
            Assert(condition);
            return;
        }

        thread_local static std::string formatStr2;
        formatStr2 = "Assertion Failed: ";
        formatStr2 += formatStr;
        
        std::va_list vaList;
        va_start(vaList, formatStr);
        Log(LogLevel::Warning, formatStr2.c_str(), vaList);

        std::abort();
    }
#endif
}

} /* namespace tgon */
