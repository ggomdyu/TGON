/**
 * @filename    ApplicationType.h
 * @author      ggomdyu
 * @since       03/20/2016
 */

#pragma once
#include <cstdint>

namespace tgon 
{
namespace platform
{

enum class MessageBoxIconType
{
    Informational = 0,
    Warning = 1,
};

struct BatteryState
{
/* @section Public constructor */
public:
	constexpr BatteryState(bool hasBattery, uint16_t batteryLifePercent) noexcept;

/* @section	Public variable */
public:
    /* @brief   Records whether the current device has baterry. */
	const bool hasBattery;

    /* @brief   Records the battery percentage between 0 and 100. */
	const uint16_t batteryPercentage;
};

constexpr BatteryState::BatteryState(bool hasBattery, uint16_t batteryPercentage) noexcept :
	hasBattery(hasBattery),
    batteryPercentage(batteryPercentage)
{
}

} /* namespace platform */
} /* namespace tgon */