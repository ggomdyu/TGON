#include "PrecompiledHeader.pch"
#include "../Debug.h"

#include <cstdio>
#include <cstdarg>
#include <memory>

namespace tgon
{
namespace platform
{

TGON_API void Log(const char* formatStr, ...)
{
#if (_DEBUG) || (DEBUG)
    constexpr const std::size_t strBufferSize = 1024 * 10;
    thread_local static const std::unique_ptr<char[]> strBuffer(new char[strBufferSize] {});

    va_list vaList;
    va_start(vaList, formatStr);
    vsprintf(strBuffer.get(), formatStr, vaList);

    printf(strBuffer.get());
#endif
}

} /* namespace platform */
} /* namespace tgon */
