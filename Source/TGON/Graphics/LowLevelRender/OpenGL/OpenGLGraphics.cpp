#include "PrecompiledHeader.pch"

#include <cassert>
#include <GL/glew.h>
#if TGON_PLATFORM_MACOS
#   import <AppKit/NSOpenGL.h>
#   import <OpenGL/OpenGL.h>
#endif

#include "Core/Math/Color.h"

#include "../Generic/GenericGraphicsType.h"
#include "../OpenGL/OpenGLVertexBuffer.h"
#include "../OpenGL/OpenGLIndexBuffer.h"
#include "../OpenGL/OpenGLTexture.h"

#include "OpenGLGraphics.h"
#include "OpenGLGraphicsUtility.h"
#include "OpenGLContext.h"

#if TGON_PLATFORM_WINDOWS
#   pragma comment(lib, "glew32.lib")
#endif

namespace tgon
{

OpenGLGraphics::OpenGLGraphics(const VideoMode& videoMode, const std::shared_ptr<GenericWindow>& window) :
    m_context(videoMode, window)
{
    glGenVertexArrays(1, &m_vertexArrayHandle);
    glBindVertexArray(m_vertexArrayHandle);

    this->SetClearColor(videoMode.clearColor);
    this->SetCullMode(CullMode::CW);
    this->EnableDepthTest();
}

OpenGLGraphics::~OpenGLGraphics()
{
    glBindVertexArray(m_vertexArrayHandle);
    glDeleteVertexArrays(1, &m_vertexArrayHandle);
}

void OpenGLGraphics::SetClearColor(const Color4f& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLGraphics::SetFillMode(FillMode fillMode)
{
    glPolygonMode(GL_FRONT_AND_BACK, ConvertFillModeToNative(fillMode));
}

void OpenGLGraphics::SetCullMode(CullMode cullMode)
{
    glFrontFace(ConvertCullModeToNative(cullMode));
}

void OpenGLGraphics::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
    glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLsizei>(width), static_cast<GLsizei>(height));
}

void OpenGLGraphics::EnableBlend()
{
    glEnable(GL_BLEND);
}

void OpenGLGraphics::EnableDepthTest()
{
    glEnable(GL_DEPTH_TEST);
}

void OpenGLGraphics::DisableBlend()
{
    glDisable(GL_BLEND);
}

void OpenGLGraphics::DisableDepthTest()
{
    glDisable(GL_DEPTH_TEST);
}

void OpenGLGraphics::ClearColorBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLGraphics::ClearColorDepthBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLGraphics::SwapBuffer()
{
    m_context.SwapBuffer();
}

} /* namespace tgon */