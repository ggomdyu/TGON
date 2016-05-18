#include "PrecompiledHeader.h"
#include "TCoreEngine.h"

#include <cassert>

#include "../Platform/Window/WindowEvent.h"
#include "../Platform/Window/TWindow.h"
#include "../Platform/Window/WindowStyle.h"
#include "../Platform/Application/TApplication.h"
#include "../LowLevelRenderer/Graphics/TGraphics.h"
#include "../LowLevelRenderer/Graphics/GraphicsStyle.h"


#include "../Platform/Console/TConsole.h"
#include "../System/SystemManager.h"
#include "../System/SceneSystem.h"
#include "../System/WindowSystem.h"
//#include "../System/GraphicsSystem.h"
#include "../System/TimeSystem.h"


tgon::TCoreEngine::TCoreEngine(
	TMsgCallback msgCallback )
{
	this->InitSystem( );
	this->InitWindow( msgCallback );
	this->InitGraphics( );
}

tgon::TCoreEngine::~TCoreEngine( )
{
}

void tgon::TCoreEngine::InitSystem( )
{
	TConsole::Get( );

	SystemManager::Get( )->AddSubSystem({
		TimeSystem::Get( ),
		WindowSystem::Get( ),
		SceneSystem::Get( )
	});

	//GraphicsSystem::Get( );
	//GraphicsManager::GetInstance( )->Setup( m_graphicsDevice );
}

void tgon::TCoreEngine::InitWindow( 
	TMsgCallback msgCallback )
{
	WindowStyle wndStyle = WindowStyle::ParseFromXML( L"WindowStyle.xml" );
	wndStyle.msgCallback = msgCallback;
	
	m_window = TWindow::Create( wndStyle );
	WindowSystem::Get( )->AddWindow( m_window );
}

void tgon::TCoreEngine::InitGraphics( )
{
	assert( m_window.get( ) &&
		"<tgon::CoreEngine::InitGraphics> must be called after the <tgon::CoreEngine::InitWindow> called." );

	GraphicsStyle grpStyle;
	grpStyle.backBufferWidth = 0;
	grpStyle.backBufferHeight = 0;
	grpStyle.isWindowed = true;

	m_graphics = TGraphics::Create( m_window, grpStyle );
}

void tgon::TCoreEngine::Run( )
{
	/*
		Message Loop
	*/
	WindowEvent wndEvent = WindowEvent::kNone;
	while ( !m_window->IsDestroyed( ))
	{
		const bool isMsgExist = TApplication::DispatchEvent( &wndEvent );

		// Idle time
		if ( !isMsgExist )
		{
			float tickTime = TimeSystem::Get( )->GetTickTime( );
			SystemManager::Get()->Update( tickTime );
		}
	}
}