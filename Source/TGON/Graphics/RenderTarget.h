/**
 * @file    RenderTarget.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include "Math/Extent.h"

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
    using PlatformRenderTarget::PlatformRenderTarget;

    RenderTarget(const FExtent2D& extent, int32_t depthBits);
    
/**@section Method */
public:
    using PlatformRenderTarget::Use;
    using PlatformRenderTarget::Unuse;
};

} /* namespace tgon */
