/**
 * @filename    ComPtr.h
 * @author      ggomdyu
 * @since       05/17/2016
 */

#pragma once
#include "../RAII.h"

#include <Windows.h>

namespace tgon
{
namespace core
{

template <typename _ResourceType>
class HandleGuardTraits
{
public:
    template <std::enable_if_t<std::is_pointer_v<_ResourceType>>* = nullptr>
    static constexpr const HANDLE GetNullValue() noexcept
    {
        return INVALID_HANDLE_VALUE;
    }
};

/**
 * @class   HandleGuard
 * @brief   RAII object that manages the reference count of windows handle automatically.
 */
class HandleGuard final :
    public RAII<HANDLE, HandleGuard, HandleGuardTraits<HANDLE>>
{
/* @section Public constructor */
public:
    using RAII::RAII;

/* @section Public method */
public:
    void AddRef() {}

    /* @brief   Releases the managed resource. */
    void Release();
};

inline void HandleGuard::Release()
{
    if (m_resource != TraitsType::GetNullValue())
    {
        CloseHandle(m_resource);
        m_resource = TraitsType::GetNullValue();
    }
}

} /* namespace core */
} /* namespace tgon */