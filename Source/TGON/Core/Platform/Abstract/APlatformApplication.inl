#include "PrecompiledHeader.h"
#include "APlatformApplication.h"


namespace tgon
{


bool APlatformApplication::PumpEvent( )
{
	return false;
}

void APlatformApplication::ExitThread( int32_t exitCode )
{
}

void APlatformApplication::Quit( int32_t exitCode )
{
}

bool APlatformApplication::ToggleFullScreen( const APlatformWindowFrame & )
{
	return false;
}

void APlatformApplication::ShowCursor( bool enableShow )
{
}

BatteryProperty APlatformApplication::GetPowerInfo( )
{
	return BatteryProperty( );
}


} /*namespace tgon*/
