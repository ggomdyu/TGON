#include "PrecompiledHeader.h"

#include "Engine/GraphicsModule.h"
#include "Game/GameObject.h"

#include "SpriteRendererComponent.h"

namespace tgon
{

SpriteRendererComponent::SpriteRendererComponent(const std::shared_ptr<UISprite>& sprite) :
    RendererComponent(),
    m_sprite(sprite)
{
}

void SpriteRendererComponent::Update()
{
    if (m_sprite == nullptr || m_sprite->GetBlendColor().a <= 0.0f)
    {
        return;
    }
    
    auto gameObject = m_gameObject.lock();
    if (gameObject != nullptr)
    {
        m_graphicsModule->GetUIRenderer().AddSpritePrimitive(m_sprite, m_sortingLayer, gameObject->GetComponent<Transform>()->GetWorldMatrix());
    }
}

void SpriteRendererComponent::SetSprite(const std::shared_ptr<UISprite>& sprite) noexcept
{
    m_sprite = sprite;
}

void SpriteRendererComponent::SetSortingLayer(int32_t sortingLayer) noexcept
{
    m_sortingLayer = sortingLayer;
}
    
std::shared_ptr<UISprite> SpriteRendererComponent::GetSprite() noexcept
{
    return m_sprite;
}

std::shared_ptr<const UISprite> SpriteRendererComponent::GetSprite() const noexcept
{
    return m_sprite;
}

int32_t SpriteRendererComponent::GetSortingLayer() const noexcept
{
    return m_sortingLayer;
}

} /* namespace tgon */
