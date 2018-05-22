#include "PrecompiledHeader.h"

#include "../Log.h"

#include <string>
#include <cstdarg>
#include <mutex>
#include <AppKit/NSAlert.h>

namespace tgon
{
namespace
{

#if defined(_DEBUG) || !defined(NDEBUG)
std::mutex g_mutex;
#endif

} /* namespace */

TGON_API void Log(LogLevel logLevel, const char* formatStr, ...)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    std::lock_guard<std::mutex> lockGuard(g_mutex);

    va_list vaList;
    va_start(vaList, formatStr);
    
    vprintf(formatStr, vaList);
    

//    if (logLevel == LogLevel::Warning)
//    {
//        
//    }
//    else
//    {
//        NSAlert *alert = [[NSAlert alloc] init];
//        [alert setMessageText:[NSString stringWithUTF8String:title]];
//        [alert setInformativeText:[NSString stringWithUTF8String:message]];
//        [alert setAlertStyle:nativeNSAlertStyleArray[static_cast<int32_t>(iconType)]];
//        [alert runModal];
//    }
#endif
}

} /* namespace tgon */
