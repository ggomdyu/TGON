/**
 * @file    IndexBuffer.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include <initializer_list>
#include <gsl/span>

#include "Platform/Config.h"

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
    IndexBuffer();
    IndexBuffer(IndexBuffer&& rhs) noexcept;

/**@section Destructor */
public:
    ~IndexBuffer();
    
/**@section Operator */
public:
    IndexBuffer& operator=(IndexBuffer&& rhs);

/**@section Method */
public:
    PlatformIndexBuffer& GetPlatformDependency() noexcept;
    const PlatformIndexBuffer& GetPlatformDependency() const noexcept;
    template <typename _Type>
    void SetData(const gsl::span<_Type>& data, bool isDynamicUsage);
    void SetData(const void* data, int32_t dataBytes, bool isDynamicUsage);
    void Use();
    void Unuse();

private:
    void Destroy();
};

template<typename _Type>
inline void IndexBuffer::SetData(const gsl::span<_Type>& data, bool isDynamicUsage)
{
    this->SetData(data.data(), data.size() * sizeof(_Type), isDynamicUsage);
}

} /* namespace tgon */
