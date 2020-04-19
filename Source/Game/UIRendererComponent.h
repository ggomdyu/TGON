#pragma once

#include "Engine/UIRendererModule.h"

#include "RendererComponent.h"

namespace tg
{

class UIRendererComponent :
	public RendererComponent
{
public:
    TGON_DECLARE_RTTI(UIRendererComponent)

/**@section Constructor */
public:
    explicit UIRendererComponent(const std::shared_ptr<Material>& material = nullptr) noexcept;
    UIRendererComponent(const std::shared_ptr<Material>& material, const std::shared_ptr<UIElement>& uiElement) noexcept;

/**@section Method */
public:
    void SetSortingLayer(int32_t sortingLayer) noexcept;
    void SetMaterial(const std::shared_ptr<Material>& material) noexcept;
    std::shared_ptr<Material> GetMaterial() noexcept;
    std::shared_ptr<const Material> GetMaterial() const noexcept;
    int32_t GetSortingLayer() const noexcept;

/**@section Variable */
protected:
    int32_t m_sortingLayer = 0;
    std::shared_ptr<UIElement> m_element;
    std::shared_ptr<UIRendererModule> m_uiRendererModule;
};

}
