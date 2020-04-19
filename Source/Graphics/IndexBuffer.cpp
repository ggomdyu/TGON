#include "PrecompiledHeader.h"

#include "IndexBuffer.h"

namespace tg
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

IndexBuffer::~IndexBuffer()
{
    this->Destroy();
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& rhs)
{
    this->Destroy();

    OpenGLIndexBuffer::operator=(std::move(rhs));

    return *this;
}

}
