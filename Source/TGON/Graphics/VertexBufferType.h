/**
 * @file    VertexBufferType.h
 * @author  ggomdyu
 * @since   01/05/2018
 */

#pragma once
#include <cstdlib>

namespace tgon
{
    
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

enum class VertexAttributeIndex
{
    Position = 0,
    Normal = 1,
    UV = 1,
};

struct VertexBufferLayoutDescriptor
{
/**section  Constructor */
public:
    constexpr VertexBufferLayoutDescriptor(VertexAttributeIndex attribute, int32_t dimension, VertexFormatType type, bool normalized, int32_t stride, std::size_t offset) noexcept;

/**section  Variable */
public:
    VertexAttributeIndex attribute;
    int32_t dimension;
    VertexFormatType type;
    bool normalized;
    int32_t stride;
    std::size_t offset;
};

constexpr VertexBufferLayoutDescriptor::VertexBufferLayoutDescriptor(VertexAttributeIndex attribute, int32_t dimension, VertexFormatType type, bool normalized, int32_t stride, std::size_t offset) noexcept :
    attribute(attribute),
    dimension(dimension),
    type(type),
    normalized(normalized),
    stride(stride),
    offset(offset)
{
}

}
