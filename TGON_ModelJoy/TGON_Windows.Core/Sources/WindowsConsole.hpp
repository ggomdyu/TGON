#pragma once
#include "WindowsConsole.h"


template <typename T, typename ...Args>
void tgon::WindowsConsole::WriteLog( T&& arg, Args&& ...args )
{
#if defined( DEBUG ) | defined( _DEBUG )
	FillLogBuffer( std::forward<T>( arg ));

	WriteLog( args... );
#endif
}

