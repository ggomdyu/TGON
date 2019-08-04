#import "PrecompiledHeader.h"

#import <string>
#import <cstdarg>
#import <mutex>
#import <AppKit/NSAlert.h>

#import "Misc/Algorithm.h"
#import "String/StringTraits.h"

#import "../Log.h"

namespace tgon
{
namespace
{

#if defined(_DEBUG) || !defined(NDEBUG)
thread_local std::unique_ptr<char[]> g_strBuffer(new char[1024 * 8] {});
std::mutex g_mutex;
#endif

} /* namespace */

TGON_API void Debug::Log(LogLevel logLevel, const char* formatStr, va_list vaList)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    if (formatStr == nullptr || formatStr[0] == '\0')
    {
        return;
    }

    vsprintf(g_strBuffer.get(), formatStr, vaList);
	
    std::lock_guard<std::mutex> lockGuard(g_mutex);
    
    if (logLevel == LogLevel::Debug)
    {
        NSLog(@"%s", g_strBuffer.get());
    }
    else if (logLevel == LogLevel::Warning)
    {
        NSAlert *alert = [[NSAlert alloc] init];
        [alert setMessageText:@""];
        [alert setInformativeText:[NSString stringWithUTF8String:g_strBuffer.get()]];
        [alert setAlertStyle:NSAlertStyleCritical];
        [alert runModal];
    }
#endif
}
   
} /* namespace tgon */
