#include "PrecompiledHeader.pch"

#include <cassert>
#include <GL/glew.h>

#include "OpenGLIndexBuffer.h"

namespace tgon
{

OpenGLIndexBuffer::OpenGLIndexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage) :
    GenericIndexBuffer(dataBytes, isDynamicUsage),
    m_indexBufferHandle(GenerateBuffer())
{
    assert(data != nullptr && dataBytes != 0);

    this->SetData(data, dataBytes, isDynamicUsage);
}

OpenGLIndexBuffer::OpenGLIndexBuffer(OpenGLIndexBuffer&& rhs) :
    GenericIndexBuffer(std::move(rhs)),
    m_indexBufferHandle(rhs.m_indexBufferHandle)
{
    rhs.m_indexBufferHandle = 0;
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_indexBufferHandle);
}

OpenGLIndexBuffer& OpenGLIndexBuffer::operator=(OpenGLIndexBuffer&& rhs)
{
    if (&rhs == this)
    {
        return *this;
    }

    glDeleteBuffers(1, &m_indexBufferHandle);

    OpenGLIndexBuffer::operator=(std::move(rhs));
    m_indexBufferHandle = rhs.m_indexBufferHandle;

    rhs.m_indexBufferHandle = 0;

    return *this;
}

void OpenGLIndexBuffer::SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataBytes, data, isDynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void OpenGLIndexBuffer::Use()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle);
}

void OpenGLIndexBuffer::Unuse()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool OpenGLIndexBuffer::IsValid() const noexcept
{
    return m_indexBufferHandle != 0;
}

GLuint OpenGLIndexBuffer::GenerateBuffer() const
{
    GLuint vertexBufferHandle;
    glGenBuffers(1, &vertexBufferHandle);

    return vertexBufferHandle;
}

} /* namespace tgon */