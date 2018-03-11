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

/* @section Public operator */
public:
    operator bool() noexcept;
};

template<typename _PointerType>
inline ComPtr<_PointerType>::operator bool() noexcept
{
    return m_resource != nullptr;
}

} /* namespace core */
} /* namespace tgon */