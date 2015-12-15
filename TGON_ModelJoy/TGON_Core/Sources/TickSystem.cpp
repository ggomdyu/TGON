#include "TickSystem.h"

//Implement_Singleton_Instance( tgon::TickSystem )

//std::shared_ptr<tgon::TickSystem> tgon::TickSystem::m_instance;

using namespace std;


float tgon::GetElapsedTime( )
{
	return TickSystem::GetInstance( )->GetElapsedTime( );
}

#include <windows.h>
tgon::TickSystem::TickSystem( ) :
	ISystem( *TickSystem::GetInstance( )),
	m_startTime( chrono::time_point_cast<chrono::milliseconds>( chrono::system_clock::now( ))),
	m_elapsedTime( 0.0f )
{
}


tgon::TickSystem::~TickSystem( )
{
}


void tgon::TickSystem::FrameMove( float elapsedTime )
{
	MiliTimePoint endTime = chrono::time_point_cast<chrono::milliseconds>(
			std::chrono::system_clock::now( ));

	m_elapsedTime = static_cast<float>(( endTime-m_startTime ).count( ))*0.001f;
	m_startTime = endTime;
}

void tgon::TickSystem::RecvMessage( const SociableMessage& msg )
{
}