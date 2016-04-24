#include "PrecompiledHeader.h"
#include "WindowsApplication.h"

#include "../../Window/WindowEvent.h"
#include "../../Application/TApplicationTypes.h"


bool tgon::WindowsApplication::DispatchEvent( _Out_ WindowEvent* const globalEvent )
{
	MSG msg;
	BOOL isMsgExist = PeekMessageW( &msg, NULL, 0, 0, PM_REMOVE );

	if ( isMsgExist )
	{
		//TranslateMessage( &msg ); // Process WM_CHAR
		DispatchMessageW( &msg );

		*globalEvent = static_cast<WindowEvent>( msg.message );
		return true;
	}
	else
	{
		*globalEvent = WindowEvent::None;
		return false;
	}
}

tgon::TSystemBatteryInfo tgon::WindowsApplication::GetPowerInfo( )
{
	SYSTEM_POWER_STATUS sps;
	GetSystemPowerStatus( &sps );

	TSystemBatteryInfo adapter;
	adapter.batteryFlag = sps.BatteryFlag;
	adapter.batteryFlag = sps.BatteryLifePercent;

	return adapter;
}