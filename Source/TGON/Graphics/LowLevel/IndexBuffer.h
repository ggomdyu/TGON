/**
 * @file    IndexBuffer.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include <initializer_list>

#include "Core/Platform/Config.h"

#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLIndexBuffer.h"
#endif

namespace tgon
{
    
class TGON_API IndexBuffer final :
    private PlatformIndexBuffer
{
/**@section Constructor */
public:
    /**
     * @brief                       Initializes the index buffer with the specified data.
     * @param [in] data             The data to store in the index buffer.
     * @param [in] isDynamicUsage   If true, then the index buffer will not be modified after set.
     */
    template <typename _DataArrayType, std::size_t _DataArraySize>
    IndexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage);
    
    using PlatformIndexBuffer::PlatformIndexBuffer;
    
/**@section Method */
public:
    PlatformIndexBuffer* GetPlatformDependency() noexcept;
    const PlatformIndexBuffer* GetPlatformDependency() const noexcept;
    
    template <typename _DataArrayType, std::size_t _DataArraySize>
    void SetData(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage);
    
    using PlatformIndexBuffer::SetData;
    using PlatformIndexBuffer::GetDataBytes;
    using PlatformIndexBuffer::Use;
    using PlatformIndexBuffer::Unuse;
    using PlatformIndexBuffer::IsValid;
    using PlatformIndexBuffer::IsDynamicUsage;
};
    
template <typename _DataArrayType, std::size_t _DataArraySize>
inline IndexBuffer::IndexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage) :
    IndexBuffer(data, sizeof(data), isDynamicUsage)
{
}

template <typename _DataArrayType, std::size_t _DataArraySize>
inline void IndexBuffer::SetData(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage)
{
    this->SetData(data, sizeof(data), isDynamicUsage);
}

} /* namespace tgon */
