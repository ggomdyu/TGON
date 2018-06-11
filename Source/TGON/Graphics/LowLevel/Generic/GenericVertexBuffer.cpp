#include "PrecompiledHeader.h"

#include "GenericVertexBuffer.h"

namespace tgon
{

GenericVertexBuffer::GenericVertexBuffer(std::size_t dataBytes, bool isDynamicUsage) :
    m_dataBytes(dataBytes),
    m_isDynamicUsage(isDynamicUsage)
{
}

GenericVertexBuffer::GenericVertexBuffer(GenericVertexBuffer&& rhs) :
    m_dataBytes(rhs.m_dataBytes),
    m_isDynamicUsage(rhs.m_isDynamicUsage)
{
    rhs.m_dataBytes = 0;
    rhs.m_isDynamicUsage = false;
}

GenericVertexBuffer& GenericVertexBuffer::operator=(GenericVertexBuffer&& rhs)
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

std::size_t GenericVertexBuffer::GetDataBytes() const noexcept
{
    return m_dataBytes;
}

bool GenericVertexBuffer::IsDynamicUsage() const noexcept
{
    return m_isDynamicUsage;
}

} /* namespace tgon */