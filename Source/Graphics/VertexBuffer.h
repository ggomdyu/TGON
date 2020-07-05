#pragma once

#include <vector>
#include <span>

#if TGON_GRAPHICS_OPENGL
#include "OpenGL/OpenGLVertexBuffer.h"
#endif

namespace tg
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
    Color = 1,
    UV = 2,
    Normal = 3,
};

struct VertexBufferLayoutDescriptor
{
/**@section Constructor */
public:
    constexpr VertexBufferLayoutDescriptor(VertexAttributeIndex attribute, int32_t dimension, VertexFormatType type, bool normalized, int32_t stride, std::size_t offset) noexcept;

/**@section Variable */
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

class VertexBuffer final :
    private PlatformVertexBuffer
{
/**@section Constructor */
public:
    VertexBuffer();
    VertexBuffer(const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayouts);
    VertexBuffer(const VertexBuffer& rhs) = delete;
    VertexBuffer(VertexBuffer&& rhs) noexcept = default;
    
/**@section Destructor */
public:
    ~VertexBuffer();

/**@section Operator */
public:
    VertexBuffer& operator=(const VertexBuffer& rhs) = delete;
    VertexBuffer& operator=(VertexBuffer&& rhs) noexcept = default;

/**@section Method */
public:
    [[nodiscard]] PlatformVertexBuffer& GetPlatformDependency() noexcept;
    [[nodiscard]] const PlatformVertexBuffer& GetPlatformDependency() const noexcept;
    template <typename _Type>
    void SetData(const std::span<_Type>& data, bool isDynamicUsage);
    void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage);
    void SetLayoutDescriptor(const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs);
    void Use();
    void Unuse();

/**@section Variable */
private:
    std::vector<VertexBufferLayoutDescriptor> m_vertexBufferLayouts;
};

template <typename _Type>
inline void VertexBuffer::SetData(const std::span<_Type>& data, bool isDynamicUsage)
{
    this->SetData(data.data(), data.size() * sizeof(_Type), isDynamicUsage);
}

}
