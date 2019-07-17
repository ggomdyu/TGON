/**
 * @file    DateTime.h
 * @author  ggomdyu
 * @since   04/23/2017
 * @seealso https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
 */

#pragma once
#include <cstdint>
#include <ctime>
#include <stdexcept>

#include "Platform/Config.h"

#include "DateTimeType.h"
#include "TimeSpan.h"

namespace tgon
{

class TGON_API DateTime final
{
/**@section Constructor */
public:
    constexpr DateTime(int32_t year, int32_t month, int32_t day) noexcept;
    constexpr DateTime(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second) noexcept;
    constexpr DateTime(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, DateTimeKind dateTimeKind) noexcept;
    constexpr DateTime(const TimeSpan& timeSpan) noexcept;

/**@section Operator */
public:

/**@section Method */
public:
    static DateTime Now();
    static DateTime UtcNow();
    static DateTime Today();
    static constexpr bool IsLeapYear(int32_t year) noexcept;
    static constexpr int32_t DaysInMonth(int32_t year, int32_t month) noexcept;
    void AddDays(int days);
    void AddDays(float days);
    constexpr int32_t GetMonth() const noexcept;
    constexpr int32_t GetDay() const noexcept;
    constexpr int32_t GetYear() const noexcept;
    constexpr int32_t GetHour() const noexcept;
    constexpr int32_t GetMinute() const noexcept;
    constexpr int32_t GetSecond() const noexcept;
    constexpr DayOfWeek GetDayOfWeek() const noexcept;
    static constexpr DayOfWeek GetDayOfWeek(int32_t year, int32_t month, int32_t day);
    constexpr int32_t GetDayOfYear() const noexcept;
    constexpr DateTimeKind GetDateTimeKind() const noexcept;
    //static DateTime GetMaxValue();
    //static DateTime GetMinValue();
    //static constexpr DateTime GetUnixEpoch(); -> 1970.1.1

private:
    static constexpr int64_t DateToTicks(int32_t year, int32_t month, int32_t day) noexcept;
    static constexpr int64_t TimeToTicks(int32_t hour, int32_t minute, int32_t second) noexcept;
    constexpr int32_t GetDatePart(int32_t part) const noexcept;

/**@section Variable */
public:
    static constexpr int64_t TicksPerMillisecond = 10000;
    static constexpr int64_t TicksPerSecond = TicksPerMillisecond * 1000;
    static constexpr int64_t TicksPerMinute = TicksPerSecond * 60;
    static constexpr int64_t TicksPerHour = TicksPerMinute * 60;
    static constexpr int64_t TicksPerDay = TicksPerHour * 24;

private:
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
    //DateTimeKind m_dateTimeKind;
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
    m_ticks(DateToTicks(year, month, day) + TimeToTicks(hour, minute, second))
{
}

constexpr DateTime::DateTime(const TimeSpan& timeSpan) noexcept :
    m_ticks(timeSpan.GetTicks())
{
}

constexpr bool DateTime::IsLeapYear(int32_t year) noexcept
{
    return (year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0));
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

constexpr int32_t DateTime::GetDatePart(int32_t part) const noexcept
{
    int64_t n = m_ticks / TicksPerDay;
    int y400 = n / DaysPer400Years;
    n -= y400 * DaysPer400Years;
    
    int y100 = n / DaysPer100Years;
    if ( y100 == 4 )
    {
        y100 = 3;
    }
    n -= y100 * DaysPer100Years;
    
    int y4 = n / DaysPer4Years;
    n -= y4 * DaysPer4Years;
    int y1 = n / DaysPerYear;
    if ( y1 == 4 )
    {
        y1 = 3;
    }
    
    if ( part == DatePartYear ) {
        return y400 * 400 + y100 * 100 + y4 * 4 + y1 + 1;
    }
    
    n -= y1 * DaysPerYear;
    if ( part == DatePartDayOfYear )
    {
        return n + 1;
    }
    
    bool isLeapYear = y1 == 3 && ( y4 != 24 || y100 == 3 );
    const int* days = isLeapYear ? DaysToMonth366 : DaysToMonth365;
    int m = (n >> 5) + 1;
    while ( n >= days[m] )
    {
        ++m;
    }
    if ( part == DatePartMonth )
    {
        return m;
    }
    
    return n - days[m - 1] + 1;
}

constexpr int32_t DateTime::GetHour() const noexcept
{
    return (m_ticks / TicksPerHour) % 24;
}

constexpr int32_t DateTime::GetMinute() const noexcept
{
    return (m_ticks / TicksPerMinute) % 60;
}

constexpr int32_t DateTime::GetSecond() const noexcept
{
    return (m_ticks / TicksPerSecond) % 60;
}

constexpr DayOfWeek DateTime::GetDayOfWeek() const noexcept
{
    return DayOfWeek((m_ticks / TicksPerDay + 1) % 7);
}

constexpr DayOfWeek DateTime::GetDayOfWeek(int32_t year, int32_t month, int32_t day)
{
    constexpr int32_t termTable[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

    year -= month < 3;
    
    return DayOfWeek((year + year / 4 - year / 100 + year / 400 + termTable[month - 1] + day) % 7);
}

constexpr int32_t DateTime::GetDayOfYear() const noexcept
{
    // todo: impl
    return -1;
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

constexpr int32_t DateTime::DaysInMonth(int32_t year, int32_t month) noexcept
{
    // todo: test
    if (month == 2)
    {
        return IsLeapYear(year) ? DaysToMonth366[month] - DaysToMonth366[month - 1] : DaysToMonth365[month] - DaysToMonth365[month - 1];
    }
    else
    {
        return DaysToMonth365[month] - DaysToMonth365[month - 1];
    }
}

} /* namespace tgon */
