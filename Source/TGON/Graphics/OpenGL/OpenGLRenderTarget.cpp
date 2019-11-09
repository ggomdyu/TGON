#include "PrecompiledHeader.h"

#include <stdexcept>

#include "OpenGLRenderTarget.h"

#if TGON_GRAPHICS_OPENGL
namespace tgon
{

OpenGLRenderTarget::OpenGLRenderTarget(float width, float height, int32_t depthBits) :
    m_width(width),
    m_height(height),
    m_frameBufferHandle(this->CreateFrameBuffer()),
    m_colorBufferHandle(this->CreateColorBuffer(m_width, m_height)),
    m_depthStencilBufferHandle(this->CreateDepthStencilBuffer(m_width, m_height, depthBits))
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorBufferHandle, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilBufferHandle);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        throw std::runtime_error("Failed to create frame buffer.");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

OpenGLRenderTarget::OpenGLRenderTarget(OpenGLRenderTarget&& rhs) noexcept :
    m_width(rhs.m_width),
    m_height(rhs.m_height),
    m_colorBufferHandle(rhs.m_colorBufferHandle),
    m_depthStencilBufferHandle(rhs.m_depthStencilBufferHandle),
    m_frameBufferHandle(rhs.m_frameBufferHandle)
{
    rhs.m_width = 0;
    rhs.m_height = 0;
    rhs.m_colorBufferHandle = 0;
    rhs.m_depthStencilBufferHandle = 0;
    rhs.m_frameBufferHandle = 0;
}

OpenGLRenderTarget::~OpenGLRenderTarget()
{
    this->Destroy();
}
    
OpenGLRenderTarget& OpenGLRenderTarget::operator=(OpenGLRenderTarget&& rhs) noexcept
{
    this->Destroy();
    
    m_width = rhs.m_width;
    m_height = rhs.m_height;
    m_colorBufferHandle = rhs.m_colorBufferHandle;
    m_depthStencilBufferHandle = rhs.m_depthStencilBufferHandle;
    m_frameBufferHandle = rhs.m_frameBufferHandle;
    
    rhs.m_width = 0;
    rhs.m_height = 0;
    rhs.m_colorBufferHandle = 0;
    rhs.m_depthStencilBufferHandle = 0;
    rhs.m_frameBufferHandle = 0;
    
    return *this;
}

void OpenGLRenderTarget::Use()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);
    glViewport(0, 0, static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height));
}

void OpenGLRenderTarget::Unuse()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, m_colorBufferHandle);
}

GLuint OpenGLRenderTarget::CreateColorBuffer(float width, float height)
{
    GLuint colorBuffer;
    glGenTextures(1, &colorBuffer);
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return colorBuffer;
}

GLuint OpenGLRenderTarget::CreateDepthBuffer(float width, float height, int32_t depthBits) const
{
    GLuint renderBuffer;
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, depthBits == 32 ? GL_DEPTH_COMPONENT32 : depthBits == 24 ? GL_DEPTH_COMPONENT24 : GL_DEPTH_COMPONENT16, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    return renderBuffer;
}

GLuint OpenGLRenderTarget::CreateDepthStencilBuffer(float width, float height, int32_t depthBits) const
{
    GLuint renderBuffer;
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, depthBits == 32 ? GL_DEPTH32F_STENCIL8 : GL_DEPTH24_STENCIL8, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    return renderBuffer;
}

GLuint OpenGLRenderTarget::CreateFrameBuffer() const
{
    GLuint frameBufferHandle;
    glGenFramebuffers(1, &frameBufferHandle);

    return frameBufferHandle;
}

void OpenGLRenderTarget::Destroy()
{
    if (m_colorBufferHandle != 0)
    {
        glDeleteTextures(1, &m_colorBufferHandle);
        m_colorBufferHandle = 0;
    }
    
    if (m_depthStencilBufferHandle != 0)
    {
        glDeleteRenderbuffers(1, &m_depthStencilBufferHandle);
        m_depthStencilBufferHandle = 0;
    }
    
    if (m_frameBufferHandle != 0)
    {
        glDeleteFramebuffers(1, &m_frameBufferHandle);
        m_frameBufferHandle = 0;
    }
}
    
} /* namespace tgon */
#endif
