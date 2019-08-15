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

}

TimeZoneInfo::TimeZoneInfo(const std::string& id, const TimeSpan& baseUtcOffset, const std::string& displayName, const std::string& standardDisplayName, const std::string& daylightDisplayName, bool supportsDaylightSavingTime) :
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

DateTime TimeZoneInfo::ConvertTime(const DateTime& dateTime, const TimeZoneInfo& destinationTimeZone)
{
    if (dateTime.GetKind() == DateTimeKind::Utc)
    {
        return ConvertTime(dateTime, Utc(), destinationTimeZone);
    }
    else
    {
        return ConvertTime(dateTime, Local(), destinationTimeZone);
    }
}

DateTime TimeZoneInfo::ConvertTimeFromUtc(const DateTime& dateTime, const TimeZoneInfo& destinationTimeZone)
{
    return ConvertTime(dateTime, TimeZoneInfo::Utc(), destinationTimeZone);
}

DateTime TimeZoneInfo::ConvertTimeToUtc(const DateTime& dateTime)
{
    return ConvertTime(dateTime, TimeZoneInfo::Local(), TimeZoneInfo::Utc());
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

DateTimeKind TimeZoneInfo::GetCorrespondingKind(const TimeZoneInfo& timeZone)
{
    if (&timeZone == &Utc())
    {
        return DateTimeKind::Utc;
    }
    else if (&timeZone == &Local())
    {
        return DateTimeKind::Local;
    }
    
    return DateTimeKind::Unspecified;
}

DateTime TimeZoneInfo::ConvertTime(const DateTime& dateTime, const TimeZoneInfo& sourceTimeZone, const TimeZoneInfo& destinationTimeZone)
{
    // The kind of dateTime and sourceTimeZone must be the same.
    DateTimeKind sourceKind = GetCorrespondingKind(sourceTimeZone);
    if (dateTime.GetKind() != sourceKind)
    {
        return dateTime;
    }

    // Filter the special case like UTC->UTC or Local->Local
    DateTimeKind destinationKind = GetCorrespondingKind(destinationTimeZone);
    if (sourceKind != DateTimeKind::Unspecified && destinationKind != DateTimeKind::Unspecified && sourceKind == destinationKind)
    {
        return dateTime;
    }

    // Convert the dateTime utc offset to 0.
    int64_t ticks = dateTime.GetTicks() - sourceTimeZone.GetBaseUtcOffset().GetTicks();

    if (destinationKind == DateTimeKind::Local)
    {
        return DateTime(ticks + destinationTimeZone.GetBaseUtcOffset().GetTicks(), DateTimeKind::Local);
    }
    else
    {
        return DateTime(ticks, destinationKind);
    }
}

}
