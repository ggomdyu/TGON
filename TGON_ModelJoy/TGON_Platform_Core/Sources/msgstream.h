#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-11
* 최종 수정 : 
* 최종 수정일 :
*/

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <Windows.h>
	#include <sstream>
#endif

namespace msg
{
	class msgstream
	{
	public:
		class warn_traits {};
		class alert_traits {};

	public:
		template <typename T>
		msgstream& operator<<( const T& type ) {
			ss << type;
			return *this;
		}

		void operator<<( alert_traits )
		{
#ifdef PLATFORM_WINDOWS_OS
			MessageBoxA( GetFocus( ), ss.str( ).c_str( ), "Alert", MB_OK );
			ss.str( "" ); // clear all buffer
#elif
#error "msgstream support only Win32"
#endif
		}

		void operator<<( warn_traits )
		{
#ifdef PLATFORM_WINDOWS_OS
			MessageBoxA( GetFocus(), ss.str( ).c_str( ), "Warning", MB_OK | MB_ICONEXCLAMATION );
			ss.str( "" ); // clear all buffer
#elif
#error "msgstream support only Win32"
#endif
		}

	private:
		std::stringstream ss;
		
	};

	extern msgstream out;
	extern msgstream::alert_traits alert;
	extern msgstream::warn_traits warn;
}