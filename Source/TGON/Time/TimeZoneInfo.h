/**
 * @file    TimeZoneInfo.h
 * @author  ggomdyu
 * @since   07/22/2019
 */

#pragma once
#include <string>

#include "Platform/Config.h"

#include "DateTime.h"
#include "TimeSpan.h"

namespace tgon
{

class TGON_API TimeZoneInfo final
{
/**@section Constructor */
public:
    TimeZoneInfo(const std::string& id, TimeSpan baseUtcOffset, const std::string& displayName, const std::string& standardDisplayName, const std::string& daylightDisplayName, bool isSupportDaylightSaveingTime);
    
/**@section Method */
public:
    static const TimeZoneInfo& Local();
    static const TimeZoneInfo& Utc();
    static DateTime ConvertTimeFromUtc(const DateTime& dateTime, const TimeZoneInfo& destinationTimeZone);
    static DateTime ConvertTimeToUtc(const DateTime& dateTime);
    const std::string& GetId() const noexcept;
    const TimeSpan& GetBaseUtcOffset() const noexcept;
    const std::string& GetStandardDisplayName() const noexcept;
    const std::string& GetDaylightDisplayName() const noexcept;
    bool IsSupportDaylightSaveingTime() const noexcept;
    
/**@section Variable */
private:
    std::string m_id;
    TimeSpan m_baseUtcOffset;
    std::string m_displayName;
    std::string m_standardDisplayName;
    std::string m_daylightDisplayName;
    bool m_isSupportDaylightSaveingTime;
};

} /* namespace tgon */
