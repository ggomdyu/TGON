/*
* 작성자 : 김태우
* 작성일 : 2015-04-25
* 최종 수정 : 김태우
* 최종 수정일 : 2015-04-26
*/

#include <Windows.h>
#include "Define.h"
#include "ToolManager.h"

#ifdef _DEBUG // Memory Leak
	#include <crtdbg.h>
	#define _CRTDBG_MAP_ALLOC
	#define new new ( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif


LRESULT CALLBACK MsgProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam );

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR, INT )
{

#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	WNDCLASSEX wc;
	ZeroMemory( &wc, sizeof( wc ) );
	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = ( WNDPROC )MsgProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( hInstance, NULL );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.lpszClassName = CLASS_NAME;
	RegisterClassEx( &wc );

	HWND hWnd = CreateWindowEx( NULL, wc.lpszClassName, WINDOW_NAME, WS_OVERLAPPEDWINDOW,
								GetSystemMetrics( SM_CXSCREEN ) / 2 - SCREEN_WIDTH / 2, GetSystemMetrics( SM_CYSCREEN ) / 2 - SCREEN_HEIGHT / 2,
								SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL, hInstance, NULL );

	ToolMgr( )->TOOLINIT( hWnd, true );
	ToolMgr( )->GetLoadMgr( )->LoadModel( "Resource//FBXModel//humanoid.fbx", "FBX" );
	Direct3D( )->InitializeVB( );

	ShowWindow( hWnd, SW_SHOWDEFAULT );
	UpdateWindow( hWnd );

	MSG Message;
	ZeroMemory( &Message, sizeof( Message ) );
	while ( Message.message != WM_QUIT )
	{
		if ( PeekMessage( &Message, NULL, 0L, 0L, PM_REMOVE ) )
		{
			DispatchMessage( &Message );
		}
		else
		{
			ToolMgr( )->Render( );
		}
	}

	ToolMgr( )->TOOLUNINIT( );
	ToolMgr( )->DestroyInstance( );

	return 0;
}

LRESULT CALLBACK MsgProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam )
{
	switch ( iMessage )
	{
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;
	}

	return( DefWindowProc( hWnd, iMessage, wParam, lParam ) );
}