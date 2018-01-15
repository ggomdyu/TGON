#include "PrecompiledHeader.pch"

#include "../Log.h"

#include <string>
#include <cstdarg>
#include <mutex>

namespace tgon
{
namespace core
{
namespace
{

#ifndef NDEBUG
std::mutex g_mutex;
#endif

} /* namespace */

TGON_API void Log(const char* formatStr, ...)
{
#ifndef NDEBUG
    std::lock_guard<std::mutex> lockGuard(g_mutex);

    va_list vaList;
    va_start(vaList, formatStr);

    vprintf(formatStr, vaList);
#endif
}

} /* namespace core */
} /* namespace tgon */
