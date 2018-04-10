/**
 * @filename    Stopwatch.h
 * @author      ggomdyu
 * @since       04/07/2018
 */

#pragma once

#include <chrono>
#include <cassert>

namespace tgon
{

class Stopwatch final
{
/* @section Public constructor */
public:
    Stopwatch() noexcept;

/* @section Public method */
public:
    /* @brief   Starts, or resumes, measuring elapsed time for an interval. */
    void Start();
    
    /* @brief   Stops measuring elapsed time for an interval. */
    void Stop() noexcept;

    /* @brief   Stops time interval measurement and resets the elapsed time to zero. */
    void Reset() noexcept;

    /* @brief   Stops time interval measurement, resets the elapsed time to zero, and starts measuring elapsed time. */
    void Restart();

    /**
     * @brief   Gets a value indicating whether the timer is running.
     * @return  True if the instance is currently running and measuring elapsed time for an interval; otherwise, false.
     */
    bool IsRunning() const noexcept;

    /* @brief   Gets the total elapsed time measured by the current instance in seconds. */
    int64_t GetElapsedSeconds() const;

    /* @brief   Gets the total elapsed time measured by the current instance in milliseconds. */
    int64_t GetElapsedMilliseconds() const;

    /* @brief   Gets the total elapsed time measured by the current instance in nanoseconds. */
    int64_t GetElapsedNanoseconds() const;

/* @section Public static method */
public:
    static int64_t GetFrequency();

/* @section Private variable */
private:
    int64_t m_oldTime;
};

inline Stopwatch::Stopwatch() noexcept :
    m_oldTime(0)
{
}

inline void Stopwatch::Start()
{
    m_oldTime = std::chrono::steady_clock::now().time_since_epoch().count();
}

inline void Stopwatch::Stop() noexcept
{
}

inline void Stopwatch::Restart()
{
    this->Start();
}

inline void Stopwatch::Reset() noexcept
{
    this->Stop();
    m_oldTime = {};
}

inline int64_t Stopwatch::GetElapsedSeconds() const
{
    return static_cast<int64_t>(this->GetElapsedMilliseconds() * 0.001f);
}

inline int64_t Stopwatch::GetElapsedMilliseconds() const
{
    return static_cast<int64_t>(this->GetElapsedNanoseconds() * 0.000001f);
}

/* @brief   Gets the total elapsed time measured by the current instance, in timer ticks. */
inline int64_t Stopwatch::GetElapsedNanoseconds() const
{
    assert(this->IsRunning() == true && "StopWatch is not running but you tried to get elapsed time.");
    return std::chrono::steady_clock::now().time_since_epoch().count() - m_oldTime;
}
    
inline bool Stopwatch::IsRunning() const noexcept
{
    return m_oldTime > 0;
}

} /* namespace tgon */