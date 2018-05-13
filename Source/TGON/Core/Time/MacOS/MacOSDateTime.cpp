#include "PrecompiledHeader.pch"

#include <ctime>

#include "../DateTime.h"

namespace tgon
{

DateTime DateTime::Now() noexcept
{
    std::time_t unixTime = std::time(nullptr);

    std::tm rawLocalTime;
    gmtime_r(&unixTime, &rawLocalTime);
    localtime_r(&unixTime, &rawLocalTime);

    return DateTime(rawLocalTime);
}

DateTime DateTime::UtcNow() noexcept
{
    std::time_t unixTime = std::time(nullptr);

    std::tm rawUtcTime;
    gmtime_r(&unixTime, &rawUtcTime);

    return DateTime(rawUtcTime);
}

} /* namespace tgon */