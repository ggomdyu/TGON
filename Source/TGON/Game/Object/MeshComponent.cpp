#include "PrecompiledHeader.h"

#include "MeshComponent.h"

namespace tgon
{

MeshComponent::MeshComponent(const std::shared_ptr<Mesh>& mesh) noexcept :
    m_mesh(mesh)
{
}

void MeshComponent::Update()
{
}

void MeshComponent::SetMesh(const std::shared_ptr<Mesh>& mesh)
{
    m_mesh = mesh;
}

const std::shared_ptr<Mesh>& MeshComponent::GetMesh() const noexcept
{
    return m_mesh;
}

} /* namespace tgon */
