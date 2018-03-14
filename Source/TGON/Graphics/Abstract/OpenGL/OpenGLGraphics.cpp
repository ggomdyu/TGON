#include "PrecompiledHeader.pch"

#include "OpenGLGraphics.h"
#include "OpenGLGraphicsUtility.h"
#include "OpenGLContext.h"

#include "../Generic/GenericGraphicsType.h"
#include "../OpenGL/OpenGLVertexBuffer.h"
#include "../OpenGL/OpenGLIndexBuffer.h"
#include "../OpenGL/OpenGLTexture.h"

#include "Core/Math/Color.h"

#include <cassert>
#include <GL/glew.h>
#if TGON_PLATFORM_WINDOWS
#   pragma comment(lib, "glew32.lib")
#elif TGON_PLATFORM_MACOS
#   import <AppKit/NSOpenGL.h>
#   import <OpenGL/OpenGL.h>
#endif

namespace tgon
{
namespace graphics
{

OpenGLGraphics::OpenGLGraphics(const VideoMode& videoMode, const std::shared_ptr<core::GenericWindow>& window) :
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

void OpenGLGraphics::SetClearColor(const core::Color4f& color)
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
#if TGON_PLATFORM_WINDOWS
    ::SwapBuffers(m_context.dcHandle);
#elif TGON_PLATFORM_MACOS
    CGLFlushDrawable([m_context.context CGLContextObj]);
#endif
}

std::shared_ptr<GenericVertexBuffer> OpenGLGraphics::CreateVertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs)
{
    return std::make_shared<OpenGLVertexBuffer>(data, dataBytes, isDynamicUsage, vertexBufferDescs);
}

std::shared_ptr<GenericIndexBuffer> OpenGLGraphics::CreateIndexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage)
{
    return std::make_shared<OpenGLIndexBuffer>(data, dataBytes, isDynamicUsage);
}

} /* namespace graphics */
} /* namespace tgon */
