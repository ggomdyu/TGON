/*
* Author : Junho-Cha
* Date : 05/15/2016
* Latest author :
* Latest date :
*/


#pragma once
#include <stdint.h>

namespace tgon
{


enum struct TDayOfWeek
{
	Sunday = 0,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
};

struct TSystemTime
{
	int32_t month, day, year;
	int32_t dayOfWeek;
	int32_t hour, minute, second;
};


}