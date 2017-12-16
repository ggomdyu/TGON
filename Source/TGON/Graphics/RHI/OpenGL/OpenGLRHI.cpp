#include "PrecompiledHeader.pch"
#include "OpenGLRHI.h"
#include "OpenGLRHIUtility.h"

#ifdef _MSC_VER
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#   include <windows.h>
#   include <gl/GL.h>
#else
#   include <OpenGL/OpenGL.h>
#   include <OpenGL/gl.h>
#endif

#include "Core/Math/Color.h"

namespace tgon
{
namespace rhi
{

OpenGLRHI::OpenGLRHI(const std::shared_ptr<platform::Window>& window, const rhi::VideoMode& videoMode) :
    m_context(window, videoMode)
{
}

void OpenGLRHI::SetClearColor(const math::Color4f& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRHI::SetFillMode(FillMode fillMode)
{
    glPolygonMode(GL_FRONT_AND_BACK, ConvertFillModeToNative(fillMode));
}

void OpenGLRHI::SetCullMode(CullMode cullMode)
{
    glFrontFace(ConvertCullModeToNative(cullMode));
}

void OpenGLRHI::BeginScene(PrimitiveType primitiveType)
{
    glBegin(ConvertPrimitiveTypeToNative(primitiveType));
}

void OpenGLRHI::EndScene()
{
    glEnd();
}

void OpenGLRHI::ClearColorBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRHI::ClearColorDepthBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRHI::SwapBuffer()
{
//    ::SwapBuffers(m_context.dcHandle);
}

} /* namespace rhi */
} /* namespace tgon */
