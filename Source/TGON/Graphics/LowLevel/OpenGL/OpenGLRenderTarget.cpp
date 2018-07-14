#include "PrecompiledHeader.h"

#include "OpenGLRenderTarget.h"
#include "OpenGLUtility.h"

namespace tgon
{

class Framebuffer
{
public:
    Framebuffer(int32_t width, int32_t height);
    
private:
    GLuint m_frameBufferHandle;
    GLuint m_colorRenderBufferHandle;
    GLuint m_depthRenderBufferHandle;
};
    
Framebuffer::Framebuffer(int32_t width, int32_t height) :
    m_colorRenderBufferHandle(CreateRenderBuffer(GL_RGBA, width, height)),
    m_depthRenderBufferHandle(CreateRenderBuffer(GL_DEPTH_COMPONENT16, width, height))
{
}

RenderTargetImpl::RenderTargetImpl(int32_t width, int32_t height, int32_t multisampleLevel) :
    m_width(width),
    m_height(height)
{
}

void RenderTargetImpl::Use()
{
//    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);
    glViewport(0, 0, m_width, m_height);
}

void RenderTargetImpl::Unuse()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} /* namespace tgon */
