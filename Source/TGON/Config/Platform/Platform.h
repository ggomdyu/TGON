/*
* 작성자 : 차준호
* 작성일 : 2016-01-28
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once

#if defined( linux ) || defined( __linux ) || defined( __linux__ )
	#define TGON_PLATFORM_LINUX

#elif defined( __ANDROID__ ) || defined( __ANDROID_API__ )
	#define TGON_PLATFORM_ANDROID

#elif defined( _WIN32 ) || defined( __WIN32__ ) || defined( WIN32 ) ||	\
		defined( _WIN64 ) || defined( __WIN64__ ) || defined( WIN64 )
	#define TGON_PLATFORM_WINDOWS

#elif defined( macintosh ) || defined( __APPLE__ ) || defined( __APPLE_CC__ )
	#define TGON_PLATFORM_MAC
#endif