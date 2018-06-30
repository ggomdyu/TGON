#include "PrecompiledHeader.h"

#include <cassert>

#include "OpenGLIndexBuffer.h"
#include "OpenGLUtility.h"

namespace tgon
{

IndexBufferImpl::IndexBufferImpl(const void* data, std::size_t dataBytes, bool isDynamicUsage) :
    m_dataBytes(dataBytes),
    m_isDynamicUsage(isDynamicUsage),
    m_indexBufferHandle(this->CreateIndexBufferHandle())
{
    assert(data != nullptr && dataBytes != 0);

    this->SetData(data, dataBytes, isDynamicUsage);
}

IndexBufferImpl::~IndexBufferImpl()
{
    TGON_GL_ERROR_CHECK(glDeleteBuffers(1, &m_indexBufferHandle));
}

void IndexBufferImpl::SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage)
{
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle));
    TGON_GL_ERROR_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataBytes, data, isDynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
}

std::size_t IndexBufferImpl::GetDataBytes() const noexcept
{
    return m_dataBytes;
}

void IndexBufferImpl::Use()
{
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle));
}

void IndexBufferImpl::Unuse()
{
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

bool IndexBufferImpl::IsValid() const noexcept
{
    return m_indexBufferHandle != 0;
}

bool IndexBufferImpl::IsDynamicUsage() const noexcept
{
    return m_isDynamicUsage;
}

GLuint IndexBufferImpl::CreateIndexBufferHandle() const
{
    GLuint vertexBufferHandle;
    TGON_GL_ERROR_CHECK(glGenBuffers(1, &vertexBufferHandle));

    return vertexBufferHandle;
}

} /* namespace tgon */