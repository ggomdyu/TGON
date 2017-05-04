/**
 * filename GenericSystem.h
 * author   ggomdyu
 * since    03/20/2016
 */

#pragma once
#include "Core/Platform/TConfig.h"

#include <cstdint>

namespace tgon 
{

struct BatteryProperty
{
	BatteryProperty(bool _hasBattery, uint16_t _batteryLifePercent) noexcept :
		hasBattery(_hasBattery),
		batteryLifePercent(_batteryLifePercent)
	{
	}

	const bool hasBattery;
	const uint16_t batteryLifePercent; // 0% ~ 100%
};

template <typename DerivedTy>
class TGON_API GenericSystem
{
/**
 * @section Ctor/Dtor
 */
public:
	GenericSystem() = delete;
	~GenericSystem() = delete;
};

} /* namespace tgon */
