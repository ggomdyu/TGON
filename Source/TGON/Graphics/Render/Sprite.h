/**
 * @file    Sprite.h
 * @author  ggomdyu
 * @since   06/06/2018
 */

#pragma once
#include "Core/Math/Matrix4x4.h"

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
    Sprite(const std::shared_ptr<Texture>& texture, const std::shared_ptr<Material>& material);
    explicit Sprite(const std::string& filePath);

/* @section Public method */
public:
    void Draw(Graphics& graphics);
    
    void SetTexture(const std::shared_ptr<Texture>& texture);
    void SetWorldViewProjectionMatrix(const Matrix4x4& matWVP) noexcept;

    const std::shared_ptr<Texture>& GetTexture() const noexcept;
    const std::shared_ptr<Material>& GetMaterial() const noexcept;
    const std::shared_ptr<Mesh>& GetMesh() const noexcept;
    const Matrix4x4& GetWorldViewProjectionMatrix() const noexcept;

/* @section Private variable */
private:
    Matrix4x4 m_matWVP;

    std::shared_ptr<Mesh> m_quad;
    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<Material> m_material;
};
    
} /* namespace tgon */
