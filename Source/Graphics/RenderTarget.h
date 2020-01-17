/**
 * @file    RenderTarget.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once

#if TGON_GRAPHICS_OPENGL
#   include "OpenGL/OpenGLRenderTarget.h"
#endif

namespace tgon
{

class RenderTarget :
    private PlatformRenderTarget
{
/**@section Constructor */
public:
    RenderTarget(const FExtent2D& extent, int32_t depthBits);

/**@section Method */
public:
    bool Initialize(const FExtent2D& extent, int32_t depthBits = 0, int32_t stencilBits = 0);
    void Use();
    void Unuse();
};

} /* namespace tgon */
