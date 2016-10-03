#include "PrecompiledHeader.h"
#include "WindowsSystem.h"

#include <Windows.h>


namespace tgon
{


BatteryProperty WindowsSystem::GetPowerInfo( )
{
	SYSTEM_POWER_STATUS sps;
	::GetSystemPowerStatus( &sps );

	BatteryProperty adapter {
		sps.BatteryFlag == 128 ? false : true,
		sps.BatteryLifePercent
	};

	return adapter;
}


} /*namespace tgon*/
