#include "PrecompiledHeader.h"

#include <array>
#if TGON_PLATFORM_MACOS
#   import <AppKit/NSOpenGL.h>
#   import <OpenGL/OpenGL.h>
#endif

#include "Core/Math/Color.h"

#include "OpenGLGraphics.h"
#include "../GraphicsType.h"
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
    m_context(videoMode, displayTarget)
{
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

void GraphicsImpl::DrawPrimitives(PrimitiveType primitiveType, int32_t startVertex, int32_t primitiveCount)
{
    glDrawElements(GL_TRIANGLES, GetVertexCountPerPrimitive(primitiveType), GL_UNSIGNED_INT, nullptr);
}

} /* namespace tgon */
