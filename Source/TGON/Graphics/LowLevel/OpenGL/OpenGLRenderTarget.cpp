#include "PrecompiledHeader.h"

#include "OpenGLRenderTarget.h"

namespace tgon
{

RenderTargetImpl::RenderTargetImpl(int32_t width, int32_t height, int32_t multisampleLevel) :
    m_width(width),
    m_height(height)
{
}

RenderTargetImpl::~RenderTargetImpl()
{
    if (m_frameBufferHandle != 0)
    {
        glDeleteFramebuffers(1, &m_frameBufferHandle);
        m_frameBufferHandle = 0;
    }
}

void RenderTargetImpl::Use()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);
    glViewport(0, 0, m_width, m_height);
}

void RenderTargetImpl::Unuse()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint RenderTargetImpl::CreateRenderBuffer(GLenum format, int32_t width, int32_t height) const
{
    GLuint renderBuffer;
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);

    return renderBuffer;
}

GLuint RenderTargetImpl::CreateFrameBuffer() const
{
    GLuint frameBufferHandle;
    glGenFramebuffers(1, &frameBufferHandle);

    return frameBufferHandle;
}

} /* namespace tgon */