/**
 * @file    VertexBuffer.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include <initializer_list>
#include <memory>

#include "Core/Platform/Config.h"

#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLVertexBuffer.h"
#endif

namespace tgon
{

class TGON_API VertexBuffer final :
    private PlatformVertexBuffer
{
/**@section Public constructor */
public:
    template <typename _DataArrayType, std::size_t _DataArraySize>
    VertexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage, const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs);

    using PlatformVertexBuffer::PlatformVertexBuffer;

/**@section Public method */
public:
    PlatformVertexBuffer* GetPlatformDependency() noexcept;
    const PlatformVertexBuffer* GetPlatformDependency() const noexcept;
    
    using PlatformVertexBuffer::SetData;
    using PlatformVertexBuffer::GetDataBytes;
    using PlatformVertexBuffer::Use;
    using PlatformVertexBuffer::Unuse;
    using PlatformVertexBuffer::IsValid;
    using PlatformVertexBuffer::IsDynamicUsage;
};

template <typename _DataArrayType, std::size_t _DataArraySize>
inline VertexBuffer::VertexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage, const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs) :
    VertexBuffer(data, sizeof(data), isDynamicUsage, vertexBufferLayoutDescs)
{
}

} /* namespace tgon */
