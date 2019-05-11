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

namespace tgon
{

class RenderTargetImpl final :
    private boost::noncopyable
{
/**@section Constructor */
public:
    RenderTargetImpl(int32_t width, int32_t height, int32_t multisampleLevel);
    
/**@section Destructor */
public:
    ~RenderTargetImpl();
    
/**@section Method */
public:
    void Use();
    void Unuse();

private:
    GLuint CreateRenderBuffer(GLenum format, int32_t width, int32_t height) const;
    GLuint CreateFrameBuffer() const;

/**@section Variable */
private:
    int32_t m_width;
    int32_t m_height;
    GLuint m_frameBufferHandle;
};

} /* namespace tgon */
