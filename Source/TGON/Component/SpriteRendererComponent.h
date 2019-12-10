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

class SpriteRendererComponent :
    public RendererComponent
{
public:
    TGON_DECLARE_RTTI(SpriteRendererComponent)

/**@section Constructor */
public:
    SpriteRendererComponent();

/**@section Method */
public:
    void SetTexture(const std::shared_ptr<Texture>& texture) noexcept;
    void SetTextureRect(const FRect& textureRect) noexcept;
    void SetTextureSize(const FExtent2D& textureSize) noexcept;
    void SetFilterMode(FilterMode filterMode) noexcept;
    void SetWrapMode(WrapMode wrapMode) noexcept;
    void SetBlendMode(BlendMode blendMode) noexcept;
    void SetBlendColor(const Color4f& blendColor) noexcept;
    void SetPivot(const Vector2& pivot) noexcept;
    void SetSortingLayer(int32_t sortingLayer) noexcept;
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
    int32_t GetSortingLayer() const noexcept;
    void Update() override;

/**@section Variable */
private:
    std::shared_ptr<UISprite> m_sprite;
    int32_t m_sortingLayer = 0;
};

} /* namespace tgon */
