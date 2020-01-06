#include "PrecompiledHeader.h"

#if TGON_GRAPHICS_OPENGL
#include <cassert>

#include "OpenGLDebug.h"

#include "../VertexBuffer.h"

namespace tgon
{
namespace
{

constexpr GLenum ConvertVertexFormatTypeToNative(VertexFormatType vertexFormatType) noexcept
{
    constexpr GLenum nativeVertexFormatTypes[] = {
        GL_FLOAT,
        GL_DOUBLE,
        GL_BYTE,
        GL_UNSIGNED_BYTE,
        GL_SHORT,
        GL_UNSIGNED_SHORT,
        GL_INT,
        GL_UNSIGNED_INT
    };
    
    return nativeVertexFormatTypes[static_cast<int>(vertexFormatType)];
}

GLuint CreateVertexBufferHandle()
{
    GLuint vertexBufferHandle;
    TGON_GL_ERROR_CHECK(glGenBuffers(1, &vertexBufferHandle));

    return vertexBufferHandle;
}

} /* namespace */

OpenGLVertexBuffer::OpenGLVertexBuffer(GLuint vertexBufferHandle) noexcept :
    m_vertexBufferHandle(vertexBufferHandle)
{
}

OpenGLVertexBuffer::OpenGLVertexBuffer(OpenGLVertexBuffer&& rhs) noexcept :
    m_vertexBufferHandle(rhs.m_vertexBufferHandle)
{
    rhs.m_vertexBufferHandle = 0;
}

OpenGLVertexBuffer& OpenGLVertexBuffer::operator=(OpenGLVertexBuffer&& rhs) noexcept
{
    m_vertexBufferHandle = rhs.m_vertexBufferHandle;

    rhs.m_vertexBufferHandle = 0;

    return *this;
}

GLuint OpenGLVertexBuffer::GetVertexBufferHandle() const noexcept
{
    return m_vertexBufferHandle;
}

VertexBuffer::VertexBuffer() :
    OpenGLVertexBuffer(CreateVertexBufferHandle())
{
}

VertexBuffer::VertexBuffer(const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs) :
    OpenGLVertexBuffer(CreateVertexBufferHandle()),
    m_vertexBufferLayoutDescs(vertexBufferLayoutDescs)
{
}

void VertexBuffer::SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage)
{
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle));
    TGON_GL_ERROR_CHECK(glBufferData(GL_ARRAY_BUFFER, dataBytes, data, isDynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
}

void VertexBuffer::SetLayoutDescriptor(const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs)
{
    m_vertexBufferLayoutDescs = vertexBufferLayoutDescs;
}

void VertexBuffer::Use()
{
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle));

    for (size_t i = 0; i < m_vertexBufferLayoutDescs.size(); ++i)
    {
        const auto& vertexBufferDesc = m_vertexBufferLayoutDescs[i];

        TGON_GL_ERROR_CHECK(glEnableVertexAttribArray(GLuint(i)));
        TGON_GL_ERROR_CHECK(glVertexAttribPointer(
            static_cast<GLuint>(vertexBufferDesc.attribute),
            vertexBufferDesc.dimension,
            ConvertVertexFormatTypeToNative(vertexBufferDesc.type),
            vertexBufferDesc.normalized,
            vertexBufferDesc.stride,
            reinterpret_cast<const void*>(vertexBufferDesc.offset)
        ));
    }
}

void VertexBuffer::Unuse()
{
    for (size_t i = 0; i < m_vertexBufferLayoutDescs.size(); ++i)
    {
        TGON_GL_ERROR_CHECK(glDisableVertexAttribArray(GLuint(i)));
    }
}

void VertexBuffer::Destroy()
{
    if (m_vertexBufferHandle != 0)
    {
        TGON_GL_ERROR_CHECK(glDeleteBuffers(1, &m_vertexBufferHandle));
        m_vertexBufferHandle = 0;
    }
}

} /* namespace tgon */
#endif
