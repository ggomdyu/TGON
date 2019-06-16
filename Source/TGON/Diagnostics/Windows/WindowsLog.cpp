#include "PrecompiledHeader.h"

#include <Windows.h>
#include <cstdarg>
#include <mutex>
#include <iostream>

#include "Core/Algorithm.h"
#include "String/Encoding.h"
#include "String/StringTraits.h"

#include "../Log.h"

namespace tgon
{
namespace
{

#if defined(_DEBUG) || !defined(NDEBUG)
constexpr std::size_t g_strBufferLen = 1024 * 8;
std::unique_ptr<char[]> g_utf8StrBuffer(new char[g_strBufferLen] {});
std::unique_ptr<wchar_t[]> g_utf16StrBuffer(new wchar_t[g_strBufferLen] {});
std::mutex g_mutex;
#endif

} /* namespace */

void Log(LogLevel logLevel, const char* formatStr, ...)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    std::lock_guard<std::mutex> lockGuard(g_mutex);

    va_list vaList;
    va_start(vaList, formatStr);
    int utf8StrLen = vsprintf_s(g_utf8StrBuffer.get(), g_strBufferLen, formatStr, vaList);
        
    bool isConvertSucceed = UTF8::ConvertTo<UTF16LE>(std::string_view(g_utf8StrBuffer.get(), utf8StrLen), g_utf16StrBuffer.get(), g_strBufferLen) != -1;
    if (isConvertSucceed)
    {
        if (logLevel == LogLevel::Debug)
        {
            OutputDebugStringW(g_utf16StrBuffer.get());
        }
        else if (logLevel == LogLevel::Warning)
        {
            MessageBoxW(nullptr, g_utf16StrBuffer.get(), L"", MB_OK);
        }
    }
#endif
}

} /* namespace tgon */
