#include "PrecompiledHeader.h"

#include "Platform/Application.h"

#include "UIRendererComponent.h"

namespace tgon
{
    
UIRendererComponent::UIRendererComponent(const std::shared_ptr<Material>& material) noexcept :
    RendererComponent(material),
    m_uiRendererModule(Application::GetInstance().GetEngine()->FindModule<UIRendererModule>())
{
}

void UIRendererComponent::SetSortingLayer(int32_t sortingLayer) noexcept
{
    m_sortingLayer = sortingLayer;
}

int32_t UIRendererComponent::GetSortingLayer() const noexcept
{
    return m_sortingLayer;
}

} /* namespace tgon */
