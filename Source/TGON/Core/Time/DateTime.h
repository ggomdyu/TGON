/**
 * @file    DateTime.h
 * @author  ggomdyu
 * @since   04/23/2017
 */

#pragma once
#include <cstdint>
#include <ctime>

#include "DateTimeType.h"

namespace tgon
{

class DateTime
{
/* @section Private constructor */
private:
    constexpr explicit DateTime(const std::tm& rawTime) noexcept;

/* @section Public method */
public:
    static DateTime Now() noexcept;
    static DateTime UtcNow() noexcept;
    static bool IsLeapYear(int32_t year) noexcept;
    static int32_t DaysInMonth(int year, int month) noexcept;
    
    void AddDays(float days);

    uint16_t GetMonth() const;
    uint16_t GetDay() const;
    uint16_t GetYear() const;
    uint16_t GetHour() const;
    uint16_t GetMinute() const;
    uint16_t GetSecond() const;
    DayOfWeek GetDayOfWeek() const;

/* @section Public variable */
private:
    uint16_t m_month;
    uint16_t m_day;
    uint16_t m_year;
    uint16_t m_hour;
    uint16_t m_minute;
    uint16_t m_second;
    DayOfWeek m_dayOfWeek;
};

constexpr DateTime::DateTime(const std::tm& rawTime) noexcept :
    m_month(static_cast<uint16_t>(rawTime.tm_mon + 1)),
    m_day(static_cast<uint16_t>(rawTime.tm_mday)),
    m_year(static_cast<uint16_t>(1900 + rawTime.tm_year)),
    m_hour(static_cast<uint16_t>(rawTime.tm_hour)),
    m_minute(static_cast<uint16_t>(rawTime.tm_min)),
    m_second(static_cast<uint16_t>(rawTime.tm_sec)),
    m_dayOfWeek(static_cast<DayOfWeek>(rawTime.tm_wday))
{
}

inline uint16_t DateTime::GetMonth() const
{
    return m_month;
}

inline uint16_t DateTime::GetDay() const
{
    return m_day;
}

inline uint16_t DateTime::GetYear() const
{
    return m_year;
}

inline uint16_t DateTime::GetHour() const
{
    return m_hour;
}

inline uint16_t DateTime::GetMinute() const
{
    return m_minute;
}

inline uint16_t DateTime::GetSecond() const
{
    return m_second;
}

inline DayOfWeek DateTime::GetDayOfWeek() const
{
    return m_dayOfWeek;
}

} /* namespace tgon */
