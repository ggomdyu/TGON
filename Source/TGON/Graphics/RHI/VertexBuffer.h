/**
 * @filename    VertexBuffer.h
 * @author      ggomdyu
 * @since       01/05/2018
 * @brief
 */

#pragma once
#include <cstdint>
#include <GL/glew.h>

namespace tgon
{
namespace graphics
{

enum class BufferType
{
    Vertex,
    Index,
    Uniform,
};

enum class VertexFormat
{
    Position,
    TexCoord,
    Color,
};

struct VertexInputAttributeDescription
{
    VertexFormat vertexFormat;
    bool normalized;
    std::size_t size;
    std::size_t stride;
    std::size_t offset;
};

class VertexBuffer
{
public:
    std::size_t GetBufferSize() const;
    offset
private:
    GLuint m_vertexArray;
    GLuint m_vertexBufferID;

    template <std::size_t _VertexInputAttrDescArraySize>
    VertexBuffer(std::size_t bufferSize, void* data, const VertexInputAttributeDescription(&vertexInputAttrDescs)[_VertexInputAttrDescArraySize])
    {
        glGenVertexArrays(1, &m_vertexArray);
        glBindVertexArray(m_vertexArray);

        glGenBuffers(1, &m_vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, bufferSize, data, m_isDynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

        for (const auto& vertexInputAttrDesc : vertexInputAttrDescs)
        {
            glVertexAttribPointer(static_cast<int>(vertexInputAttrDesc.vertexFormat), vertexInputAttrDesc.size, GL_FLOAT, vertexInputAttrDesc.normalized, vertexInputAttrDesc.stride, reinterpret_cast<const void*>(vertexInputAttrDesc.offset));
        }
    }
    
    std::size_t m_bufferSize;
    bool m_isDynamicUsage;
};

class IndexBuffer
{
public:
};

} /* namespace graphics */
} /* namespace tgon */