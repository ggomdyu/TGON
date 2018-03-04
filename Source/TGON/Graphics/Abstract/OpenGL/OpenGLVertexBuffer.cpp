#include "PrecompiledHeader.pch"

#include "OpenGLVertexBuffer.h"
#include "OpenGLVertexBufferUtility.h"

#include <cassert>

namespace tgon
{
namespace graphics
{

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) :
    GenericVertexBuffer(dataBytes, isDynamicUsage),
    m_vertexBufferDesc(vertexBufferDescs.size()),
    m_vertexBufferHandle(GenerateBuffer())
{
    assert(data != nullptr && dataBytes != 0 && vertexBufferDescs.size() > 0);

    this->SetData(data, dataBytes, isDynamicUsage, vertexBufferDescs);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(OpenGLVertexBuffer&& rhs) :
    GenericVertexBuffer(std::move(rhs)),
    m_vertexBufferHandle(rhs.m_vertexBufferHandle),
    m_vertexBufferDesc(std::move(rhs.m_vertexBufferDesc))
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

    this->~OpenGLVertexBuffer();

    GenericVertexBuffer::operator=(std::move(rhs));
    
    new (this) OpenGLVertexBuffer(std::move(rhs));

    return *this;
}

void OpenGLVertexBuffer::SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs)
{
    int index = 0;
    for (auto& vertexBufferDesc : vertexBufferDescs)
    {
        m_vertexBufferDesc[index++] = ConvertVertexBufferDescToNative(vertexBufferDesc);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, dataBytes, data, isDynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void OpenGLVertexBuffer::Use()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);

    for (int i = 0; i < m_vertexBufferDesc.size(); ++i)
    {
        const auto& vertexBufferDesc = m_vertexBufferDesc[i];

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
    for (int i = 0; i < m_vertexBufferDesc.size(); ++i)
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

} /* namespace graphics */
} /* namespace tgon */