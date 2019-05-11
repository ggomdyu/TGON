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

class TGON_API VertexBuffer final :
    private PlatformVertexBuffer
{
/**@section Constructor */
public:
    using PlatformVertexBuffer::PlatformVertexBuffer;

/**@section Method */
public:
    PlatformVertexBuffer* GetPlatformDependency() noexcept;
    const PlatformVertexBuffer* GetPlatformDependency() const noexcept;
    
    template <typename _DataArrayType, std::size_t _DataArraySize>
    void SetData(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage, const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs);

    using PlatformVertexBuffer::SetData;
    using PlatformVertexBuffer::GetDataBytes;
    using PlatformVertexBuffer::Use;
    using PlatformVertexBuffer::Unuse;
    using PlatformVertexBuffer::IsValid;
    using PlatformVertexBuffer::IsDynamicUsage;
};

template <typename _DataArrayType, std::size_t _DataArraySize>
inline void VertexBuffer::SetData(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage, const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs)
{
    this->SetData(data, sizeof(data), isDynamicUsage, vertexBufferLayoutDescs);
}

} /* namespace tgon */
