#include "PrecompiledHeader.pch"

#include "../Debug.h"

#include <Windows.h>
#include <cstdarg>
#include <memory>

namespace tgon
{
namespace platform
{

TGON_API void Log(const char* formatStr, ...)
{
#ifdef _DEBUG
    constexpr const std::size_t strBufferSize = 1024 * 10;
    thread_local static const std::unique_ptr<char[]> strBuffer(new char[strBufferSize] {});

    va_list vaList;
    va_start(vaList, formatStr);
    vsprintf_s(strBuffer.get(), strBufferSize, formatStr, vaList);

    OutputDebugStringA(strBuffer.get());
#endif
}

} /* namespace platform */
} /* namespace tgon */