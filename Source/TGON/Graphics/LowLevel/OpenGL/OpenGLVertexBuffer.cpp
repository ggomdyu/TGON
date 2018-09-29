#include "PrecompiledHeader.h"

#include <cassert>

#include "OpenGLUtility.h"
#include "OpenGLVertexBuffer.h"

namespace tgon
{

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs) :
    m_dataBytes(dataBytes),
    m_isDynamicUsage(isDynamicUsage),
    m_vertexBufferHandle(this->CreateVertexBufferHandle())
{
    assert(data != nullptr && dataBytes > 0 && vertexBufferLayoutDescs.size() > 0);

    this->SetData(data, dataBytes, isDynamicUsage, vertexBufferLayoutDescs);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(OpenGLVertexBuffer&& rhs) :
    m_dataBytes(rhs.m_dataBytes),
    m_isDynamicUsage(rhs.m_isDynamicUsage),
    m_vertexBufferHandle(rhs.m_vertexBufferHandle),
    m_vertexBufferLayoutDescs(std::move(rhs.m_vertexBufferLayoutDescs))
{
    rhs.m_dataBytes = 0;
    rhs.m_isDynamicUsage = false;
    rhs.m_vertexBufferHandle = 0;
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    if (m_vertexBufferHandle != 0)
    {
        TGON_GL_ERROR_CHECK(glDeleteBuffers(1, &m_vertexBufferHandle));
    }
}

void OpenGLVertexBuffer::SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs)
{
    m_vertexBufferLayoutDescs.clear();
    m_vertexBufferLayoutDescs = vertexBufferLayoutDescs;

    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle));
    TGON_GL_ERROR_CHECK(glBufferData(GL_ARRAY_BUFFER, dataBytes, data, isDynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
}

std::size_t OpenGLVertexBuffer::GetDataBytes() const noexcept
{
    return m_dataBytes;
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

bool OpenGLVertexBuffer::IsDynamicUsage() const noexcept
{
    return m_isDynamicUsage;
}

GLuint OpenGLVertexBuffer::CreateVertexBufferHandle() const
{
    GLuint vertexBufferHandle;
    TGON_GL_ERROR_CHECK(glGenBuffers(1, &vertexBufferHandle));

    return vertexBufferHandle;
}

} /* namespace tgon */
