/*
* Author : Cha Junho
* Date : 05/15/2016
* Latest author :
* Latest date :
* Description : Abstract-API Sets for Windows
*/


#pragma once
#include "../TTimeType.h"
#include "../../../Platform/Config/Build.h"

#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN


namespace tgon
{


class WindowsTime;
using TimeImpl = WindowsTime;

class TGON_API WindowsTime
{
public:
	// Getting OS's execution time as millisecond
	static uint32_t GetBootTime( );
	static uint64_t GetBootTime64( );

	// Get current application's execution time as millisecond
	static uint64_t GetAppExecutionTime( );

	// Getting current system time
	static TSystemTime GetLocalTime( );


private:
	WindowsTime( ) = delete;
	~WindowsTime( ) = delete;

private:
	static const uint32_t ms_oldTime;
};


BOOST_FORCEINLINE uint32_t WindowsTime::GetBootTime( )
{
	return GetTickCount( );
}

BOOST_FORCEINLINE uint64_t WindowsTime::GetBootTime64( )
{
	return GetTickCount64( );
}

BOOST_FORCEINLINE uint64_t WindowsTime::GetAppExecutionTime( )
{
	return GetTickCount( ) - ms_oldTime;
}


}