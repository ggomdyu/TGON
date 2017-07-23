#include "PrecompiledHeader.pch"
#include "GenericTimeType.h"

namespace tgon {
namespace platform {

DateTime::DateTime(const std::tm& rawTime) noexcept :
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