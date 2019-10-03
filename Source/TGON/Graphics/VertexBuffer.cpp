#include "PrecompiledHeader.h"

#include "VertexBuffer.h"

namespace tgon
{

PlatformVertexBuffer& VertexBuffer::GetPlatformDependency() noexcept
{
    return *this;
}

const PlatformVertexBuffer& VertexBuffer::GetPlatformDependency() const noexcept
{
    return *this;
}

VertexBuffer::VertexBuffer(VertexBuffer&& rhs) noexcept :
    PlatformVertexBuffer(std::move(rhs)),
    m_vertexBufferLayoutDescs(std::move(rhs.m_vertexBufferLayoutDescs))
{
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& rhs)
{
    PlatformVertexBuffer::operator=(std::move(rhs));

    m_vertexBufferLayoutDescs = std::move(rhs.m_vertexBufferLayoutDescs);

    return *this;
}

VertexBuffer::~VertexBuffer()
{
    this->Destroy();
}

} /* namespace tgon */
