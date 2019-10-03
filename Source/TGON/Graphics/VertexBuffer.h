/**
 * @file    VertexBuffer.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include <initializer_list>
#include <memory>

#include "Platform/Config.h"

#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLVertexBuffer.h"
#endif

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

class TGON_API VertexBuffer final :
    private PlatformVertexBuffer
{
/**@section Constructor */
public:
    using PlatformVertexBuffer::PlatformVertexBuffer;

/**@section Method */
public:
    PlatformVertexBuffer& GetPlatformDependency() noexcept;
    const PlatformVertexBuffer& GetPlatformDependency() const noexcept;
//    template <typename _DataArrayType, std::size_t _DataArraySize>
//    void SetData(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage);
    void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage);
    void SetLayoutDescriptor(const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs);
    void Use();
    void Unuse();
};

//template <typename _DataArrayType, std::size_t _DataArraySize>
//inline void VertexBuffer::SetData(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage)
//{
//    this->SetData(data, sizeof(data), isDynamicUsage);
//}

} /* namespace tgon */
