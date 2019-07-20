/**
 * @file    DateTime.h
 * @author  ggomdyu
 * @since   04/23/2017
 * @seealso https://referencesource.microsoft.com/#mscorlib/system/datetime.cs
            https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
 */

#pragma once
#include <cstdint>
#include <chrono>
#include <ctime>
#include <tuple>

#include "TimeSpan.h"
#include "DateTimeType.h"

namespace tgon
{

class DateTime final
{
/**@section Constructor */
public:
    constexpr DateTime(int32_t year, int32_t month, int32_t day) noexcept;
    constexpr DateTime(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second) noexcept;
    constexpr DateTime(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, DateTimeKind dateTimeKind) noexcept;
    constexpr DateTime(int64_t ticks) noexcept;
    constexpr DateTime(int64_t ticks, DateTimeKind dateTimeKind) noexcept;

/**@section Operator */
public:
    constexpr DateTime operator+(const DateTime& rhs) const noexcept;
    constexpr DateTime operator-(const DateTime& rhs) const noexcept;
    constexpr TimeSpan operator-(const TimeSpan& rhs) const noexcept;
    constexpr bool operator==(const DateTime& rhs) const noexcept;
    constexpr bool operator!=(const DateTime& rhs) const noexcept;
    constexpr bool operator>(const DateTime& rhs) const noexcept;
    constexpr bool operator>=(const DateTime& rhs) const noexcept;
    constexpr bool operator<(const DateTime& rhs) const noexcept;
    constexpr bool operator<=(const DateTime& rhs) const noexcept;

/**@section Method */
public:
    static constexpr int Compare(const DateTime& lhs, const DateTime& rhs) noexcept;
    constexpr int CompareTo(const DateTime& value) const noexcept;
    static DateTime Now();
    static DateTime UtcNow();
    static DateTime Today();
    static constexpr bool IsLeapYear(int32_t year) noexcept;
    static constexpr int32_t DaysInMonth(int32_t year, int32_t month) noexcept;
    constexpr DateTime AddYears(int32_t value) noexcept;
    constexpr DateTime AddMonths(int32_t value) noexcept;
    constexpr DateTime AddDays(double value) noexcept;
    constexpr DateTime AddHours(double value) noexcept;
    constexpr int32_t GetYear() const noexcept;
    constexpr int32_t GetMonth() const noexcept;
    constexpr int32_t GetDay() const noexcept;
    constexpr int32_t GetHour() const noexcept;
    constexpr int32_t GetMinute() const noexcept;
    constexpr int32_t GetSecond() const noexcept;
    constexpr int64_t GetTicks() const noexcept;
    constexpr DateTime GetDate() const noexcept;
    constexpr DayOfWeek GetDayOfWeek() const noexcept;
    static constexpr DayOfWeek GetDayOfWeek(int32_t year, int32_t month, int32_t day);
    constexpr int32_t GetDayOfYear() const noexcept;
    constexpr DateTimeKind GetKind() const noexcept;
    static constexpr DateTime GetMaxValue() noexcept;
    static constexpr DateTime GetMinValue() noexcept;
    static constexpr DateTime GetUnixEpoch() noexcept;

private:
    static constexpr int64_t DateToTicks(int32_t year, int32_t month, int32_t day) noexcept;
    static constexpr int64_t TimeToTicks(int32_t hour, int32_t minute, int32_t second) noexcept;
    constexpr int32_t GetDatePart(int32_t part) const noexcept;
    constexpr std::tuple<int32_t, int32_t, int32_t> GetDateParts() const noexcept;
    static int64_t GetTimeSinceUnixEpoch();

/**@section Variable */
public:
    static constexpr int64_t TicksPerMillisecond = 10000;
    static constexpr int64_t TicksPerSecond = TicksPerMillisecond * 1000;
    static constexpr int64_t TicksPerMinute = TicksPerSecond * 60;
    static constexpr int64_t TicksPerHour = TicksPerMinute * 60;
    static constexpr int64_t TicksPerDay = TicksPerHour * 24;

private:
    static constexpr int64_t TicksMask = 0x3FFFFFFFFFFFFFFF;
    static constexpr int64_t KindUnspecified = 0x0000000000000000;
    static constexpr int64_t KindUtc = 0x4000000000000000;
    static constexpr int64_t KindLocal = 0x8000000000000000;
    static constexpr int64_t KindShift = 62;
    static constexpr int32_t DaysToMonth365[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    static constexpr int32_t DaysToMonth366[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};
    static constexpr int32_t DatePartYear = 0;
    static constexpr int32_t DatePartDayOfYear = 1;
    static constexpr int32_t DatePartMonth = 2;
    static constexpr int32_t DatePartDay = 3;
    static constexpr int32_t DaysPerYear = 365;
    static constexpr int32_t DaysPer4Years = DaysPerYear * 4 + 1;
    static constexpr int32_t DaysPer100Years = DaysPer4Years * 25 - 1;
    static constexpr int32_t DaysPer400Years = DaysPer100Years * 4 + 1;
    static constexpr int32_t DaysTo1601 = DaysPer400Years * 4;
    static constexpr int32_t DaysTo1899 = DaysPer400Years * 4 + DaysPer100Years * 3 - 367;
    static constexpr int32_t DaysTo1970 = DaysPer400Years * 4 + DaysPer100Years * 3 + DaysPer4Years * 17 + DaysPerYear;
    static constexpr int32_t DaysTo10000 = DaysPer400Years * 25 - 366;

    int64_t m_ticks;
};

constexpr DateTime::DateTime(int32_t year, int32_t month, int32_t day) noexcept :
    DateTime(year, month, day, 0, 0, 0)
{
}

constexpr DateTime::DateTime(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second) noexcept :
    DateTime(year, month, day, hour, minute, second, DateTimeKind::Unspecified)
{
}

constexpr DateTime::DateTime(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, DateTimeKind dateTimeKind) noexcept :
    DateTime(DateToTicks(year, month, day) + TimeToTicks(hour, minute, second), dateTimeKind)
{
}

constexpr DateTime::DateTime(int64_t ticks) noexcept :
    m_ticks(ticks)
{
}

constexpr DateTime::DateTime(int64_t ticks, DateTimeKind dateTimeKind) noexcept :
    m_ticks(ticks | (static_cast<int64_t>(dateTimeKind) << DateTime::KindShift))
{
}

constexpr DateTime DateTime::operator+(const DateTime& rhs) const noexcept
{
    return DateTime(this->GetTicks() + rhs.GetTicks(), this->GetKind());
}

constexpr DateTime DateTime::operator-(const DateTime& rhs) const noexcept
{
    return DateTime(this->GetTicks() - rhs.GetTicks(), this->GetKind());
}

constexpr TimeSpan DateTime::operator-(const TimeSpan& rhs) const noexcept
{
    return TimeSpan(this->GetTicks() - rhs.GetTicks());
}

constexpr bool DateTime::operator==(const DateTime& rhs) const noexcept
{
    return this->GetTicks() == rhs.GetTicks();
}

constexpr bool DateTime::operator!=(const DateTime& rhs) const noexcept
{
    return this->GetTicks() != rhs.GetTicks();
}

constexpr bool DateTime::operator>(const DateTime& rhs) const noexcept
{
    return this->GetTicks() > rhs.GetTicks();
}

constexpr bool DateTime::operator>=(const DateTime& rhs) const noexcept
{
    return this->GetTicks() >= rhs.GetTicks();
}

constexpr bool DateTime::operator<(const DateTime& rhs) const noexcept
{
    return this->GetTicks() < rhs.GetTicks();
}

constexpr bool DateTime::operator<=(const DateTime& rhs) const noexcept
{
    return this->GetTicks() <= rhs.GetTicks();
}

constexpr int DateTime::Compare(const DateTime& lhs, const DateTime& rhs) noexcept
{
    return lhs.CompareTo(rhs);
}

constexpr int DateTime::CompareTo(const DateTime& value) const noexcept
{
    if (this->GetTicks() > value.GetTicks())
    {
        return 1;
    }
    else if (this->GetTicks() < value.GetTicks())
    {
        return -1;
    }

    return 0;
}

inline DateTime DateTime::Now()
{
    time_t utcTime = 0;
    time(&utcTime);

#ifdef _MSC_VER
    tm localTimeInfo {};
    gmtime_s(&localTimeInfo, &utcTime);
    
    time_t localTime = mktime(&localTimeInfo);
    int64_t utcOffset = static_cast<int64_t>((difftime(utcTime, localTime) / 3600.0) * TicksPerHour);
#else
    const tm* localTimeInfo = localtime(&utcTime);
    int64_t utcOffset = localTimeInfo->tm_gmtoff / 3600
#endif
    
    return DateTime(GetUnixEpoch().GetTicks() + GetTimeSinceUnixEpoch() + utcOffset, DateTimeKind::Local);
}

inline DateTime DateTime::UtcNow()
{
    return DateTime(GetUnixEpoch().GetTicks() + GetTimeSinceUnixEpoch(), DateTimeKind::Local);
}

inline DateTime DateTime::Today()
{
    return Now().GetDate();
}

constexpr bool DateTime::IsLeapYear(int32_t year) noexcept
{
    return (year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0));
}

constexpr int32_t DateTime::DaysInMonth(int32_t year, int32_t month) noexcept
{
    if (month == 2)
    {
        return IsLeapYear(year) ? DaysToMonth366[month] - DaysToMonth366[month - 1] : DaysToMonth365[month] - DaysToMonth365[month - 1];
    }
    else
    {
        return DaysToMonth365[month] - DaysToMonth365[month - 1];
    }
}

constexpr DateTime DateTime::AddYears(int32_t value) noexcept
{
    return this->AddMonths(value * 12);
}

constexpr DateTime DateTime::AddMonths(int32_t value) noexcept
{
    auto dateParts = GetDateParts();

    int32_t year = std::get<0>(dateParts);
    int32_t month = std::get<1>(dateParts) + value;
    int32_t day = std::get<2>(dateParts);

    if (month > 12)
    {
        int32_t y = (month - 1) / 12;
        year += y;
        month -= (y * 12);
    }

    return DateTime(DateToTicks(year, month, day) + (this->GetTicks() % TicksPerDay), this->GetKind());
}

constexpr DateTime DateTime::AddDays(double value) noexcept
{
    return DateTime(this->GetTicks() + static_cast<int64_t>(value * TicksPerDay), this->GetKind());
}

constexpr DateTime DateTime::AddHours(double value) noexcept
{
    return DateTime(this->GetTicks() + static_cast<int64_t>(value * TicksPerHour), this->GetKind());
}

constexpr int32_t DateTime::GetYear() const noexcept
{
    return this->GetDatePart(DatePartYear);
}

constexpr int32_t DateTime::GetMonth() const noexcept
{
    return this->GetDatePart(DatePartMonth);
}

constexpr int32_t DateTime::GetDay() const noexcept
{
    return this->GetDatePart(DatePartDay);
}

constexpr int32_t DateTime::GetHour() const noexcept
{
    return (this->GetTicks() / TicksPerHour) % 24;
}

constexpr int32_t DateTime::GetMinute() const noexcept
{
    return (this->GetTicks() / TicksPerMinute) % 60;
}

constexpr int32_t DateTime::GetSecond() const noexcept
{
    return (this->GetTicks() / TicksPerSecond) % 60;
}

constexpr int64_t DateTime::GetTicks() const noexcept
{
    return m_ticks & TicksMask;
}

constexpr DateTime DateTime::GetDate() const noexcept
{
    auto ticks = this->GetTicks();
    return DateTime(ticks - (ticks % TicksPerDay), this->GetKind());
}

constexpr DayOfWeek DateTime::GetDayOfWeek() const noexcept
{
    return DayOfWeek((this->GetTicks() / TicksPerDay + 1) % 7);
}

constexpr DayOfWeek DateTime::GetDayOfWeek(int32_t year, int32_t month, int32_t day)
{
    constexpr int32_t termTable[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

    year -= month < 3;
    
    return DayOfWeek((year + year / 4 - year / 100 + year / 400 + termTable[month - 1] + day) % 7);
}

constexpr int32_t DateTime::GetDayOfYear() const noexcept
{
    return GetDatePart(DatePartDayOfYear);
}

constexpr DateTimeKind DateTime::GetKind() const noexcept
{
    return static_cast<DateTimeKind>(m_ticks >> KindShift);
}

constexpr DateTime DateTime::GetMaxValue() noexcept
{
    return DateTime(DaysTo10000 * TicksPerDay - 1);
}

constexpr DateTime DateTime::GetMinValue() noexcept
{
    return DateTime(0);
}

constexpr DateTime DateTime::GetUnixEpoch() noexcept
{
    return DateTime(1970, 1, 1);
}

constexpr int64_t DateTime::DateToTicks(int32_t year, int32_t month, int32_t day) noexcept
{
    if (1 <= month && month <= 12)
    {
        const int* daysToMonth = IsLeapYear(year) ? DaysToMonth366 : DaysToMonth365;
        if (1 <= day && day <= daysToMonth[month])
        {
            int y = year - 1;
            int n = y * 365 + y / 4 - y / 100 + y / 400 + daysToMonth[month - 1] + day - 1;
            return n * TicksPerDay;
        }
    }

    return 0;
}

constexpr int64_t DateTime::TimeToTicks(int32_t hour, int32_t minute, int32_t second) noexcept
{
    int64_t totalSeconds = (static_cast<int64_t>(hour) * 3600) + (static_cast<int64_t>(minute) * 60) + static_cast<int64_t>(second);
    return totalSeconds * TicksPerSecond;
}

constexpr int32_t DateTime::GetDatePart(int32_t part) const noexcept
{
    int64_t n = this->GetTicks() / TicksPerDay;
    int64_t y400 = n / DaysPer400Years;
    n -= y400 * DaysPer400Years;
    
    int64_t y100 = n / DaysPer100Years;
    if (y100 == 4)
    {
        y100 = 3;
    }
    n -= y100 * DaysPer100Years;
    
    int64_t y4 = n / DaysPer4Years;
    n -= y4 * DaysPer4Years;
    int64_t y1 = n / DaysPerYear;
    if (y1 == 4)
    {
        y1 = 3;
    }
    
    if (part == DatePartYear)
    {
        return static_cast<int32_t>(y400 * 400 + y100 * 100 + y4 * 4 + y1 + 1);
    }
    
    n -= y1 * DaysPerYear;
    if (part == DatePartDayOfYear)
    {
        return static_cast<int32_t>(n + 1);
    }
    
    bool isLeapYear = y1 == 3 && (y4 != 24 || y100 == 3);
    const int* days = isLeapYear ? DaysToMonth366 : DaysToMonth365;
    int64_t m = (n >> 5) + 1;
    while (n >= days[m])
    {
        ++m;
    }
    if (part == DatePartMonth)
    {
        return static_cast<int32_t>(m);
    }
    
    return static_cast<int32_t>(n - days[m - 1] + 1);
}

constexpr std::tuple<int32_t, int32_t, int32_t> DateTime::GetDateParts() const noexcept
{
    int64_t n = this->GetTicks() / TicksPerDay;
    int64_t y400 = n / DaysPer400Years;
    n -= y400 * DaysPer400Years;
    
    int64_t y100 = n / DaysPer100Years;
    if (y100 == 4)
    {
        y100 = 3;
    }
    n -= y100 * DaysPer100Years;
    
    int64_t y4 = n / DaysPer4Years;
    n -= y4 * DaysPer4Years;
    int64_t y1 = n / DaysPerYear;
    if (y1 == 4)
    {
        y1 = 3;
    }
    
    int32_t year = static_cast<int32_t>(y400 * 400 + y100 * 100 + y4 * 4 + y1 + 1);
    
    n -= y1 * DaysPerYear;
    
    bool isLeapYear = y1 == 3 && (y4 != 24 || y100 == 3);
    const int* days = isLeapYear ? DaysToMonth366 : DaysToMonth365;
    int64_t m = (n >> 5) + 1;
    while (n >= days[m])
    {
        ++m;
    }
    
    int32_t month = static_cast<int32_t>(m);
    int32_t day = static_cast<int32_t>(n - days[m - 1] + 1);
    
    return {year, month, day};
}

inline int64_t DateTime::GetTimeSinceUnixEpoch()
{
    auto timeSinceEpoch = std::chrono::system_clock::now().time_since_epoch();
    
    using DurationType = decltype(timeSinceEpoch);
    if constexpr(DurationType::period::den == 10000000)
    {
        return timeSinceEpoch.count();
    }
    else
    {
        auto castedTimeSinceEpoch = std::chrono::duration_cast<std::chrono::duration<int64_t, std::ratio<1, 10000000>>>(timeSinceEpoch);
        return castedTimeSinceEpoch.count();
    }
}

} /* namespace tgon */
