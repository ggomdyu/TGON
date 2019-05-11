#include "PrecompiledHeader.h"

#include "Platform/Application.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Engine/GraphicsModule.h"

#include "MeshRendererComponent.h"

#include "../GameObject.h"

namespace tgon
{

MeshRendererComponent::MeshRendererComponent(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material) :
    RendererComponent(material),
    m_mesh(mesh)
{
}

void MeshRendererComponent::Update()
{
    //m_graphicsModule->GetView().AddBatch(m_material, {m_mesh, &GetOwner()->GetWorldMatrix()});
}
    
void MeshRendererComponent::SetMesh(const std::shared_ptr<Mesh>& mesh)
{
    m_mesh = mesh;
}

const std::shared_ptr<Mesh>& MeshRendererComponent::GetMesh() const noexcept
{
    return m_mesh;
}
    
} /* namespace tgon */
