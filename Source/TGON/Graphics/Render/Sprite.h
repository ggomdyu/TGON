/**
 * @file    Sprite.h
 * @author  ggomdyu
 * @since   06/06/2018
 */

#pragma once
#include "Core/Math/Matrix4x4.h"

#include "GraphicsResource.h"
#include "Mesh.h"
#include "Material.h"

namespace tgon
{
    
class Sprite
{
/* @section Public constructor */
public:
    Sprite();
    explicit Sprite(const std::string& filePath);
    explicit Sprite(std::shared_ptr<TextureMaterial> material);

/* @section Public method */
public:
    void Draw(Graphics& graphics);
    
    void SetTexture(std::shared_ptr<Texture> texture);
    void SetWorldViewProjectionMatrix(const Matrix4x4& matWVP) noexcept;

    std::shared_ptr<const Texture> GetTexture() const noexcept;
    std::shared_ptr<Material> GetMaterial() noexcept;
    std::shared_ptr<const Material> GetMaterial() const noexcept;
    std::shared_ptr<Mesh> GetMesh() noexcept;
    std::shared_ptr<const Mesh> GetMesh() const noexcept;
    Matrix4x4& GetWorldViewProjectionMatrix() noexcept;
    const Matrix4x4& GetWorldViewProjectionMatrix() const noexcept;

    bool CanBatch(Material* material) const;

/* @section Private variable */
private:
    Matrix4x4 m_matWVP;

    std::shared_ptr<Mesh> m_quad;
};
    
} /* namespace tgon */
