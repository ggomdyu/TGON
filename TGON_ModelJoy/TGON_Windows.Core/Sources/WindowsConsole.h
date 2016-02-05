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
	typedef WindowsConsole ConsoleImpl;
	
	class WindowsConsole
	{
	public:
		template <typename T, typename ...Args>
		static void Write( T&& arg, Args&& ...args );

		template <typename T, typename ...Args>
		static void WriteLine( T&& arg, Args&& ...args );

#if defined( DEBUG ) | defined( _DEBUG )
	private:
		template<class T>
		inline static void FillLogBuffer( T&& arg );
		inline static void FillLogBuffer( const wchar_t* arg );
		
		static void Write( );
		static void WriteLine( );

	private:
		static	std::wstring	m_buf;
#endif
	};


}

#include "WindowsConsole.hpp"