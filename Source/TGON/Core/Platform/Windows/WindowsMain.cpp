#include "PrecompiledHeader.h"
#include "../TMain.h"

#include <cstdint>

#include <crtdbg.h>
#include <Windows.h>
#include "WindowsApplication.h"


#ifndef NDEBUG
	#define _CRTDBG_MAP_ALLOC
	#define new new ( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif

// Using common control v6.0.0.0
#pragma comment( linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"" )


namespace 
{

void EnableFloatingException( )
{
	unsigned int currStat;
	_controlfp_s( &currStat, 0, 0 );

	unsigned int newStat = currStat;
	newStat &= ~( EM_ZERODIVIDE );
	_controlfp_s( &currStat, newStat, MCW_EM );
}

bool RegisterWindowClass( )
{
	// This is the base form of window class.
	WNDCLASSEXW wcex {};

	wcex.cbSize = sizeof( wcex );
	wcex.lpszClassName = tgon::WindowsApplication::AppClassName;
	wcex.style = CS_DBLCLKS;
	wcex.hbrBackground = static_cast<HBRUSH>( GetStockObject( WHITE_BRUSH ));
	wcex.hCursor = LoadCursorW( NULL, IDC_ARROW );
	wcex.hIcon = LoadIconW( NULL, IDI_APPLICATION );
	wcex.hInstance = tgon::WindowsApplication::InstanceHandle;
	wcex.lpfnWndProc = tgon::WindowsApplication::OnMessageHandled; // Default message procedure; More fast than EvHandleMsgProc

	return RegisterClassExW( &wcex ) != 0;
}

} /* namespace } */


int WINAPI WinMain(
	_In_ HINSTANCE instanceHandle,
	_In_ HINSTANCE prevInstanceHandle,
	_In_ LPSTR commandLine,
	_In_ int commandShow )
{
#ifndef NDEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	//
	// Platform-independent initialization is here
	//
	{
		EnableFloatingException( );

		// TODO: Insert mini-dump setting code here

		RegisterWindowClass( );
	}

	// Call the platform independent main
	tgon::main( __argc, __argv );

}