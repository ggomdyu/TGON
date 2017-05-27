#include "PrecompiledHeader.h"
#include "WindowsTime.h"

#ifndef NOMINMAX
#   define NOMINMAX
#endif
#include <Windows.h>

namespace tgon {
namespace platform {

uint32_t GetOSExecutionTime()
{
    return GetTickCount();
}

uint64_t GetOSExecutionTime64()
{
    return GetTickCount64();
}

} /* namespace platform */
} /* namespace tgon */