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

class CanvasSprite;

class TGON_API CanvasSpriteRendererComponent :
	public RendererComponent
{
public:
    TGON_DECLARE_RTTI(CanvasSpriteRendererComponent);

/**@section Constructor */
public:
    using RendererComponent::RendererComponent;
    
    CanvasSpriteRendererComponent(const std::shared_ptr<Material>& material, const Color4f& blendColor);

/**@section Method */
public:
    virtual void Update() override;
    void SetSprite(const std::shared_ptr<CanvasSprite>& sprite);
    std::shared_ptr<CanvasSprite> GetSprite() noexcept;
    std::shared_ptr<const CanvasSprite> GetSprite() const noexcept;
    void SetBlendColor(const Color4f& blendColor);
    const Color4f& GetBlendColor() const noexcept;

/**@section Variable */
private:
    std::shared_ptr<CanvasSprite> m_sprite;

    Color4f m_blendColor;
};

} /* namespace tgon */
