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
   
class TGON_API OpenGLRenderTarget :
    private boost::noncopyable
{
/**@section Constructor */
public:
    OpenGLRenderTarget(float width, float height, int32_t depthBits);
    OpenGLRenderTarget(OpenGLRenderTarget&& rhs) noexcept;
    
/**@section Destructor */
public:
    ~OpenGLRenderTarget();

/**@section Operator */
public:
    OpenGLRenderTarget& operator=(OpenGLRenderTarget&& rhs) noexcept;
    
/**@section Method */
public:
    void Use();
    void Unuse();

private:
    GLuint CreateColorBuffer(float width, float height);
    GLuint CreateDepthBuffer(float width, float height, int32_t depthBits) const;
    GLuint CreateDepthStencilBuffer(float width, float height, int32_t depthBits) const;
    GLuint CreateFrameBuffer() const;
    void Destroy();

/**@section Variable */
private:
    float m_width;
    float m_height;
    GLuint m_colorBufferHandle;
    GLuint m_depthStencilBufferHandle;
    GLuint m_frameBufferHandle;
};
    
using PlatformRenderTarget = OpenGLRenderTarget;

} /* namespace tgon */
