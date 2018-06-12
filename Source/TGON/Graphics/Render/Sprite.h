/**
 * @filename    Sprite.h
 * @author      ggomdyu
 * @since       06/06/2018
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
    explicit Sprite(const std::shared_ptr<TextureMaterial>& material);

/* @section Public method */
public:
    void SetTexture(const std::shared_ptr<Texture>& texture);
    void SetWorldViewProjectionMatrix(const Matrix4x4& matWVP) noexcept;

    const std::shared_ptr<Texture>& GetTexture() const noexcept;
    std::shared_ptr<Material>& GetMaterial() noexcept;
    const std::shared_ptr<Material>& GetMaterial() const noexcept;
    Matrix4x4& GetWorldViewProjectionMatrix() noexcept;
    const Matrix4x4& GetWorldViewProjectionMatrix() const noexcept;
    std::shared_ptr<Mesh>& GetMesh() noexcept;
    const std::shared_ptr<Mesh>& GetMesh() const noexcept;

    bool CanBatch(Material* material) const;
    void Draw(Graphics& graphics);

/* @section Private variable */
private:
    Matrix4x4 m_matWVP;

    std::shared_ptr<Mesh> m_quad;
};
    
} /* namespace tgon */
