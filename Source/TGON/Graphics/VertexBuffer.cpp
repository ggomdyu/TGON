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

} /* namespace tgon */
