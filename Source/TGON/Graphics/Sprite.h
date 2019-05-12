/**
 * @file    Sprite.h
 * @author  ggomdyu
 * @since   06/06/2018
 */

#pragma once
#include <memory>
#include <string>

#include "Math/Rect.h"
#include "Math/Vector2.h"
#include "Math/Extent.h"

#include "GraphicsType.h"
#include "Transform.h"

namespace tgon
{

class Texture;

class TGON_API Sprite final
{
/**@section Constructor */
public:
    explicit Sprite(const std::shared_ptr<Texture>& texture);
    Sprite(Sprite&& rhs);

/**@section Destructor */
public:
    virtual ~Sprite() = default;
    
/**@section Method */
public:
    void SetTexture(const std::shared_ptr<Texture>& texture) noexcept;
    void SetTextureRect(const FRect& textureRect);
    void SetBlendMode(BlendMode blendMode) noexcept;
    void SetLayer(int32_t layer) noexcept;
    std::shared_ptr<Texture> GetTexture() noexcept;
    std::shared_ptr<const Texture> GetTexture() const noexcept;
    FRect& GetTextureRect() noexcept;
    const FRect& GetTextureRect() const noexcept;
    BlendMode GetBlendMode() const noexcept;
    void EnableScissorRect() noexcept;
    void DisableScissorRect() noexcept;
    bool IsEnableScissorRect() const noexcept;
    void SetScissorRect(const FRect& rect) noexcept;
    FRect& GetScissorRect() noexcept;
    const FRect& GetScissorRect() const noexcept;
    int32_t GetLayer() const noexcept;
    
/**@section Variable */
private:
    std::shared_ptr<Texture> m_texture;
    BlendMode m_blendMode;
    bool m_enableScissorRect;
    FRect m_scissorRect;
    FRect m_textureRect;
    int32_t m_layer;
};

class NinePatchSprite
{
public:
private:
    Sprite m_sprites[9];
};
    
} /* namespace tgon */
