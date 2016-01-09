//#include "stdafx.h"
#include "WindowSystem.h"

#include "CoreEngine.h"
#include "MessageManager.h"
#include "WindowSystemMessageType.h"
#include "WindowStyle.h"


tgon::WindowSystem::WindowSystem( ) :
	ISystem( *this )
{
	WindowStyle ws;
	ws.ShowMiddle = true;
	ws.width = 1200;
	ws.height = 1000;
	ws.caption = L"ModelJoy";
	ws.Popup = true;

	m_window.reset( new Window( ws ));
}


tgon::WindowSystem::~WindowSystem( )
{
}


void tgon::WindowSystem::FrameMove( float elapsedTime )
{
	m_window->FrameMove( );
}


void tgon::WindowSystem::RecvMessage( _In_ const SociableMessage& msg )
{
}


void tgon::WindowSystem::AddWindowEventCallback( const uint32_t evType, const EventProc& evProc )
{
	m_window->AddWindowEventCallback( evType, evProc );
}


const WindowEvent tgon::WindowSystem::GetWindowEvent( ) const
{
	return m_window->GetWindowEvent( );
}
