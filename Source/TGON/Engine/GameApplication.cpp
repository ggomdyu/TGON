#include "PrecompiledHeader.h"
#include "GameApplication.h"

#include "../Core/Platform/PlatformApplication.h"


namespace tgon {


GameApplication::GameApplication( const std::shared_ptr<TPlatformWindow>& windowFrame ) :
	m_paused( false ),
	m_rootWindow( std::make_shared<TPlatformWindow>( ))
{
}

GameApplication::~GameApplication( )
{
}

void GameApplication::OnUpdate( )
{
	
}

void GameApplication::OnRender( )
{
}

void GameApplication::OnDestroy( )
{
}


}