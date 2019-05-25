/**
 * @file    DispatchQueue.h
 * @author  ggomdyu
 * @since   05/23/2019
 */

#pragma once
#include <cstdint>
#include <thread>
#include <deque>
#include <mutex>
#include <boost/noncopyable.hpp>

#include "Platform/Config.h"
#include "Core/Delegate.h"

namespace tgon
{
    
class TGON_API SerialDispatchQueue final :
    private boost::noncopyable
{
/**@section Method */
public:
    void AddAsyncTask(const Delegate<void()>& task);
    void AddAsyncTask(Delegate<void()>&& task);
    void AddSyncTask(const Delegate<void()>& task);
    void Dispatch();
    
/**@section Variable */
private:
    std::deque<Delegate<void()>> m_taskPool;
};
    
enum class ConcurrentDispatchQoS
{
    UserInteractive,
    UserInitiated,
    Default,
    Utility,
    Background,
};

class TGON_API ConcurrentDispatchQueue final :
    private boost::noncopyable
{
/**@section Constructor */
public:
    ConcurrentDispatchQueue(ConcurrentDispatchQoS qos, int32_t threadPoolCount);
    
/**@section Destructor */
public:
    ~ConcurrentDispatchQueue();

/**@section Method */
public:
    void AddAsyncTask(const Delegate<void()>& task);
    void AddAsyncTask(Delegate<void()>&& task);
    void AddSyncTask(const Delegate<void()>& task);
    
private:
    void DispatchQueueHandler();

/**@section Variable */
private:
    std::condition_variable m_cv;
    std::mutex m_mutex;
    std::deque<std::thread> m_threadPool;
    std::deque<Delegate<void()>> m_taskPool;
    bool m_needToDestroy;
};
    
} /* namespace tgon */
