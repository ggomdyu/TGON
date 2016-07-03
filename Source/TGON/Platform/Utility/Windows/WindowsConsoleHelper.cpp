#include "PrecompiledHeader.h"
#include "WindowsConsoleHelper.h"

#include <Windows.h>


tgon::WindowsConsoleHelper::WindowsConsoleHelper( )
{
	// Console already created or Console builded
	if ( !GetConsoleWindow( ))
	{
		BOOL isSuccess = AllocConsole( );
		assert( isSuccess == TRUE && "Failed to invoke AllocConsole." );
	}

	// @ WARNING!
	// <GetStdHandle> should be invoked after allocated console.
	const_cast<HANDLE>( m_outputHandle ) = GetStdHandle( STD_OUTPUT_HANDLE );
}

tgon::WindowsConsoleHelper::~WindowsConsoleHelper( )
{
	FreeConsole( );
}
