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

void SpriteComponent::SetSprite(const std::string& filePath)
{
    m_sprite.se //filePath;
}

void SpriteComponent::SetSprite(const Sprite& imagePath)
{
    
}

void SpriteComponent::SetSprite(Sprite&& imagePath)
{
    
}

const Sprite& SpriteComponent::GetSprite() const noexcept
{
    
}

Sprite& SpriteComponent::GetSprite() noexcept
{
    
}

} /* namespace tgon */
