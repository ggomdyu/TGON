#include "PrecompiledHeader.h"

#include <cassert>

#include "OpenGLDebug.h"

#include "../IndexBuffer.h"

#if TGON_GRAPHICS_OPENGL
namespace tgon
{
namespace
{

GLuint CreateIndexBufferHandle()
{
    GLuint vertexBufferHandle;
    TGON_GL_ERROR_CHECK(glGenBuffers(1, &vertexBufferHandle));

    return vertexBufferHandle;
}

} /* namespace */

OpenGLIndexBuffer::OpenGLIndexBuffer(GLuint indexBufferHandle) noexcept :
    m_indexBufferHandle(indexBufferHandle)
{
}

OpenGLIndexBuffer::OpenGLIndexBuffer(OpenGLIndexBuffer&& rhs) noexcept :
    m_indexBufferHandle(rhs.m_indexBufferHandle)
{
    rhs.m_indexBufferHandle = 0;
}

OpenGLIndexBuffer& OpenGLIndexBuffer::operator=(OpenGLIndexBuffer&& rhs) noexcept
{
    m_indexBufferHandle = rhs.m_indexBufferHandle;

    rhs.m_indexBufferHandle = 0;

    return *this;
}

GLuint OpenGLIndexBuffer::GetIndexBufferHandle() const noexcept
{
    return m_indexBufferHandle;
}

IndexBuffer::IndexBuffer() :
    OpenGLIndexBuffer(CreateIndexBufferHandle())
{
}

void IndexBuffer::SetData(const void* data, int32_t dataBytes, bool isDynamicUsage)
{
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle));
    TGON_GL_ERROR_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataBytes, data, isDynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
}

void IndexBuffer::Use()
{
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle));
}

void IndexBuffer::Unuse()
{
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::Destroy()
{
    if (m_indexBufferHandle != 0)
    {
        TGON_GL_ERROR_CHECK(glDeleteBuffers(1, &m_indexBufferHandle));
        m_indexBufferHandle = 0;
    }
}

} /* namespace tgon */
#endif
