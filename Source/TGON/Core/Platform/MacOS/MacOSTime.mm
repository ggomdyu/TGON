#include "PrecompiledHeader.pch"
#include "../Time.h"
#include "../TimeType.h"

#include <mach/mach_time.h>
#include <ctime>

namespace tgon
{
namespace core
{

TGON_API int64_t GetTickCount()
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

} /* namespace core */
} /* namespace tgon */
