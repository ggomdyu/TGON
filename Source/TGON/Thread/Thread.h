/**
 * @file    Thread.h
 * @author  ggomdyu
 * @since   05/26/2019
 */

#pragma once
#include <thread>

#include "Platform/Config.h"

namespace tgon
{

enum class ThreadPriority
{
    TimeCritical,
    Highest,
    Normal,
    Lowest
};

class TGON_API Thread :
    private std::thread
{
/**@section Type */
public:
    using SuperType = std::thread;
    using ThreadId = std::thread::id;

/**@section Constructor */
public:
    using SuperType::SuperType;

/**@section Method */
public:
    void SetPriority(ThreadPriority threadPriority);
    void Detach();
    void Join();
    bool Joinable() const;
    static int32_t GetHardwareConcurrency() noexcept;
    static bool IsMainThread(ThreadId threadId) noexcept;
    ThreadId GetId() const noexcept;
    const void* GetNativeHandle() const;
    void* GetNativeHandle();
};

}
