/**
 * @file    DispatchQueue.h
 * @author  ggomdyu
 * @since   05/23/2019
 */

#pragma once
#include <deque>
#include <vector>
#include <mutex>

#include "Core/Delegate.h"
#include "Core/NonCopyable.h"

#include "Thread.h"

namespace tgon
{
    
class SerialDispatchQueue :
    private NonCopyable
{
/**@section Method */
public:
    void AddAsyncTask(const Delegate<void()>& task);
    void AddAsyncTask(Delegate<void()>&& task);
    void AddSyncTask(const Delegate<void()>& task);
    void AddSyncTask(Delegate<void()>&& task);
    void Dispatch();
    
/**@section Variable */
private:
    std::mutex m_mutex;
    std::deque<Delegate<void()>> m_taskPool;
};

class ConcurrentDispatchQueue :
    private NonCopyable
{
/**@section Constructor */
public:
    explicit ConcurrentDispatchQueue(int32_t threadPoolCount);
    
/**@section Destructor */
public:
    ~ConcurrentDispatchQueue();

/**@section Method */
public:
    void AddAsyncTask(const Delegate<void()>& task);
    void AddAsyncTask(Delegate<void()>&& task);
    void AddSyncTask(const Delegate<void()>& task);
    void AddSyncTask(Delegate<void()>&& task);
    
private:
    void DispatchQueueHandler();

/**@section Variable */
private:
    std::condition_variable m_cv;
    std::mutex m_mutex;
    std::vector<Thread> m_threadPool;
    std::deque<Delegate<void()>> m_taskPool;
    bool m_needToDestroy;
};
    
} /* namespace tgon */
