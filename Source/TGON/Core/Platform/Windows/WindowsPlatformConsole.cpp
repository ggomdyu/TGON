#include "PrecompiledHeader.h"
#include "WindowsPlatformConsole.h"


namespace tgon {
namespace {

class WindowsPlatformConsoleHelper final
{
	//
	// Gets
	//
public:
	static WindowsPlatformConsoleHelper& Get( )
	{
		static WindowsPlatformConsoleHelper instance;
		return instance;
	}

	HANDLE GetConsoleHandle( ) const
	{
		return m_outputHandle;
	}

	//
	// Ctor/Dtor
	//
private:
	WindowsPlatformConsoleHelper( );
public:
	~WindowsPlatformConsoleHelper( );

	//
	// Private variables
	//
private:
	HANDLE m_outputHandle;
};

WindowsPlatformConsoleHelper::WindowsPlatformConsoleHelper( )
{
#ifndef NDEBUG
	// If console already created, GetConsoleWindow return NULL.
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

	// GetStdHandle must be invoked after created console by AllocConsole!
	m_outputHandle = ::GetStdHandle( STD_OUTPUT_HANDLE );
#endif
}

WindowsPlatformConsoleHelper::~WindowsPlatformConsoleHelper( )
{
#ifndef NDEBUG
	::FreeConsole( );
#endif
}


} /*namespace*/
} /*namespace tgon*/


namespace tgon
{


void WindowsPlatformConsole::WriteImpl( /*IN*/ const char* str )
{
#ifndef NDEBUG
	::WriteConsoleA(
		WindowsPlatformConsoleHelper::Get().GetConsoleHandle( ),
		str,
		std::strlen( str ),
		nullptr,
		nullptr
	);
#endif
}

void WindowsPlatformConsole::WriteImpl( /*IN*/ const wchar_t* str )
{
#ifndef NDEBUG
	::WriteConsoleW(
		WindowsPlatformConsoleHelper::Get( ).GetConsoleHandle( ),
		str,
		std::wcslen( str ),
		nullptr,
		nullptr
	);
#endif
}


} /*namespace tgon*/