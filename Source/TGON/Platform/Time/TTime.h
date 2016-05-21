/*
* Author : Junho-Cha
* Date : 05/09/2016
* Latest author :
* Latest date :
* Description : API Sets for cross-platform
*/


#pragma once
#include "../Platform/Slate/PlatformTime.h"
#include "../Platform/Config/BuildOption.h"


namespace tgon
{


class TGON_API TTime : 
	public TimeImpl
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
	TTime( ) = delete;
	~TTime( ) = delete;
};


BOOST_FORCEINLINE uint32_t TTime::GetBootTime( )
{
	return TimeImpl::GetBootTime( );
}

BOOST_FORCEINLINE uint64_t TTime::GetBootTime64( )
{
	return TimeImpl::GetBootTime64( );
}

BOOST_FORCEINLINE uint64_t TTime::GetAppExecutionTime( )
{
	return TimeImpl::GetAppExecutionTime( );
}

BOOST_FORCEINLINE tgon::TSystemTime TTime::GetLocalTime( )
{
	return TimeImpl::GetLocalTime( );
}

};