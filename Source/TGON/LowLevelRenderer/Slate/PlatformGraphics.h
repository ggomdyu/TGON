/*
* Author : Cha Junho
* Date : 04/03/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Config/Graphics.h"

#if TGON_GRAPHICS_DIRECTX9
	#include "../Graphics/Direct3D9/D3d9Graphics.h"
#elif TGON_GRAPHICS_OPENGL
#elif TGON_GRAPHICS_OPENGLES
#endif