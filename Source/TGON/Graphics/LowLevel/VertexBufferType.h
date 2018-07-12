/**
 * @file    VertexBufferType.h
 * @author  ggomdyu
 * @since   01/05/2018
 */

#pragma once
#include <cstdlib>

#include "Core/Platform/Config.h"

#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLVertexBufferType.h"
#endif

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
    int32_t dimension;
    VertexFormatType type;
    bool normalized;
    int32_t stride;
    std::size_t offset;
};

} /* namespace tgon */
