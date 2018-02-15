#include "PrecompiledHeader.pch"

#include "OpenGLGraphics.h"
#include "OpenGLContext.h"

#include "../VertexBuffer.h"
#include "../Generic/GenericGraphicsType.h"
#include "../Generic/GenericVertexBuffer.h"

#include "Core/Math/Color.h"

#include <cassert>
#include <GL/glew.h>
#if BOOST_OS_WINDOWS
#elif BOOST_OS_MACOS
#   import <AppKit/NSOpenGL.h>
#   import <AppKit/NSOpenGLView.h>
#   import <AppKit/NSWindow.h>
#   import <OpenGL/OpenGL.h>
#endif

namespace tgon
{
namespace graphics
{

OpenGLGraphics::OpenGLGraphics(const VideoMode& videoMode, const std::shared_ptr<core::GenericWindow>& window) :
    m_context(videoMode, window)
{
    this->SetClearColor(videoMode.clearColor);
}

OpenGLGraphics::~OpenGLGraphics()
{
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
#if BOOST_OS_WINDOWS
    ::SwapBuffers(m_context.dcHandle);
#else
    CGLFlushDrawable([m_context.context CGLContextObj]);
#endif
}

std::shared_ptr<VertexBuffer> OpenGLGraphics::CreateVertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs)
{
    return std::make_shared<VertexBuffer>(data, dataBytes, isDynamicUsage, vertexBufferDescs);
}

} /* namespace graphics */
} /* namespace tgon */
