/*
* Author : Cha Junho
* Date : 05/15/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Generic/GenericTime.h"

#include <Windows.h>


namespace tgon
{


class TGON_API WindowsTime :
	public GenericTime<WindowsTime>
{
	/* 
	 * Ctor/Dtor
	*/ 
public:
	WindowsTime( ) = delete;
	~WindowsTime( ) = delete;

	/* 
	 * Commands
	*/
public:
	/* @return Return execution time of OS as millisecond */
	static uint32_t GetBootTime( );
	
	/* @return Return this process's execution time as millisecond */
	static uint64_t GetBootTime64( );

	/* @return Return current system time */
	static LocalTime GetLocalTime( );
	
	/*
	 * @note Put to sleep which caller thread of this function while passed millisecond
	 * @param milliSec Caller thread's sleep time
	*/
	static void Sleep( unsigned int milliSec );
};


using Time = WindowsTime;


} /*namespace tgon*/