/*
* Author : Cha Junho
* Date : 01/24/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Interface/IConsole.h"
#include "../../Utility/Windows/WindowsConsoleHelper.h"


#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#	undef WIN32_LEAN_AND_MEAN
#endif


namespace tgon
{


using ConsoleImpl = class WindowsConsole;

class TGON_API WindowsConsole : 
	private IConsole
{

public:
	/*
		Cons/Destructor
	*/
	WindowsConsole( ) = delete;

	virtual ~WindowsConsole( ) = delete;
	
	
	/*
		Commands
	*/
	// Write
	template<class _Ty>
	static void Write( _Ty&& str )
	{
#if defined ( _DEBUG ) || ( DEBUG )
		Write( std::forward<_Ty>( str ),
			std::is_array<typename std::remove_reference<_Ty>::type>( ));
#endif
	}

	template <std::size_t N>
	static void Write( _In_ const char( &str )[N], std::true_type )
	{
#if defined ( _DEBUG ) || ( DEBUG )
		WriteConsoleA(
			WindowsConsoleHelper::Get( )->GetConsoleHandle( ),
			str,
			N-1,
			nullptr,
			nullptr
		);
#endif
	}

	static void Write( _In_ const char* str, std::false_type )
	{
#if defined ( _DEBUG ) || ( DEBUG )
		WriteConsoleA(
			WindowsConsoleHelper::Get( )->GetConsoleHandle( ),
			str,
			std::strlen( str ),
			nullptr,
			nullptr
		);
#endif
	}

	template<class _Ty>
	static void Write( const _Ty& str, std::false_type )
	{
#if defined ( _DEBUG ) || ( DEBUG )
		const std::string strTemp = std::to_string( str );

		WriteConsoleA(
			WindowsConsoleHelper::Get( )->GetConsoleHandle( ),
			strTemp.c_str( ),
			strTemp.length( ),
			nullptr,
			nullptr
		);
#endif
	}

	template <std::size_t N>
	static void Write( _In_ const wchar_t( &str )[N], std::true_type )
	{
#if defined ( _DEBUG ) || ( DEBUG )
		WriteConsoleW(
			WindowsConsoleHelper::Get( )->GetConsoleHandle( ),
			str,
			N-1,
			nullptr,
			nullptr
		);
#endif
	}

	static void Write( _In_ const wchar_t* str, std::false_type )
	{
#if defined ( _DEBUG ) || ( DEBUG )
		WriteConsoleW(
			WindowsConsoleHelper::Get( )->GetConsoleHandle( ),
			str,
			std::wcslen( str ),
			nullptr,
			nullptr
		);
#endif
	}
};


}