//#include "stdafx.h"
#include "WindowSystem.h"

#include "WindowStyle.h"

tgon::WindowSystem::WindowSystem( )
{
	this->SetName( "WindowSystem" );
}


tgon::WindowSystem::~WindowSystem( )
{
}

void tgon::WindowSystem::Initialize( )
{
	WindowStyle ws;
	ws.ShowMiddle = true;
	ws.width = 1200;
	ws.height = 1000;
	ws.caption = L"ModelJoy";
	ws.Popup = true;

	m_window.reset( new Window( ws ));
}

void tgon::WindowSystem::FrameMove( )
{
}

bool tgon::WindowSystem::PumpWindowEvent( )
{
	return m_window->PumpWindowEvent( );
}

bool tgon::WindowSystem::IsEventOccured( const uint32_t eventType )
{
	auto iter = GetWindow( )->GetWindowEventRepo( ).find( WindowEvent::Destroy );
	
	return GetWindow( )->GetWindowEventRepo( ).end( ) != iter;
}

void tgon::WindowSystem::RecvMessage( _In_ const CommMessage& msg )
{
}
