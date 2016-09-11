/*
 * Author : Cha Junho
 * Date : 05/15/2016
 * Latest author :
 * Latest date :
*/


#pragma once
#include "../OSAL/PlatformInclude.h"

#include <cstdint>


namespace tgon
{


enum class DayOfWeek
{
	Sunday = 0,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
};

struct LocalTime
{
	int32_t month;
	int32_t day;
	int32_t year;
	int32_t hour;
	int32_t minute;
	int32_t second;
	DayOfWeek dayOfWeek;
};

class TGON_API AbstractTime
{
	//
	//	Commands
	//
public:
	/* @return Return execution time of OS as millisecond */
	static uint32_t GetBootTime( ) {}
	
	/* @@return Return current application's execution time as millisecond */
	static uint32_t GetAppExecTime( );

	/* @return Return execution time of OS as millisecond */
	static uint64_t GetBootTime64( ) {}

	/* @return Return current system time */
	static LocalTime GetLocalTime( ) {}

	/*
	 * @note Put to sleep which caller thread of this function while passed millisecond
	 * @param milliSec Caller thread's sleep time
	*/
	static void Sleep( unsigned int milliSec ) {}

	// 
	// Ctor/Dtor
	// 
public:
	AbstractTime( ) = delete;
	virtual ~AbstractTime( ) = delete;

	//
	// Private variables
	//
private:
	static const uint32_t ms_oldTime;
};


} /*namespace tgon*/