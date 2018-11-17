#include "PrecompiledHeader.h"

#include "SpriteRendererComponent.h"

namespace tgon
{

SpriteRendererComponent::SpriteRendererComponent(const std::shared_ptr<Sprite>& sprite) :
    m_sprite(sprite)
{
}

SpriteRendererComponent::SpriteRendererComponent(const std::shared_ptr<Material>& material) :
    RendererComponent(material)
{
}

SpriteRendererComponent::SpriteRendererComponent(const std::shared_ptr<Sprite>& sprite, const std::shared_ptr<Material>& material) :
    RendererComponent(material),
    m_sprite(sprite)
{
}

void SpriteRendererComponent::Update()
{
    //m_graphicsModule->GetView().AddSpriteBatch(m_material, { GetOwner()->GetWorldMatrix() });
}

void SpriteRendererComponent::SetSprite(const std::shared_ptr<Sprite>& sprite)
{
    m_sprite = sprite;
}

std::shared_ptr<Sprite>& SpriteRendererComponent::GetSprite() noexcept
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
