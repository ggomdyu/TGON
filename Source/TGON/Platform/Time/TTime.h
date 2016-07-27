/*
* Author : Cha Junho
* Date : 05/09/2016
* Latest author :
* Latest date :
* Description : API Sets for cross-platform
*/


#pragma once
#include "../../Platform/Slate/PlatformTime.h"


namespace tgon
{


class TGON_API TTime :
	public TimeImpl
{
public:
	/*
		Commands
	*/
	// Get current application's execution time as millisecond
	static uint32_t GetAppExecTime( );


public:
	/*
		Cons/Destructor
	*/
	TTime( ) = delete;
	
	virtual ~TTime( ) = delete;


private:
	static const uint32_t ms_oldTime;
};


inline uint32_t TTime::GetAppExecTime( )
{
	return TimeImpl::GetBootTime( ) - ms_oldTime;
}


};