/**
 * @filename    GraphicsConfig.h
 * @author      ggomdyu
 * @since       05/08/2018
 */

#pragma once

#if TGON_USING_OPENGL
#   include "OpenGL/OpenGLGraphicsConfig.h"
#elif TGON_USING_DIRECT3D11
#   include "Direct3D11/Direct3D11GraphicsConfig.h"
#endif
