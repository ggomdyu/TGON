#include "PrecompiledHeader.h"

#include "RendererComponent.h"

namespace tgon
{
    
RendererComponent::RendererComponent(const std::shared_ptr<Material>& material) noexcept :
    Component(),
    m_material(material)
{
}

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
