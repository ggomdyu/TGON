#include "PrecompiledHeader.h"
#include "GenericTime.h"

#include <chrono>
#include <ctime>

namespace tgon
{
namespace platform
{
namespace
{

const uint32_t g_oldOSExecutionTime = GetOSExecutionTime();
const uint64_t g_oldOSExecutionTime64 = GetOSExecutionTime64();

} /* namespace */

TGON_API uint32_t GetProcessExecutionTime()
{
    return GetOSExecutionTime() - g_oldOSExecutionTime;
}

TGON_API uint64_t GetProcessExecutionTime64()
{
    return GetOSExecutionTime64() - g_oldOSExecutionTime64;
}

TGON_API UnixTimeTy GetUnixTime()
{
    return static_cast<UnixTimeTy>(std::time(nullptr));
}

} /* namespace platform */
} /* namespace tgon */
