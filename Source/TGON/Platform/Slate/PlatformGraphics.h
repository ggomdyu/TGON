/*
* Author : Junho-Cha
* Date : 04/03/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../Platform/Config/Platform.h"


#define TGON_WINDOWS_USING_DIRECTX9 1


#if BOOST_OS_WINDOWS
	#include <sdkddkver.h>

	// Using Windows version XP or lower?
	#if ( WINVER <= 0x0501 ) || ( _WIN32_WINNT <= 0x0501 )
		#define TGON_WINDOWS_USING_DIRECTX9
	#endif	

	#if TGON_WINDOWS_USING_DIRECTX9
		#include "../Graphics/Direct3D9/D3d9Graphics.h"
	#elif TGON_WINDOWS_USING_OPENGL
		#include "../Graphics/OpenGL/OpenGLGraphics.h"
	#else // Best Choice
		#include "../Graphics/Direct3D11/D3d11Graphics.h"
	#endif

#elif BOOST_OS_LINUX
	#include "../Graphics/OpenGL/OpenGLGraphics.h"

#elif BOOST_OS_ANDROID
	#include "../Graphics/OpenGL/OpenGLESGraphics.h"
#endif