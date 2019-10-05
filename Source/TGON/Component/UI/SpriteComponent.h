/**
 * @file    SpriteRendererComponent.h
 * @author  ggomdyu
 * @since   08/11/2018
 */

#pragma once
#include "Math/Color.h"

#include "../RendererComponent.h"

namespace tgon
{

class UISprite;

class TGON_API SpriteRendererComponent :
	public RendererComponent
{
public:
    TGON_DECLARE_RTTI(SpriteRendererComponent)

/**@section Constructor */
public:
    using RendererComponent::RendererComponent;
    
    explicit SpriteRendererComponent(const std::shared_ptr<UISprite>& sprite);
    explicit SpriteRendererComponent(const std::shared_ptr<Material>& material);

/**@section Method */
public:
    virtual void Update() override;
    void SetSprite(const std::shared_ptr<UISprite>& sprite);
    std::shared_ptr<UISprite> GetSprite() noexcept;
    std::shared_ptr<const UISprite> GetSprite() const noexcept;

/**@section Variable */
private:
    std::shared_ptr<UISprite> m_sprite;
};

} /* namespace tgon */
