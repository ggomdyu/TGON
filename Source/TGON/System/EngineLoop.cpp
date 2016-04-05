#include "PrecompiledHeader.h"
#include "EngineLoop.h"

#include <cassert>

#include "../Time/TTime.h"
#include "../Console/TConsole.h"
#include "../Window/TWindow.h"
#include "../Application/TApplication.h"
#include "../Math/TMath.h"
#include "../Graphics/TGraphicsDevice.h"

#include "../Window/WindowEvent.h"
#include "../Window/WindowStyle.h"
#include "../Graphics/GraphicsDeviceProp.h"

#include "../System/SystemManager.h"
#include "../System/WindowSystem.h"


tgon::EngineLoop::EngineLoop( const TMsgCallback msgCallback ) :
	TObject( "EngineLoop", nullptr )
{
	this->PreInit( );

	this->InitWindow( msgCallback );
	//this->InitGraphicsDevice( );
	//this->InitManagers( );
}

tgon::EngineLoop::~EngineLoop( )
{

}

void tgon::EngineLoop::PreInit( )
{
	//TConsole::Get( )->SetFlashOnLogging( true );


	SystemManager::Get( )->AddSubSystem( new WindowSystem );

	//SystemManager::GetInstance( )->LoadSubSystem(
	//	L"Renderer" );

	//SystemManager::GetInstance( )->LoadSubSystem(
	//	L"Window" );
}

void tgon::EngineLoop::InitWindow( const TMsgCallback msgCallback )
{
	WindowStyle wndStyle = WindowStyle::ParseFromXML( L"WindowStyle.xml" );
	wndStyle.msgCallback = msgCallback;
	
	m_window = TWindow::Create( wndStyle );
}

void tgon::EngineLoop::InitGraphicsDevice( )
{
	GraphicsDeviceProp gdp;
	gdp.backBufferWidth = 0;
	gdp.backBufferHeight = 0;
	gdp.isWindowed = true;

	m_graphics = TGraphicsDevice::Create( m_window, gdp );
}

void tgon::EngineLoop::InitManagers( )
{
	//GraphicsManager::GetInstance( )->Setup( m_graphicsDevice );
	//SceneManager::GetInstance( )->LoadScene( new ModelScene );
}

void tgon::EngineLoop::Run( )
{
	/*
		Message loop
	*/
	WindowEvent wndEvent = WindowEvent::None;


	while ( !m_window->IsQuitted( ))
	{
		TApplication::Get( )->DispatchEvent( &wndEvent );

		// Idle time
		if ( wndEvent == WindowEvent::None )
		{
			//::GetInstance( )->Tick( TTime::GetElapsedTime( ));
			//SceneManager::GetInstance( )->Render( );
		}
	}
}