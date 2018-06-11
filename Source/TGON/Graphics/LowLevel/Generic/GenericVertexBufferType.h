/**
 * @filename    GenericVertexBuffer.h
 * @author      ggomdyu
 * @since       01/05/2018
 * @brief
 */

#pragma once
#include <cstdlib>

#include "Core/Math/Color.h"
#include "Core/Math/Vector3.h"

namespace tgon
{

enum class BufferType
{
    Vertex,
    Index,
    Uniform,
};

enum class VertexAttributeIndex
{
    Position = 0,
    Normal = 1,
    UV = 1,
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
public:
    constexpr VertexBufferDesc(VertexAttributeIndex attribute, std::size_t dimension, VertexFormatType type, bool normalized, std::size_t stride, std::size_t offset) noexcept :
        attribute(attribute),
        dimension(dimension),
        type(type),
        normalized(normalized),
        stride(stride),
        offset(offset)
    {
    }

public:
    VertexAttributeIndex attribute;
    std::size_t dimension;
    VertexFormatType type;
    bool normalized;
    std::size_t stride;
    std::size_t offset;
};

} /* namespace tgon */