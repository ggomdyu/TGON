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
    private boost::noncopyable
{
/* @section Public constructor */
public:
    template <typename _DataArrayType, std::size_t _DataArraySize>
    VertexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs);
    
    VertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs);
    
/* @section Public method */
public:
    void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs);
    
    std::size_t GetDataBytes() const noexcept;
    
    void Use();
    
    void Unuse();
    
    bool IsValid() const noexcept;
    
    bool IsDynamicUsage() const noexcept;

/* @section Private variable */
public:
    VertexBufferImpl m_vertexBufferImpl;
};
    
template <typename _DataArrayType, std::size_t _DataArraySize>
inline VertexBuffer::VertexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) :
    VertexBuffer(data, sizeof(data), isDynamicUsage, vertexBufferDescs)
{
}

} /* namespace tgon */
