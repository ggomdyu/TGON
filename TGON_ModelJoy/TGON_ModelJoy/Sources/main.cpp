#include "stdafx.h"


#include "CoreEngine.h"
#include "CoreEngineUtil.h"

#include <System\GraphicsSystem.h>
#include <System\TickSystem.h>

#include "TGraphicsDevice.h"
#include "WindowStyleUtil.h"


using namespace tgon;
using namespace tgon::Window;


int tgMain( int argc, char* argv[] )
{
	WindowStyle wndStyle = GetWindowStyleFromXML( "WindowStyle.xml" );


	// Make window
	auto	tgWindow			( std::make_shared<TWindow>( false, wndStyle ));


	// Make graphics device on window
	GraphicsDeviceCreateParam gdcp;
	gdcp.gdpt = ::GraphicsDeviceProcessType::kHardware;
	gdcp.isFullWindow = true;
	gdcp.resolution_x = wndStyle.width;
	gdcp.resoultion_y = wndStyle.height;

	auto	tgGraphicsDevice	( std::make_shared<TGraphicsDevice>( tgWindow, gdcp ));
	

	// Register systems that will be used and window
	//CoreEngine::GetInstance( )->Setup(
	//			tgWindow,
	//			{ GraphicsSystem::GetInstance( ), TickSystem::GetInstance( )}
	//);


	WindowEvent wndEvent = WindowEvent::None;
	while ( wndEvent != WindowEvent::Destroy )
	{
		CoreEngine::DispatchEvent( &wndEvent );

		// Idle time
		if ( wndEvent == WindowEvent::None )
		{
			CoreEngine::Run( );
			continue;
		}
	}
	
	return 0;
}