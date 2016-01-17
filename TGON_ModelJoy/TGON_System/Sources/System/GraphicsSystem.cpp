#include "stdafx.h"
#include "GraphicsSystem.h"


#include "WindowSystem.h"
#include "Direct3D9Device.h"


tgon::GraphicsSystem::GraphicsSystem( ) :
	ISystem( *this ), gd( GetWindowSystem( )->GetWindow( ). GetWindowHandle( ))
{
	// TODO: Use XML and assemble device info!! 

	D3dDeviceCreateParam d3dCreateParam;
	HWND wndHandle = WindowSystem::GetInstance( )->GetWindow( ).GetWindowHandle( );
	
	d3dCreateParam.d3dBehaviorFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	d3dCreateParam.gdpt = GraphicsDeviceProcessType::kHardware;

	gd.Setup( &d3dCreateParam );
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