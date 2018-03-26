/**
 * @filename    ComPtr.h
 * @author      ggomdyu
 * @since       05/17/2016
 */

#pragma once
#include "../RAII.h"

namespace tgon
{

template <typename _PointerType>
class ComPtrTraits :
    public DefaultRAIITraits<_PointerType>
{
public:
    /* @brief   Adds the reference count of managed resource. */
    void AddRef(_PointerType& resource)
    {
        if (resource != GetNullValue())
        {
            resource->AddRef();
        }
    }

    /* @brief   Releases the managed resource. */
    void Release(_PointerType& resource)
    {
        if (resource != GetNullValue())
        {
            resource->Release();
            resource = GetNullValue();
        }
    }
};

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

/* @section Public operator */
public:
    operator bool() noexcept;

/* @section Protected variable */
protected:
    using RAII<_PointerType, ComPtr<_PointerType>>::m_resource;
};

template<typename _PointerType>
inline ComPtr<_PointerType>::operator bool() noexcept
{
    return m_resource != GetNullValue();
}

} /* namespace tgon */