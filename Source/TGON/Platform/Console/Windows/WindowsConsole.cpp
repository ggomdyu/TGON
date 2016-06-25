#include "PrecompiledHeader.h"
#include "WindowsConsole.h"

#include <windows.h>


tgon::WindowsConsole::WindowsConsoleExecuter::WindowsConsoleExecuter( ) :
	m_outputHandle( nullptr )
{
#if defined( DEBUG ) | defined( _DEBUG )
	// Console already created or Console builded
	if ( !GetConsoleWindow( ) )
	{
		BOOL isSuccess = AllocConsole( );
		assert( isSuccess == TRUE && "Failed to invoke AllocConsole." );
	}

	// @ WARNING!
	// <GetStdHandle> should be invoked after allocated console.
	 const_cast<HANDLE>( m_outputHandle ) = GetStdHandle( STD_OUTPUT_HANDLE );
#endif
}

tgon::WindowsConsole::WindowsConsoleExecuter::~WindowsConsoleExecuter( )
{
#if defined( DEBUG ) | defined( _DEBUG )
	FreeConsole( );
#endif
}