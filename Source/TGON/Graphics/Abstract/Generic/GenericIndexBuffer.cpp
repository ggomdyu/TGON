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

GenericIndexBuffer::GenericIndexBuffer(GenericIndexBuffer&& rhs) :
    m_dataBytes(rhs.m_dataBytes),
    m_isDynamicUsage(rhs.m_isDynamicUsage)
{
    rhs.m_dataBytes = 0;
    rhs.m_isDynamicUsage = false;
}

GenericIndexBuffer& GenericIndexBuffer::operator=(GenericIndexBuffer&& rhs)
{
    if (&rhs == this)
    {
        return *this;
    }

    m_dataBytes = rhs.m_dataBytes;
    m_isDynamicUsage = rhs.m_isDynamicUsage;

    rhs.m_dataBytes = 0;
    rhs.m_isDynamicUsage = false;

    return *this;
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