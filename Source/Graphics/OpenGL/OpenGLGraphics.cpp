#include "PrecompiledHeader.h"

#if TGON_GRAPHICS_OPENGL
#include <stb_image.h>
#include <stb_image_write.h>

#include "Platform/Window.h"
#include "Drawing/FontFactory.h"

#include "OpenGLDebug.h"

#include "../Graphics.h"

#ifdef _MSC_VER
#   pragma comment(lib, "OpenGL32.Lib")
#endif

namespace tgon
{
namespace
{
    
constexpr GLenum ConvertPrimitiveTypeToNative(PrimitiveType primitiveType) noexcept
{
    constexpr GLenum nativePrimitiveTypes[] = {
        GL_POINTS,
        GL_LINES,
        GL_LINE_STRIP,
        GL_TRIANGLES,
        GL_TRIANGLE_STRIP,
        GL_TRIANGLE_FAN,
    };
    
    return nativePrimitiveTypes[static_cast<int>(primitiveType)];
}
    
constexpr GLenum ConvertFillModeToNative(FillMode fillMode) noexcept
{
    constexpr GLenum nativeFillModes[] = {
        GL_POINT,
        GL_LINE,
        GL_FILL,
    };
    
    return nativeFillModes[static_cast<int>(fillMode)];
}
    
constexpr GLenum ConvertCullModeToNative(CullMode cullMode) noexcept
{
    constexpr GLenum nativecullModes[] = {
        GL_CW,
        GL_CCW,
    };
    
    return nativecullModes[static_cast<int>(cullMode)];
}
    
} /* namespace */

OpenGLGraphics::OpenGLGraphics(const std::shared_ptr<Window>& displayWindow, const VideoMode& videoMode) :
    m_context(displayWindow, videoMode)
{
    TGON_GL_ERROR_CHECK(glGenVertexArrays(1, &m_vertexArrayHandle));
    TGON_GL_ERROR_CHECK(glBindVertexArray(m_vertexArrayHandle));
}

OpenGLGraphics::OpenGLGraphics(OpenGLGraphics&& rhs) noexcept :
    m_context(std::move(rhs.m_context)),
    m_vertexArrayHandle(rhs.m_vertexArrayHandle)
{
    rhs.m_vertexArrayHandle = 0;
}

OpenGLGraphics::~OpenGLGraphics()
{
    if (m_vertexArrayHandle != 0)
    {
        TGON_GL_ERROR_CHECK(glBindVertexArray(m_vertexArrayHandle));
        TGON_GL_ERROR_CHECK(glDeleteVertexArrays(1, &m_vertexArrayHandle));
        m_vertexArrayHandle = 0;
    }
}

OpenGLContext& OpenGLGraphics::GetContext() noexcept
{
    return m_context;
}

const OpenGLContext& OpenGLGraphics::GetContext() const noexcept
{
    return m_context;
}

GLuint OpenGLGraphics::GetVertexArrayHandle() const noexcept
{
    return m_vertexArrayHandle;
}

void Graphics::SetScissorRect(const FRect& scissorRect)
{
    TGON_GL_ERROR_CHECK(glScissor(static_cast<GLint>(scissorRect.x), static_cast<GLint>(scissorRect.y), static_cast<GLint>(scissorRect.width), static_cast<GLint>(scissorRect.height)));
}

void Graphics::SetClearColor(const Color4f& color)
{
    TGON_GL_ERROR_CHECK(glClearColor(color.r, color.g, color.b, color.a));
}

void Graphics::SetFillMode(FillMode fillMode)
{
    TGON_GL_ERROR_CHECK(glPolygonMode(GL_FRONT_AND_BACK, ConvertFillModeToNative(fillMode)));
}

void Graphics::SetCullMode(CullMode cullMode)
{
    TGON_GL_ERROR_CHECK(glFrontFace(ConvertCullModeToNative(cullMode)));
}

void Graphics::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
    TGON_GL_ERROR_CHECK(glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLsizei>(width), static_cast<GLsizei>(height)));
}
    
void Graphics::SetBlendMode(BlendMode blendMode)
{
    switch (blendMode)
    {
    case BlendMode::Normal:
        TGON_GL_ERROR_CHECK(glBlendFunc(GL_ONE, GL_ZERO));
        TGON_GL_ERROR_CHECK(glBlendEquation(GL_FUNC_ADD));
        break;
            
    case BlendMode::Alpha:
        TGON_GL_ERROR_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//        TGON_GL_ERROR_CHECK(glBlendEquation(GL_FUNC_ADD));
        break;
            
    case BlendMode::Additive:
        TGON_GL_ERROR_CHECK(glBlendFunc(GL_ONE, GL_ONE));
        TGON_GL_ERROR_CHECK(glBlendEquation(GL_FUNC_ADD));
        break;
            
    case BlendMode::Subtractive:
        TGON_GL_ERROR_CHECK(glBlendFunc(GL_ONE, GL_ONE));
        TGON_GL_ERROR_CHECK(glBlendEquation(GL_FUNC_REVERSE_SUBTRACT));
        break;
    }
}

void Graphics::EnableCullFace()
{
    TGON_GL_ERROR_CHECK(glEnable(GL_CULL_FACE));
}
    
void Graphics::EnableBlend()
{
    TGON_GL_ERROR_CHECK(glEnable(GL_BLEND));
}

void Graphics::EnableDepthTest()
{
    TGON_GL_ERROR_CHECK(glEnable(GL_DEPTH_TEST));
}

void Graphics::EnableScissorTest()
{
    TGON_GL_ERROR_CHECK(glEnable(GL_SCISSOR_TEST));
}
    
void Graphics::DisableCullFace()
{
    TGON_GL_ERROR_CHECK(glDisable(GL_CULL_FACE));
}

void Graphics::DisableBlend()
{
    TGON_GL_ERROR_CHECK(glDisable(GL_BLEND));
}

void Graphics::DisableDepthTest()
{
    TGON_GL_ERROR_CHECK(glDisable(GL_DEPTH_TEST));
}

void Graphics::DisableScissorTest()
{
    TGON_GL_ERROR_CHECK(glDisable(GL_SCISSOR_TEST));
}

void Graphics::ClearColorBuffer()
{
    TGON_GL_ERROR_CHECK(glClear(GL_COLOR_BUFFER_BIT));
}

void Graphics::ClearColorDepthBuffer()
{
    TGON_GL_ERROR_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void Graphics::SwapBuffer()
{
    m_context.SwapBuffer();
}

void Graphics::DrawPrimitives(PrimitiveType primitiveType, int32_t vertexStartOffset, int32_t vertexCount)
{
    TGON_GL_ERROR_CHECK(glDrawArrays(ConvertPrimitiveTypeToNative(primitiveType), static_cast<int32_t>(vertexStartOffset), vertexCount));
}
    
void Graphics::DrawIndexedPrimitives(PrimitiveType primitiveType, int32_t indexCount)
{
    TGON_GL_ERROR_CHECK(glDrawElements(ConvertPrimitiveTypeToNative(primitiveType), indexCount, GL_UNSIGNED_INT, nullptr));
}

} /* namespace tgon */
#endif
