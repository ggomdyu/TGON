/*
* Author : Junho-Cha
* Date : 01/24/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <tgLib/Singleton.h>
#include "../Interface/IConsole.h"

#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#	undef WIN32_LEAN_AND_MEAN
#endif


namespace tgon
{


class WindowsConsole;
using ConsoleImpl = WindowsConsole;

class TGON_API WindowsConsole : 
	private IConsole
{
	class WindowsConsoleExecuter :
		public TSingleton<WindowsConsoleExecuter>
	{
	public:
		HANDLE GetOutputHandle( ) const;
	protected:
		WindowsConsoleExecuter( );
		virtual ~WindowsConsoleExecuter( );
	private:
		const HANDLE m_outputHandle;
	};

public:
	/*
		Commands
	*/
	template <typename _ValTy>
	static void Write( _ValTy&& arg );
	static void Write( const wchar_t* );
	static void Write( const char* );

	template <typename _ValTy>
	static void WriteLine( _ValTy&& arg );
	static void WriteLine( const wchar_t* );
	static void WriteLine( const char* );

protected:
	WindowsConsole( ) = delete;
	virtual ~WindowsConsole( ) = delete;
};


}


inline HANDLE tgon::WindowsConsole::WindowsConsoleExecuter::GetOutputHandle( ) const
{ 
	return m_outputHandle; 
}


template<typename _ValTy>
inline void tgon::WindowsConsole::Write( 
	_ValTy&& arg )
{
#if defined( DEBUG ) | defined( _DEBUG )
	Write( std::to_wstring( std::forward<_ValTy>( arg )).c_str( ));
#endif
}

inline void tgon::WindowsConsole::Write( 
	const wchar_t* str )
{
#if defined( DEBUG ) | defined( _DEBUG )
	WriteConsoleW(
		WindowsConsoleExecuter::Get( )->GetOutputHandle( ),
		str,
		std::wcslen( str ),
		nullptr,
		nullptr 
	);
#endif
}

inline void tgon::WindowsConsole::Write( 
	const char* str )
{
#if defined( DEBUG ) | defined( _DEBUG )
	WriteConsoleA(
		WindowsConsoleExecuter::Get( )->GetOutputHandle( ),
		str,
		std::strlen( str ),
		nullptr,
		nullptr
	);
#endif
}

template<typename _ValTy>
inline void tgon::WindowsConsole::WriteLine(
	_ValTy&& arg )
{
#if defined( DEBUG ) | defined( _DEBUG )
	WriteLine( std::to_wstring( std::forward<_ValTy>( arg )).c_str( ));
#endif
}


inline void tgon::WindowsConsole::WriteLine(
	const wchar_t* str )
{
#if defined( DEBUG ) | defined( _DEBUG )
	WriteConsoleW(
		WindowsConsoleExecuter::Get( )->GetOutputHandle( ),
		str,
		std::wcslen( str ),
		nullptr,
		nullptr 
	);
	WriteConsoleW(
		WindowsConsoleExecuter::Get( )->GetOutputHandle( ),
		L"\n",
		1,
		nullptr,
		nullptr 
	);
#endif
}

inline void tgon::WindowsConsole::WriteLine( 
	const char* str )
{
#if defined( DEBUG ) | defined( _DEBUG )
	WriteConsoleA(
		WindowsConsoleExecuter::Get( )->GetOutputHandle( ),
		str,
		std::strlen( str ),
		nullptr,
		nullptr
	);
	WriteConsoleA(
		WindowsConsoleExecuter::Get( )->GetOutputHandle( ),
		"\n",
		1,
		nullptr,
		nullptr
	);
#endif
}
