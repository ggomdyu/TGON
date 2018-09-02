#include "PrecompiledHeader.h"

#include "Core/Platform/Application.h"

#include "SpriteRendererComponent.h"

#include "../Object/GameObject.h"

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
    m_graphicsModule->GetRenderStage().AddSpriteBatch(m_material, {GetOwner()->GetTransform().GetWorldMatrix()});
}

} /* namespace tgon */
