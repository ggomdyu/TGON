#include "PrecompiledHeader.h"

#include <cassert>

#include "OpenGLIndexBuffer.h"
#include "OpenGLDebug.h"

namespace tgon
{

OpenGLIndexBuffer::OpenGLIndexBuffer() :
    m_dataBytes(0),
    m_isDynamicUsage(false),
    m_indexBufferHandle(this->CreateIndexBufferHandle())
{
}
    
OpenGLIndexBuffer::OpenGLIndexBuffer(OpenGLIndexBuffer&& rhs) noexcept :
    m_dataBytes(rhs.m_dataBytes),
    m_isDynamicUsage(rhs.m_isDynamicUsage),
    m_indexBufferHandle(rhs.m_indexBufferHandle)
{
    rhs.m_dataBytes = 0;
    rhs.m_isDynamicUsage = false;
    rhs.m_indexBufferHandle = 0;
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    this->Destroy();
}
    
OpenGLIndexBuffer& OpenGLIndexBuffer::operator=(OpenGLIndexBuffer&& rhs) noexcept
{
    this->Destroy();
    
    m_dataBytes = rhs.m_dataBytes;
    m_isDynamicUsage = rhs.m_isDynamicUsage;
    m_indexBufferHandle = rhs.m_indexBufferHandle;
        
    rhs.m_dataBytes = 0;
    rhs.m_isDynamicUsage = false;
    rhs.m_indexBufferHandle = 0;

    return *this;
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

void OpenGLIndexBuffer::Destroy()
{
    if (m_indexBufferHandle != 0)
    {
        TGON_GL_ERROR_CHECK(glDeleteBuffers(1, &m_indexBufferHandle));
        m_indexBufferHandle = 0;
    }
}

}
