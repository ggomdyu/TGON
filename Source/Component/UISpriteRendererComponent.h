/**
 * @file    SpriteRendererComponent.h
 * @author  ggomdyu
 * @since   08/11/2018
 */

#pragma once
#include "UI/UISprite.h"

#include "UIRendererComponent.h"

namespace tgon
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
    void SetFilterMode(FilterMode filterMode) noexcept;
    void SetWrapMode(WrapMode wrapMode) noexcept;
    void SetBlendMode(BlendMode blendMode) noexcept;
    void SetBlendColor(const Color4f& blendColor) noexcept;
    void SetPivot(const Vector2& pivot) noexcept;
    std::shared_ptr<Texture> GetTexture() noexcept;
    std::shared_ptr<const Texture> GetTexture() const noexcept;
    const FRect& GetTextureRect() const noexcept;
    FilterMode GetFilterMode() const noexcept;
    WrapMode GetWrapMode() const noexcept;
    BlendMode GetBlendMode() const noexcept;
    const Color4f& GetBlendColor() const noexcept;
    void EnableScissorRect() noexcept;
    void DisableScissorRect() noexcept;
    bool IsEnableScissorRect() const noexcept;
    void SetScissorRect(const FRect& rect) noexcept;
    const FRect& GetScissorRect() const noexcept;
    const Vector2& GetPivot() const noexcept;
    void Update() override;

/**@section Variable */
protected:
    std::shared_ptr<UISprite> m_sprite;
};

} /* namespace tgon */
