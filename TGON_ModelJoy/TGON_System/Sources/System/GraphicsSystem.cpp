#include "stdafx.h"
#include "GraphicsSystem.h"


#include "WindowSystem.h"


tgon::GraphicsSystem::GraphicsSystem( ) :
	ISystem( *this )
{
	GraphicsDeviceCreateParam gdcp;

#ifdef PLATFORM_WINDOWS_OS
	HWND wndHandle = WindowSystem::GetInstance( )->GetWindow( ).GetWindowHandle( );
	
	RECT rt;
	GetClientRect( wndHandle, &rt );

	gdcp.width = rt.right;
	gdcp.height = rt.bottom;
	gdcp.presentWnd = wndHandle;
	gdcp.gdpt = GraphicsDeviceProcessType::kHardware;

#endif

	gd.Setup( gdcp );
}


tgon::GraphicsSystem::~GraphicsSystem( )
{
}

void tgon::GraphicsSystem::Initialize( )
{
}


void tgon::GraphicsSystem::FrameMove( float elapsedTime )
{
	gd.Display( );
}


void tgon::GraphicsSystem::RecvMessage( _In_ const SociableMessage& msg )
{
}