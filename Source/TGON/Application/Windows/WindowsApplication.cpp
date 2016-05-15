#include "PrecompiledHeader.h"
#include "WindowsApplication.h"

#include "../../Window/WindowEvent.h"
#include "../../Application/TApplicationTypes.h"


tgon::WindowsApplication::WindowsApplication( ) :
	m_instanceHandle( GetModuleHandle( NULL ))
{
}

tgon::WindowsApplication::~WindowsApplication( )
{
}


bool tgon::WindowsApplication::DispatchEvent(
	_Out_ WindowEvent* outEvent )
{
	BOOL isMsgExist = PeekMessageW( &m_msg, NULL, 0, 0, PM_REMOVE );

	if ( isMsgExist )
	{
		::TranslateMessage( &m_msg ); // Process WM_CHAR
		::DispatchMessageW( &m_msg );

		*outEvent = static_cast<WindowEvent>( m_msg.message );
		return true;
	}
	else
	{
		*outEvent = WindowEvent::None;
		return false;
	}
}

tgon::TSystemBatteryInfo tgon::WindowsApplication::GetPowerInfo( )
{
	SYSTEM_POWER_STATUS sps;
	::GetSystemPowerStatus( &sps );

	TSystemBatteryInfo adapter;
	adapter.batteryFlag = sps.BatteryFlag;
	adapter.batteryFlag = sps.BatteryLifePercent;

	return adapter;
}