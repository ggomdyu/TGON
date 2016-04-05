#include "PrecompiledHeader.h"
#include "WindowsApplication.h"

#include "../../Window/WindowEvent.h"
#include "../../Application/TApplicationTypes.h"


void tgon::WindowsApplication::DispatchEvent( _Out_ WindowEvent* const globalEvent )
{
	MSG msg;
	BOOL isMsgExist = PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );

	if ( isMsgExist )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );

		*globalEvent = static_cast<WindowEvent>( msg.message );
	}
	else
	{
		*globalEvent = WindowEvent::None;
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