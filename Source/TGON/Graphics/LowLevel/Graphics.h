/**
 * @file    Graphics.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include "Core/Platform/Config.h"

#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLGraphics.h"
#endif

namespace tgon
{

class TGON_API Graphics final :
    private PlatformGraphics
{
/* @section Public constructor */
public:
    using PlatformGraphics::PlatformGraphics;
    
/* @section Public method */
public:
    using PlatformGraphics::SetClearColor;
    using PlatformGraphics::SetFillMode;
    using PlatformGraphics::SetCullMode;
    using PlatformGraphics::SetViewport;
    using PlatformGraphics::SetBlendMode;
    using PlatformGraphics::EnableBlend;
    using PlatformGraphics::EnableDepthTest;
    using PlatformGraphics::DisableBlend;
    using PlatformGraphics::DisableDepthTest;
    using PlatformGraphics::ClearColorBuffer;
    using PlatformGraphics::ClearColorDepthBuffer;
    using PlatformGraphics::SwapBuffer;
    using PlatformGraphics::DrawPrimitives;
    using PlatformGraphics::DrawIndexedPrimitives;
};

} /* namespace tgon */
