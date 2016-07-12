/*
* Author : Cha Junho
* Date : 01/24/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Interface/IConsole.h"
#include "../../Utility/Windows/WindowsConsoleHelper.h"


#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#	undef WIN32_LEAN_AND_MEAN
#endif


namespace tgon
{


using ConsoleImpl = class WindowsConsole;

class TGON_API WindowsConsole : 
	private IConsole
{

public:
	/*
		Cons/Destructor
	*/
	WindowsConsole( ) = delete;

	virtual ~WindowsConsole( ) = delete;
	
	
	/*
		Commands
	*/
	// Write
	static void Write( _In_ const char* str )
	{
#if defined ( _DEBUG ) || ( DEBUG )
		WriteConsoleA(
			WindowsConsoleHelper::Get( )->GetConsoleHandle( ),
			str,
			std::strlen( str ),
			nullptr,
			nullptr
		);
#endif
	}

	static void Write( _In_ const wchar_t* str )
	{
#if defined ( _DEBUG ) || ( DEBUG )
		WriteConsoleW(
			WindowsConsoleHelper::Get( )->GetConsoleHandle( ),
			str,
			std::wcslen( str ),
			nullptr,
			nullptr
		);
#endif
	}
};


}