/**
 * @filename    OpenGLGraphics.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include "OpenGLContext.h"

#include "../Generic/GenericGraphics.h"

#include <GL/glew.h>
#include <memory>

namespace tgon
{
namespace graphics
{

constexpr GLenum ConvertFillModeToNative(FillMode fillMode) noexcept
{
    constexpr GLenum nativeFillModeTable[] =
    {
        GL_POINT,
        GL_LINE,
        GL_FILL
    };

    return nativeFillModeTable[static_cast<std::size_t>(fillMode)];
}

constexpr GLenum ConvertCullModeToNative(CullMode cullMode) noexcept
{
    constexpr GLenum nativeCullModeTable[] =
    {
        GL_CW,
        GL_CCW
    };

    return nativeCullModeTable[static_cast<std::size_t>(cullMode)];
}

constexpr GLenum ConvertPrimitiveTypeToNative(PrimitiveType primitiveType) noexcept
{
    constexpr GLenum nativePrimitiveTypeTable[] =
    {
        GL_POINTS,
        GL_LINES,
        GL_LINE_STRIP,
        GL_TRIANGLES,
        GL_TRIANGLE_STRIP,
        GL_TRIANGLE_FAN,
    };

    return nativePrimitiveTypeTable[static_cast<std::size_t>(primitiveType)];
}

class OpenGLGraphics :
    public GenericGraphics
{
/* @section Public constructor */
public:
    OpenGLGraphics(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode);
    virtual ~OpenGLGraphics() override;

/* @section Public method */
public:
    virtual void SetClearColor(const core::Color4f& color) override;
    virtual void SetFillMode(FillMode fillMode) final override;
    virtual void SetCullMode(CullMode cullMode) final override;
    virtual void EnableBlend() final override;
    virtual void EnableDepthTest() final override;
    virtual void DisableBlend() final override;
    virtual void DisableDepthTest() final override;
    virtual void ClearColorBuffer() final override;
    virtual void ClearColorDepthBuffer() final override;
    virtual void SwapBuffer() final override;
    virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) final override;

/* @section Private variable */
private:
    OpenGLContext m_context;
};

} /* namespace graphics */
} /* namespace tgon */