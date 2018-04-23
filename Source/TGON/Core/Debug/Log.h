/**
 * @filename    Log.h
 * @author      ggomdyu
 * @since       04/01/2016
 * @brief       Supports plaform-agnostic logger.
 */

#pragma once
#include <cstdarg>

#include "Core/Platform/Config.h"

namespace tgon
{

enum class LogLevel
{
    Debug,
    Warning,
};

namespace detail
{

template <LogLevel _LogLevel>
inline void Log(const char* formatStr, va_list vaList);

} /* namespace detail */

template <LogLevel _LogLevel = LogLevel::Debug>
inline void Log(const char* formatStr, ...)
{
    static std::mutex g_mutex;

    std::lock_guard<std::mutex> lockGuard(g_mutex);
    {
        va_list vaList;
        va_start(vaList, formatStr);
        detail::Log<_LogLevel>(formatStr, vaList);
    }
}

} /* namespace tgon */

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsLog.inl"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSLog.inl"
#endif
