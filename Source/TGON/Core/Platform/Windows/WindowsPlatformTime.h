/*
* Author : Cha Junho
* Date : 05/15/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Abstract/APlatformTime.h"

#include <Windows.h>


namespace tgon
{


class TGON_API WindowsPlatformTime :
	public APlatformTime<WindowsPlatformTime>
{
	// 
	// Commands
	// 
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

	// 
	// Ctor/Dtor
	// 
public:
	WindowsPlatformTime( ) = delete;
	virtual ~WindowsPlatformTime( ) = delete;
};


using TPlatformTime = WindowsPlatformTime;


} /*namespace tgon*/


#include "WindowsPlatformTime.inl"
