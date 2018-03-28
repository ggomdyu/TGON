#include "PrecompiledHeader.pch"

#include <cassert>

#include "OpenGLVertexBuffer.h"
#include "OpenGLVertexBufferUtility.h"

namespace tgon
{

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) :
    GenericVertexBuffer(dataBytes, isDynamicUsage),
    m_vertexBufferHandle(GenerateBuffer())
{
    assert(data != nullptr && dataBytes != 0 && vertexBufferDescs.size() > 0);

    this->SetData(data, dataBytes, isDynamicUsage, vertexBufferDescs);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(OpenGLVertexBuffer&& rhs) :
    GenericVertexBuffer(std::move(rhs)),
    m_vertexBufferHandle(rhs.m_vertexBufferHandle),
    m_vertexBufferDescs(std::move(rhs.m_vertexBufferDescs))
{
    rhs.m_vertexBufferHandle = 0;
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_vertexBufferHandle);
}

OpenGLVertexBuffer& OpenGLVertexBuffer::operator=(OpenGLVertexBuffer&& rhs)
{
    if (&rhs == this)
    {
        return *this;
    }

    glDeleteBuffers(1, &m_vertexBufferHandle);

    GenericVertexBuffer::operator=(std::move(rhs));
    m_vertexBufferHandle = rhs.m_vertexBufferHandle;
    m_vertexBufferDescs = std::move(rhs.m_vertexBufferDescs);
    
    rhs.m_vertexBufferHandle = 0;

    return *this;
}

void OpenGLVertexBuffer::SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs)
{
    int index = 0;
    for (auto& vertexBufferDesc : vertexBufferDescs)
    {
        m_vertexBufferDescs[index++] = ConvertVertexBufferDescToNative(vertexBufferDesc);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, dataBytes, data, isDynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void OpenGLVertexBuffer::Use()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);

    for (int i = 0; i < m_vertexBufferDescs.size(); ++i)
    {
        const auto& vertexBufferDesc = m_vertexBufferDescs[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            vertexBufferDesc.attribute,
            vertexBufferDesc.dimension,
            vertexBufferDesc.type,
            vertexBufferDesc.normalized,
            vertexBufferDesc.stride,
            vertexBufferDesc.offset
        );
    }
}

void OpenGLVertexBuffer::Unuse()
{
    for (int i = 0; i < m_vertexBufferDescs.size(); ++i)
    {
        glDisableVertexAttribArray(i);
    }
}

bool OpenGLVertexBuffer::IsValid() const noexcept
{
    return m_vertexBufferHandle != 0;
}

GLuint OpenGLVertexBuffer::GenerateBuffer() const
{
    GLuint vertexBufferHandle;
    glGenBuffers(1, &vertexBufferHandle);

    return vertexBufferHandle;
}

} /* namespace tgon */