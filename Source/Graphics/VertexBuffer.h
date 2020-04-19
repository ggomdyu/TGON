#pragma once

#include <vector>
#include <gsl/span>

#if TGON_GRAPHICS_OPENGL
#   include "OpenGL/OpenGLVertexBuffer.h"
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
    VertexBuffer(const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs);
    VertexBuffer(VertexBuffer&& rhs) noexcept;
    
/**@section Destructor */
public:
    ~VertexBuffer();

/**@section Operator */
protected:
    VertexBuffer& operator=(VertexBuffer&& rhs) noexcept;

/**@section Method */
public:
    [[nodiscard]] PlatformVertexBuffer& GetPlatformDependency() noexcept;
    [[nodiscard]] const PlatformVertexBuffer& GetPlatformDependency() const noexcept;
    template <typename _Type>
    void SetData(const gsl::span<_Type>& data, bool isDynamicUsage);
    void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage);
    void SetLayoutDescriptor(const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs);
    void Use();
    void Unuse();

private:
    void Destroy();
    
/**@section Variable */
private:
    std::vector<VertexBufferLayoutDescriptor> m_vertexBufferLayoutDescs;
};

template <typename _Type>
inline void VertexBuffer::SetData(const gsl::span<_Type>& data, bool isDynamicUsage)
{
    this->SetData(data.data(), data.size() * sizeof(_Type), isDynamicUsage);
}

}
