#include "PrecompiledHeader.pch"

#include "OpenGLDynamicGraphics.h"
#include "OpenGLContext.h"

#include "../GraphicsType.h"

#include "Core/Math/Color.h"
#include "Graphics/RHI/GraphicsType.h"

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

OpenGLDynamicGraphics::OpenGLDynamicGraphics(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode) :
    m_context(window)
{
    this->SetClearColor(videoMode.clearColor);
}

OpenGLDynamicGraphics::~OpenGLDynamicGraphics()
{
}

void OpenGLDynamicGraphics::SetClearColor(const core::Color4f& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLDynamicGraphics::SetFillMode(FillMode fillMode)
{
    glPolygonMode(GL_FRONT_AND_BACK, ConvertFillModeToNative(fillMode));
}

void OpenGLDynamicGraphics::SetCullMode(CullMode cullMode)
{
    glFrontFace(ConvertCullModeToNative(cullMode));
}

void OpenGLDynamicGraphics::EnableBlend()
{
    glEnable(GL_BLEND);
}

void OpenGLDynamicGraphics::EnableDepthTest()
{
    glEnable(GL_DEPTH_TEST);
}

void OpenGLDynamicGraphics::DisableBlend()
{
    glDisable(GL_BLEND);
}

void OpenGLDynamicGraphics::DisableDepthTest()
{
    glDisable(GL_DEPTH_TEST);
}

void OpenGLDynamicGraphics::ClearColorBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLDynamicGraphics::ClearColorDepthBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLDynamicGraphics::SwapBuffer()
{
#if BOOST_OS_WINDOWS
    ::SwapBuffers(m_context.dcHandle);
#else
    CGLFlushDrawable([m_context->context CGLContextObj]);
#endif
}

} /* namespace graphics */
} /* namespace tgon */
