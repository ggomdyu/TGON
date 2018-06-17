/**
 * @filename    GenericVertexBuffer.h
 * @author      ggomdyu
 * @since       01/05/2018
 * @brief
 */

#pragma once
#include <initializer_list>
#include <boost/noncopyable.hpp>

#include "GenericVertexBufferType.h"

namespace tgon
{

class GenericVertexBuffer :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    GenericVertexBuffer(std::size_t dataBytes, bool isDynamicUsage);
    GenericVertexBuffer(GenericVertexBuffer&&);

/* @section Public destructor */
public:
    virtual ~GenericVertexBuffer() = default;

/* @section Public operator */
public:
    GenericVertexBuffer& operator=(GenericVertexBuffer&&);

/* @section Public method */
public:
    template <typename _DataArrayType, std::size_t _DataArraySize>
    void SetData(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs);
    virtual void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) = 0;
    std::size_t GetDataBytes() const noexcept;
    virtual void Use() = 0;
    virtual void Unuse() = 0;
    virtual bool IsValid() const noexcept = 0;
    bool IsDynamicUsage() const noexcept;

/* @section Protected variable */
protected:
    std::size_t m_dataBytes;
    bool m_isDynamicUsage;
};

template <typename _DataArrayType, std::size_t _DataArraySize>
inline void GenericVertexBuffer::SetData(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs)
{
    this->SetData(data, sizeof(data), isDynamicUsage, vertexBufferDescs);
}

} /* namespace tgon */
