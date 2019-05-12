#include "PrecompiledHeader.h"

#include <cassert>

#include "OpenGLUtility.h"
#include "OpenGLVertexBuffer.h"

namespace tgon
{

OpenGLVertexBuffer::OpenGLVertexBuffer() :
    m_vertexBufferHandle(this->CreateVertexBufferHandle())
{
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs) :
    m_vertexBufferHandle(this->CreateVertexBufferHandle()),
    m_vertexBufferLayoutDescs(vertexBufferLayoutDescs)

{
}

OpenGLVertexBuffer::OpenGLVertexBuffer(OpenGLVertexBuffer&& rhs) noexcept :
    m_vertexBufferHandle(rhs.m_vertexBufferHandle),
    m_vertexBufferLayoutDescs(std::move(rhs.m_vertexBufferLayoutDescs))
{
    rhs.m_vertexBufferHandle = 0;
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    if (m_vertexBufferHandle != 0)
    {
        TGON_GL_ERROR_CHECK(glDeleteBuffers(1, &m_vertexBufferHandle));
    }
}
    
OpenGLVertexBuffer& OpenGLVertexBuffer::operator=(OpenGLVertexBuffer&& rhs) noexcept
{
    if (&rhs != this)
    {
        m_vertexBufferHandle = rhs.m_vertexBufferHandle;
        m_vertexBufferLayoutDescs = std::move(rhs.m_vertexBufferLayoutDescs);
        
        rhs.m_vertexBufferHandle = 0;
    }
    
    return *this;
}

void OpenGLVertexBuffer::SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage)
{
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle));
    TGON_GL_ERROR_CHECK(glBufferData(GL_ARRAY_BUFFER, dataBytes, data, isDynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
}

void OpenGLVertexBuffer::SetVertexBufferLayoutDescriptor(const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs)
{
    m_vertexBufferLayoutDescs = vertexBufferLayoutDescs;
}

void OpenGLVertexBuffer::Use()
{
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle));

    for (size_t i = 0; i < m_vertexBufferLayoutDescs.size(); ++i)
    {
        const auto& vertexBufferDesc = m_vertexBufferLayoutDescs[i];

        TGON_GL_ERROR_CHECK(glEnableVertexAttribArray(GLuint(i)));
        TGON_GL_ERROR_CHECK(glVertexAttribPointer(
            static_cast<GLuint>(vertexBufferDesc.attribute),
            vertexBufferDesc.dimension,
            static_cast<GLenum>(vertexBufferDesc.type),
            vertexBufferDesc.normalized,
            vertexBufferDesc.stride,
            reinterpret_cast<const void*>(vertexBufferDesc.offset)
        ));
    }
}

void OpenGLVertexBuffer::Unuse()
{
    for (size_t i = 0; i < m_vertexBufferLayoutDescs.size(); ++i)
    {
        TGON_GL_ERROR_CHECK(glDisableVertexAttribArray(GLuint(i)));
    }
}

bool OpenGLVertexBuffer::IsValid() const noexcept
{
    return m_vertexBufferHandle != 0;
}

GLuint OpenGLVertexBuffer::CreateVertexBufferHandle() const
{
    GLuint vertexBufferHandle;
    TGON_GL_ERROR_CHECK(glGenBuffers(1, &vertexBufferHandle));

    return vertexBufferHandle;
}

} /* namespace tgon */
