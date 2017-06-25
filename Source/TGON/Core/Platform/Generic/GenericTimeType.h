/**
 * @filename    GenericTimeType.h
 * @author      ggomdyu
 * @since       04/23/2017
 */

#pragma once
#include <cstdint>
#include <ctime>
#include <type_traits>

namespace tgon
{
namespace platform
{

using UnixTimeTy = typename std::conditional<sizeof(time_t) == sizeof(uint64_t), uint64_t, uint32_t>::type;

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
    DateTime(const std::tm& rawTime) noexcept;
    
    uint16_t month;
    uint16_t day;
    uint16_t year;
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
    DayOfWeek dayOfWeek;
};

} /* namespace platform */
} /* namespace tgon */
