#include "PrecompiledHeader.h"

#include "VertexBuffer.h"

namespace tgon
{

VertexBuffer::VertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs) :
    m_vertexBufferImpl(data, dataBytes, isDynamicUsage, vertexBufferLayoutDescs)
{
}

VertexBuffer::VertexBuffer(VertexBuffer&& rhs) :
    m_vertexBufferImpl(std::move(rhs.m_vertexBufferImpl))
{
}

void VertexBuffer::SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs)
{
    m_vertexBufferImpl.SetData(data, dataBytes, isDynamicUsage, vertexBufferLayoutDescs);
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
