/**
 * @file    Sprite.h
 * @author  ggomdyu
 * @since   06/06/2018
 */

#pragma once
#include <memory>

#include "../LowLevel/Texture.h"
#include "../Object/GraphicsObject.h"

namespace tgon
{

class TGON_API Sprite final :
    public GraphicsObject
{
/* @section Public constructor */
public:
    /* @brief   Initializes the sprite with specified file path. */
    explicit Sprite(const std::string& filePath);
    
    /* @brief   Initializes the sprite with texture and material. */
    explicit Sprite(const std::shared_ptr<Texture>& texture);

/* @section Public destructor */
public:
    virtual ~Sprite() override = default;
    
/* @section Public method */
public:
    /* @brief   Sets the texture. */
    void SetTexture(const std::shared_ptr<Texture>& texture);
    
    //void SetScissorRect(const I32Rect& scissorRect);

    /* @brief   Gets the texture. */
    std::shared_ptr<Texture>& GetTexture() noexcept;

    /* @brief   Gets the texture. */
    const std::shared_ptr<Texture>& GetTexture() const noexcept;
    
    //const I32Rect& GetScissorRect() const noexcept;

/* @section Private variable */
private:
    std::shared_ptr<Texture> m_texture;

    bool m_isUseScissor;
};

class NinePatchSprite
{
public:
private:
    Sprite m_sprites[9];
};
    
} /* namespace tgon */
