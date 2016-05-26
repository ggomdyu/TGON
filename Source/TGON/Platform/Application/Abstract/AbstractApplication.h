/*
* Author : Junho-Cha
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : Platform abstraction API
*/


#pragma once
#include "../TApplicationType.h"
#include "../../../Platform/Config/Build.h"


namespace tgon
{


class TGON_API AbstractApplication
{
public:
	/*
		About using window
	*/
	static void Run( class WindowsWindow& ) {}
	static bool MessageLoop( _Out_ enum struct WindowEvent* ) {}

	/*
		About System
	*/
	static struct TSystemBatteryInfo GetPowerInfo( ) {}
	static void ExitThread( ) {}
	static void Exit( int32_t exitCode ) {}
	static void Quit( int32_t exitCode ) {}
	static void Restart( ) {}

	/*
		About UI
	*/
	static void GetScreenSize( int32_t* width, int32_t* height ) {}


private:
	AbstractApplication( ) = delete;
	~AbstractApplication( ) = delete;
};


}