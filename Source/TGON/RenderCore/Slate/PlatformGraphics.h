/*
* Author : Cha Junho
* Date : 04/03/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Config/Graphics.h"

#if TGON_GRAPHICS_DIRECT3D9
#	include "../Graphics/Direct3D9/D3D9GraphicsDevice.h"
#elif TGON_GRAPHICS_OPENGL
#	include "../Graphics/OpenGL/OpenGLGraphicsDevice.h"
#elif TGON_GRAPHICS_OPENGLES
#endif