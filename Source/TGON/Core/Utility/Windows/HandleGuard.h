/**
 * @filename    ComPtr.h
 * @author      ggomdyu
 * @since       05/17/2016
 */

#pragma once
#include "../RAII.h"

#include <boost/noncopyable.hpp>
#include <Windows.h>

namespace tgon
{
namespace core
{

/**
 * @class   HandleGuard
 * @brief   RAII object that manages the reference count of windows handle automatically.
 */
class HandleGuard final :
    public RAII<HANDLE, HandleGuard>,
    private boost::noncopyable
{
/* @section Public constructor */
public:
    using RAII::RAII;

/* @section Public method */
public:
    /* @brief   Adds the reference count of managed resource. */
    void AddRef() {}

    /* @brief   Releases the managed resource. */
    void Release();

    /* @brief   Returns special value which indicates resource is null. */
    HANDLE GetNullValue() const noexcept;
};

inline void HandleGuard::Release()
{
    if (m_resource != GetNullValue())
    {
        CloseHandle(m_resource);
        m_resource = GetNullValue();
    }
}

inline HANDLE HandleGuard::GetNullValue() const noexcept
{
    return INVALID_HANDLE_VALUE;
}

} /* namespace core */
} /* namespace tgon */