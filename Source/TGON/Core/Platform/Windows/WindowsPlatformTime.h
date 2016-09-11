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


class WindowsTime;
using TimeImpl = WindowsTime;

class TGON_API WindowsTime :
	public AbstractTime
{
	/*
		Commands
	*/
public:
	//
	// @return Return execution time of OS as millisecond
	//
	static uint32_t GetBootTime( );
	
	//
	// @return Return execution time of OS as millisecond
	//
	static uint64_t GetBootTime64( );

	//
	// @return Return current system time
	//
	static LocalTime GetLocalTime( );
	
	//
	// @note Put to sleep which caller thread of this function while passed millisecond
	// @param milliSec Caller thread's sleep time
	//
	static void Sleep( unsigned int milliSec );


	/*
		Ctor/Dtor
	*/
public:
	WindowsTime( ) = delete;

	virtual ~WindowsTime( ) = delete;
};


inline uint32_t WindowsTime::GetBootTime( )
{
	return GetTickCount( );
}

inline uint64_t WindowsTime::GetBootTime64( )
{
	return GetTickCount64( );
}

inline void WindowsTime::Sleep( unsigned int milliSec )
{
	::Sleep( milliSec );
}


} /*namespace tgon*/