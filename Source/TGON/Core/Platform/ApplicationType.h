/**
 * filename TimeType.h
 * author   ggomdyu
 * since    03/20/2016
 */

#pragma once
#include <cstdint>

namespace tgon 
{
namespace utility
{

struct BatteryStatus
{
/* @section	Ctor/Dtor */
public:
	constexpr BatteryStatus(bool _hasBattery, uint16_t _batteryLifePercent) noexcept;

/* @section	Public variable */
public:
	const bool hasBattery;
	const uint16_t batteryLifePercent; // 0% ~ 100%
};

constexpr BatteryStatus::BatteryStatus(bool _hasBattery, uint16_t _batteryLifePercent) noexcept :
	hasBattery(_hasBattery),
	batteryLifePercent(_batteryLifePercent)
{
}

} /* namespace utility */
} /* namespace tgon */