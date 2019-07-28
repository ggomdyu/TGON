#include "PrecompiledHeader.h"

#include "TimeZoneInfo.h"

namespace tgon
{
namespace
{

TimeZoneInfo CreateUtc()
{
    std::string id = "UTC";
    return TimeZoneInfo(id, TimeSpan(0), id, id, id, false);
}

} /* namespace */

TimeZoneInfo::TimeZoneInfo(const std::string& id, TimeSpan baseUtcOffset, const std::string& displayName, const std::string& standardDisplayName, const std::string& daylightDisplayName, bool supportsDaylightSavingTime) :
    m_id(id),
    m_baseUtcOffset(baseUtcOffset),
    m_displayName(displayName),
    m_standardDisplayName(standardDisplayName),
    m_daylightDisplayName(daylightDisplayName),
    m_supportsDaylightSavingTime(supportsDaylightSavingTime)
{
}

const TimeZoneInfo& TimeZoneInfo::Utc()
{
    static auto timeZoneInfo = CreateUtc();
    return timeZoneInfo;
}

DateTime TimeZoneInfo::ConvertTimeFromUtc(const DateTime& dateTime, const TimeZoneInfo& destinationTimeZone)
{
    if (dateTime.GetKind() == DateTimeKind::Local)
    {
        return dateTime;
    }
    else
    {
        return dateTime + destinationTimeZone.GetBaseUtcOffset();
    }
}

DateTime TimeZoneInfo::ConvertTimeToUtc(const DateTime& dateTime)
{
    if (dateTime.GetKind() == DateTimeKind::Utc)
    {
        return dateTime;
    }
    else
    {
        return dateTime - TimeZoneInfo::Local().GetBaseUtcOffset();
    }
}

const std::string& TimeZoneInfo::GetId() const noexcept
{
    return m_id;
}

const TimeSpan& TimeZoneInfo::GetBaseUtcOffset() const noexcept
{
    return m_baseUtcOffset;
}

const std::string& TimeZoneInfo::GetStandardDisplayName() const noexcept
{
    return m_standardDisplayName;
}

const std::string& TimeZoneInfo::GetDaylightDisplayName() const noexcept
{
    return m_daylightDisplayName;
}

bool TimeZoneInfo::IsSupportDaylightSavingTime() const noexcept
{
    return m_supportsDaylightSavingTime;
}

} /* namespace tgon */
