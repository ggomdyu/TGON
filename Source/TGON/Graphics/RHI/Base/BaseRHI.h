/**
 * @filename    BaseRHI.h
 * @author      ggomdyu
 * @since       10/22/2017
 * @brief
 */

#pragma once
#include "Core/Platform/Config.h"
#include "Core/Math/Rect.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Color.h"

#include "BaseRHIFwd.h"

namespace tgon
{
namespace rhi
{
class TGON_API BaseRHI
{
    /* @section Public constructor */
public:
    BaseRHI() = default;

    /* @section Public method */
public:
    virtual void SetClearColor(const math::Color4f& color) {}
    virtual void SetFillMode(FillMode fillMode) {}
    virtual void SetCullMode(CullMode cullMode) {}
    virtual void SetScissorRect(const math::FRect& rect) {}

    virtual void BeginScene(PrimitiveType primitiveType) {}
    virtual void EndScene() {}
    virtual void ClearColorBuffer() {}
    virtual void ClearColorDepthBuffer() {}
    virtual void SwapBuffer() {}

    virtual void DrawPoint(const math::Vector2&) {}
    virtual void DrawLine(const math::Vector2&, const math::Vector2&) {}
    virtual void DrawTriangle(const math::Vector2&, const math::Vector2&, const math::Vector2&) {}
    virtual void DrawTriangleStrip(float*) {}
    virtual void DrawTriangleFan(float*) {}
    virtual void DrawQuad(float*) {}

    //virtual void CreateShader(const char* shaderCode, int shaderCodeLength) {}
};

} /* namespace rhi */
} /* namespace tgon */
