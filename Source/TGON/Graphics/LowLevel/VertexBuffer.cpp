#include "PrecompiledHeader.h"

#include "VertexBuffer.h"

namespace tgon
{

VertexBuffer::VertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) :
    m_vertexBufferImpl(data, dataBytes, isDynamicUsage, vertexBufferDescs)
{
}

void VertexBuffer::SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs)
{
    m_vertexBufferImpl.SetData(data, dataBytes, isDynamicUsage, vertexBufferDescs);
}

std::size_t VertexBuffer::GetDataBytes() const noexcept
{
    return m_vertexBufferImpl.GetDataBytes();
}

void VertexBuffer::Use()
{
    m_vertexBufferImpl.Use();
}

void VertexBuffer::Unuse()
{
    m_vertexBufferImpl.Unuse();
}

bool VertexBuffer::IsValid() const noexcept
{
    return m_vertexBufferImpl.IsValid();
}

bool VertexBuffer::IsDynamicUsage() const noexcept
{
    return m_vertexBufferImpl.IsDynamicUsage();
}

} /* namespace tgon */
