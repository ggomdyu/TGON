#include "PrecompiledHeader.h"

#include "Engine/GraphicsModule.h"
#include "Game/GameObject.h"

#include "SpriteRendererComponent.h"

namespace tgon
{

SpriteRendererComponent::SpriteRendererComponent(const std::shared_ptr<CanvasSprite>& sprite, const std::shared_ptr<Material>& material, const Color4f& blendColor) :
    RendererComponent(material),
    m_sprite(sprite),
    m_blendColor(blendColor)
{
    this->SetSprite(sprite);
}

SpriteRendererComponent::~SpriteRendererComponent()
{
    if (m_sprite != nullptr)
    {
        m_graphicsModule->GetCanvasRenderer().RemoveSprite(m_sprite);
    }
}
    
void SpriteRendererComponent::Update()
{
}

void SpriteRendererComponent::SetSprite(const std::shared_ptr<CanvasSprite>& sprite)
{
    m_graphicsModule->GetCanvasRenderer().AddSprite(sprite);
    m_sprite = sprite;
}
    
std::shared_ptr<CanvasSprite> SpriteRendererComponent::GetSprite() noexcept
{
    return m_sprite;
}

std::shared_ptr<const CanvasSprite> SpriteRendererComponent::GetSprite() const noexcept
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
