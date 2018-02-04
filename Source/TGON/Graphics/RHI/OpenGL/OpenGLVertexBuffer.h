/**
 * @filename    VertexBuffer.h
 * @author      ggomdyu
 * @since       01/05/2018
 * @brief
 */

#pragma once
#include "../VertexBuffer.h"

#include <GL/glew.h>
#include <vector>

namespace tgon
{
namespace graphics
{

constexpr GLenum ConvertVertexFormatTypeToNative(VertexFormatType vertexFormatType)
{
    constexpr GLenum nativeVertexFormatTypeTable[] =
    {
        GL_FLOAT,
        GL_DOUBLE,
        GL_BYTE,
        GL_UNSIGNED_BYTE,
        GL_SHORT,
        GL_UNSIGNED_SHORT,
        GL_INT,
        GL_UNSIGNED_INT,
    };

    return nativeVertexFormatTypeTable[static_cast<std::size_t>(vertexFormatType)];
}

class OpenGLVertexBuffer :
    public BaseVertexBuffer
{
public:
    GLuint m_vertexBufferID = 0;
    std::vector<VertexBufferDesc> m_vertexInputDescs;

public:
    template <typename _VertexArrayType, std::size_t _VertexArraySize>
    VertexBuffer(const _VertexArrayType(&data)[_VertexArraySize], const std::initializer_list<VertexBufferDesc>& descs) :
        VertexBuffer(data, sizeof(data), descs)
    {
    }

    VertexBuffer(const void* data, std::size_t dataBytes, const std::initializer_list<VertexBufferDesc>& descs)
    {
        m_vertexInputDescs.assign(descs);

        glGenBuffers(1, &m_vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, rawDataBytes, rawData, m_isDynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }
    
    ~VertexBuffer()
    {
        glDeleteBuffers(1, &m_vertexBufferID);
    }

    void BeginScene()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);

        for (int i = 0; i < m_vertexInputDescs.size(); ++i)
        {
            const VertexBufferDesc& vertexInputAttrDesc = m_vertexInputDescs[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(
                static_cast<int>(vertexInputAttrDesc.attribute),
                vertexInputAttrDesc.dimension,
                ConvertVertexFormatTypeToNative(vertexInputAttrDesc.type),
                vertexInputAttrDesc.normalized ? GL_TRUE : GL_FALSE,
                vertexInputAttrDesc.stride,
                reinterpret_cast<const void*>(vertexInputAttrDesc.offset)
            );
        }
    }
    
    void EndScene()
    {
        for (int i = 0; i < m_vertexInputDescs.size(); ++i)
        {
            glDisableVertexAttribArray(i);
        }
    }
};

class IndexBuffer
{
public:
};

} /* namespace graphics */
} /* namespace tgon */