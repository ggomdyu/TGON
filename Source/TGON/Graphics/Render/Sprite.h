/**
 * @file    Sprite.h
 * @author  ggomdyu
 * @since   06/06/2018
 */

#pragma once
#include <memory>
#include <string>

#include "Core/Platform/Config.h"

enum class BlendMode
{
    AlphaMinusOne,
    SrcMinusDest,
};

namespace tgon
{

class Mesh;
class Texture;
class Graphics;
    
class TGON_API Sprite final
{
/* @section Public constructor */
public:
    /* @brief   Initializes the sprite with specified file path. */
    explicit Sprite(const std::string& filePath);
    
    /* @brief   Initializes the sprite with texture and material. */
    explicit Sprite(const std::shared_ptr<Texture>& texture);

/* @section Public method */
public:
    /* @brief   Sets the texture. */
    void SetTexture(const std::shared_ptr<Texture>& texture);

    /* @brief   Sets the world-view-projection matrix. */
    void SetWVP(const Matrix4x4& matWVP) noexcept;
    
    /* @brief   Gets the texture. */
    std::shared_ptr<Texture>& GetTexture() noexcept;

    /* @brief   Gets the texture. */
    const std::shared_ptr<Texture>& GetTexture() const noexcept;
    
    /* @brief   Gets the world-view-projection matrix. */
    Matrix4x4& GetWVP() noexcept;

    /* @brief   Gets the world-view-projection matrix. */
    const Matrix4x4& GetWVP() const noexcept;

    /* @brief   Gets the mesh. */
    std::shared_ptr<Mesh>& GetQuadMesh() noexcept;

    /* @brief   Gets the mesh. */
    const std::shared_ptr<Mesh>& GetQuadMesh() const noexcept;

/* @section Private variable */
private:
    std::shared_ptr<Mesh> m_quadMesh;

    std::shared_ptr<Texture> m_texture;

    Matrix4x4 m_matWVP;
};

class NinePatchSprite
{
public:
private:
    Sprite m_sprites[9];
};
    
} /* namespace tgon */
