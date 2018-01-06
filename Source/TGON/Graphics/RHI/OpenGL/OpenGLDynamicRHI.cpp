#include "PrecompiledHeader.pch"

#include "OpenGLDynamicRHI.h"
#include "OpenGLContext.h"

#include "../RHIType.h"

#include "Core/Math/Color.h"
#include "Core/Platform/Debug.h"
#include "Graphics/RHI/RHIType.h"
 
#include <atomic>
#include <GL/glew.h>

namespace tgon
{
namespace graphics
{

OpenGLDynamicRHI::OpenGLDynamicRHI(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode) :
    m_context(std::make_unique<OpenGLContext>(window, videoMode))
{
}

OpenGLDynamicRHI::~OpenGLDynamicRHI() = default;

void OpenGLDynamicRHI::SetClearColor(const core::Color4f& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLDynamicRHI::SetFillMode(FillMode fillMode)
{
    static GLenum nativeFillModeTable[] =
    {
        GL_POINT,
        GL_LINE,
        GL_FILL
    };

    glPolygonMode(GL_FRONT_AND_BACK, nativeFillModeTable[static_cast<GLenum>(fillMode)]);
}

void OpenGLDynamicRHI::SetCullMode(CullMode cullMode)
{
    static GLenum nativeCullModeTable[] =
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
    ::SwapBuffers(m_context->dcHandle);
}

} /* namespace graphics */
} /* namespace tgon */