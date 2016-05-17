#include "PrecompiledHeader.h"
#include "WindowsApplication.h"

#include "../../Window/WindowEvent.h"


const ::HINSTANCE tgon::WindowsApplication::m_instanceHandle( ::GetModuleHandleW( NULL ));
::MSG tgon::WindowsApplication::m_msg;


tgon::TSystemBatteryInfo tgon::WindowsApplication::GetPowerInfo( )
{
	SYSTEM_POWER_STATUS sps;
	::GetSystemPowerStatus( &sps );

	TSystemBatteryInfo adapter;
	adapter.batteryFlag = sps.BatteryFlag;
	adapter.batteryFlag = sps.BatteryLifePercent;

	return adapter;
}
