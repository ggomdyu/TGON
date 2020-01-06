/**
 * @file    Sprite.h
 * @author  ggomdyu
 * @since   06/06/2018
 */

#pragma once
#include "Graphics/Graphics.h"
#include "Graphics/Texture.h"
#include "Math/Rect.h"
#include "Math/Vector2.h"
#include "Math/Matrix4x4.h"

#include "UIElement.h"

namespace tgon
{

class UISprite :
    public UIElement
{
/**@section Constructor */
public:
    UISprite() noexcept = default;
    UISprite(const std::shared_ptr<Texture>& texture, FilterMode filterMode = FilterMode::Bilinear, WrapMode wrapMode = WrapMode::Clamp, BlendMode blendMode = BlendMode::Normal, Color4f blendColor = Color4f(1.0f, 1.0f, 1.0f, 1.0f)) noexcept;

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
    const Vector2& GetPivot() const noexcept;
    void GetBatches(std::vector<UIBatch>* batches, const Matrix4x4& matWorld, std::vector<float>* vertices) const override;
       
/**@section Variable */
private:
    std::shared_ptr<Texture> m_texture;
    FRect m_textureRect;
    FExtent2D m_textureSize;
    FilterMode m_filterMode = FilterMode::Bilinear;
    WrapMode m_wrapMode = WrapMode::Clamp;
    BlendMode m_blendMode = BlendMode::Normal;
    Color4f m_blendColor = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
    Vector2 m_pivot = Vector2(0.5f, 0.5f);
};

} /* namespace tgon */
