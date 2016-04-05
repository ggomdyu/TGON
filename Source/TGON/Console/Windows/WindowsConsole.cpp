#include "PrecompiledHeader.h"
#include "WindowsConsole.h"

#include <windows.h>


tgon::WindowsConsole::WindowsConsole( )
{
#if defined( DEBUG ) | defined( _DEBUG )
	if ( AllocConsole( ) == FALSE )
	{
		MessageBoxW( GetFocus( ),
					 L"Failed to invoke AllocConsole.",
					 L"WARNING!",
					 MB_OK | MB_ICONEXCLAMATION );
		abort( );
	}
	
	// WARN: This function should be invoked after allocated console.
	m_outputHandle = GetStdHandle( STD_OUTPUT_HANDLE );
#endif
}


tgon::WindowsConsole::~WindowsConsole( )
{
#if defined( DEBUG ) | defined( _DEBUG )
	CloseHandle( m_outputHandle );
#endif
}


void tgon::WindowsConsole::WriteLine( ) 
{
#if defined( DEBUG ) | defined( _DEBUG )
	this->FillBuffer( L"\n" );

	WriteConsoleW( m_outputHandle,
				   this->GetBuffer( ).c_str( ),
				   this->GetBuffer( ).length( ),
				   NULL,
				   NULL );

	this->ClearBuffer( );

	if ( this->IsFlashOnLogging( ))
	{
		FLASHWINFO fwi = {0};
		fwi.cbSize = sizeof( fwi );
		fwi.hwnd = GetConsoleWindow( );
		fwi.dwFlags = FLASHW_CAPTION;
		fwi.uCount = 1;

		FlashWindowEx( &fwi );
	}
#endif
}