/**
 * @filename    GenericIndexBuffer.h
 * @author      ggomdyu
 * @since       02/17/2018
 * @brief
 */

#pragma once

#include <cstdlib>

namespace tgon
{
namespace graphics
{

class GenericIndexBuffer
{
/* @section Public constructor */
public:
    GenericIndexBuffer(std::size_t dataBytes, bool isDynamicUsage);
    virtual ~GenericIndexBuffer() = default;

/* @section Public method */
public:
    template <typename _DataArrayType, std::size_t _DataArraySize>
    void SetData(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage);
    virtual void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage) = 0;
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

template<typename _DataArrayType, std::size_t _DataArraySize>
inline void GenericIndexBuffer::SetData(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage)
{
    this->SetData(data, sizeof(data), isDynamicUsage);
}

} /* namespace graphics */
} /* namespace tgon */
