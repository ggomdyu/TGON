#include "PrecompiledHeader.h"

#include "Core/Platform/Application.h"
#include "Graphics/Engine/GraphicsModule.h"

#include "RendererComponent.h"

namespace tgon
{

RendererComponent::RendererComponent(const std::shared_ptr<Material>& material) :
    m_material(material),
    m_graphicsModule(Application::GetEngine()->FindModule<GraphicsModule>())
{
}

RendererComponent::~RendererComponent() = default;

void RendererComponent::SetMaterial(const std::shared_ptr<Material>& material)
{
    m_material = material;
}

std::shared_ptr<Material>& RendererComponent::GetMaterial() noexcept
{
    return m_material;
}

const std::shared_ptr<Material> RendererComponent::GetMaterial() const noexcept
{
    return m_material;
}


} /* namespace tgon */
