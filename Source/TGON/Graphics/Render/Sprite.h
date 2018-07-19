/**
 * @file    Sprite.h
 * @author  ggomdyu
 * @since   06/06/2018
 */

#pragma once
#include "Core/Math/Matrix4x4.h"
#include "Core/Math/Color.h"

#include "Mesh.h"
#include "Material.h"

namespace tgon
{

class Texture;
class Mesh;
    
class Sprite
{
/* @section Public constructor */
public:
    Sprite();
    
    /* @brief   Initializes the sprite with specified file path. */
    explicit Sprite(const std::string& filePath);
    
    Sprite(const std::string& filePath, const Color4f& blendColor);
    
    Sprite(const std::shared_ptr<Texture>& texture, const std::shared_ptr<Material>& material);
    
    Sprite(const std::shared_ptr<Texture>& texture, const std::shared_ptr<Material>& material, const Color4f& blendColor);

/* @section Public method */
public:
    void Draw(Graphics& graphics);
    
    void SetBlendColor(const Color4f& blendColor);
    
    void SetTexture(const std::shared_ptr<Texture>& texture);
    
    void SetWVP(const Matrix4x4& matWVP) noexcept;

    const Matrix4x4& GetWVP() const noexcept;
    
    const Color4f& GetBlendColor() const noexcept;
    
    const std::shared_ptr<Texture>& GetTexture() const noexcept;
    
    const std::shared_ptr<Material>& GetMaterial() const noexcept;
    
    const std::shared_ptr<Mesh>& GetMesh() const noexcept;

/* @section Private variable */
private:
    Matrix4x4 m_matWVP;
    
    Color4f m_blendColor;
                       
    std::shared_ptr<Mesh> m_quad;
    
    std::shared_ptr<Texture> m_texture;
    
    std::shared_ptr<Material> m_material;
};
    
} /* namespace tgon */
