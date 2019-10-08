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
    auto gameObject = m_gameObject.lock();
    if (gameObject != nullptr)
    {
        m_graphicsModule->GetUIRenderer().AddSpritePrimitive(m_sprite, gameObject->GetComponent<Transform>()->GetWorldMatrix());
    }
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

} /* namespace tgon */