/*
* Author : Cha Junho
* Date : 05/09/2016
* Latest author :
* Latest date :
* Description : API Sets for cross-platform
*/


#pragma once
#include "Candidate/PlatformTime.h"


namespace tgon {
namespace platform {


class TGON_API TTime :
	public TimeImpl
{
	/*
		Commands
	*/
public:
	//
	// 
	//
	


	/*
		Con/Destructor
	*/
public:
	TTime( ) = delete;
	
	virtual ~TTime( ) = delete;


private:
};


inline uint32_t TTime::GetAppExecTime( )
{
	return TimeImpl::GetBootTime( ) - ms_oldTime;
}


}}