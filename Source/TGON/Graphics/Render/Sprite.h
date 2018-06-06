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
    Sprite() noexcept;
    explicit Sprite(const std::shared_ptr<TextureMaterial>& material) noexcept;

/* @section Public method */
public:
    void SetWorldViewProjectionMatrix(const Matrix4x4& matWVP) noexcept;
    Matrix4x4& GetWorldViewProjectionMatrix() noexcept;
    const Matrix4x4& GetWorldViewProjectionMatrix() const noexcept;
    void SetTexture(const std::shared_ptr<Texture>& texture);
    const std::shared_ptr<Texture>& GetTexture() const noexcept;
    std::shared_ptr<TextureMaterial> GetMaterial() noexcept;
    std::shared_ptr<TextureMaterial> GetMaterial() const noexcept;
    void Draw(GraphicsContext& context);

/* @section Private variable */
private:
    Matrix4x4 m_matWVP;

    std::shared_ptr<Mesh> m_quad;
};
    
} /* namespace tgon */
