#include "PrecompiledHeader.pch"

#include "VertexBuffer.h"

namespace tgon
{
namespace graphics
{

BaseVertexBuffer::BaseVertexBuffer(std::size_t bufferSize, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) :
    m_bufferSize(bufferSize),
    m_isDynamicUsage(isDynamicUsage),
    m_vertexBufferDescs(vertexBufferDescs)
{
}

std::size_t BaseVertexBuffer::GetBufferSize() const noexcept
{
    return m_bufferSize;
}

bool BaseVertexBuffer::IsDynamicUsage() const noexcept
{
    return m_isDynamicUsage;
}

} /* namespace graphics */
} /* namespace tgon */