#import "PrecompiledHeader.h"

#import "TimeZoneInfo.h"

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

TimeZoneInfo::TimeZoneInfo(const std::string& id, TimeSpan baseUtcOffset, const std::string& displayName, const std::string& standardDisplayName, const std::string& daylightDisplayName, bool isSupportDaylightSaveingTime) :
    m_id(id),
    m_baseUtcOffset(baseUtcOffset),
    m_displayName(displayName),
    m_standardDisplayName(standardDisplayName),
    m_daylightDisplayName(daylightDisplayName),
    m_isSupportDaylightSaveingTime(isSupportDaylightSaveingTime)
{
}

const TimeZoneInfo& TimeZoneInfo::Utc()
{
    static auto timeZoneInfo = CreateUtc();
    return TimeZoneInfo;
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

bool TimeZoneInfo::IsSupportDaylightSaveingTime() const noexcept
{
    return m_isSupportDaylightSaveingTime;
}

} /* namespace tgon */
