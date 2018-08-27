/**
 * @file    Sprite.h
 * @author  ggomdyu
 * @since   06/06/2018
 */

#pragma once
#include <memory>

#include "Core/Math/Rect.h"

#include "../LowLevel/Texture.h"

namespace tgon
{

class TGON_API Sprite final
{
/* @section Public constructor */
public:
    /* @brief   Initializes the sprite with specified file path. */
    explicit Sprite(const std::string& filePath);
    
    /* @brief   Initializes the sprite with texture and material. */
    explicit Sprite(const std::shared_ptr<Texture>& texture);

/* @section Public destructor */
public:
    virtual ~Sprite() = default;
    
/* @section Public method */
public:
    /* @brief   Sets the texture of the sprite. */
    void SetTexture(const std::shared_ptr<Texture>& texture);

    /* @brief   Gets the texture of the sprite. */
    std::shared_ptr<Texture>& GetTexture() noexcept;

    /* @brief   Gets the texture of the sprite. */
    std::shared_ptr<const Texture> GetTexture() const noexcept;
    
    /* @brief   Sets the size of the texture. */
    void SetTextureSize(const I32Rect& textureSize);
    
    /* @brief   Gets the size of the texture. */
    I32Rect& GetTextureSize() noexcept;
    
    /* @brief   Gets the size of the texture. */
    const I32Rect& GetTextureSize() const noexcept;
    
/* @section Private variable */
private:
    std::shared_ptr<Texture> m_texture;
    
    I32Rect m_textureSize;
};

class NinePatchSprite
{
public:
private:
    Sprite m_sprites[9];
};
    
} /* namespace tgon */
