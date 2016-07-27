/*
* Author : Cha Junho
* Date : 05/15/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Abstract/AbstractTime.h"

#include <Windows.h>


namespace tgon
{


class WindowsTime;

using TimeImpl = WindowsTime;


class TGON_API WindowsTime :
	public AbstractTime
{
public:
	/*
		Commands
	*/
	// Get execution time of OS as millisecond
	static uint32_t GetBootTime( );
	
	// Get execution time of OS as millisecond
	static uint64_t GetBootTime64( );

	// Get current system time
	static TSystemTime GetLocalTime( );
	
	static void Sleep( unsigned int milliSec );


public:
	/*
		Cons/Destructor
	*/
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

inline void tgon::WindowsTime::Sleep( unsigned int milliSec )
{
	::Sleep( milliSec );
}


}