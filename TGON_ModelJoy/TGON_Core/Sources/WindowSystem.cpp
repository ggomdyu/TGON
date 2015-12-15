//#include "stdafx.h"
#include "WindowSystem.h"

#include "CoreEngine.h"
#include "MessageManager.h"
#include "WindowSystemMessageType.h"
#include "WindowStyle.h"


tgon::WindowSystem::WindowSystem( ) :
	ISystem( *WindowSystem::GetInstance( ))
{
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


void tgon::WindowSystem::FrameMove( float elapsedTime )
{
	this->PumpWindowEvent( );
/*
	if ( this->IsEventOccured( WindowEvent::Destroy ))
	{
		CoreEngine::GetInstance( )->Exit( );
	}
	*/
}


void tgon::WindowSystem::PumpWindowEvent( )
{
	MessageBox( 0, 0, 0, 0 );

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