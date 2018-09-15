/**
 * @file    DateTime.h
 * @author  ggomdyu
 * @since   04/23/2017
 * @seealso https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
 */

#pragma once
#include <cstdint>
#include <ctime>

#include "Core/Platform/Config.h"

#include "DateTimeType.h"

namespace tgon
{

class TGON_API DateTime final
{
/**@section Public constructor */
public:
    constexpr DateTime(const std::tm& rawTime, DateTimeKind dateTimeKind) noexcept;
    constexpr DateTime(int32_t year, int32_t month, int32_t day);
    constexpr DateTime(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second);

/**@section Private constructor */
private:
    constexpr DateTime(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, DayOfWeek dayOfWeek, DateTimeKind dateTimeKind) noexcept;

/**@section Public method */
public:
    static DateTime Now();
    static DateTime UtcNow();
    static DateTime Today();
    static constexpr bool IsLeapYear(int32_t year) noexcept;
    static constexpr int32_t DaysInMonth(int32_t year, int32_t month);
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

/**@section Public variable */
private:
    int32_t m_month;
    int32_t m_day;
    int32_t m_year;
    int32_t m_hour;
    int32_t m_minute;
    int32_t m_second;
    DayOfWeek m_dayOfWeek;
    DateTimeKind m_dateTimeKind;
};

constexpr DateTime::DateTime(const std::tm& rawTime, DateTimeKind dateTimeKind) noexcept :
    DateTime(
        static_cast<int32_t>(1900 + rawTime.tm_year),
        static_cast<int32_t>(rawTime.tm_mon + 1),
        static_cast<int32_t>(rawTime.tm_mday),
        static_cast<int32_t>(rawTime.tm_hour),
        static_cast<int32_t>(rawTime.tm_min),
        static_cast<int32_t>(rawTime.tm_sec),
        static_cast<DayOfWeek>(rawTime.tm_wday),
        dateTimeKind
    )
{
}

constexpr DateTime::DateTime(int32_t year, int32_t month, int32_t day) :
    DateTime(year, month, day, 0, 0, 0)
{
}

constexpr DateTime::DateTime(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second) :
    DateTime(year, month, day, hour, minute, second, DateTime::GetDayOfWeek(year, month, day), DateTimeKind::Unspecified)
{
}

constexpr DateTime::DateTime(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, DayOfWeek dayOfWeek, DateTimeKind dateTimeKind) noexcept :
    m_year(year),
    m_month(month),
    m_day(day),
    m_hour(hour),
    m_minute(minute),
    m_second(second),
    m_dayOfWeek(dayOfWeek),
    m_dateTimeKind(dateTimeKind)
{
}

constexpr bool DateTime::IsLeapYear(int32_t year) noexcept
{
    return (year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0));
}

constexpr int32_t DateTime::GetMonth() const noexcept
{
    return m_month;
}

constexpr int32_t DateTime::GetDay() const noexcept
{
    return m_day;
}

constexpr int32_t DateTime::GetYear() const noexcept
{
    return m_year;
}

constexpr int32_t DateTime::GetHour() const noexcept
{
    return m_hour;
}

constexpr int32_t DateTime::GetMinute() const noexcept
{
    return m_minute;
}

constexpr int32_t DateTime::GetSecond() const noexcept
{
    return m_second;
}

constexpr DayOfWeek DateTime::GetDayOfWeek() const noexcept
{
    return m_dayOfWeek;
}

constexpr DayOfWeek DateTime::GetDayOfWeek(int32_t year, int32_t month, int32_t day)
{
    constexpr int32_t termTable[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

    year -= month < 3;
    
    return DayOfWeek((year + year / 4 - year / 100 + year / 400 + termTable[month - 1] + day) % 7);
}

constexpr int32_t DateTime::GetDayOfYear() const noexcept
{
    int32_t dayOfYear = 0;

    for (int month = 1; month < m_month; ++month)
    {
        dayOfYear += DateTime::DaysInMonth(m_year, month);
    }

    return dayOfYear + m_day;
}

constexpr DateTimeKind DateTime::GetDateTimeKind() const noexcept
{
    return m_dateTimeKind;
}

constexpr int32_t DateTime::DaysInMonth(int32_t year, int32_t month)
{
    constexpr int32_t daysInMonthTable[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2)
    {
        return IsLeapYear(year) ? daysInMonthTable[month] + 1 : daysInMonthTable[month];
    }
    else
    {
        return daysInMonthTable[month];
    }
}

} /* namespace tgon */
