/**
 * @file    Mesh.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include <memory>

#include "Core/Math/Matrix4x4.h"

namespace tgon
{
    
class Mesh;
class Material;
    
class MeshRenderer final
{
/* @section Public constructor */
public:
    /* @brief   Initializes the mesh renderer with mesh, material, and world-view-projection matrix. */
    MeshRenderer(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const Matrix4x4& matWVP);
    
/* @section Public method */
public:
    /* @brief   Sets the mesh. */
    void SetMesh(const std::shared_ptr<Mesh>& mesh);
    
    /* @brief   Sets the material. */
    void SetMaterial(const std::shared_ptr<Material>& mesh);
    
    /* @brief   Sets the world-view-projection matrix. */
    void SetWVP(const Matrix4x4& matWVP) noexcept;
    
    /* @brief   Gets the mesh. */
    const std::shared_ptr<Mesh>& GetMesh() const noexcept;
    
    /* @brief   Gets the material. */
    const std::shared_ptr<Material>& GetMaterial() const noexcept;
    
    /* @brief   Gets the world-view-projection matrix. */
    Matrix4x4& GetWVP() noexcept;
    
    /* @brief   Gets the world-view-projection matrix. */
    const Matrix4x4& GetWVP() const noexcept;

/* @section Protected variable */
protected:
    std::shared_ptr<Mesh> m_mesh;
    
    std::shared_ptr<Material> m_material;
    
    Matrix4x4 m_matWVP;
};

} /* namespace tgon */
