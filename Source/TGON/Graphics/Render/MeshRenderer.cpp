#include "PrecompiledHeader.h"

#include "Material/Material.h"
#include "Mesh.h"
#include "MeshRenderer.h"

namespace tgon
{

MeshRenderer::MeshRenderer(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const Matrix4x4& matWVP) :
    m_mesh(mesh),
    m_material(material),
    m_matWVP(matWVP)
{
}

void MeshRenderer::SetMesh(const std::shared_ptr<Mesh>& mesh)
{
    m_mesh = mesh;
}
    
void MeshRenderer::SetMaterial(const std::shared_ptr<Material>& material)
{
    m_material = material;
}
    
void MeshRenderer::SetWVP(const Matrix4x4& matWVP) noexcept
{
    m_matWVP = matWVP;
}

const std::shared_ptr<Mesh>& MeshRenderer::GetMesh() const noexcept
{
    return m_mesh;
}
    
const std::shared_ptr<Material>& MeshRenderer::GetMaterial() const noexcept
{
    return m_material;
}

Matrix4x4& MeshRenderer::GetWVP() noexcept
{
    return m_matWVP;
}
    
const Matrix4x4& MeshRenderer::GetWVP() const noexcept
{
    return m_matWVP;
}

} /* namespace tgon */
