#include "PrecompiledHeader.pch"

#include "../Log.h"

#include <Windows.h>
#include <cstdarg>
#include <memory>
#include <mutex>

namespace tgon
{
namespace core
{
namespace
{

std::mutex g_mutex;

} /* namespace */

TGON_API void Log(const char* formatStr, ...)
{
#ifdef _DEBUG
    std::lock_guard<std::mutex> lockGuard(g_mutex);

    constexpr const std::size_t strBufferSize = 1024 * 10;
    static const std::unique_ptr<char[]> strBuffer(new char[strBufferSize] {});

    va_list vaList;
    va_start(vaList, formatStr);
    vsprintf_s(strBuffer.get(), strBufferSize, formatStr, vaList);

    OutputDebugStringA(strBuffer.get());
#endif
}

} /* namespace core */
} /* namespace tgon */