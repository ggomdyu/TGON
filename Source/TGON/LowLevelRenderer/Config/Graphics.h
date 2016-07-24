/*
* Author : Junho-Cha
* Date : 04/03/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <boost/predef.h>

#define TGON_FORCE_TO_DIRECTX9 1

#if BOOST_OS_WINDOWS
#	include <sdkddkver.h>

// Select DX9 if Windows version is XP or lower or forced
#	if ((( WINVER <= 0x0501 ) || ( _WIN32_WINNT <= 0x0501 )) && \
		!TGON_FORCE_TO_OPENGL ) || TGON_FORCE_TO_DIRECTX9
#		define TGON_GRAPHICS_DIRECTX9 1
#	elif TGON_FORCE_TO_OPENGL
#		define TGON_GRAPHICS_OPENGL 1
#	else
#		define TGON_GRAPHICS_DIRECTX11 1
#	endif

#elif BOOST_OS_LINUX
#	define TGON_GRAPHICS_OPENGL 1
#elif BOOST_OS_ANDROID
#	define TGON_GRAPHICS_OPENGLES 1
#endif