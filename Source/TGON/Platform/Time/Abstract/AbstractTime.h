/*
* Author : Cha Junho
* Date : 05/15/2016
* Latest author :
* Latest date :
* Description : Abstract-API Sets for Windows
*/


#pragma once
#include "../../../Platform/Config/Build.h"
#include "../TTimeType.h"


namespace tgon
{


class TGON_API AbstractTime
{
public:
	/*
		Commands
	*/
	// Getting OS's execution time as millisecond
	static uint32_t GetBootTime( ) {};

	static uint64_t GetBootTime64( ) {};

	// Getting current system time
	static TSystemTime GetLocalTime( ) {};


private:
	/*
		Cons/Destructor
	*/
	AbstractTime( ) = delete;

	virtual ~AbstractTime( ) = delete;
};


}