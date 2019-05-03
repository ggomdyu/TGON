#include "PrecompiledHeader.h"

#include "Graphics/Engine/GraphicsModule.h"
#include "Game/Object/GameObject.h"

#include "SpriteRendererComponent.h"

namespace tgon
{

SpriteRendererComponent::SpriteRendererComponent(const std::shared_ptr<Sprite>& sprite, const std::shared_ptr<Material>& material, const Color4f& blendColor) :
    RendererComponent(material),
    m_sprite(sprite),
    m_blendColor(blendColor)
{
}

void SpriteRendererComponent::Update()
{
}

void SpriteRendererComponent::SetSprite(const std::shared_ptr<Sprite>& sprite)
{
    m_sprite = sprite;
}
    
std::shared_ptr<Sprite> SpriteRendererComponent::GetSprite() noexcept
{
    return m_sprite;
}

std::shared_ptr<const Sprite> SpriteRendererComponent::GetSprite() const noexcept
{
    return m_sprite;
}

void SpriteRendererComponent::SetBlendColor(const Color4f& blendColor)
{
    m_blendColor = blendColor;
}

const Color4f& SpriteRendererComponent::GetBlendColor() const noexcept
{
    return m_blendColor;
}

} /* namespace tgon */
