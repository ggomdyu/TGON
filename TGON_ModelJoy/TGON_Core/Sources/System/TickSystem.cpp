#include "TickSystem.h"


float tgon::GetElapsedTime( )
{
	return TickSystem::GetInstance( )->GetElapsedTime( );
}


tgon::TickSystem::TickSystem( ) :
	ISystem( *this ),
	m_startTime( std::chrono::time_point_cast<std::chrono::milliseconds>( std::chrono::system_clock::now( ))),
	m_elapsedTime( 0.0f )
{
}


tgon::TickSystem::~TickSystem( )
{
}


void tgon::TickSystem::FrameMove( float elapsedTime )
{
	MiliTimePoint endTime = std::chrono::time_point_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now( ));

	m_elapsedTime = static_cast<float>(( endTime-m_startTime ).count( ))*0.001f;
	m_startTime = endTime;
}

void tgon::TickSystem::RecvMessage( const SociableMessage& msg )
{
}