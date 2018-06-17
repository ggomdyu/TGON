#include "PrecompiledHeader.h"

#include "Mesh.h"

namespace tgon
{

Mesh::Mesh(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer, std::shared_ptr<Material> material) :
    m_vertexBuffer(vertexBuffer),
    m_indexBuffer(indexBuffer),
    m_material(material)
{
}

void Mesh::SetVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer)
{
    m_vertexBuffer = vertexBuffer;
}

void Mesh::SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer)
{
    m_indexBuffer = indexBuffer;
}

void Mesh::SetMaterial(std::shared_ptr<Material> material)
{
    m_material = material;
}
    
std::shared_ptr<VertexBuffer> Mesh::GetVertexBuffer() noexcept
{
    return m_vertexBuffer;
}

std::shared_ptr<const VertexBuffer> Mesh::GetVertexBuffer() const noexcept
{
    return m_vertexBuffer;
}

std::shared_ptr<IndexBuffer> Mesh::GetIndexBuffer() noexcept
{
    return m_indexBuffer;
}
    
std::shared_ptr<const IndexBuffer> Mesh::GetIndexBuffer() const noexcept
{
    return m_indexBuffer;
}

std::shared_ptr<Material> Mesh::GetMaterial() noexcept
{
    return m_material;
}
    
std::shared_ptr<const Material> Mesh::GetMaterial() const noexcept
{
    return m_material;
}

} /* namespace tgon */
