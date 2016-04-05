/*
* Author : 차준호
* Date : 2016-03-12
* 최종 수정 :
* 최종 수정일 :
* Description :
*/


#pragma once
#include <stdint.h>
#include "../Config/Platform/Platform.h"


namespace tgon
{


struct TSystemBatteryInfo
{
	enum BateryFlagTable
	{
#ifdef TGON_PLATFORM_WINDOWS
		High = 1,
		Low = 2,
		Critical = 4,
		kCharging = 8,
		kHasNoBattery = 128,
#else
#endif
	};

	uint8_t batteryFlag;
	uint16_t batteryLifePercent; // 0 ~ 100
};


}
