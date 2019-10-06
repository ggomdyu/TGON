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
    void SetSprite(const std::shared_ptr<UISprite>& sprite);
    std::shared_ptr<UISprite> GetSprite() noexcept;
    std::shared_ptr<const UISprite> GetSprite() const noexcept;
    virtual void Update() override;

/**@section Variable */
private:
    std::shared_ptr<UISprite> m_sprite;
};

} /* namespace tgon */