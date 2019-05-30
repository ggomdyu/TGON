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
#include <boost/noncopyable.hpp>
#include <GL/glew.h>

#include "Platform/Config.h"

namespace tgon
{
    
struct RenderTargetProperty;

class TGON_API OpenGLRenderTarget :
    private boost::noncopyable
{
/**@section Constructor */
public:
    OpenGLRenderTarget(const RenderTargetProperty& renderTargetProperty);
    OpenGLRenderTarget(OpenGLRenderTarget&& rhs) noexcept;
    
/**@section Destructor */
public:
    ~OpenGLRenderTarget();

/**@section Operator */
public:
    OpenGLRenderTarget& operator=(OpenGLRenderTarget&& rhs);
    
/**@section Method */
public:
    void Use();
    void Unuse();

private:
    GLuint CreateColorBuffer(float width, float height);
    GLuint CreateDepthBuffer(float width, float height) const;
    GLuint CreateDepthStencilBuffer(float width, float height) const;
    GLuint CreateFrameBuffer() const;
    void Destroy();

/**@section Variable */
private:
    int32_t m_width;
    int32_t m_height;
    GLuint m_colorBufferHandle;
    GLuint m_depthBufferHandle;
    GLuint m_depthStencilBufferHandle;
    GLuint m_frameBufferHandle;
};
    
using PlatformRenderTarget = OpenGLRenderTarget;

} /* namespace tgon */
