#include "PrecompiledHeader.h"

#include "Mesh.h"

namespace tgon
{

Mesh::Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, const std::shared_ptr<Material>& material) :
    m_vertexBuffer(vertexBuffer),
    m_indexBuffer(indexBuffer),
    m_material(material)
{
}

void Mesh::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    m_vertexBuffer = vertexBuffer;
}

void Mesh::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    m_indexBuffer = indexBuffer;
}

void Mesh::SetMaterial(const std::shared_ptr<Material>& material)
{
    m_material = material;
}
    
std::shared_ptr<VertexBuffer>& Mesh::GetVertexBuffer() noexcept
{
    return m_vertexBuffer;
}

const std::shared_ptr<VertexBuffer>& Mesh::GetVertexBuffer() const noexcept
{
    return m_vertexBuffer;
}

std::shared_ptr<IndexBuffer>& Mesh::GetIndexBuffer() noexcept
{
    return m_indexBuffer;
}
    
const std::shared_ptr<IndexBuffer>& Mesh::GetIndexBuffer() const noexcept
{
    return m_indexBuffer;
}

std::shared_ptr<Material>& Mesh::GetMaterial() noexcept
{
    return m_material;
}
    
const std::shared_ptr<Material>& Mesh::GetMaterial() const noexcept
{
    return m_material;
}

} /* namespace tgon */
