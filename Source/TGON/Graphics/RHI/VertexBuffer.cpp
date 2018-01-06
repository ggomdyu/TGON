#include "PrecompiledHeader.pch"

#include "VertexBuffer.h"

namespace tgon
{
namespace graphics
{

std::size_t VertexBuffer::GetBufferSize() const
{
    return m_bufferSize;
}

void* VertexBuffer::GetRawBuffer()
{
    return m_buffer;
}

const void* VertexBuffer::GetRawBuffer() const
{
    return m_buffer;
}

} /* namespace graphics */
} /* namespace tgon */