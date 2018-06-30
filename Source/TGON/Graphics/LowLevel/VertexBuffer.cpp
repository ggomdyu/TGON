#include "PrecompiledHeader.h"

#include "Core/Platform/Config.h"

#include "VertexBuffer.h"
#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLVertexBuffer.h"
#endif

namespace tgon
{

VertexBuffer::~VertexBuffer() = default;

VertexBuffer::VertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) :
    m_vertexBufferImpl(std::make_unique<VertexBufferImpl>(data, dataBytes, isDynamicUsage, vertexBufferDescs))
{
}

void VertexBuffer::SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs)
{
    m_vertexBufferImpl->SetData(data, dataBytes, isDynamicUsage, vertexBufferDescs);
}

std::size_t VertexBuffer::GetDataBytes() const noexcept
{
    return m_vertexBufferImpl->GetDataBytes();
}

void VertexBuffer::Use()
{
    m_vertexBufferImpl->Use();
}

void VertexBuffer::Unuse()
{
    m_vertexBufferImpl->Unuse();
}

bool VertexBuffer::IsValid() const noexcept
{
    return m_vertexBufferImpl->IsValid();
}

bool VertexBuffer::IsDynamicUsage() const noexcept
{
    return m_vertexBufferImpl->IsDynamicUsage();
}

} /* namespace tgon */