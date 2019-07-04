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

class Sprite;

class TGON_API SpriteRendererComponent :
	public RendererComponent
{
public:
    TGON_DECLARE_RTTI(SpriteRendererComponent);

/**@section Constructor */
public:
    using RendererComponent::RendererComponent;
    
    explicit SpriteRendererComponent(const std::shared_ptr<Sprite>& sprite);
    SpriteRendererComponent(const std::shared_ptr<Material>& material, const Color4f& blendColor);

/**@section Method */
public:
    virtual void Update() override;
    void SetSprite(const std::shared_ptr<Sprite>& sprite);
    std::shared_ptr<Sprite> GetSprite() noexcept;
    std::shared_ptr<const Sprite> GetSprite() const noexcept;
    void SetBlendColor(const Color4f& blendColor);
    const Color4f& GetBlendColor() const noexcept;

/**@section Variable */
private:
    std::shared_ptr<Sprite> m_sprite;

    Color4f m_blendColor;
};

} /* namespace tgon */
