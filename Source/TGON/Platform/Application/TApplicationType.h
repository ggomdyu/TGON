/*
* Author : Junho-Cha
* Date : 03/12/2016
* Latest author :
* Latest date :
* Description :
*/


#pragma once
#include <stdint.h>
#include "../Config/Platform.h"


namespace tgon
{


struct TSystemBatteryInfo
{
	enum BateryFlagTable
	{
#ifdef TGON_PLATFORM_WINDOWS
		kHigh = 1,
		kLow = 2,
		kCritical = 4,
		kCharging = 8,
		kHasNoBattery = 128,
#else
#endif
	};

	uint8_t batteryFlag;
	uint16_t batteryLifePercent; // 0 ~ 100
};


}
