#include "PrecompiledHeader.h"
#include "GenericRenderer.h"

namespace tgon {
namespace graphics {

inline GenericRenderer::GenericRenderer(void* surfaceWindow, const std::shared_ptr<IGraphicsInstance>& sdkInstance) :
    m_sdkInstance(sdkInstance)
{
}

inline GenericRenderer::~GenericRenderer()
{
}

inline void GenericRenderer::PushScissorRect(const math::TIntRect& scissorRect)
{
}

inline void GenericRenderer::SetClearColor(uint32_t packedColor) noexcept
{
    m_clearColor = packedColor;
}

inline void GenericRenderer::SetWorldMatrix(const math::TMatrix4x4& worldMat) noexcept
{
    m_worldMat = worldMat;
}

inline void GenericRenderer::SetViewMatrix(const math::TMatrix4x4& viewMat) noexcept
{
    m_viewMat = viewMat;
}

inline void GenericRenderer::SetProjectionMatrix(const math::TMatrix4x4& projMat) noexcept
{
    m_projMat = projMat;
}

inline void GenericRenderer::SetViewProjectionMatrix(const math::TMatrix4x4& viewProjMat) noexcept
{
}

inline uint32_t GenericRenderer::GetClearColor() const noexcept
{
    return m_clearColor;
}

} /* namespace graphics */
} /* namespace tgon */