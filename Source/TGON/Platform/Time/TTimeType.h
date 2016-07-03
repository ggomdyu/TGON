/*
* Author : Cha Junho
* Date : 05/15/2016
* Latest author :
* Latest date :
*/


#pragma once


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
	int32_t month, day, year, hour, minute, second;
	TDayOfWeek dayOfWeek;
};


}