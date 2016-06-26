/*
* Author : Junho-Cha
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : Platform abstraction API
*/


#pragma once
#include "../../Window/TWindow.h"

#include "../../../Platform/Config/Build.h"
#include "../TApplicationType.h"


#define TGON_GENERATE_MAINLOOP( className )\
int RunApplication( )\
{\
    std::shared_ptr<className> app( new className );\
    return app->Run();\
}\

namespace tgon
{


class TGON_API AbstractApplication : 
	public AbstractWindowDelegate
{
public:
	AbstractApplication( const struct WindowStyle& );
	virtual ~AbstractApplication( );

public:
	virtual int32_t Run( ) = 0;
	static void Run( class WindowsWindow& ) {}
	static bool MessageLoop( _Out_ enum struct WindowEvent* ) {}
	static void ExitThread( ) {}
	static void Exit( int32_t exitCode ) {}
	static void Quit( int32_t exitCode ) {}
	static void Restart( ) {}
	static void GetScreenSize( int32_t* width, int32_t* height ) {}
	static struct TSystemBatteryInfo GetPowerInfo( ) {}

protected:
	virtual void SetupWindowComponents( );

private:
	SpTWindow m_window;
	WindowStyle m_rootWndStyle;
};


}