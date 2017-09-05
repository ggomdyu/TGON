/**
 * @filename    BaseTimeType.h
 * @author      ggomdyu
 * @since       04/23/2017
 */

#pragma once
#include <cstdint>
#include <ctime>

namespace tgon
{
namespace platform
{

enum class DayOfWeek
{
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
};

struct DateTime
{
/* @section Public constructor */
public:
    constexpr explicit DateTime(const std::tm& rawTime) noexcept;

/* @section Public variable */
public:
    uint16_t month;
    uint16_t day;
    uint16_t year;
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
    DayOfWeek dayOfWeek;
};

constexpr DateTime::DateTime(const std::tm& rawTime) noexcept :
    month(static_cast<uint16_t>(rawTime.tm_mon + 1)),
    day(static_cast<uint16_t>(rawTime.tm_mday)),
    year(static_cast<uint16_t>(1900 + rawTime.tm_year)),
    hour(static_cast<uint16_t>(rawTime.tm_hour)),
    minute(static_cast<uint16_t>(rawTime.tm_min)),
    second(static_cast<uint16_t>(rawTime.tm_sec)),
    dayOfWeek(static_cast<DayOfWeek>(rawTime.tm_wday))
{
}

} /* namespace platform */
} /* namespace tgon */
