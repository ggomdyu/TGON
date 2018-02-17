#include "PrecompiledHeader.pch"

#include "GenericIndexBuffer.h"

namespace tgon
{
namespace graphics
{

GenericIndexBuffer::GenericIndexBuffer(std::size_t dataBytes, bool isDynamicUsage) :
    m_dataBytes(dataBytes),
    m_isDynamicUsage(isDynamicUsage)
{
}

std::size_t GenericIndexBuffer::GetDataBytes() const noexcept
{
    return m_dataBytes;
}

bool GenericIndexBuffer::IsDynamicUsage() const noexcept
{
    return m_isDynamicUsage;
}

} /* namespace graphics */
} /* namespace tgon */