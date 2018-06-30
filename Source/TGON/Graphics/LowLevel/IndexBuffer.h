/**
 * @file    IndexBuffer.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>
#include <initializer_list>

namespace tgon
{

struct IndexBufferDesc;
class IndexBufferImpl;
    
class IndexBuffer final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    template <typename _DataArrayType, std::size_t _DataArraySize>
    IndexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage);
    IndexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage);
    
/* @section Public destructor */
public:
    ~IndexBuffer();
    
/* @section Public method */
public:
    template <typename _DataArrayType, std::size_t _DataArraySize>
    void SetData(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage);
    void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage);
    std::size_t GetDataBytes() const noexcept;
    void Use();
    void Unuse();
    bool IsValid() const noexcept;
    bool IsDynamicUsage() const noexcept;

/* @section Private variable */
public:
    std::unique_ptr<IndexBufferImpl> m_indexBufferImpl;
};
    
template <typename _DataArrayType, std::size_t _DataArraySize>
inline IndexBuffer::IndexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage) :
    IndexBuffer(data, sizeof(data), isDynamicUsage)
{
}

template<typename _DataArrayType, std::size_t _DataArraySize>
inline void IndexBuffer::SetData(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage)
{
    this->SetData(data, sizeof(data), isDynamicUsage);
}

} /* namespace tgon */
