/**
 * @file    RenderTarget.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include "Core/Platform/Config.h"

#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLRenderTarget.h"
#endif

namespace tgon
{

class TGON_API RenderTarget final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    RenderTarget(int32_t width, int32_t height, int32_t multisampleLevel);
    
/* @section Public destructor */
public:
    ~RenderTarget() = default;
    
/* @section Public method */
public:
    void Use();
    void Unuse();
    
/* @section Private variable */
private:
    RenderTargetImpl m_renderTargetImpl;
};

} /* namespace tgon */
