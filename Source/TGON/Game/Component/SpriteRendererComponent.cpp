#include "PrecompiledHeader.h"

#include "SpriteRendererComponent.h"

namespace tgon
{

SpriteRendererComponent::SpriteRendererComponent(const std::string& filePath) :
    m_sprite(filePath),
    m_material(std::make_shared<TextureMaterial>(m_sprite.GetTexture())),
    m_graphicsModule(Application::GetInstance()->GetEngine()->FindModule<GraphicsModule>())
{
}

SpriteRendererComponent::SpriteRendererComponent(std::string&& filePath) :
    m_sprite(std::move(filePath)),
    m_material(std::make_shared<TextureMaterial>(m_sprite.GetTexture())),
    m_graphicsModule(Application::GetInstance()->GetEngine()->FindModule<GraphicsModule>())
{
}

void SpriteRendererComponent::Update()
{
    m_graphicsModule->GetRenderStage().AddSpriteBatch(m_material, { GetOwner()->GetTransform().GetWorldMatrix() });
}

void SpriteRendererComponent::SetSprite(const Sprite& sprite)
{
    m_sprite = sprite;
}

Sprite& SpriteRendererComponent::GetSprite() noexcept
{
    return m_sprite;
}

const Sprite& SpriteRendererComponent::GetSprite() const noexcept
{
    return m_sprite;
}

void SpriteRendererComponent::SetBlendColor(const Color4f& blendColor)
{
    m_material->SetBlendColor(blendColor);
}

Color4f& SpriteRendererComponent::GetBlendColor() noexcept
{
    return m_material->GetBlendColor();
}

const Color4f& SpriteRendererComponent::GetBlendColor() const noexcept
{
    return m_material->GetBlendColor();
}

} /* namespace tgon */
