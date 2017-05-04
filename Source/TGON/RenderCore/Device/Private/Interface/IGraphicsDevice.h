/**
 * @filename    IGraphicsDevice.h
 * @author   ggomdyu
 * since    04/02/2017
 */

#pragma once
#include "../Interface/IGraphicsInstance.h"

#include "./Core/Math/TMatrix4x4.h"
#include "./Core/Math/TRect.h"

#include <memory>
#include <vector>
#include <cstdint>

namespace tgon
{

template <typename GraphicsSDKTy>
class GenericRenderer
{
/**
 * @section Ctor/Dtor
 */
public:
    GenericRenderer(void* surfaceWindow, const std::shared_ptr<IGraphicsInstance>& sdkInstance);
    ~GenericRenderer();

/**
 * @section Public command method
 */
public:
    virtual void Clear() = 0;
    virtual void BeginScene() = 0;
    virtual void EndScene() = 0;
    virtual void Present() = 0;
    
    void PushScissorRect(const math::TIntRect& scissorRect);
    void PopScissorRect();

/**
 * @section Set method
 */
public:
    void SetClearColor(uint32_t packedColor) noexcept;
    void SetWorldMatrix(const math::TMatrix4x4& worldMat) noexcept;
    void SetViewMatrix(const math::TMatrix4x4& viewMat) noexcept;
    void SetProjectionMatrix(const math::TMatrix4x4& projMat) noexcept;
    void SetViewProjectionMatrix(const math::TMatrix4x4& viewProjMat) noexcept;
    void SetScissorRect(const math::TIntRect& scissorRect) noexcept;

/**
 * @section Get method
 */
public:
    uint32_t GetClearColor() const noexcept;

/**
 * @section Private variable
 */
protected:
    std::shared_ptr<IGraphicsInstance> m_sdkInstance;

    uint32_t m_clearColor;

    math::TMatrix4x4 m_worldMat;
    math::TMatrix4x4 m_viewMat;
    math::TMatrix4x4 m_projMat;
    math::TMatrix4x4 m_viewProjMat;

    std::vector<math::TIntRect> m_scissorRectStack;
};

template <typename GraphicsSDKTy>
inline GenericRenderer<GraphicsSDKTy>::GenericRenderer(void* surfaceWindow, const std::shared_ptr<IGraphicsInstance>& sdkInstance) :
    m_sdkInstance(sdkInstance)
{
}

template <typename GraphicsSDKTy>
inline GenericRenderer<GraphicsSDKTy>::~GenericRenderer()
{
}

template <typename GraphicsSDKTy>
inline void GenericRenderer<GraphicsSDKTy>::PushScissorRect(const math::TIntRect& scissorRect)
{
    m_scissorRectStack.push_back(scissorRect);
}

template <typename GraphicsSDKTy>
inline void GenericRenderer<GraphicsSDKTy>::PopScissorRect()
{
    m_scissorRectStack.pop_back();
}

template <typename GraphicsSDKTy>
inline void GenericRenderer<GraphicsSDKTy>::SetClearColor(uint32_t packedColor) noexcept
{
    m_clearColor = packedColor;
}

template <typename GraphicsSDKTy>
inline void GenericRenderer<GraphicsSDKTy>::SetWorldMatrix(const math::TMatrix4x4& worldMat) noexcept
{
    m_worldMat = worldMat;
}

template <typename GraphicsSDKTy>
inline void GenericRenderer<GraphicsSDKTy>::SetViewMatrix(const math::TMatrix4x4& viewMat) noexcept
{
    m_viewMat = viewMat;
}

template <typename GraphicsSDKTy>
inline void GenericRenderer<GraphicsSDKTy>::SetProjectionMatrix(const math::TMatrix4x4& projMat) noexcept
{
    m_projMat = projMat;
}

template <typename GraphicsSDKTy>
inline void GenericRenderer<GraphicsSDKTy>::SetViewProjectionMatrix(const math::TMatrix4x4& viewProjMat) noexcept
{
}

template <typename GraphicsSDKTy>
inline uint32_t GenericRenderer<GraphicsSDKTy>::GetClearColor() const noexcept
{
    return m_clearColor;
}

} /* namespace tgon */