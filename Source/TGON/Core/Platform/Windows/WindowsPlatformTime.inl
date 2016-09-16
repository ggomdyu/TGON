/*
* Author : Cha Junho
* Date : 05/15/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "WindowsPlatformTime.h"


namespace tgon
{


inline uint32_t WindowsPlatformTime::GetBootTime( )
{
	return GetTickCount( );
}

 uint64_t WindowsPlatformTime::GetBootTime64( )
{
	return GetTickCount64( );
}

inline void WindowsPlatformTime::Sleep( unsigned int milliSec )
{
	::Sleep( milliSec );
}


} /*namespace tgon*/