#include "PrecompiledHeader.h"

#include "Material.h"
#include "Mesh.h"
#include "MeshRenderer.h"

namespace tgon
{

MeshRenderer::MeshRenderer(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material) :
    m_mesh(mesh),
    m_material(material)
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
    
const std::shared_ptr<Mesh>& MeshRenderer::GetMesh() const noexcept
{
    return m_mesh;
}
    
const std::shared_ptr<Material>& MeshRenderer::GetMaterial() const noexcept
{
    return m_material;
}

} /* namespace tgon */
