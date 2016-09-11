#include "PrecompiledHeader.h"
#include "GameApplication.h"

#include "../Core/Platform/OSAL/PlatformApplication.h"


namespace tgon {


GameApplication::GameApplication( const WindowStyle& wndStyle ) :
	m_paused( false ),
	m_rootWindow( std::make_shared<TPlatformWindow>( wndStyle ))
{
}

GameApplication::~GameApplication( )
{
}

void GameApplication::Update( )
{
	
}


}