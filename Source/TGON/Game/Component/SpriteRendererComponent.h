/**
 * @file    SpriteRendererComponent.h
 * @author  ggomdyu
 * @since   08/11/2018
 */

#pragma once
#include "Math/Color.h"

#include "RendererComponent.h"

namespace tgon
{

class Sprite;

class TGON_API SpriteRendererComponent :
	public RendererComponent
{
public:
    TGON_DECLARE_RTTI(SpriteRendererComponent);

/**@section Constructor */
public:
    using RendererComponent::RendererComponent;
    
    SpriteRendererComponent(const std::shared_ptr<Sprite>& sprite, const std::shared_ptr<Material>& material, const Color4f& blendColor);

/**@section Destructor */
public:
    virtual ~SpriteRendererComponent() override = default;

/**@section Method */
public:
    /**@brief   Updates this component. */
    virtual void Update() override;

    /**@brief   Sets a sprite that rendered by this component. */
    void SetSprite(const std::shared_ptr<Sprite>& sprite);
    
    std::shared_ptr<Sprite> GetSprite() noexcept;
    
    std::shared_ptr<const Sprite> GetSprite() const noexcept;

    /**@brief   Sets a color that blended with the sprite. */
    void SetBlendColor(const Color4f& blendColor);

    const Color4f& GetBlendColor() const noexcept;

/**@section Variable */
private:
    std::shared_ptr<Sprite> m_sprite;

    Color4f m_blendColor;
};

} /* namespace tgon */
