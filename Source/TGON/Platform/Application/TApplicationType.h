/*
* Author : Junho-Cha
* Date : 03/12/2016
* Latest author :
* Latest date :
*/


#pragma once


namespace tgon
{


enum class TBatteryState
{
#if BOOST_OS_WINDOWS
	kHigh = 1,
	kLow = 2,
	kCritical = 4,
	kCharging = 8,
	kHasNoBattery = 128,
#else
#endif
};

struct TSystemBatteryInfo
{

	TBatteryState batteryFlag;
	uint16_t batteryLifePercent; // 0 ~ 100
};


}
