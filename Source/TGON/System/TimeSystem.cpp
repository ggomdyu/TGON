#include "PrecompiledHeader.h"
#include "TimeSystem.h"

#include "../Console/TConsole.h"


tgon::TimeSystem::TimeSystem( ) :
	m_timeScale( 1.f ),
	m_oldTime( TTime::GetBootTime( ))
{
	TLOG( "[CREATED] tgon::TimeSystem" );
}

tgon::TimeSystem::~TimeSystem( )
{
	TLOG( "[DESTROYED] tgon::TimeSystem" );
}

void tgon::TimeSystem::Update( float tickTIme )
{
	auto currTime = TTime::GetBootTime( );
	m_tickTime = currTime - m_oldTime;

	m_oldTime = TTime::GetBootTime( );
}