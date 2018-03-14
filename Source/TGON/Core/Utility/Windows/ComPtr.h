/**
 * @filename    ComPtr.h
 * @author      ggomdyu
 * @since       05/17/2016
 */

#pragma once
#include "../RAII.h"

namespace tgon
{
namespace core
{

/**
 * @class   ComPtr
 * @brief   RAII object that manages the reference count of COM object automatically.
 */
template <typename _PointerType>
class ComPtr final :
    public RAII<_PointerType, ComPtr<_PointerType>>
{
/* @section Public type */
public:
    using PointerType = _PointerType;

/* @section Public constructor */
public:
    using ComPtr::ComPtr;

/* @section Public constructor */
public:
    /* @brief   Adds the reference count of managed resource. */
    void AddRef();

    /* @brief   Releases the managed resource. */
    void Release();

    /* @brief   Returns special value which indicates resource is null. */
    _PointerType GetNullValue() const noexcept;

/* @section Public operator */
public:
    operator bool() noexcept;
};

template<typename _PointerType>
inline void ComPtr<_PointerType>::AddRef()
{
    if (m_resource != GetNullValue())
    {
        m_resource->AddRef();
    }
}

template<typename _PointerType>
inline void ComPtr<_PointerType>::Release()
{
    if (m_resource != GetNullValue())
    {
        m_resource->Release();
        m_resource = GetNullValue();
    }
}

template<typename _PointerType>
inline _PointerType ComPtr<_PointerType>::GetNullValue() const noexcept
{
    return nullptr;
}

template<typename _PointerType>
inline ComPtr<_PointerType>::operator bool() noexcept
{
    return m_resource != GetNullValue();
}

} /* namespace core */
} /* namespace tgon */