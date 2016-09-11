#include "PrecompiledHeader.h"
#include "WindowsPlatformConsole.h"


namespace tgon
{


WindowsPlatformConsole::WindowsPlatformConsole( )
{
#if defined ( _DEBUG ) || ( DEBUG )
	this->SetupConsole( );
#endif
}

WindowsPlatformConsole::~WindowsPlatformConsole( )
{
#if defined ( _DEBUG ) || ( DEBUG )
	::FreeConsole( );
#endif
}

void WindowsPlatformConsole::SetupConsole( )
{
	// GetConsoleWindow return handle if the console already created, else NULL.
	if ( !::GetConsoleWindow( ))
	{
		if ( ::AllocConsole( ) == FALSE )
		{
			MessageBox( GetFocus( ),
				L"Failed to create console!",
				L"WARNING!",
				MB_OK | MB_ICONEXCLAMATION
			);
			std::abort( );
		}
	}

	// <GetStdHandle> must be invoked after AllocConsole.
	const_cast<HANDLE>( m_outputHandle ) = ::GetStdHandle( STD_OUTPUT_HANDLE );
}

void WindowsPlatformConsole::WriteImpl( const char* str )
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

void WindowsPlatformConsole::WriteImpl( const wchar_t* str )
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