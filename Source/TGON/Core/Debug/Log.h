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

template <LogLevel _LogLevel = LogLevel::Debug>
inline void Log(const char* formatStr, ...)
{
    this->Log(formatStr);
}

} /* namespace tgon */

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsLog.inl"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSLog.inl"
#endif