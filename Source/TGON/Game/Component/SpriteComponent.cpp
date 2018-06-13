#include "PrecompiledHeader.h"

#include "Graphics/Render/SpriteBatch.h"

#include "SpriteComponent.h"

namespace tgon
{

SpriteComponent::SpriteComponent(const std::string& filePath) :
    m_sprite(std::make_shared<Sprite>(filePath))
{
}
    
SpriteComponent::SpriteComponent(const std::shared_ptr<Sprite>& sprite) :
    m_sprite(sprite)
{
}

const std::shared_ptr<Sprite>& SpriteComponent::GetSprite() const noexcept
{
    return m_sprite;
}

std::shared_ptr<Sprite>& SpriteComponent::GetSprite() noexcept
{
    return m_sprite;
}
   
void SpriteComponent::Update()
{
}
    
void SpriteComponent::Draw(Graphics& graphics)
{
    m_sprite->Draw(graphics);
}
    
void SpriteComponent::Draw(SpriteBatch& spriteBatch)
{
    spriteBatch.AddSprite(m_sprite);
}

} /* namespace tgon */
