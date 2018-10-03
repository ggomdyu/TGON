#include "PrecompiledHeader.h"

#include "Core/Platform/Application.h"

#include "MeshRendererComponent.h"

#include "../GameObject.h"

namespace tgon
{

MeshRendererComponent::MeshRendererComponent(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material) :
    m_mesh(mesh),
    m_material(material),
    m_graphicsModule(Application::GetEngine()->FindModule<GraphicsModule>())
{
}

void MeshRendererComponent::Update()
{
    m_graphicsModule->GetView().AddBatch(m_material, {m_mesh, &GetOwner()->GetWorldMatrix()});
}
    
void MeshRendererComponent::SetMesh(const std::shared_ptr<Mesh>& mesh)
{
    m_mesh = mesh;
}

const std::shared_ptr<Mesh>& MeshRendererComponent::GetMesh() const noexcept
{
    return m_mesh;
}
    
void MeshRendererComponent::SetMaterial(const std::shared_ptr<Material>& material)
{
    m_material = material;
}

const std::shared_ptr<Material>& MeshRendererComponent::GetMaterial() const noexcept
{
    return m_material;
}


} /* namespace tgon */
