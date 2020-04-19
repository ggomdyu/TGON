#include "PrecompiledHeader.h"

#include "VertexBuffer.h"

namespace tg
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

VertexBuffer::~VertexBuffer()
{
    this->Destroy();
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& rhs) noexcept
{
    PlatformVertexBuffer::operator=(std::move(rhs));

    m_vertexBufferLayoutDescs = std::move(rhs.m_vertexBufferLayoutDescs);

    return *this;
}

}
