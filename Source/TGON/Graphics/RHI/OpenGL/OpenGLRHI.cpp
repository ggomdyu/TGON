#include "PrecompiledHeader.pch"
#include "OpenGLRHI.h"

#include <GL/glew.h>

#include "Core/Math/Color.h"
#include "Graphics/RHI/Base/BaseRHIType.h"

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
    static GLenum nativeFillModeTable[] =
    {
        GL_POINT,
        GL_LINE,
        GL_FILL
    };

    glPolygonMode(GL_FRONT_AND_BACK, nativeFillModeTable[static_cast<GLenum>(fillMode)]);
}

void OpenGLRHI::SetCullMode(CullMode cullMode)
{
    static GLenum nativeCullModeTable[] =
    {
        GL_CW,
        GL_CCW
    };

    glFrontFace(nativeCullModeTable[static_cast<GLenum>(cullMode)]);
}

void OpenGLRHI::EnalbleDepthTest()
{
    glEnable(GL_DEPTH_TEST);
}

void OpenGLRHI::DisableDepthTest()
{
    glDisable(GL_DEPTH_TEST);
}

void OpenGLRHI::BeginScene(PrimitiveType primitiveType)
{
    static GLenum nativePrimitiveTable[] =
    {
        GL_POINTS,
        GL_LINES,
        GL_LINE_STRIP,
        GL_TRIANGLES,
        GL_TRIANGLE_STRIP,
        GL_TRIANGLE_FAN,
    };

    glBegin(nativePrimitiveTable[static_cast<GLenum>(primitiveType)]);
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
    ::SwapBuffers(m_context.dcHandle);
}

} /* namespace rhi */
} /* namespace tgon */