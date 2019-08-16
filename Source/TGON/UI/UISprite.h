/**
 * @file    Sprite.h
 * @author  ggomdyu
 * @since   06/06/2018
 */

#pragma once
#include <memory>

#include "Math/Rect.h"
#include "Graphics/GraphicsType.h"
#include "Graphics/Transform.h"

namespace tgon
{

class Texture;
class Transform;

class TGON_API UISprite final
{
/**@section Constructor */
public:
    UISprite() noexcept;
    explicit UISprite(const std::shared_ptr<Texture>& texture) noexcept;
    UISprite(const std::shared_ptr<Texture>& texture, const std::shared_ptr<Transform>& transform) noexcept;
    UISprite(const std::shared_ptr<Texture>& texture, const FRect& textureRect, const std::shared_ptr<Transform>& transform) noexcept;
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
    void SetTextureRect(const FRect& textureRect);
    void SetTransform(const std::shared_ptr<Transform>& transform) noexcept;
    void SetBlendMode(BlendMode blendMode) noexcept;
    std::shared_ptr<Texture> GetTexture() noexcept;
    std::shared_ptr<const Texture> GetTexture() const noexcept;
    std::shared_ptr<Transform> GetTransform() noexcept;
    std::shared_ptr<const Transform> GetTransform() const noexcept;
    FRect& GetTextureRect() noexcept;
    const FRect& GetTextureRect() const noexcept;
    BlendMode GetBlendMode() const noexcept;
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
    std::shared_ptr<Transform> m_transform;
    BlendMode m_blendMode;
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
