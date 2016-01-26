/*
* 작성자 : 차준호
* 작성일 : 2016-01-24
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <iostream>
#include <string>

namespace tgon {

	class WindowsConsole;
	typedef WindowsConsole Console;

	class WindowsConsole
	{
	public:
		template <typename T, typename ...Args>
		static void WriteLog( T&& arg, Args&& ...args );

#if defined( DEBUG ) | defined( _DEBUG )
	private:
		template<class T>
		static void FillLogBuffer( T&& arg )				{ g_buf += std::to_wstring( std::forward<T>( arg )); };
		static void FillLogBuffer( const wchar_t* arg )	{ g_buf += arg; }
		
		static void WriteLog( );

	private:
		static	std::wstring			g_buf;
#endif
	};
}

#include "WindowsConsole.hpp"