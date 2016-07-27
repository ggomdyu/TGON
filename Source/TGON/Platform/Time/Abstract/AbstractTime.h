/*
* Author : Cha Junho
* Date : 05/15/2016
* Latest author :
* Latest date :
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
	// Get execution time of OS as millisecond
	static uint32_t GetBootTime( ) {}

	// Get execution time of OS as millisecond
	static uint64_t GetBootTime64( ) {}

	// Get current system time
	static TSystemTime GetLocalTime( ) {}

	static void Sleep( unsigned int milliSec ) {}


public:
	/*
		Cons/Destructor
	*/
	AbstractTime( ) = delete;

	virtual ~AbstractTime( ) = delete;
};


}