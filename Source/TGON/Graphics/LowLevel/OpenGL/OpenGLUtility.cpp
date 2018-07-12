#include "PrecompiledHeader.h"

#include "OpenGLUtility.h"

namespace tgon
{

GLuint CreateRenderBuffer(GLenum format, int32_t width, int32_t height)
{
    GLuint renderBuffer;
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
    
    return renderBuffer;
}
    
GLuint CreateFrameBuffer()
{
    GLuint frameBufferHandle;
    glGenFramebuffers(1, &frameBufferHandle);
    
    return frameBufferHandle;
}

} /* namespace tgon */
