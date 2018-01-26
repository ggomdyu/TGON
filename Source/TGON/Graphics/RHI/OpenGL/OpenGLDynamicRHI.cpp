#include "PrecompiledHeader.pch"

#include "OpenGLDynamicRHI.h"
#include "OpenGLContext.h"

#include "../RHIType.h"

#include "Core/Math/Color.h"
#include "Graphics/RHI/RHIType.h"

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

OpenGLDynamicRHI::OpenGLDynamicRHI(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode) :
    m_context(std::make_unique<OpenGLContext>(window, videoMode))
{
    glGenVertexArrays(1, &m_vertexArray);
    glBindVertexArray(m_vertexArray);
}

OpenGLDynamicRHI::~OpenGLDynamicRHI()
{
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_vertexArray);
}

void OpenGLDynamicRHI::SetClearColor(const core::Color4f& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLDynamicRHI::SetFillMode(FillMode fillMode)
{
    static constexpr GLenum nativeFillModeTable[] =
    {
        GL_POINT,
        GL_LINE,
        GL_FILL
    };

    glPolygonMode(GL_FRONT_AND_BACK, nativeFillModeTable[static_cast<GLenum>(fillMode)]);
}

void OpenGLDynamicRHI::SetCullMode(CullMode cullMode)
{
    static constexpr GLenum nativeCullModeTable[] =
    {
        GL_CW,
        GL_CCW
    };

    glFrontFace(nativeCullModeTable[static_cast<GLenum>(cullMode)]);
}

void OpenGLDynamicRHI::EnableBlend()
{
    glEnable(GL_BLEND);
}

void OpenGLDynamicRHI::EnableDepthTest()
{
    glEnable(GL_DEPTH_TEST);
}

void OpenGLDynamicRHI::DisableBlend()
{
    glDisable(GL_BLEND);
}

void OpenGLDynamicRHI::DisableDepthTest()
{
    glDisable(GL_DEPTH_TEST);
}

//VideoBuffer OpenGLDynamicRHI::CreateVideoBuffer(VideoBufferType videoBufferType, std::size_t bufferSize)
//{
//    static std::atomic<int> bufferIndex;
//
//    GLuint videoBuffer;
//    glCreateBuffers(bufferIndex++, &videoBuffer);
//
//    return reinterpret_cast<VideoBuffer>(videoBuffer);
//}

void OpenGLDynamicRHI::BeginScene(PrimitiveType primitiveType)
{
    static constexpr GLenum nativePrimitiveTable[] =
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

void OpenGLDynamicRHI::EndScene()
{
    glEnd();
}

void OpenGLDynamicRHI::ClearColorBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLDynamicRHI::ClearColorDepthBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLDynamicRHI::SwapBuffer()
{
#if BOOST_OS_WINDOWS
    ::SwapBuffers(m_context->dcHandle);
#else
    CGLFlushDrawable([m_context->context CGLContextObj]);
#endif
}

} /* namespace graphics */
} /* namespace tgon */
