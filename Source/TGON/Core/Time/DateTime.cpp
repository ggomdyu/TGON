#include "PrecompiledHeader.h"

#include <ctime>
#include <array>

#include "../DateTime.h"

namespace tgon
{

constexpr DateTime::DateTime(const std::tm& rawTime) noexcept :
    m_month(static_cast<int32_t>(rawTime.tm_mon + 1)),
    m_day(static_cast<int32_t>(rawTime.tm_mday)),
    m_year(static_cast<int32_t>(1900 + rawTime.tm_year)),
    m_hour(static_cast<int32_t>(rawTime.tm_hour)),
    m_minute(static_cast<int32_t>(rawTime.tm_min)),
    m_second(static_cast<int32_t>(rawTime.tm_sec)),
    m_dayOfWeek(static_cast<DayOfWeek>(rawTime.tm_wday))
{
}

bool DateTime::IsLeapYear(int32_t year) noexcept
{
    return (year % 400 == 0) || (year % 100 == 0) || (year % 4 == 0);
}

int32_t DateTime::DaysInYear(int32_t year, int32_t month) noexcept
{
    constexpr std::array<int32_t, 12> daysInYearTable = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2)
    {
        if (IsLeapYear(year))
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }
    else
    {
        return daysInYearTable[month - 1];
    }
}

int32_t DateTime::GetMonth() const noexcept
{
    return m_month;
}

int32_t DateTime::GetDay() const noexcept
{
    return m_day;
}

int32_t DateTime::GetYear() const noexcept
{
    return m_year;
}

int32_t DateTime::GetHour() const noexcept
{
    return m_hour;
}

int32_t DateTime::GetMinute() const noexcept
{
    return m_minute;
}

int32_t DateTime::GetSecond() const noexcept
{
    return m_second;
}

DayOfWeek DateTime::GetDayOfWeek() const noexcept
{
    return m_dayOfWeek;
}

} /* namespace tgon */
