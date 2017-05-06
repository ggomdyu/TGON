/**
 * @filename    GenericTimeType.h
 * @author      ggomdyu
 * @since       04/23/2017
 */

#pragma once
#include <cstdint>

namespace tgon {
namespace platform {

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

struct LocalTime
{
    std::size_t month;
    std::size_t day;
    std::size_t year;
    std::size_t hour;
    std::size_t minute;
    std::size_t second;
    DayOfWeek dayOfWeek;
};

} /* namespace platform */
} /* namespace tgon */