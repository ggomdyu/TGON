#include "PrecompiledHeader.h"

#if TGON_GRAPHICS_OPENGL
#include <stdexcept>

#include "Diagnostics/Debug.h"

#include "../RenderTarget.h"

namespace tgon
{

OpenGLRenderTarget::OpenGLRenderTarget() :
    m_frameBufferHandle(CreateFrameBuffer())
{
}

OpenGLRenderTarget::OpenGLRenderTarget(OpenGLRenderTarget&& rhs) noexcept :
    m_extent(rhs.m_extent),
    m_frameBufferHandle(rhs.m_frameBufferHandle),
    m_colorBufferHandle(rhs.m_colorBufferHandle),
    m_depthStencilBufferHandle(rhs.m_depthStencilBufferHandle)
{
}

OpenGLRenderTarget::~OpenGLRenderTarget()
{
    this->Destroy();
}
    
OpenGLRenderTarget& OpenGLRenderTarget::operator=(OpenGLRenderTarget&& rhs) noexcept
{
    std::swap(m_frameBufferHandle, rhs.m_frameBufferHandle);
    std::swap(m_colorBufferHandle, rhs.m_colorBufferHandle);
    std::swap(m_depthStencilBufferHandle, rhs.m_depthStencilBufferHandle);

    m_extent = rhs.m_extent;
    
    return *this;
}

bool RenderTarget::Initialize(const FExtent2D& extent, int32_t depthBits, int32_t stencilBits)
{
    m_colorBufferHandle = CreateColorBuffer(extent);
    m_depthStencilBufferHandle = CreateDepthStencilBuffer(extent, depthBits, stencilBits);

    //glNamedFramebufferTexture2DEXT(m_frameBufferHandle, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorBufferHandle, 0);
    //glNamedFramebufferRenderbuffer(m_frameBufferHandle, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilBufferHandle);
    //glCheckNamedFramebufferStatus(m_frameBufferHandle, GL_FRAMEBUFFER);

    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorBufferHandle, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilBufferHandle);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        return false;
    }

    return true;
}

void RenderTarget::Use()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);
    glViewport(0, 0, static_cast<GLsizei>(m_extent.width), static_cast<GLsizei>(m_extent.height));
}

void RenderTarget::Unuse()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint OpenGLRenderTarget::CreateColorBuffer(const FExtent2D& extent)
{
    GLuint colorBufferHandle;
    glGenTextures(1, &colorBufferHandle);
    glBindTexture(GL_TEXTURE_2D, colorBufferHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<GLsizei>(extent.width), static_cast<GLsizei>(extent.height), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    return colorBufferHandle;
}

GLuint OpenGLRenderTarget::CreateDepthBuffer(const FExtent2D& extent, int32_t depthBits)
{
    Debug::Assert(depthBits == 32 || depthBits == 24 || depthBits == 16);

    GLuint depthBufferHandle;
    glGenRenderbuffers(1, &depthBufferHandle);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBufferHandle);
    glRenderbufferStorage(GL_RENDERBUFFER, depthBits == 32 ? GL_DEPTH_COMPONENT32 : depthBits == 24 ? GL_DEPTH_COMPONENT24 : GL_DEPTH_COMPONENT16, static_cast<GLsizei>(extent.width), static_cast<GLsizei>(extent.height));
    //glNamedRenderbufferStorage(depthBufferHandle, depthBits == 32 ? GL_DEPTH_COMPONENT32 : depthBits == 24 ? GL_DEPTH_COMPONENT24 : GL_DEPTH_COMPONENT16, static_cast<GLsizei>(extent.width), static_cast<GLsizei>(extent.height));
    
    return depthBufferHandle;
}

GLuint OpenGLRenderTarget::CreateDepthStencilBuffer(const FExtent2D& extent, int32_t depthBits, int32_t stencilBits)
{
    Debug::Assert((depthBits == 32 || depthBits == 24) && stencilBits == 8);

    GLuint depthStencilBuffer;
    glGenRenderbuffers(1, &depthStencilBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthStencilBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, depthBits == 32 ? GL_DEPTH32F_STENCIL8 : GL_DEPTH24_STENCIL8, static_cast<GLsizei>(extent.width), static_cast<GLsizei>(extent.height));

    return depthStencilBuffer;
}

GLuint OpenGLRenderTarget::CreateFrameBuffer()
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
