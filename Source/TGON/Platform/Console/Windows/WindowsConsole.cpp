#include "PrecompiledHeader.h"
#include "WindowsConsole.h"


tgon::WindowsConsole::WindowsConsole( )
{
	// Console already created or Console builded
	if ( !GetConsoleWindow( ) )
	{
		BOOL isSuccess = AllocConsole( );
		assert( isSuccess == TRUE && "Failed to invoke AllocConsole." );
	}

	// @ WARNING!
	// <GetStdHandle> should be invoked after allocated console.
	const_cast<HANDLE>( m_outputHandle ) = GetStdHandle( STD_OUTPUT_HANDLE );
}

tgon::WindowsConsole::~WindowsConsole( )
{
	FreeConsole( );
}

void tgon::WindowsConsole::Write( const char* str )
{
#if defined ( _DEBUG ) || ( DEBUG )
	WriteConsoleA(
		m_outputHandle,
		str,
		std::strlen( str ),
		nullptr,
		nullptr
	);
#endif
}

void tgon::WindowsConsole::Write( const wchar_t* str )
{
#if defined ( _DEBUG ) || ( DEBUG )
	WriteConsoleW(
		m_outputHandle,
		str,
		std::wcslen( str ),
		nullptr,
		nullptr
	);
#endif
}
