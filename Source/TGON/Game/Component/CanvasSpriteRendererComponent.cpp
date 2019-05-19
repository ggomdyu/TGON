#include "PrecompiledHeader.h"

#include "Game/GameObject.h"
#include "Engine/GraphicsModule.h"

#include "CanvasSpriteRendererComponent.h"

namespace tgon
{

CanvasSpriteRendererComponent::CanvasSpriteRendererComponent(const std::shared_ptr<Material>& material, const Color4f& blendColor) :
    RendererComponent(material),
    m_blendColor(blendColor)
{
}

CanvasSpriteRendererComponent::~CanvasSpriteRendererComponent()
{
    if (m_sprite != nullptr)
    {
        m_graphicsModule->GetCanvasRenderer().RemoveSprite(m_sprite);
    }
}
    
void CanvasSpriteRendererComponent::Update()
{
}

void CanvasSpriteRendererComponent::SetSprite(const std::shared_ptr<CanvasSprite>& sprite)
{
    m_graphicsModule->GetCanvasRenderer().AddSprite(sprite, GetOwner()->GetTransform()->GetWorldMatrix());

    m_sprite = sprite;
}
    
std::shared_ptr<CanvasSprite> CanvasSpriteRendererComponent::GetSprite() noexcept
{
    return m_sprite;
}

std::shared_ptr<const CanvasSprite> CanvasSpriteRendererComponent::GetSprite() const noexcept
{
    return m_sprite;
}

void CanvasSpriteRendererComponent::SetBlendColor(const Color4f& blendColor)
{
    m_blendColor = blendColor;
}

const Color4f& CanvasSpriteRendererComponent::GetBlendColor() const noexcept
{
    return m_blendColor;
}

} /* namespace tgon */
