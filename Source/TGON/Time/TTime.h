/*
* Author : Junho-Cha
* Date : 05/09/2016
* Latest author :
* Latest date :
* Description : API Sets for cross-platform
*/


#pragma once
#include <stdint.h>
#include "../Platform/PlatformTime.h"
#include "../Config/SyntaxCompatible.h"
#include "../Config/Build.h"


namespace tgon
{


class TGON_API TTime final : 
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


TGON_FORCEINLINE uint32_t TTime::GetBootTime( )
{
	return TimeImpl::GetBootTime( );
}

TGON_FORCEINLINE uint64_t TTime::GetBootTime64( )
{
	return TimeImpl::GetBootTime64( );
}

TGON_FORCEINLINE uint64_t TTime::GetAppExecutionTime( )
{
	return TimeImpl::GetAppExecutionTime( );
}

TGON_FORCEINLINE tgon::TSystemTime TTime::GetLocalTime( )
{
	return TimeImpl::GetLocalTime( );
}

};