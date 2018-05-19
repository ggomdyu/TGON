/**
 * @filename    GenericApplicationType.h
 * @author      ggomdyu
 * @since       03/20/2016
 */

#pragma once
#include <cstdint>

namespace tgon 
{

enum class MessageBoxIcon
{
    Informational = 0,
    Warning = 1,
};

struct BatteryState
{
/* @section Public constructor */
public:
    constexpr BatteryState(bool hasBattery, bool isCharging, int16_t batteryLifePercent) noexcept;

/* @section	Public variable */
public:
    /* @brief   Records whether the current device has battery. */
    const bool hasBattery;

    /* @brief   Records whether the battery is charging. */
    const bool isCharging;

    /* @brief   Records the battery percentage between 0 and 100. or -1 if status is unknown. */
    const int16_t batteryPercentage;
};

constexpr BatteryState::BatteryState(bool hasBattery, bool isCharging, int16_t batteryPercentage) noexcept :
    hasBattery(hasBattery),
    isCharging(isCharging),
    batteryPercentage(hasBattery ? batteryPercentage : -1)
{
}

} /* namespace tgon */