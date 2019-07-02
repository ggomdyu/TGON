#include "PrecompiledHeader.h"

#include "Game/GameObject.h"
#include "Engine/GraphicsModule.h"

#include "CanvasSpriteRendererComponent.h"

namespace tgon
{

CanvasSpriteRendererComponent::CanvasSpriteRendererComponent(const std::shared_ptr<CanvasSprite>& sprite) :
    m_sprite(sprite)
{
}

CanvasSpriteRendererComponent::CanvasSpriteRendererComponent(const std::shared_ptr<Material>& material, const Color4f& blendColor) :
    RendererComponent(material),
    m_blendColor(blendColor)
{
}
    
void CanvasSpriteRendererComponent::Update()
{
    m_graphicsModule->GetCanvasRenderer().AddSpritePrimitive(m_sprite, GetOwner()->GetTransform()->GetWorldMatrix());
}

void CanvasSpriteRendererComponent::SetSprite(const std::shared_ptr<CanvasSprite>& sprite)
{
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
