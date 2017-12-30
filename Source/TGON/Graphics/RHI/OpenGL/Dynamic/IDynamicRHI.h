/**
 * @filename    BaseRHI.h
 * @author      ggomdyu
 * @since       10/22/2017
 * @brief       Set of Low level rendering interfaces.
 */

#pragma once
#include "Core/Platform/Config.h"

namespace tgon
{
namespace math
{

struct Color4f;
struct Vector2;
struct Vector3;
struct Matrix4x4;
template <typename _ValueType>
struct BasicRect;
using FRect = BasicRect<float>;
using Shader = void*;

} /* namespace math */

namespace rhi
{

class TGON_API IDynamicRHI
{
    /* @section Public constructor */
public:
    IDynamicRHI() = default;
    virtual ~IDynamicRHI() = default;

    /* @section Public method */
public:
    virtual void SetClearColor(const math::Color4f& color) = 0;
    virtual void SetFillMode(FillMode) = 0;
    virtual void SetCullMode(CullMode cullMode) = 0;
    virtual void SetScissorRect(const math::FRect& rect) = 0;
    virtual void EnalbleDepthTest() = 0;
    virtual void DisableDepthTest() = 0;

    virtual Shader CreateShader(const char* shaderCode, int shaderCodeLength) = 0;
    virtual VideoBuffer CreateBuffer(VideoBufferType videoBufferType) = 0;

    virtual void BeginScene(PrimitiveType primitiveType) = 0;
    virtual void EndScene() = 0;
    virtual void ClearColorBuffer() = 0;
    virtual void ClearColorDepthBuffer() = 0;
    virtual void SwapBuffer() = 0;

    /*virtual void DrawPoint(const math::Vector3&);
    virtual void DrawLine(const math::Vector3&, const math::Vector3&);
    virtual void DrawTriangle(const math::Vector3&, const math::Vector3&, const math::Vector3&) {}
    virtual void DrawTriangleStrip(float*) {}
    virtual void DrawTriangleFan(float*) {}
    virtual void DrawQuad(float*) {}*/

};

} /* namespace rhi */
} /* namespace tgon */
