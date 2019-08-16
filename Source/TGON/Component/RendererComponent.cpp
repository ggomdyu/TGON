#include "PrecompiledHeader.h"

#include "Engine/Engine.h"
#include "Engine/GraphicsModule.h"
#include "Platform/Application.h"

#include "RendererComponent.h"

namespace tgon
{
    
RendererComponent::RendererComponent() :
    RendererComponent(nullptr)
{
}

RendererComponent::RendererComponent(const std::shared_ptr<Material>& material) :
    m_graphicsModule(Application::GetInstance().GetEngine()->FindModule<GraphicsModule>()),
    m_material(material)
{
}

RendererComponent::~RendererComponent() = default;

void RendererComponent::SetMaterial(const std::shared_ptr<Material>& material)
{
    m_material = material;
}

std::shared_ptr<Material> RendererComponent::GetMaterial() noexcept
{
    return m_material;
}

std::shared_ptr<const Material> RendererComponent::GetMaterial() const noexcept
{
    return m_material;
}


} /* namespace tgon */
