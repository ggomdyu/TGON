/**
 * @file    TimeZoneInfo.h
 * @author  ggomdyu
 * @since   07/22/2019
 * @warn    TimeZoneInfo doesn't consider time conversion with Daylight Saving Time currently!!
 */

#pragma once
#include <string>

#include "Platform/Config.h"

#include "DateTime.h"

namespace tgon
{

class TGON_API TimeZoneInfo final
{
/**@section Constructor */
public:
    template <typename _StringType1, typename _StringType2, typename _StringType3, typename _StringType4>
    TimeZoneInfo(_StringType1&& id, const TimeSpan& baseUtcOffset, _StringType2&& displayName, _StringType3&& standardDisplayName, _StringType4&& daylightDisplayName, bool supportsDaylightSavingTime);
    TimeZoneInfo() = default;

/**@section Method */
public:
    static const TimeZoneInfo& Local();
    static const TimeZoneInfo& Utc();
    static DateTime ConvertTime(const DateTime& dateTime, const TimeZoneInfo& destinationTimeZone);
    static DateTime ConvertTimeFromUtc(const DateTime& dateTime, const TimeZoneInfo& destinationTimeZone);
    static DateTime ConvertTimeToUtc(const DateTime& dateTime);
    const std::string& GetId() const noexcept;
    const TimeSpan& GetBaseUtcOffset() const noexcept;
    const std::string& GetStandardDisplayName() const noexcept;
    const std::string& GetDaylightDisplayName() const noexcept;
    bool IsSupportDaylightSavingTime() const noexcept;
    
private:
    static DateTimeKind GetCorrespondingKind(const TimeZoneInfo& timeZone);
    static DateTime ConvertTime(const DateTime& dateTime, const TimeZoneInfo& sourceTimeZone, const TimeZoneInfo& destinationTimeZone);

/**@section Variable */
private:
    std::string m_id;
    TimeSpan m_baseUtcOffset;
    std::string m_displayName;
    std::string m_standardDisplayName;
    std::string m_daylightDisplayName;
    bool m_supportsDaylightSavingTime = false;
};

template <typename _StringType1, typename _StringType2, typename _StringType3, typename _StringType4>
inline TimeZoneInfo::TimeZoneInfo(_StringType1&& id, const TimeSpan& baseUtcOffset, _StringType2&& displayName, _StringType3&& standardDisplayName, _StringType4&& daylightDisplayName, bool supportsDaylightSavingTime) :
    m_id(std::forward<std::string>(id)),
    m_baseUtcOffset(baseUtcOffset),
    m_displayName(std::forward<std::string>(displayName)),
    m_standardDisplayName(std::forward<std::string>(standardDisplayName)),
    m_daylightDisplayName(std::forward<std::string>(daylightDisplayName)),
    m_supportsDaylightSavingTime(supportsDaylightSavingTime)
{
}

inline const TimeZoneInfo& TimeZoneInfo::Utc()
{
    static auto timeZoneInfo = []()
    {
        std::string id = "UTC";
        return TimeZoneInfo(id, TimeSpan(0), id, id, id, false);
    } ();
    return timeZoneInfo;
}

inline DateTime TimeZoneInfo::ConvertTime(const DateTime& dateTime, const TimeZoneInfo& destinationTimeZone)
{
    if (dateTime.GetKind() == DateTimeKind::Utc)
    {
        return ConvertTime(dateTime, Utc(), destinationTimeZone);
    }

    return ConvertTime(dateTime, Local(), destinationTimeZone);
}

inline DateTime TimeZoneInfo::ConvertTimeFromUtc(const DateTime& dateTime, const TimeZoneInfo& destinationTimeZone)
{
    return ConvertTime(dateTime, TimeZoneInfo::Utc(), destinationTimeZone);
}

inline DateTime TimeZoneInfo::ConvertTimeToUtc(const DateTime& dateTime)
{
    return ConvertTime(dateTime, TimeZoneInfo::Local(), TimeZoneInfo::Utc());
}

inline const std::string& TimeZoneInfo::GetId() const noexcept
{
    return m_id;
}

inline const TimeSpan& TimeZoneInfo::GetBaseUtcOffset() const noexcept
{
    return m_baseUtcOffset;
}

inline const std::string& TimeZoneInfo::GetStandardDisplayName() const noexcept
{
    return m_standardDisplayName;
}

inline const std::string& TimeZoneInfo::GetDaylightDisplayName() const noexcept
{
    return m_daylightDisplayName;
}

inline bool TimeZoneInfo::IsSupportDaylightSavingTime() const noexcept
{
    return m_supportsDaylightSavingTime;
}

inline DateTimeKind TimeZoneInfo::GetCorrespondingKind(const TimeZoneInfo& timeZone)
{
    if (&timeZone == &Utc())
    {
        return DateTimeKind::Utc;
    }

    if (&timeZone == &Local())
    {
        return DateTimeKind::Local;
    }
    
    return DateTimeKind::Unspecified;
}

inline DateTime TimeZoneInfo::ConvertTime(const DateTime& dateTime, const TimeZoneInfo& sourceTimeZone, const TimeZoneInfo& destinationTimeZone)
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

} /* namespace tgon */
