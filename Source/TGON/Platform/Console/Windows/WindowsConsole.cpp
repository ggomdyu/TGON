#include "PrecompiledHeader.h"
#include "WindowsConsole.h"

#include <windows.h>


tgon::WindowsConsole::WindowsConsole( )
{
#if defined( DEBUG ) | defined( _DEBUG )
	// Console already created or Console builded
	if ( !GetConsoleWindow( ))
	{
		BOOL isSuccess = AllocConsole( );
		assert( isSuccess == TRUE && "Failed to invoke AllocConsole." );
	}

	// WARNING!!
	// This function should be invoked after allocated console!!
	m_outputHandle = GetStdHandle( STD_OUTPUT_HANDLE );
#endif
}

tgon::WindowsConsole::~WindowsConsole( )
{
#if defined( DEBUG ) | defined( _DEBUG )
	FreeConsole( );
#endif
}


void tgon::WindowsConsole::Write( 
	const wchar_t* str )
{
#if defined( DEBUG ) | defined( _DEBUG )
	WriteConsoleW(
		m_outputHandle,
		str,
		std::wcslen( str ),
		nullptr,
		nullptr 
	);
#endif
}

void tgon::WindowsConsole::Write( 
	const char* str )
{
	WriteConsoleA(
		m_outputHandle,
		str,
		std::strlen( str ),
		nullptr,
		nullptr
	);
}
