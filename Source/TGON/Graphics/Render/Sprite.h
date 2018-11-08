/**
 * @file    Sprite.h
 * @author  ggomdyu
 * @since   06/06/2018
 */

#pragma once
#include <memory>
#include <string>

#include "Core/Math/Rect.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Extent.h"

namespace tgon
{

class Texture;

class TGON_API Sprite final
{
/**@section Public constructor */
public:
    /**@brief   Initializes the sprite with texture. */
    explicit Sprite(const std::shared_ptr<Texture>& texture);

    Sprite(Sprite&& rhs);

/**@section Public destructor */
public:
    virtual ~Sprite() = default;
    
/**@section Public method */
public:
    /**@brief   Sets a texture of the sprite. */
    void SetTexture(const std::shared_ptr<Texture>& texture) noexcept;

    /**@brief   Gets the texture of the sprite. */
    std::shared_ptr<Texture>& GetTexture() noexcept;

    /**@brief   Gets the texture of the sprite. */
    std::shared_ptr<const Texture> GetTexture() const noexcept;

/**@section Private variable */
private:
    std::shared_ptr<Texture> m_texture;
};

class NinePatchSprite
{
public:
private:
    Sprite m_sprites[9];
};
    
} /* namespace tgon */
