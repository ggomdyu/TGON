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

enum class VertexAttributeType
{
    Position,
    Color,
    TexCoord,
};

enum class VertexType
{
    Float,
    Double,
    Byte,
    UnsignedByte,
    Short,
    UnsignedShort,
    Int,
    UnsignedInt,
};

struct VertexInputAttributeDescription
{
    VertexAttributeType attribute;
    std::size_t dimension;
    VertexType type;
    bool normalized;
    std::size_t stride;
    std::size_t offset;
};

namespace
{

inline int32_t ConvertVertexTypeToNative(VertexType vertexType)
{
    static constexpr int32_t nativeVertexTypeTable[] =
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

    return nativeVertexTypeTable[(int)vertexType];
}

} /* namespace */

class Buffer
{
public:
    
};

class VertexBuffer :
    public Buffer
{
public:
    std::size_t GetBufferSize() const;
public:
    GLuint m_vertexBufferID = 0;
    std::vector<VertexInputAttributeDescription> m_vertexInputDesc;

public:
    template <typename _VertexArrayType, std::size_t _VertexArraySize>
    VertexBuffer(const _VertexArrayType(&rawData)[_VertexArraySize], const std::initializer_list<VertexInputAttributeDescription>& descs) :
        VertexBuffer(rawData, sizeof(rawData), descs)
    {
    }

    VertexBuffer(const void* rawData, std::size_t rawDataBytes, const std::initializer_list<VertexInputAttributeDescription>& descs)
    {
        m_vertexInputDesc.assign(descs);

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

        for (int i = 0; i < m_vertexInputDesc.size(); ++i)
        {
            const VertexInputAttributeDescription& vertexInputAttrDesc = m_vertexInputDesc[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(
                static_cast<int>(vertexInputAttrDesc.attribute),
                vertexInputAttrDesc.dimension,
                ConvertVertexTypeToNative(vertexInputAttrDesc.type),
                vertexInputAttrDesc.normalized ? GL_TRUE : GL_FALSE,
                vertexInputAttrDesc.stride,
                reinterpret_cast<const void*>(vertexInputAttrDesc.offset)
            );
        }
    }
    
    void EndScene()
    {
        for (int i = 0; i < m_vertexInputDesc.size(); ++i)
        {
            glDisableVertexAttribArray(i);
        }
    }

    std::size_t m_bufferSize = 0;
    bool m_isDynamicUsage = false;
};

class IndexBuffer
{
public:
};

} /* namespace graphics */
} /* namespace tgon */