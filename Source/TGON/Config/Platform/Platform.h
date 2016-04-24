/*
* Author : Junho-Cha
* Date : 01/28/2016
* Latest author :
* Latest date :
*/

#pragma once


#if defined( linux ) || defined( __linux ) || defined( __linux__ )
	#define TGON_PLATFORM_LINUX

#elif defined( __ANDROID__ ) || defined( __ANDROID_API__ )
	#define TGON_PLATFORM_ANDROID

#elif defined( _WIN32 ) || defined( __WIN32__ ) || defined( WIN32 ) ||	\
		defined( _WIN64 ) || defined( __WIN64__ ) || defined( WIN64 )
	#define TGON_PLATFORM_WINDOWS

	// Disable the min and max macros that defined in <windows.h>
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif

#elif defined( macintosh ) || defined( __APPLE__ ) || defined( __APPLE_CC__ )
	#define TGON_PLATFORM_MAC
#endif