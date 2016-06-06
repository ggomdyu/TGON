#include "PrecompiledHeader.h"
#include "../TMain.h"

#include <Windows.h>
#include <crtdbg.h>


#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#define new new ( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif


// Using common control v6.0.0.0
#pragma comment( linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"" )


int32_t WINAPI WinMain(
	HINSTANCE instanceHandle,
	HINSTANCE prevInstanceHandle,
	LPSTR commandLine,
	int32_t commandShow )
{
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	if ( SDL_Init( SDL_INIT_VIDEO |
				   SDL_INIT_JOYSTICK | 
				   SDL_INIT_AUDIO |
				   SDL_INIT_GAMECONTROLLER ) < 0 )
	{
		// TODO: Log Error
	}
	
	// TODO: Make mini dump executer

	int32_t errCode = tgon::RunApplication( );
	SDL_Quit( );

	return errCode;
}