/*
* Author : Junho-Cha
* Date : 04/03/2016
* Latest author :
* Latest date :
*/

#pragma once

// We support only DirectX9 now... ;(
#define TGON_FORCE_TO_DIRECTX9 1
#include <tgLib/Graphics.h>

#if TGON_GRAPHICS_DIRECTX9
	#include "../Graphics/Direct3D9/D3d9Graphics.h"
#elif TGON_GRAPHICS_OPENGL
#elif TGON_GRAPHICS_OPENGLES
#endif