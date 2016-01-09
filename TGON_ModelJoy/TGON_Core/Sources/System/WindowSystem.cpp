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
	this->PumpWindowEvent( );
}


void tgon::WindowSystem::PumpWindowEvent( )
{
	if ( !m_window->PumpWindowEvent( ))
	{
		MessageManager::GetInstance( )->Broadcast(
			SociableMessage( this->GetKey( ), SociableMessageType::ClearAllWindowEvents ));
	}
}


void tgon::WindowSystem::RecvMessage( _In_ const SociableMessage& msg )
{
	switch ( msg.GetMsgType( ))
	{
	case SociableMessageType::ReadyToExit:
		CoreEngine::GetInstance( )->Exit( );
		break;
	}
}


void tgon::WindowSystem::RegisterEventCallback( const uint32_t eventType, const WorkProc& eventWork )
{
	m_window->RegisterEventCallback( eventType, eventWork );
}
