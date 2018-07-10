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

    int32_t GetMonth() const noexcept;
    int32_t GetDay() const noexcept;
    int32_t GetYear() const noexcept;
    int32_t GetHour() const noexcept;
    int32_t GetMinute() const noexcept;
    int32_t GetSecond() const noexcept;
    DayOfWeek GetDayOfWeek() const;

/* @section Public variable */
private:
    int32_t m_month;
    int32_t m_day;
    int32_t m_year;
    int32_t m_hour;
    int32_t m_minute;
    int32_t m_second;
    DayOfWeek m_dayOfWeek;
};

} /* namespace tgon */
