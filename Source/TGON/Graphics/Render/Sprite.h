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
#include "Graphics/LowLevel/Texture.h"

namespace tgon
{

class Material;

class TGON_API Sprite final
{
/**@section Public constructor */
public:
    /**@brief   Initializes the sprite with specified file path. */
    template <typename _StringType>
    explicit Sprite(_StringType&& filePath);

    /**@brief   Initializes the sprite with texture and material. */
    explicit Sprite(const std::shared_ptr<Texture>& texture);

    Sprite(Sprite&& rhs);

/**@section Public destructor */
public:
    virtual ~Sprite() = default;
    
/**@section Public method */
public:
    /**@brief   Sets a material to sprite. */
    void SetMaterial(const std::shared_ptr<Material>& material) noexcept;

    ///**@brief   Sets an origin point of the sprite. */
    //void SetOriginPoint(const Vector2& originPoint) noexcept;

    ///**@brief   Sets an anchor point of the sprite. */
    //void SetAnchorPoint(const Vector2& anchorPoint) noexcept;

    /**@brief   Sets a texture of the sprite. */
    void SetTexture(const std::shared_ptr<Texture>& texture) noexcept;

    /**@brief   Gets a material that used in the sprite. */
    std::shared_ptr<Material>& GetMaterial() noexcept;

    /**@brief   Gets a material that used in the sprite. */
    std::shared_ptr<const Material> GetMaterial() const noexcept;

    ///**@brief   Gets an origin point of the sprite. */
    //Vector2& GetOriginPoint() noexcept;

    ///**@brief   Gets an origin point of the sprite. */
    //const Vector2& GetOriginPoint() const noexcept;

    ///**@brief   Gets an anchor point of the sprite. */
    //Vector2& GetAnchorPoint() noexcept;
    //
    ///**@brief   Gets an anchor point of the sprite. */
    //const Vector2& GetAnchorPoint() const noexcept;

    /**@brief   Gets the texture of the sprite. */
    std::shared_ptr<Texture>& GetTexture() noexcept;

    /**@brief   Gets the texture of the sprite. */
    std::shared_ptr<const Texture> GetTexture() const noexcept;

    /**@brief   Gets the size of texture. */
    const Extent2D GetTextureSize() const noexcept;

/**@section Private variable */
private:
    //Vector2 m_originPoint;
    //Vector2 m_anchorPoint;
    std::shared_ptr<Material> m_material;
    std::shared_ptr<Texture> m_texture;
};

template<typename _StringType>
inline Sprite::Sprite(_StringType&& filePath) :
    Sprite(std::make_shared<Texture>(std::forward<_StringType>(filePath)))
{
}

class NinePatchSprite
{
public:
private:
    Sprite m_sprites[9];
};
    
} /* namespace tgon */
