#include "PrecompiledHeader.h"
#include "WindowsPlatformConsole.h"


namespace tgon
{


WindowsConsole::WindowsConsole( )
{
#if defined ( _DEBUG ) || ( DEBUG )
	this->SetupConsole( );
#endif
}

WindowsConsole::~WindowsConsole( )
{
#if defined ( _DEBUG ) || ( DEBUG )
	::FreeConsole( );
#endif
}

void WindowsConsole::SetupConsole( )
{
	// If return true, the console already created
	if ( !::GetConsoleWindow( ))
	{
		if ( ::AllocConsole( ) == FALSE )
		{
			MessageBox( GetFocus( ),
				L"Failed to create console.",
				L"WARNING!",
				MB_OK | MB_ICONEXCLAMATION
			);
			std::abort( );
		}
	}

	// <GetStdHandle> must be invoked after AllocConsole.
	const_cast<HANDLE>( m_outputHandle ) = ::GetStdHandle( STD_OUTPUT_HANDLE );
}

void WindowsConsole::Write( const char* str )
{
#if defined ( _DEBUG ) || ( DEBUG )
	::WriteConsoleA(
		m_outputHandle,
		str,
		std::strlen( str ),
		nullptr,
		nullptr
	);
#endif
}

void WindowsConsole::Write( const wchar_t* str )
{
#if defined ( _DEBUG ) || ( DEBUG )
	::WriteConsoleW(
		m_outputHandle,
		str,
		std::wcslen( str ),
		nullptr,
		nullptr
	);
#endif
}


} /*namespace tgon*/