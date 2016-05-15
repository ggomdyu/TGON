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

void tgon::WindowsConsole::WriteLine( ) 
{
#if defined( DEBUG ) | defined( _DEBUG )
	this->FillBuffer( L"\n" );
	
	WriteConsoleW(
		m_outputHandle,
		this->GetBuffer( ).c_str( ),
		this->GetBuffer( ).length( ),
		nullptr,
		nullptr );

	this->ClearBuffer( );
#endif
}

void tgon::WindowsConsole::Write( ) 
{
#if defined( DEBUG ) | defined( _DEBUG )
	WriteConsoleW(
		m_outputHandle,
		this->GetBuffer( ).c_str( ),
		this->GetBuffer( ).length( ),
		nullptr,
		nullptr );

	this->ClearBuffer( );
#endif
}