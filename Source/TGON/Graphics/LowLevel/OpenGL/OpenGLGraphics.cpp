#include "PrecompiledHeader.h"

#include <cassert>
#include <GL/glew.h>
#if TGON_PLATFORM_MACOS
#   import <AppKit/NSOpenGL.h>
#   import <OpenGL/OpenGL.h>
#endif

#include "Core/Math/Color.h"
#include "Core/Utility/Algorithm.h"

#include "../OpenGL/OpenGLVertexBuffer.h"
#include "../OpenGL/OpenGLIndexBuffer.h"
#include "../OpenGL/OpenGLTexture.h"

#include "OpenGLGraphics.h"
#include "OpenGLContext.h"
#include "OpenGLUtility.h"

#if TGON_PLATFORM_WINDOWS
#   pragma comment(lib, "glew32.lib")
#endif

namespace tgon
{

OpenGLGraphics::OpenGLGraphics(const VideoMode& videoMode, std::shared_ptr<Window> displayTarget) :
    m_context(videoMode, displayTarget)
{
    TGON_GL_ERROR_CHECK(glGenVertexArrays(1, &m_vertexArrayHandle));
    TGON_GL_ERROR_CHECK(glBindVertexArray(m_vertexArrayHandle));

    this->SetClearColor(videoMode.clearColor);
    this->SetCullMode(CullMode::CW);
    this->EnableDepthTest();
}

OpenGLGraphics::~OpenGLGraphics()
{
    if (m_vertexArrayHandle != 0)
    {
        TGON_GL_ERROR_CHECK(glBindVertexArray(m_vertexArrayHandle));
        TGON_GL_ERROR_CHECK(glDeleteVertexArrays(1, &m_vertexArrayHandle));
    }
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

void OpenGLGraphics::EnableBlend()
{
    TGON_GL_ERROR_CHECK(glEnable(GL_BLEND));
}

void OpenGLGraphics::EnableDepthTest()
{
    TGON_GL_ERROR_CHECK(glEnable(GL_DEPTH_TEST));
}

void OpenGLGraphics::DisableBlend()
{
    TGON_GL_ERROR_CHECK(glDisable(GL_BLEND));
}

void OpenGLGraphics::DisableDepthTest()
{
    TGON_GL_ERROR_CHECK(glDisable(GL_DEPTH_TEST));
}

void OpenGLGraphics::ClearColorBuffer()
{
    TGON_GL_ERROR_CHECK(glClear(GL_COLOR_BUFFER_BIT));
}

void OpenGLGraphics::ClearColorDepthBuffer()
{
    TGON_GL_ERROR_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void OpenGLGraphics::SwapBuffer()
{
    m_context.SwapBuffer();
}

void OpenGLGraphics::DrawPrimitives(PrimitiveType primitiveType, int32_t startVertex, int32_t primitiveCount)
{
    int32_t vertexCountPerPrimitive = 0;
    if (primitiveType == PrimitiveType::Triangles)
    {
        vertexCountPerPrimitive = primitiveCount * 3;
    }
    else if (primitiveType == PrimitiveType::Lines)
    {
        vertexCountPerPrimitive = primitiveCount * 2;
    }
    else if (primitiveType == PrimitiveType::Points)
    {
        vertexCountPerPrimitive = primitiveCount;
    }

    glDrawElements(GL_TRIANGLES, vertexCountPerPrimitive, GL_UNSIGNED_INT, nullptr);
}

} /* namespace tgon */
