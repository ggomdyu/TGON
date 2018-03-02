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

class OpenGLGraphics :
    public GenericGraphics
{
/* @section Public constructor */
public:
    OpenGLGraphics(const VideoMode& videoMode, const std::shared_ptr<core::GenericWindow>& window);
    virtual ~OpenGLGraphics() override;

/* @section Public method */
public:
    virtual void SetClearColor(const core::Color4f& color) override;
    virtual void SetFillMode(FillMode fillMode) final override;
    virtual void SetCullMode(CullMode cullMode) final override;
    virtual void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height) final override;
    virtual void EnableBlend() final override;
    virtual void EnableDepthTest() final override;
    virtual void DisableBlend() final override;
    virtual void DisableDepthTest() final override;
    virtual void ClearColorBuffer() final override;
    virtual void ClearColorDepthBuffer() final override;
    virtual void SwapBuffer() final override;
    virtual std::shared_ptr<GenericVertexBuffer> CreateVertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) final override;
    virtual std::shared_ptr<GenericIndexBuffer> CreateIndexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage) final override;

/* @section Private variable */
private:
    OpenGLContext m_context;
};

} /* namespace graphics */
} /* namespace tgon */
