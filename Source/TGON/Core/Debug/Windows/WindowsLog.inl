#include <Windows.h>
#include <cstdarg>
#include <mutex>

#include "Core/String/Encoding.h"

namespace tgon
{

template <>
inline void Log<LogLevel::Debug>(const char* formatStr, ...)
{
    static std::mutex g_mutex;
    
    std::lock_guard<std::mutex> lockGuard(g_mutex);
    {
        constexpr const std::size_t strBufferSize = 1024 * 10;
        static std::unique_ptr<char[]> utf8StrBuffer(new char[strBufferSize] {});
        static std::unique_ptr<wchar_t[]> utf16StrBuffer(new wchar_t[strBufferSize] {});

        va_list vaList;
        va_start(vaList, formatStr);
        int utf8StrLen = vsprintf_s(utf8StrBuffer.get(), strBufferSize, formatStr, vaList);

        bool isConvertSucceed = UTF8::Convert<UTF16LE>(utf8StrBuffer.get(), utf8StrLen, reinterpret_cast<char*>(&utf16StrBuffer[0]), strBufferSize);
        if (isConvertSucceed)
        {
            OutputDebugStringW(utf16StrBuffer.get());
        }
    }
}

template <>
inline void Log<LogLevel::Warning>(const char* formatStr, ...)
{
    static std::mutex g_mutex;
    
    std::lock_guard<std::mutex> lockGuard(g_mutex);
    {
        constexpr const std::size_t strBufferSize = 1024 * 10;
        static std::unique_ptr<char[]> utf8StrBuffer(new char[strBufferSize] {});
        static std::unique_ptr<wchar_t[]> utf16StrBuffer(new wchar_t[strBufferSize] {});

        va_list vaList;
        va_start(vaList, formatStr);
        int utf8StrLen = vsprintf_s(utf8StrBuffer.get(), strBufferSize, formatStr, vaList);

        bool isConvertSucceed = UTF8::Convert<UTF16LE>(utf8StrBuffer.get(), utf8StrLen, reinterpret_cast<char*>(&utf16StrBuffer[0]), strBufferSize);
        if (isConvertSucceed)
        {        
            MessageBoxW(nullptr, utf16StrBuffer.get(), L"", MB_OK);
        }
    }
}

} /* namespace tgon */