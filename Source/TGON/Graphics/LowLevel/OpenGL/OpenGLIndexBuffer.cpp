#include "PrecompiledHeader.h"

#include <cassert>

#include "OpenGLIndexBuffer.h"
#include "OpenGLUtility.h"

namespace tgon
{

OpenGLIndexBuffer::OpenGLIndexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage) :
    m_dataBytes(dataBytes),
    m_isDynamicUsage(isDynamicUsage),
    m_indexBufferHandle(this->CreateIndexBufferHandle())
{
    assert(data != nullptr && dataBytes != 0 && m_indexBufferHandle != 0);

    this->SetData(data, dataBytes, isDynamicUsage);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    TGON_GL_ERROR_CHECK(glDeleteBuffers(1, &m_indexBufferHandle));
}

void OpenGLIndexBuffer::SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage)
{
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle));
    TGON_GL_ERROR_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataBytes, data, isDynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
}

std::size_t OpenGLIndexBuffer::GetDataBytes() const noexcept
{
    return m_dataBytes;
}

void OpenGLIndexBuffer::Use()
{
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle));
}

void OpenGLIndexBuffer::Unuse()
{
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

bool OpenGLIndexBuffer::IsValid() const noexcept
{
    return m_indexBufferHandle != 0;
}

bool OpenGLIndexBuffer::IsDynamicUsage() const noexcept
{
    return m_isDynamicUsage;
}

GLuint OpenGLIndexBuffer::CreateIndexBufferHandle() const
{
    GLuint vertexBufferHandle;
    TGON_GL_ERROR_CHECK(glGenBuffers(1, &vertexBufferHandle));

    return vertexBufferHandle;
}

} /* namespace tgon */
