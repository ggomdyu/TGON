#include "PrecompiledHeader.h"

#include <stdexcept>

#include "OpenGLRenderTarget.h"

#include "../RenderTargetType.h"

namespace tgon
{

OpenGLRenderTarget::OpenGLRenderTarget(const RenderTargetProperty& renderTargetProperty) :
    m_width(renderTargetProperty.width),
    m_height(renderTargetProperty.height),
    m_frameBufferHandle(this->CreateFrameBuffer()),
    m_colorBufferHandle(0),
    m_depthStencilBufferHandle(0)
    
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);
    
    m_colorBufferHandle = this->CreateColorBuffer(m_width, m_height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorBufferHandle, 0);
    
    m_depthStencilBufferHandle = this->CreateDepthStencilBuffer(m_width, m_height);
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
    m_depthBufferHandle(rhs.m_depthBufferHandle),
    m_depthStencilBufferHandle(rhs.m_depthStencilBufferHandle),
    m_frameBufferHandle(rhs.m_frameBufferHandle)
{
    rhs.m_width = 0;
    rhs.m_height = 0;
    rhs.m_colorBufferHandle = 0;
    rhs.m_depthBufferHandle = 0;
    rhs.m_depthStencilBufferHandle = 0;
    rhs.m_frameBufferHandle = 0;
}

OpenGLRenderTarget::~OpenGLRenderTarget()
{
    this->Destroy();
}
    
OpenGLRenderTarget& OpenGLRenderTarget::operator=(OpenGLRenderTarget&& rhs)
{
    this->Destroy();
    
    m_width = rhs.m_width;
    m_height = rhs.m_height;
    m_colorBufferHandle = rhs.m_colorBufferHandle;
    m_depthBufferHandle = rhs.m_depthBufferHandle;
    m_depthStencilBufferHandle = rhs.m_depthStencilBufferHandle;
    m_frameBufferHandle = rhs.m_frameBufferHandle;
    
    rhs.m_width = 0;
    rhs.m_height = 0;
    rhs.m_colorBufferHandle = 0;
    rhs.m_depthBufferHandle = 0;
    rhs.m_depthStencilBufferHandle = 0;
    rhs.m_frameBufferHandle = 0;
    
    return *this;
}

void OpenGLRenderTarget::Use()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);
    glViewport(0, 0, m_width, m_height);
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return colorBuffer;
}

GLuint OpenGLRenderTarget::CreateDepthBuffer(float width, float height) const
{
    GLuint renderBuffer;
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    return renderBuffer;
}

GLuint OpenGLRenderTarget::CreateDepthStencilBuffer(float width, float height) const
{
    GLuint renderBuffer;
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
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
    
    if (m_depthBufferHandle != 0)
    {
        glDeleteRenderbuffers(1, &m_depthBufferHandle);
        m_depthBufferHandle = 0;
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
