/**
 * @file    TimerHandle.h
 * @author  ggomdyu
 * @since   12/02/2019
 */

#pragma once
#include <cstdint>

namespace tgon
{

class TimerHandle
{
/**@section Constructor */
public:
    constexpr TimerHandle() noexcept = default;
    constexpr explicit TimerHandle(int64_t rawTimerHandle) noexcept;

/**@section Operator */
public:
    constexpr bool operator==(const TimerHandle& rhs) const noexcept;
    constexpr bool operator!=(const TimerHandle& rhs) const noexcept;
    constexpr bool operator>(const TimerHandle& rhs) const noexcept;
    constexpr bool operator<(const TimerHandle& rhs) const noexcept;

/**@section Variable */
public:
    constexpr bool IsValid() const noexcept;
    
/**@section Variable */
private:
    int64_t m_rawTimerHandle = 0;
};

constexpr TimerHandle::TimerHandle(int64_t rawTimerHandle) noexcept :
    m_rawTimerHandle(rawTimerHandle)
{
}

constexpr bool TimerHandle::operator==(const TimerHandle& rhs) const noexcept
{
    return m_rawTimerHandle == rhs.m_rawTimerHandle;
}

constexpr bool TimerHandle::operator!=(const TimerHandle& rhs) const noexcept
{
    return m_rawTimerHandle != rhs.m_rawTimerHandle;
}

constexpr bool TimerHandle::operator>(const TimerHandle& rhs) const noexcept
{
    return m_rawTimerHandle > rhs.m_rawTimerHandle;
}

constexpr bool TimerHandle::operator<(const TimerHandle& rhs) const noexcept
{
    return m_rawTimerHandle < rhs.m_rawTimerHandle;
}

constexpr bool TimerHandle::IsValid() const noexcept
{
    return m_rawTimerHandle != 0;
}

} /* namespace tgon */
