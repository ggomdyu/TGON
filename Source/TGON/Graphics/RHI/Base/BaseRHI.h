/**
 * @filename    BaseRHI.h
 * @author      ggomdyu
 * @since       10/22/2017
 * @brief
 */

#pragma once
#include "Core/Platform/Config.h"

#include "Core/Math/Rect.h"

namespace tgon
{
namespace math
{

struct Color4f;
struct Vector2;
struct Vector3;
struct Matrix4x4;

} /* namespace math */

namespace rhi
{
class TGON_API BaseRHI
{
    /* @section Public constructor */
public:
    BaseRHI() = default;
    virtual ~BaseRHI() = default;

    /* @section Public method */
public:
    virtual void SetClearColor(const math::Color4f& color) {}
    virtual void SetFillMode(enum class FillMode) {}
    virtual void SetCullMode(enum class CullMode cullMode) {}
    virtual void SetScissorRect(const math::FRect& rect) {}
    virtual void EnalbleDepthTest() {}
    virtual void DisableDepthTest() {}

    virtual void BeginScene(enum class PrimitiveType primitiveType) {}
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
