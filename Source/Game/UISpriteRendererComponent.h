#pragma once

#include "UI/UISprite.h"

#include "UIRendererComponent.h"

namespace tg
{

class UISpriteRendererComponent :
    public UIRendererComponent
{
public:
    TGON_DECLARE_RTTI(UISpriteRendererComponent)

/**@section Constructor */
public:
    UISpriteRendererComponent();

/**@section Method */
public:
    void SetTexture(std::shared_ptr<Texture>&& texture) noexcept;
    void SetTexture(const std::shared_ptr<Texture>& texture) noexcept;
    void SetTextureRect(const FRect& textureRect) noexcept;
    void SetTextureSize(const FExtent2D& textureSize) noexcept;
    void SetBlendMode(BlendMode blendMode) noexcept;
    void SetBlendColor(const Color4f& blendColor) noexcept;
    void SetPivot(const Vector2& pivot) noexcept;
    std::shared_ptr<Texture> GetTexture() noexcept;
    std::shared_ptr<const Texture> GetTexture() const noexcept;
    const FRect& GetTextureRect() const noexcept;
    BlendMode GetBlendMode() const noexcept;
    const Color4f& GetBlendColor() const noexcept;
    const Vector2& GetPivot() const noexcept;
    void Update() override;
};

}
