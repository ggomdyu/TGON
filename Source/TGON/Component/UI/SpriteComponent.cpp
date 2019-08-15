#include "PrecompiledHeader.h"

#include "Engine/GraphicsModule.h"
#include "Game/GameObject.h"

#include "SpriteComponent.h"

namespace tgon
{

SpriteRendererComponent::SpriteRendererComponent(const std::shared_ptr<UISprite>& sprite) :
    RendererComponent(),
    m_sprite(sprite)
{
}

SpriteRendererComponent::SpriteRendererComponent(const std::shared_ptr<Material>& material, const Color4f& blendColor) :
    RendererComponent(material),
    m_blendColor(blendColor)
{
}
    
void SpriteRendererComponent::Update()
{
    m_graphicsModule->GetUIRenderer().AddSpritePrimitive(m_sprite, GetOwner()->GetTransform()->GetWorldMatrix());
}

void SpriteRendererComponent::SetSprite(const std::shared_ptr<UISprite>& sprite)
{
    m_sprite = sprite;
}
    
std::shared_ptr<UISprite> SpriteRendererComponent::GetSprite() noexcept
{
    return m_sprite;
}

std::shared_ptr<const UISprite> SpriteRendererComponent::GetSprite() const noexcept
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

}
