/**
 * @filename    GenericGraphics.h
 * @author      ggomdyu
 * @since       10/22/2017
 * @brief       Set of Low level rendering interfaces.
 */

#pragma once
#include "GenericGraphicsFwd.h"

#include "Core/Platform/Config.h"

#include <initializer_list>

namespace tgon
{
namespace graphics
{

class TGON_API GenericGraphics
{
/* @section Public constructor */
public:
    GenericGraphics() = default;
    virtual ~GenericGraphics() = default;

/* @section Public method */
public:
    virtual void SetClearColor(const core::Color4f& color) {}
    virtual void SetFillMode(FillMode) {}
    virtual void SetCullMode(CullMode cullMode) {}
    virtual void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height) {}
    virtual void SetScissorRect(const core::FRect& rect) {}
    virtual void EnableBlend() {}
    virtual void EnableDepthTest() {}
    virtual void DisableBlend() {}
    virtual void DisableDepthTest() {}
    virtual void ClearColorBuffer() {}
    virtual void ClearColorDepthBuffer() {}
    virtual void SwapBuffer() {}
    virtual std::shared_ptr<GenericVertexBuffer> CreateVertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) = 0;

    /*virtual void DrawPoint(const core::Vector3&) {};
    virtual void DrawLine(const core::Vector3&, const core::Vector3&) {};
    virtual void DrawTriangle(const core::Vector3&, const core::Vector3&, const core::Vector3&) {}
    virtual void DrawTriangleStrip(float*) {}
    virtual void DrawTriangleFan(float*) {}
    virtual void DrawQuad(float*) {}*/
};

} /* namespace graphics */
} /* namespace tgon */
