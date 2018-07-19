/**
 * @file    VertexBuffer.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>
#include <initializer_list>

namespace tgon
{

struct VertexBufferDesc;
class VertexBufferImpl;
    
class VertexBuffer final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    template <typename _DataArrayType, std::size_t _DataArraySize>
    VertexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs);
    
    VertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs);
    
/* @section Public destructor */
public:
    ~VertexBuffer();
    
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
    std::unique_ptr<VertexBufferImpl> m_vertexBufferImpl;
};
    
template <typename _DataArrayType, std::size_t _DataArraySize>
inline VertexBuffer::VertexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) :
    VertexBuffer(data, sizeof(data), isDynamicUsage, vertexBufferDescs)
{
}

} /* namespace tgon */
