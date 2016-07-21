/*
* Author : Cha Junho
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : Abstracted platform API
*/


#pragma once
#include "../../../Platform/Config/Build.h"
#include "../TApplicationType.h"


namespace tgon
{


class TGON_API AbstractApplication
{
public:
	/*
		Cons/Destructor
	*/
	AbstractApplication( ) = delete;
	
	virtual ~AbstractApplication( ) = delete;


	/*
		Commands
	*/
	static int32_t Run( class WindowsWindow& ) {}

	static void ExitThread( ) {}

	static void Quit( int32_t exitCode ) {}


	/*
		Sets
	*/


	/*
		Gets
	*/
	static struct TSystemBatteryInfo GetPowerInfo( ) {}
};


}