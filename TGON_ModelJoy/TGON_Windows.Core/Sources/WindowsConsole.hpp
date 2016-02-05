#pragma once
#include "WindowsConsole.h"


template <typename T, typename ...Args>
void tgon::WindowsConsole::Write( T&& arg, Args&& ...args )
{
#if defined( DEBUG ) | defined( _DEBUG )
	FillLogBuffer( std::forward<T>( arg ));

	Write( args... );
#endif
}


template <typename T, typename ...Args>
void tgon::WindowsConsole::WriteLine( T&& arg, Args&& ...args )
{
#if defined( DEBUG ) | defined( _DEBUG )
	FillLogBuffer( std::forward<T>( arg ));

	WriteLine( args... );
#endif
}

#if defined( DEBUG ) | defined( _DEBUG )
template<class T>
inline void tgon::WindowsConsole::FillLogBuffer( T&& arg )
{
	m_buf += std::to_wstring( std::forward<T>( arg ));
};


inline void tgon::WindowsConsole::FillLogBuffer( const wchar_t* arg )
{
	m_buf += arg;
}
#endif