/**
 * @filename    IDynamicRHI.h
 * @author      ggomdyu
 * @since       10/22/2017
 * @brief       Set of Low level rendering interfaces.
 */

#pragma once
#include "IDynamicRHIFwd.h"

#include "Core/Platform/Config.h"

namespace tgon
{
namespace graphics
{

class TGON_API IDynamicRHI
{
    /* @section Public constructor */
public:
    IDynamicRHI() = default;
    virtual ~IDynamicRHI() = default;

    /* @section Public method */
public:
    virtual void SetClearColor(const core::Color4f& color) {}
    virtual void SetFillMode(FillMode) {}
    virtual void SetCullMode(CullMode cullMode) {}
    virtual void SetScissorRect(const core::FRect& rect) {}
    virtual void EnableBlend() {}
    virtual void EnableDepthTest() {}
    virtual void DisableBlend() {}
    virtual void DisableDepthTest() {}

    virtual void BeginScene(PrimitiveType primitiveType) {}
    virtual void EndScene() {}
    virtual void ClearColorBuffer() {}
    virtual void ClearColorDepthBuffer() {}
    virtual void SwapBuffer() {}

    /*virtual void DrawPoint(const core::Vector3&);
    virtual void DrawLine(const core::Vector3&, const core::Vector3&);
    virtual void DrawTriangle(const core::Vector3&, const core::Vector3&, const core::Vector3&) {}
    virtual void DrawTriangleStrip(float*) {}
    virtual void DrawTriangleFan(float*) {}
    virtual void DrawQuad(float*) {}*/
};

} /* namespace graphics */
} /* namespace tgon */
