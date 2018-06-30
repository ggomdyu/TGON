#include "PrecompiledHeader.h"

#include <cassert>

#include "OpenGLUtility.h"
#include "OpenGLVertexBuffer.h"
#include "../VertexBufferType.h"

namespace tgon
{

VertexBufferImpl::VertexBufferImpl(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) :
    m_dataBytes(dataBytes),
    m_isDynamicUsage(isDynamicUsage),
    m_vertexBufferHandle(this->CreateVertexBufferHandle())
{
    assert(data != nullptr && dataBytes > 0 && vertexBufferDescs.size() > 0);

    this->SetData(data, dataBytes, isDynamicUsage, vertexBufferDescs);
}

VertexBufferImpl::~VertexBufferImpl()
{
    TGON_GL_ERROR_CHECK(glDeleteBuffers(1, &m_vertexBufferHandle));
}

void VertexBufferImpl::SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs)
{
    m_vertexBufferDescs.clear();
    m_vertexBufferDescs = vertexBufferDescs;

    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle));
    TGON_GL_ERROR_CHECK(glBufferData(GL_ARRAY_BUFFER, dataBytes, data, isDynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
}

std::size_t VertexBufferImpl::GetDataBytes() const noexcept
{
    return m_dataBytes;
}

void VertexBufferImpl::Use()
{
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle));

    for (GLint i = 0; i < m_vertexBufferDescs.size(); ++i)
    {
        const auto& vertexBufferDesc = m_vertexBufferDescs[i];

        TGON_GL_ERROR_CHECK(glEnableVertexAttribArray(i));
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

void VertexBufferImpl::Unuse()
{
    for (GLint i = 0; i < m_vertexBufferDescs.size(); ++i)
    {
        TGON_GL_ERROR_CHECK(glDisableVertexAttribArray(i));
    }
}

bool VertexBufferImpl::IsValid() const noexcept
{
    return m_vertexBufferHandle != 0;
}

bool VertexBufferImpl::IsDynamicUsage() const noexcept
{
    return m_isDynamicUsage;
}

GLuint VertexBufferImpl::CreateVertexBufferHandle() const
{
    GLuint vertexBufferHandle;
    TGON_GL_ERROR_CHECK(glGenBuffers(1, &vertexBufferHandle));

    return vertexBufferHandle;
}

} /* namespace tgon */
