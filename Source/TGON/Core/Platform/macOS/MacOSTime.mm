#include "PrecompiledHeader.pch"
#include "MacOSTime.h"

#include <mach/mach_time.h>
#include <ctime>

namespace tgon
{
namespace platform
{

TGON_API uint64_t GetOSExecutionTime()
{
    return mach_absolute_time() * 0.000001f;
}

TGON_API DateTime GetSystemTime()
{
    std::time_t unixTime = std::time(nullptr);

    std::tm rawUtcTime;
    gmtime_r(&unixTime, &rawUtcTime);

    return DateTime(rawUtcTime);
}

TGON_API DateTime GetLocalTime()
{
    std::time_t unixTime = std::time(nullptr);

    std::tm rawLocalTime;
    gmtime_r(&unixTime, &rawLocalTime);
    localtime_r(&unixTime, &rawLocalTime);

    return DateTime(rawLocalTime);
}

} /* namespace platform */
} /* namespace tgon */
