#include "PrecompiledHeader.h"

#include <GL/glew.h>
#if TGON_PLATFORM_MACOS
#   import <AppKit/NSOpenGL.h>
#   import <OpenGL/OpenGL.h>
#endif
#include <stb/stb_image.h>

#include "Core/Math/Color.h"

#include "../GraphicsType.h"
#include "OpenGLGraphics.h"
#include "OpenGLUtility.h"

#if TGON_PLATFORM_WINDOWS
#   pragma comment(lib, "glew32.lib")
#endif

namespace tgon
{
namespace
{

GLsizei GetVertexCountPerPrimitive(PrimitiveType primitiveType) noexcept
{
    return (primitiveType == PrimitiveType::Triangles) ? 3 :
           (primitiveType == PrimitiveType::Lines) ? 2 :
           (primitiveType == PrimitiveType::Points) ? 1 : 0;
}

} /* namespace */

GraphicsImpl::GraphicsImpl(const Window& displayTarget, const VideoMode& videoMode) :
    m_context(videoMode, displayTarget),
    m_vertexArrayHandle(0)
{
    // It is required because OpenGL expects (0, 0) coordinates to be on the left bottom side, but images usually left top side.
    stbi_set_flip_vertically_on_load(true);
    
    TGON_GL_ERROR_CHECK(glGenVertexArrays(1, &m_vertexArrayHandle));
    TGON_GL_ERROR_CHECK(glBindVertexArray(m_vertexArrayHandle));

    this->SetClearColor(videoMode.clearColor);
    this->SetCullMode(CullMode::CW);
    this->EnableDepthTest();
}

GraphicsImpl::~GraphicsImpl()
{
    if (m_vertexArrayHandle != 0)
    {
        TGON_GL_ERROR_CHECK(glBindVertexArray(m_vertexArrayHandle));
        TGON_GL_ERROR_CHECK(glDeleteVertexArrays(1, &m_vertexArrayHandle));
    }
}

void GraphicsImpl::SetClearColor(const Color4f& color)
{
    TGON_GL_ERROR_CHECK(glClearColor(color.r, color.g, color.b, color.a));
}

void GraphicsImpl::SetFillMode(FillMode fillMode)
{
    TGON_GL_ERROR_CHECK(glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(fillMode)));
}

void GraphicsImpl::SetCullMode(CullMode cullMode)
{
    TGON_GL_ERROR_CHECK(glFrontFace(static_cast<GLenum>(cullMode)));
}

void GraphicsImpl::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
    TGON_GL_ERROR_CHECK(glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLsizei>(width), static_cast<GLsizei>(height)));
}

void GraphicsImpl::EnableBlend()
{
    TGON_GL_ERROR_CHECK(glEnable(GL_BLEND));
}

void GraphicsImpl::EnableDepthTest()
{
    TGON_GL_ERROR_CHECK(glEnable(GL_DEPTH_TEST));
}

void GraphicsImpl::DisableBlend()
{
    TGON_GL_ERROR_CHECK(glDisable(GL_BLEND));
}

void GraphicsImpl::DisableDepthTest()
{
    TGON_GL_ERROR_CHECK(glDisable(GL_DEPTH_TEST));
}

void GraphicsImpl::ClearColorBuffer()
{
    TGON_GL_ERROR_CHECK(glClear(GL_COLOR_BUFFER_BIT));
}

void GraphicsImpl::ClearColorDepthBuffer()
{
    TGON_GL_ERROR_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GraphicsImpl::SwapBuffer()
{
    m_context.SwapBuffer();
}

void GraphicsImpl::DrawPrimitives(PrimitiveType primitiveType, int32_t primitiveCount)
{
    glDrawArrays(static_cast<GLenum>(primitiveType), 0, primitiveCount);
}
    
void GraphicsImpl::DrawIndexedPrimitives(PrimitiveType primitiveType, int32_t primitiveCount)
{
    glDrawElements(static_cast<GLenum>(primitiveType), GetVertexCountPerPrimitive(primitiveType) * primitiveCount, GL_UNSIGNED_INT, nullptr);
}

} /* namespace tgon */
