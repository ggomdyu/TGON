#include "PrecompiledHeader.h"

#include "SpriteComponent.h"

namespace tgon
{
    
SpriteComponent::SpriteComponent(const std::string& filePath) :
    m_sprite(filePath)
{
}
    
SpriteComponent::SpriteComponent(const Sprite& sprite) :
    m_sprite(sprite)
{
}
    
SpriteComponent::SpriteComponent(Sprite&& sprite) :
    m_sprite(std::move(sprite))
{
}

const Sprite& SpriteComponent::GetSprite() const noexcept
{
    return m_sprite;
}

Sprite& SpriteComponent::GetSprite() noexcept
{
    return m_sprite;
}

} /* namespace tgon */
