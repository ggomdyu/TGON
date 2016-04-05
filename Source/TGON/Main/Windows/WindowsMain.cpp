#pragma once
#include "PrecompiledHeader.h"
#include "../../Main/TMain.h"

#include <Windows.h>
#include <clocale>
#include <crtdbg.h>

#include "../../String/TString.h"
#include "../../Console/TConsole.h"


#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#define new new ( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif

// Using common control v6.0.0.0
#pragma comment( linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"" )


int WINAPI WinMain(
		_In_ HINSTANCE hInstance,
		_In_ HINSTANCE hPrevInstance,
		_In_ LPSTR	   cmdLine,
		_In_ int	   cmdShow
	)
{
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	int32_t errCode = tgMain( __argc, __argv );
	return errCode;
}