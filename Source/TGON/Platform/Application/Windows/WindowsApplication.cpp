#include "PrecompiledHeader.h"
#include "WindowsApplication.h"

#include "../../Window/WindowEvent.h"
#include "../../Slate/PlatformWindow.h"


int32_t tgon::WindowsApplication::Run( WindowsWindow& window )
{
	MSG msg {0};
	while ( msg.message != WM_QUIT )
	{
		// The message does exist
		if ( PeekMessageW( &msg, nullptr, 0, 0, PM_REMOVE ) == TRUE )
		{
			::TranslateMessage( &msg ); // Process the WM_CHAR
			::DispatchMessageW( &msg );
		}
		// The message does not exist
		else
		{
			window.OnIdle( );
		}
	}

	return 0;
}

tgon::TSystemBatteryInfo tgon::WindowsApplication::GetPowerInfo( )
{
	SYSTEM_POWER_STATUS sps;
	::GetSystemPowerStatus( &sps );

	TSystemBatteryInfo adapter;
	// If sps.BatteryFlag is 128, then hardware has no battery.
	adapter.hasBattery = ( sps.BatteryFlag == 128 ) ? false : true;
	adapter.batteryLifePercent = sps.BatteryLifePercent;

	return adapter;
}