/*
* Author : Junho-Cha
* Date : 2016-04-03
* Latest author :
* Latest date :
*/

#pragma once
#include "Platform.h"

#define TGON_WINDOWS_USING_DIRECTX9

#ifdef TGON_PLATFORM_WINDOWS
	#include <sdkddkver.h>
	// Using Windows version XP or lower?
	#if ( WINVER <= 0x0501 ) || ( _WIN32_WINNT <= 0x0501 )
		#define TGON_WINDOWS_USING_DIRECTX9
	#endif	

	#ifdef TGON_WINDOWS_USING_DIRECTX9 // Special case
		#include "../../Graphics/D3d9Device.h"
	#elif TGON_WINDOWS_USING_OPENGL // Special case
		#include "../../Graphics/OpenGLDevice.h"
	#else // Best choice
		#include "../../Graphics/D3d11Device.h"
	#endif

#elif defined( TGON_PLATFORM_LINUX )
	#include "../../Graphics/OpenGLDevice.h"

#elif defined( TGON_PLATFORM_ANDROID )
	#include "../../Graphics/OpenGLESDevice.h"
#endif