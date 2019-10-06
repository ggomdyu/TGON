/**
 * @file    Sprite.h
 * @author  ggomdyu
 * @since   06/06/2018
 */

#pragma once
#include "Math/Rect.h"
#include "Graphics/Graphics.h"
#include "Graphics/Texture.h"
#include "Graphics/Transform.h"

namespace tgon
{

class TGON_API UISprite final
{
/**@section Constructor */
public:
    UISprite() noexcept;
    explicit UISprite(const std::shared_ptr<Texture>& texture) noexcept;
    UISprite(const std::shared_ptr<Texture>& texture, const FRect& textureRect) noexcept;
    UISprite(UISprite&& rhs) noexcept;

/**@section Destructor */
public:
    virtual ~UISprite() = default;

/**@section Operator */
public:
    UISprite& operator=(UISprite&& rhs) noexcept;
    
/**@section Method */
public:
    void SetTexture(const std::shared_ptr<Texture>& texture) noexcept;
    void SetTextureRect(const FRect& textureRect) noexcept;
    void SetBlendMode(BlendMode blendMode) noexcept;
    void SetBlendColor(const Color4f& blendColor) noexcept;
    std::shared_ptr<Texture> GetTexture() noexcept;
    std::shared_ptr<const Texture> GetTexture() const noexcept;
    FRect& GetTextureRect() noexcept;
    const FRect& GetTextureRect() const noexcept;
    BlendMode GetBlendMode() const noexcept;
    const Color4f& GetBlendColor() const noexcept;
    void EnableScissorRect() noexcept;
    void DisableScissorRect() noexcept;
    bool IsEnableScissorRect() const noexcept;
    void SetScissorRect(const FRect& rect) noexcept;
    FRect& GetScissorRect() noexcept;
    const FRect& GetScissorRect() const noexcept;
    
/**@section Variable */
private:
    std::shared_ptr<Texture> m_texture;
    FRect m_textureRect;
    BlendMode m_blendMode;
    Color4f m_blendColor;
    FRect m_scissorRect;
    bool m_enableScissorRect;
};

class NinePatchSprite
{
public:
private:
    UISprite m_sprites[9];
};
    
} /* namespace tgon */
