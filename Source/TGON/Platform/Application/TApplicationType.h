/*
* Author : Cha Junho
* Date : 03/12/2016
* Latest author :
* Latest date :
*/


#pragma once
#include <cstdint>


namespace tgon
{


struct TSystemBatteryInfo
{
	bool hasBattery;
	uint16_t batteryLifePercent; // 0 ~ 100
};


}
