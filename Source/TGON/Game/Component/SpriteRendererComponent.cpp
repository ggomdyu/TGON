#include "PrecompiledHeader.h"

#include "Core/Engine/Engine.h"

#include "SpriteRendererComponent.h"

#include "../Object/GameObject.h"

namespace tgon
{

SpriteRendererComponent::SpriteRendererComponent(const std::string& filePath) :
    SpriteRendererComponent(filePath, std::make_shared<TextureMaterial>())
{
}

SpriteRendererComponent::SpriteRendererComponent(std::string&& filePath) :
    SpriteRendererComponent(std::move(filePath), std::make_shared<TextureMaterial>())
{
}

SpriteRendererComponent::SpriteRendererComponent(const std::string& filePath, const std::shared_ptr<Material>& material) noexcept :
    m_sprite(filePath),
    m_material(material),
    m_graphicsModule(Engine::GetInstance()->FindModule<GraphicsModule>())
{
    static_cast<TextureMaterial*>(m_material.get())->SetTexture(m_sprite.GetTexture());
}

SpriteRendererComponent::SpriteRendererComponent(std::string&& filePath, const std::shared_ptr<Material>& material) noexcept :
    m_sprite(filePath),
    m_material(material),
    m_graphicsModule(Engine::GetInstance()->FindModule<GraphicsModule>())
{
    static_cast<TextureMaterial*>(m_material.get())->SetTexture(m_sprite.GetTexture());
}

void SpriteRendererComponent::Update()
{
    m_graphicsModule->GetRenderStage().AddSpriteBatch(m_material, {&GetOwner()->GetTransform().GetWVP()});
}

} /* namespace tgon */
