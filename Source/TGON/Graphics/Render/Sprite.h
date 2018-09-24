/**
 * @file    Sprite.h
 * @author  ggomdyu
 * @since   06/06/2018
 */

#pragma once
#include <memory>

#include "Core/Math/Rect.h"
#include "Core/Math/Vector2.h"

#include "../LowLevel/Texture.h"

namespace tgon
{

class TGON_API Sprite final
{
/**@section Public constructor */
public:
    /**@brief   Initializes the sprite with specified file path. */
    explicit Sprite(const std::string& filePath);
    
    /**@brief   Initializes the sprite with texture and material. */
    explicit Sprite(const std::shared_ptr<Texture>& texture);

/**@section Public destructor */
public:
    virtual ~Sprite() = default;
    
/**@section Public method */
public:
    /**@brief   Sets the origin point of the sprite. */
    void SetOriginPoint(const Vector2& originPoint);

    /**@brief   Gets the origin point of the sprite. */
    Vector2& GetOriginPoint() noexcept;

    /**@brief   Gets the origin point of the sprite. */
    const Vector2& GetOriginPoint() const noexcept;

    /**@brief   Sets the anchor point of the sprite. */
    void SetAnchorPoint(const Vector2& anchorPoint);
    
    /**@brief   Gets the anchor point of the sprite. */
    Vector2& GetAnchorPoint() noexcept;
    
    /**@brief   Gets the anchor point of the sprite. */
    const Vector2& GetAnchorPoint() const noexcept;

    /**@brief   Sets the texture of the sprite. */
    void SetTexture(const std::shared_ptr<Texture>& texture);

    /**@brief   Gets the texture of the sprite. */
    std::shared_ptr<Texture>& GetTexture() noexcept;

    /**@brief   Gets the texture of the sprite. */
    std::shared_ptr<const Texture> GetTexture() const noexcept;
    
/**@section Private variable */
private:
    Vector2 m_originPoint;

    Vector2 m_anchorPoint;

    std::shared_ptr<Texture> m_texture;
};

class NinePatchSprite
{
public:
private:
    Sprite m_sprites[9];
};
    
} /* namespace tgon */
