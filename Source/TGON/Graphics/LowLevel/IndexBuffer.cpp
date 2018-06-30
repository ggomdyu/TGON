#include "PrecompiledHeader.h"

#include "Core/Platform/Config.h"

#include "IndexBuffer.h"
#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLIndexBuffer.h"
#endif

namespace tgon
{

IndexBuffer::IndexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage) :
    m_indexBufferImpl(std::make_unique<IndexBufferImpl>(data, dataBytes, isDynamicUsage))
{
}

IndexBuffer::~IndexBuffer() = default;

void IndexBuffer::SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage)
{
    m_indexBufferImpl->SetData(data, dataBytes, isDynamicUsage);
}

std::size_t IndexBuffer::GetDataBytes() const noexcept
{
    return m_indexBufferImpl->GetDataBytes();
}

void IndexBuffer::Use()
{
    m_indexBufferImpl->Use();
}

void IndexBuffer::Unuse()
{
    m_indexBufferImpl->Unuse();
}

bool IndexBuffer::IsValid() const noexcept
{
    return m_indexBufferImpl->IsValid();
}

bool IndexBuffer::IsDynamicUsage() const noexcept
{
    return m_indexBufferImpl->IsDynamicUsage();
}

} /* namespace tgon */