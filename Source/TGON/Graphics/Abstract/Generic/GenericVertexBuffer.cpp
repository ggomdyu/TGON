#include "PrecompiledHeader.pch"

#include "GenericVertexBuffer.h"

namespace tgon
{
namespace graphics
{

GenericVertexBuffer::GenericVertexBuffer(std::size_t dataBytes, bool isDynamicUsage) :
    m_dataBytes(dataBytes),
    m_isDynamicUsage(isDynamicUsage)
{
}

std::size_t GenericVertexBuffer::GetDataBytes() const noexcept
{
    return m_dataBytes;
}

bool GenericVertexBuffer::IsDynamicUsage() const noexcept
{
    return m_isDynamicUsage;
}

} /* namespace graphics */
} /* namespace tgon */