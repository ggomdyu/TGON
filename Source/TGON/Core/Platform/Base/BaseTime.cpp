#include "PrecompiledHeader.pch"
#include "BaseTime.h"

#include <ctime>
#include <chrono>

namespace tgon
{
namespace platform
{
namespace
{

const uint32_t g_oldOSExecutionTime = GetOSExecutionTime();

} /* namespace */

TGON_API uint32_t GetProcessExecutionTime()
{
    return GetOSExecutionTime() - g_oldOSExecutionTime;
}

TGON_API time_t GetUnixTime()
{
    return static_cast<time_t>(std::time(nullptr));
}

} /* namespace platform */
} /* namespace tgon */
