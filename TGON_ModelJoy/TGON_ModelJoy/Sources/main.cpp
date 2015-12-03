#include "stdafx.h"

#include "GenericWindow.h"
#include "GenericApplication.h"
#include "FBXModel.h"
#include "Direct3D9.h"

using namespace tgon;

int KapMain( int argc, char* argv[] )
{
	WindowStyle ws;
	ws.ShowMiddle = true;
	ws.width = 1200;
	ws.height = 1000;
	ws.caption = L"ModelJoy";
	ws.Popup = true;
	//ws.Resizeable = true;

	const std::shared_ptr<Window> pWindow( new Window( ws ));
	pWindow->Make( );

	Direct3D9::get()->Initialize(pWindow->GetWindowHandle());
	Application::AddWindow( "MainWnd", pWindow );

	// test
	std::unique_ptr<CFBXModel> pModel( new CFBXModel( "Resources\\FBXModel\\humanoid.FBX" ));


	while ( pWindow->GetWindowEvent( ) != WindowEvent::Destroy )
	{
		if ( !Application::ResponseMessage( ))
		{
			Direct3D9::get( )->BeginDraw( );
			pModel->Render();
			Direct3D9::get( )->EndDraw( );
		}
		else
		{
			if ( pWindow->GetWindowEvent() == WM_RBUTTONDOWN )
			{
				break;
			}
		}
	}
	return 0;
}