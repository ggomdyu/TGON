/**
 * @filename    IGraphicsDevice.h
 * @author      ggomdyu
 * @since       04/02/2017
 */

#pragma once
#include "RenderCore/Graphics/TGraphicsDevice.h"

#include "Core/Math/TMatrix4x4.h"
#include "Core/Math/TRect.h"

#include <memory>
#include <vector>
#include <cstdint>

namespace tgon {
namespace graphics {

class GenericRenderer
{
/**
 * @section Ctor/Dtor
 */
public:
    GenericRenderer(TGraphicsDevice);
    ~GenericRenderer();

/**
 * @section Public command method
 */
public:
    virtual void Clear() = 0;
    virtual void BeginScene() = 0;
    virtual void EndScene() = 0;
    virtual void Present() = 0;
    
    //void PushScissorRect(const math::TIntRect& scissorRect);
    //void PopScissorRect();

/**
 * @section Set method
 */
public:
    virtual void SetClearColor(uint32_t packedColor) = 0;
    virtual void SetWorldMatrix(const math::TMatrix4x4& worldMat) = 0;
    virtual void SetViewMatrix(const math::TMatrix4x4& viewMat) = 0;
    virtual void SetProjectionMatrix(const math::TMatrix4x4& projMat) = 0;
    virtual void SetViewProjectionMatrix(const math::TMatrix4x4& viewProjMat) = 0;
    virtual void SetScissorRect(const math::TIntRect& scissorRect) = 0;

/**
 * @section Get method
 */
public:
    uint32_t GetClearColor() const noexcept;

/**
 * @section Private variable
 */
protected:
    std::shared_ptr<TGraphicsDevice> m_sdkInstance;

    uint32_t m_clearColor;

    math::TMatrix4x4 m_worldMat;
    math::TMatrix4x4 m_viewMat;
    math::TMatrix4x4 m_projMat;
    math::TMatrix4x4 m_viewProjMat;

    std::vector<math::TIntRect> m_scissorRectStack;
};

} /* namespace graphics */
} /* namespace tgon */