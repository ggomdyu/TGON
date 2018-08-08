#include "PrecompiledHeader.h"

#include "../DateTime.h"

namespace tgon
{

DateTime DateTime::Now()
{
    std::time_t unixTimestamp = std::time(nullptr);
    
    std::tm rawLocalTime;
    gmtime_s(&rawLocalTime, &unixTimestamp);
    localtime_s(&rawLocalTime, &unixTimestamp);
        
    return DateTime(rawLocalTime, DateTimeKind::Local);
}

DateTime DateTime::UtcNow()
{
    std::time_t unixTimestamp = std::time(nullptr);
    
    std::tm rawUtcTime;
    gmtime_s(&rawUtcTime, &unixTimestamp);
    
    return DateTime(rawUtcTime, DateTimeKind::Utc);
}

void DateTime::AddDays(float days)
{
    tm tempRawTime{};
    {
        tempRawTime.tm_year = m_year - 1900;
        tempRawTime.tm_mday = m_day + days;
        tempRawTime.tm_mon = m_month - 1;
        tempRawTime.tm_hour = m_hour;
        tempRawTime.tm_min = m_minute;
        tempRawTime.tm_sec = m_second + (86400.0f * (days - (int)days));
    }

    std::time_t unixTimestamp = mktime(&tempRawTime);

    std::tm newRawTime;
    gmtime_s(&newRawTime, &unixTimestamp);

    if (m_dateTimeKind != DateTimeKind::Utc)
    {
        localtime_s(&newRawTime, &unixTimestamp);
    }

    *this = DateTime(newRawTime, m_dateTimeKind);
}

} /* namespace tgon */