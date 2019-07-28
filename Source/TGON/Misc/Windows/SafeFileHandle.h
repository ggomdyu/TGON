/**
 * @file    SafeFileHandle.h
 * @author  ggomdyu
 * @since   07/29/2019
 */

#pragma once
#include <Windows.h>
#include <string>
#include <boost/noncopyable.hpp>

namespace tgon
{

class SafeFileHandle :
    private boost::noncopyable
{
/**@section Constructor */
public:
    SafeFileHandle(HANDLE handle) noexcept;
    SafeFileHandle(SafeFileHandle&& rhs) noexcept;

/**@section Destructor */
public:
    ~SafeFileHandle();

/**@section Operator */
public:
    SafeFileHandle& operator=(SafeFileHandle&& rhs) noexcept;
    bool operator==(const SafeFileHandle& rhs) const noexcept;
    bool operator!=(const SafeFileHandle& rhs) const noexcept;
    operator HANDLE() const noexcept;

/**@section Variable */
private:
    HANDLE m_handle;
};

inline SafeFileHandle::SafeFileHandle(HANDLE handle) noexcept :
    m_handle(handle)
{
}

inline SafeFileHandle::SafeFileHandle(SafeFileHandle&& rhs) noexcept :
    m_handle(rhs.m_handle)
{
    rhs.m_handle = nullptr;
}

inline SafeFileHandle::~SafeFileHandle()
{
    if (m_handle != nullptr)
    {
        CloseHandle(m_handle);
        m_handle = nullptr;
    }
}

inline SafeFileHandle& SafeFileHandle::operator=(SafeFileHandle&& rhs) noexcept
{
    m_handle = rhs.m_handle;
    rhs.m_handle = nullptr;
}

inline bool SafeFileHandle::operator==(const SafeFileHandle& rhs) const noexcept
{
    return m_handle == rhs.m_handle;
}

inline bool SafeFileHandle::operator!=(const SafeFileHandle& rhs) const noexcept
{
    return m_handle != rhs.m_handle;
}

inline SafeFileHandle::operator HANDLE() const noexcept
{
    return m_handle;
}

} /* namespace tgon */
