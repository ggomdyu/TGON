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
#if defined( WIN32 ) | defined( WIN64 )
			MessageBoxA( GetFocus( ), ss.str().c_str( ), "Alert", MB_OK );
			ss.str( "" ); // clear
#elif
#error "msgstream support only Win32"
#endif
		}

		void operator<<( warn_traits )
		{
#if defined( WIN32 ) | defined( WIN64 )
			MessageBoxA( GetFocus(), ss.str().c_str( ), "Warning", MB_OK | MB_ICONEXCLAMATION );
			ss.str( "" ); // clear
#elif
#error "msgstream support only Win32"
#endif
		}

	private:
		std::stringstream ss;
		
	}
	static out;
	static msgstream::alert_traits alert;
	static msgstream::warn_traits warn;
}