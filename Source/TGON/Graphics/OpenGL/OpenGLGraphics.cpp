#include "PrecompiledHeader.h"

#include <stb_image.h>
#include <stb_image_write.h>

#include "OpenGLGraphics.h"
#include "OpenGLUtility.h"

namespace tgon
{

OpenGLGraphics::OpenGLGraphics(const Window& displayTarget, const VideoMode& videoMode) :
    m_context(displayTarget, videoMode),
    m_vertexArrayHandle(0)
{
    // It is required because OpenGL expects (0, 0) coordinates to be the left bottom side, but images usually left top side.
    stbi_set_flip_vertically_on_load(true);
    stbi_flip_vertically_on_write(true);
    
    this->SetDefaultGLRenderState();
    
    TGON_GL_ERROR_CHECK(glGenVertexArrays(1, &m_vertexArrayHandle));
    TGON_GL_ERROR_CHECK(glBindVertexArray(m_vertexArrayHandle));
}

OpenGLGraphics::~OpenGLGraphics()
{
    if (m_vertexArrayHandle != 0)
    {
        TGON_GL_ERROR_CHECK(glBindVertexArray(m_vertexArrayHandle));
        TGON_GL_ERROR_CHECK(glDeleteVertexArrays(1, &m_vertexArrayHandle));
        m_vertexArrayHandle = 0;
    }
}
    
void OpenGLGraphics::SetDefaultGLRenderState()
{
    this->EnableCullFace();
}

void OpenGLGraphics::SetScissorRect(const FRect& scissorRect)
{
    //TGON_GL_ERROR_CHECK();
    //glScissor(scissorRect.left, scissorRect.bottom, scissorRect.)
}

void OpenGLGraphics::SetClearColor(const Color4f& color)
{
    TGON_GL_ERROR_CHECK(glClearColor(color.r, color.g, color.b, color.a));
}

void OpenGLGraphics::SetFillMode(FillMode fillMode)
{
    TGON_GL_ERROR_CHECK(glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(fillMode)));
}

void OpenGLGraphics::SetCullMode(CullMode cullMode)
{
    TGON_GL_ERROR_CHECK(glFrontFace(static_cast<GLenum>(cullMode)));
}

void OpenGLGraphics::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
    TGON_GL_ERROR_CHECK(glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLsizei>(width), static_cast<GLsizei>(height)));
}
    
void OpenGLGraphics::SetBlendMode(BlendMode blendMode)
{
    switch (blendMode)
    {
    case BlendMode::Normal:
        TGON_GL_ERROR_CHECK(glBlendFunc(GL_ONE, GL_ZERO));
        TGON_GL_ERROR_CHECK(glBlendEquation(GL_FUNC_ADD));
        break;
            
    case BlendMode::Alpha:
        TGON_GL_ERROR_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        TGON_GL_ERROR_CHECK(glBlendEquation(GL_FUNC_ADD));
        break;
            
    case BlendMode::Additive:
        TGON_GL_ERROR_CHECK(glBlendFunc(GL_ONE, GL_ONE));
        TGON_GL_ERROR_CHECK(glBlendEquation(GL_FUNC_ADD));
        break;
            
    case BlendMode::Subtractive:
        TGON_GL_ERROR_CHECK(glBlendFunc(GL_ONE, GL_ONE));
        TGON_GL_ERROR_CHECK(glBlendEquation(GL_FUNC_REVERSE_SUBTRACT));
        break;
    }
}

void OpenGLGraphics::EnableCullFace()
{
    TGON_GL_ERROR_CHECK(glEnable(GL_CULL_FACE));
}
    
void OpenGLGraphics::EnableBlend()
{
    TGON_GL_ERROR_CHECK(glEnable(GL_BLEND));
}

void OpenGLGraphics::EnableDepthTest()
{
    TGON_GL_ERROR_CHECK(glEnable(GL_DEPTH_TEST));
}

void OpenGLGraphics::EnableScissorTest()
{
    TGON_GL_ERROR_CHECK(glEnable(GL_SCISSOR_TEST));
}
    
void OpenGLGraphics::DisableCullFace()
{
    TGON_GL_ERROR_CHECK(glDisable(GL_CULL_FACE));
}

void OpenGLGraphics::DisableBlend()
{
    TGON_GL_ERROR_CHECK(glDisable(GL_BLEND));
}

void OpenGLGraphics::DisableDepthTest()
{
    TGON_GL_ERROR_CHECK(glDisable(GL_DEPTH_TEST));
}

void OpenGLGraphics::DisableScissorTest()
{
    TGON_GL_ERROR_CHECK(glDisable(GL_SCISSOR_TEST));
}

void OpenGLGraphics::ClearColorBuffer()
{
    TGON_GL_ERROR_CHECK(glClear(GL_COLOR_BUFFER_BIT));
}

void OpenGLGraphics::ClearColorDepthBuffer()
{
    TGON_GL_ERROR_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void OpenGLGraphics::SwapBuffer()
{
    m_context.SwapBuffer();
}

void OpenGLGraphics::DrawPrimitives(PrimitiveType primitiveType, int32_t vertexCount)
{
    glDrawArrays(static_cast<GLenum>(primitiveType), 0, vertexCount);
}
    
void OpenGLGraphics::DrawIndexedPrimitives(PrimitiveType primitiveType, int32_t indexCount)
{
    glDrawElements(static_cast<GLenum>(primitiveType), indexCount, GL_UNSIGNED_INT, nullptr);
}

} /* namespace tgon */
