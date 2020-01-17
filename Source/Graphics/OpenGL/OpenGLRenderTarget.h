/**
 * @file    OpenGLRenderTarget.h
 * @author  ggomdyu
 * @since   07/14/2018
 * @see     https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenFramebuffers.xhtml
 *          https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glFramebufferRenderbuffer.xhtml
 *          https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCheckFramebufferStatus.xhtml
 *          
 */

#pragma once
#if TGON_GRAPHICS_OPENGL
#include <GL/glew.h>

#include "Core/NonCopyable.h"
#include "Math/Extent.h"

namespace tgon
{
   
class OpenGLRenderTarget :
    private NonCopyable
{
/**@section Constructor */
protected:
    OpenGLRenderTarget();
    OpenGLRenderTarget(OpenGLRenderTarget&& rhs) noexcept;
    
/**@section Destructor */
protected:
    ~OpenGLRenderTarget();

/**@section Operator */
protected:
    OpenGLRenderTarget& operator=(OpenGLRenderTarget&& rhs) noexcept;
    
/**@section Method */
protected:
    static GLuint CreateColorBuffer(const FExtent2D& extent);
    static GLuint CreateDepthBuffer(const FExtent2D& extent, int32_t depthBits);
    static GLuint CreateDepthStencilBuffer(const FExtent2D& extent, int32_t depthBits, int32_t stencilBits);
    static GLuint CreateFrameBuffer();
    void Destroy();

/**@section Variable */
protected:
    FExtent2D m_extent;
    GLuint m_frameBufferHandle = 0;
    GLuint m_colorBufferHandle = 0;
    GLuint m_depthStencilBufferHandle = 0;
};
    
using PlatformRenderTarget = OpenGLRenderTarget;

} /* namespace tgon */
#endif
