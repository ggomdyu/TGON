#include "PrecompiledHeader.h"

#include "Platform/Application.h"
#include "UI/UIElement.h"

#include "UIRendererComponent.h"

namespace tg
{
    
UIRendererComponent::UIRendererComponent(const std::shared_ptr<Material>& material) noexcept :
    UIRendererComponent(material, nullptr)
{
}

UIRendererComponent::UIRendererComponent(const std::shared_ptr<Material>& material, const std::shared_ptr<UIElement>& uiElement) noexcept :
    RendererComponent(material),
    m_element(uiElement),
    m_uiRendererModule(Application::GetInstance().GetEngine()->FindModule<UIRendererModule>())
{
}

void UIRendererComponent::SetSortingLayer(int32_t sortingLayer) noexcept
{
    m_sortingLayer = sortingLayer;
}

void UIRendererComponent::SetMaterial(const std::shared_ptr<Material>& material) noexcept
{
    m_element->SetMaterial(material);
}

int32_t UIRendererComponent::GetSortingLayer() const noexcept
{
    return m_sortingLayer;
}

std::shared_ptr<Material> UIRendererComponent::GetMaterial() noexcept
{
    return m_material;
}

std::shared_ptr<const Material> UIRendererComponent::GetMaterial() const noexcept
{
    return m_material;
}

}
