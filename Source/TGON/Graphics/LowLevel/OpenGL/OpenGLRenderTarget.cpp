#include "PrecompiledHeader.h"

#include "OpenGLRenderTarget.h"

namespace tgon
{

RenderTargetImpl::RenderTargetImpl(int32_t width, int32_t height, int32_t multisampleLevel) :
    m_width(width),
    m_height(height),
    m_colorRenderBufferHandle(this->CreateRenderBuffer(GL_RGBA, width, height)),
    m_depthRenderBufferHandle(this->CreateRenderBuffer(GL_DEPTH_COMPONENT16, width, height))
{
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
    
GLuint RenderTargetImpl::CreateFrameBufferHandle() const
{
    GLuint frameBufferHandle;
    glGenFramebuffers(1, &frameBufferHandle);
    
    return frameBufferHandle;
}

} /* namespace tgon */
