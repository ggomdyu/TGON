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
    if (m_material->GetOpacity() <= 0.0f)
    {
        return;
    }

    m_graphicsModule->GetRenderStage().AddSpriteBatch(m_material, { GetOwner()->GetWorldMatrix() });
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

void SpriteRendererComponent::SetBlendColor(const Color3f& blendColor)
{
    m_material->SetBlendColor(blendColor);
}

Color3f& SpriteRendererComponent::GetBlendColor() noexcept
{
    return m_material->GetBlendColor();
}

const Color3f& SpriteRendererComponent::GetBlendColor() const noexcept
{
    return m_material->GetBlendColor();
}

void SpriteRendererComponent::SetOpacity(float opacity) noexcept
{
    m_material->SetOpacity(opacity);
}

float& SpriteRendererComponent::GetOpacity() noexcept
{
    return m_material->GetOpacity();
}

const float SpriteRendererComponent::GetOpacity() const noexcept
{
    return m_material->GetOpacity();
}

} /* namespace tgon */
