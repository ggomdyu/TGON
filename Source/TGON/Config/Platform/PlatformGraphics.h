/*
* Author : Junho-Cha
* Date : 04/03/2016
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

	#ifdef TGON_WINDOWS_USING_DIRECTX9
		#include "../../Graphics/D3d9Graphics.h"
	#elif TGON_WINDOWS_USING_OPENGL
		#include "../../Graphics/OpenGLGraphics.h"
	#else // Best Choice
		#include "../../Graphics/D3d11Graphics.h"
	#endif

#elif defined( TGON_PLATFORM_LINUX )
	#include "../../Graphics/OpenGLGraphics.h"

#elif defined( TGON_PLATFORM_ANDROID )
	#include "../../Graphics/OpenGLESGraphics.h"
#endif