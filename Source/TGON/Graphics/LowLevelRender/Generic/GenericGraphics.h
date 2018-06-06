/**
 * @filename    GenericGraphics.h
 * @author      ggomdyu
 * @since       10/22/2017
 * @brief       Set of Low level rendering interfaces.
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Object/Object.h"
#include "Core/Math/Color.h"
#include "Core/Math/Rect.h"

#include "GenericGraphicsType.h"
#include "GenericGraphicsFwd.h"

namespace tgon
{

class TGON_API GenericGraphics :
    public Object,
    private boost::noncopyable
{
public:
    TGON_RUNTIME_OBJECT(GenericGraphics)

/* @section Public constructor */
public:
    GenericGraphics() = default;
    virtual ~GenericGraphics() = default;

/* @section Public method */
public:
    virtual void SetClearColor(const Color4f& color) {}
    virtual void SetFillMode(FillMode) {}
    virtual void SetCullMode(CullMode cullMode) {}
    virtual void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height) {}
    virtual void SetScissorRect(const FRect& rect) {}
    virtual void EnableBlend() {}
    virtual void EnableDepthTest() {}
    virtual void DisableBlend() {}
    virtual void DisableDepthTest() {}
    virtual void ClearColorBuffer() {}
    virtual void ClearColorDepthBuffer() {}
    virtual void SwapBuffer() {}
    virtual void DrawPrimitives(PrimitiveType primitiveType, int32_t startVertex, int32_t primitiveCount) {}
    virtual void DrawIndexedPrimitives(int32_t primitiveCount) {}
    /*virtual void DrawPoint(const Vector3&) {};
    virtual void DrawLine(const Vector3&, const Vector3&) {};
    virtual void DrawTriangle(const Vector3&, const Vector3&, const Vector3&) {}
    virtual void DrawTriangleStrip(float*) {}
    virtual void DrawTriangleFan(float*) {}
    virtual void DrawQuad(float*) {}*/
};

} /* namespace tgon */