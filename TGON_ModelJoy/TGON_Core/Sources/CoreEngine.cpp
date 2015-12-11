#include "CoreEngine.h"

#include "MsgManager.h"
#include "WindowSystem.h"


tgon::CoreEngine::CoreEngine( )
{

}


tgon::CoreEngine::~CoreEngine( )
{
}

void tgon::CoreEngine::InitializeAllSystems( )
{
	for ( auto& system : m_systemRepo ) {
		system->Initialize( );
	}
}

void tgon::CoreEngine::FrameMoveAllSystems( )
{ 
	for ( auto& system : m_systemRepo ) {
		system->FrameMove( );
	}
}