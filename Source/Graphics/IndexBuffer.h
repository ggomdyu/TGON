#pragma once

#include <initializer_list>
#include <gsl/span>

#if TGON_GRAPHICS_OPENGL
#   include "OpenGL/OpenGLIndexBuffer.h"
#endif

namespace tg
{
    
class IndexBuffer :
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
    [[nodiscard]] PlatformIndexBuffer& GetPlatformDependency() noexcept;
    [[nodiscard]] const PlatformIndexBuffer& GetPlatformDependency() const noexcept;
    template <typename _Type>
    void SetData(const gsl::span<_Type>& data, bool isDynamicUsage);
    void SetData(const void* data, int32_t dataBytes, bool isDynamicUsage);
    void Use();
    void Unuse();

private:
    void Destroy();
};

template <typename _Type>
inline void IndexBuffer::SetData(const gsl::span<_Type>& data, bool isDynamicUsage)
{
    this->SetData(data.data(), data.size() * sizeof(_Type), isDynamicUsage);
}

}
