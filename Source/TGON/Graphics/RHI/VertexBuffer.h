/**
 * @filename    IVertexBuffer.h
 * @author      ggomdyu
 * @since       01/05/2018
 * @brief
 */

#pragma once
#include "Core/Math/Vector3.h"
#include "Core/Math/Color.h"

#include <cstdint>
#include <cstdlib>
#include <initializer_list>

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

enum class VertexAttributeIndex
{
    Position,
    Color,
    TexCoord,
};

enum class VertexFormatType
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

struct VertexBufferDesc
{
    VertexAttributeIndex attribute;
    std::size_t dimension;
    VertexFormatType type;
    bool normalized;
    std::size_t stride;
    std::size_t offset;
};

struct Vertex
{
    core::Vector3 position;
    core::Color4f color;
};

class BaseVertexBuffer
{
/* @section Public constructor */
public:
    BaseVertexBuffer(std::size_t bufferSize, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& descs);
    
/* @section Public method */
public:
    virtual void SetData(void* data, std::size_t dataBytes) = 0;

    std::size_t GetBufferSize() const noexcept;
    bool IsDynamicUsage() const noexcept;

/* @section Protected variable */
protected:
    std::size_t m_bufferSize;
    bool m_isDynamicUsage;
    std::vector<VertexBufferDesc> m_vertexBufferDescs;
};

} /* namespace graphics */
} /* namespace tgon */