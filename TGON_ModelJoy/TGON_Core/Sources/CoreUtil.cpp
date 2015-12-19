//#include "stdafx.h"
#include "CoreUtil.h"

#include <System\WindowSystem.h>
#include <System\TickSystem.h>


void tgon::System::RegisterEventCallback( const uint32_t eventType, const std::function<void( )>& eventWork )
{
	WindowSystem::GetInstance( )->RegisterEventCallback( eventType, eventWork );
}


float tgon::Time::GetElapsedTime( )
{
	return TickSystem::GetInstance( )->GetElapsedTime( );
}