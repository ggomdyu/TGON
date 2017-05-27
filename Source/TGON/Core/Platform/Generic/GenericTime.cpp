#include "PrecompiledHeader.h"
#include "GenericTime.h"

#include <chrono>
#include <ctime>

namespace tgon {
namespace platform {
namespace {

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

TGON_API DateTime GetSystemTime()
{
    std::time_t unixTime = std::time(nullptr);

    std::tm rawUtcTime;
    gmtime_s(&rawUtcTime, &unixTime);

    return DateTime(rawUtcTime);
}

TGON_API DateTime GetLocalTime()
{
    std::time_t unixTime = std::time(nullptr);

    std::tm rawLocalTime;
    gmtime_s(&rawLocalTime, &unixTime);
    localtime_s(&rawLocalTime, &unixTime);

    return DateTime(rawLocalTime);
}

} /* namespace platform */
} /* namespace tgon */