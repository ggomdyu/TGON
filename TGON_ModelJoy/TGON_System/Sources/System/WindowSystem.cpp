#include "stdafx.h"
#include "WindowSystem.h"

#include "CoreEngine.h"
#include "MessageManager.h"
#include "WindowSystemMessageType.h"
#include "WindowStyle.h"


inline const tgon::WindowStyle GetDefWindowStyle( )
{
	tgon::WindowStyle ws;
	ws.ShowMiddle = true;
	ws.width = 1200;
	ws.height = 1000;
	ws.caption = L"ModelJoy";
	ws.Popup = true;

	return ws;
}


tgon::WindowSystem::WindowSystem( ) :
	ISystem( *this ), m_window( GetDefWindowStyle( ))
{
}


tgon::WindowSystem::~WindowSystem( )
{
}


void tgon::WindowSystem::FrameMove( float elapsedTime )
{
	m_window.FrameMove( );
}


void tgon::WindowSystem::RecvMessage( _In_ const SociableMessage& msg )
{
}