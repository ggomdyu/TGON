/**
 * @file    SpriteRendererComponent.h
 * @author  ggomdyu
 * @since   08/11/2018
 */

#pragma once
#include "UI/UISprite.h"

#include "RendererComponent.h"

namespace tgon
{

class TGON_API SpriteRendererComponent :
	public RendererComponent
{
public:
    TGON_DECLARE_RTTI(SpriteRendererComponent)

/**@section Constructor */
public:
    explicit SpriteRendererComponent(const std::shared_ptr<UISprite>& sprite);

/**@section Method */
public:
    void SetSprite(const std::shared_ptr<UISprite>& sprite) noexcept;
    void SetSortingLayer(int32_t sortingLayer) noexcept;
    std::shared_ptr<UISprite> GetSprite() noexcept;
    std::shared_ptr<const UISprite> GetSprite() const noexcept;
    int32_t GetSortingLayer() const noexcept;
    virtual void Update() override;

/**@section Variable */
private:
    std::shared_ptr<UISprite> m_sprite;
    int32_t m_sortingLayer = 0;
};

} /* namespace tgon */
