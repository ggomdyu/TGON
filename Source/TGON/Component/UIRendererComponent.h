/**
 * @file    UIRendererComponent.h
 * @author  ggomdyu
 * @since   01/05/2020
 */

#pragma once
#include "Engine/UIRendererModule.h"

#include "RendererComponent.h"

namespace tgon
{

class UIRendererComponent :
	public RendererComponent
{
public:
    TGON_DECLARE_RTTI(UIRendererComponent)

/**@section Constructor */
public:
    explicit UIRendererComponent(const std::shared_ptr<Material>& material = nullptr) noexcept;

/**@section Method */
public:
    void SetSortingLayer(int32_t sortingLayer) noexcept;
    int32_t GetSortingLayer() const noexcept;

/**@section Variable */
protected:
    int32_t m_sortingLayer = 0;
    std::shared_ptr<class UIRendererModule> m_uiRendererModule;
};

} /* namespace tgon */
