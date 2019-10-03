#include "PrecompiledHeader.h"

#include "IndexBuffer.h"

namespace tgon
{

PlatformIndexBuffer& IndexBuffer::GetPlatformDependency() noexcept
{
    return *this;
}

const PlatformIndexBuffer& IndexBuffer::GetPlatformDependency() const noexcept
{
    return *this;
}

IndexBuffer::IndexBuffer(IndexBuffer&& rhs) noexcept :
    PlatformIndexBuffer(std::move(rhs))
{
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& rhs)
{
    OpenGLIndexBuffer::operator=(std::move(rhs));
    return *this;
}

IndexBuffer::~IndexBuffer()
{
    this->Destroy();
}

} /* namespace tgon */
