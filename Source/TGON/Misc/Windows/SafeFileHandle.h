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
    SafeFileHandle() noexcept;
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
    
/**@section Method */
public:
    bool IsValid() const noexcept;

/**@section Variable */
private:
    HANDLE m_handle;
};

inline SafeFileHandle::SafeFileHandle() noexcept :
    m_handle(INVALID_HANDLE_VALUE)
{
}

inline SafeFileHandle::SafeFileHandle(HANDLE handle) noexcept :
    m_handle(handle)
{
}

inline SafeFileHandle::SafeFileHandle(SafeFileHandle&& rhs) noexcept :
    m_handle(rhs.m_handle)
{
    rhs.m_handle = INVALID_HANDLE_VALUE;
}

inline SafeFileHandle::~SafeFileHandle()
{
    if (m_handle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_handle);
        m_handle = INVALID_HANDLE_VALUE;
    }
}

inline SafeFileHandle& SafeFileHandle::operator=(SafeFileHandle&& rhs) noexcept
{
    m_handle = rhs.m_handle;
    rhs.m_handle = INVALID_HANDLE_VALUE;
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

inline bool SafeFileHandle::IsValid() const noexcept
{
    return m_handle != INVALID_HANDLE_VALUE;
}

} /* namespace tgon */
