/**
 * @filename    ComPtr.h
 * @author      ggomdyu
 * @since       05/17/2016
 */

#pragma once
#include <Windows.h>
#include <boost/noncopyable.hpp>

#include "../RAII.h"

namespace tgon
{
namespace detail
{

class HandleGuardTraits :
    public DefaultRAIITraits<HANDLE>
{
public:
    /* @brief   Releases the managed resource. */
    void Release(HANDLE& resource)
    {
        if (resource != GetNullValue())
        {
            CloseHandle(resource);
            resource = GetNullValue();
        }
    }

    /* @brief   Returns special value which indicates resource is null. */
    HANDLE GetNullValue() const noexcept
    {
        return INVALID_HANDLE_VALUE;
    }
};

} /* namespace detail */

/**
 * @class   HandleGuard
 * @brief   RAII object that manages the reference count of windows handle automatically.
 */
class HandleGuard final :
    public RAII<HANDLE, detail::HandleGuardTraits>,
    private boost::noncopyable
{
/* @section Public constructor */
public:
    using RAII::RAII;
};

} /* namespace tgon */