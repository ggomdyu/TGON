#include "PrecompiledHeader.h"

#include <ctime>

#include "../DateTime.h"

namespace tgon
{

DateTime DateTime::Now() noexcept
{
    std::time_t unixTime = std::time(nullptr);
    
    std::tm rawLocalTime;
    gmtime_s(&rawLocalTime, &unixTime);
    localtime_s(&rawLocalTime, &unixTime);
        
    return DateTime(rawLocalTime);
}

DateTime DateTime::UtcNow() noexcept
{
    std::time_t unixTime = std::time(nullptr);
    
    std::tm rawUtcTime;
    gmtime_s(&rawUtcTime, &unixTime);
    
    return DateTime(rawUtcTime);
}

} /* namespace tgon */