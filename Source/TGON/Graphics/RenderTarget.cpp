#include "PrecompiledHeader.h"

#include "RenderTarget.h"

namespace tgon
{

RenderTarget::RenderTarget(int32_t width, int32_t height, int32_t multisampleLevel) :
    m_renderTargetImpl(width, height, multisampleLevel)
{
}

void RenderTarget::Use()
{
    m_renderTargetImpl.Use();
}

void RenderTarget::Unuse()
{
    m_renderTargetImpl.Unuse();
}

} /* namespace tgon */
