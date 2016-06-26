/*
* Author : Junho-Cha
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : Abstracted platform API
*/


#pragma once
#include "../../../Platform/Config/Build.h"
#include "../TApplicationType.h"
#include "../../Window/TWindow.h"

#ifdef DispatchMessage
	#undef DispatchMessage
#endif


namespace tgon
{


class TGON_API AbstractApplication
{
public:
	AbstractApplication( );
	
	virtual ~AbstractApplication( );


public:
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
	static void GetScreenSize( int32_t* width, int32_t* height ) {}

	static struct TSystemBatteryInfo GetPowerInfo( ) {}


private:
	SpTWindow m_window;

	WindowStyle m_rootWndStyle;
};


}