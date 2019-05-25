#include "PrecompiledHeader.h"

#include <pthread.h>

#include "DispatchQueue.h"

namespace tgon
{
    
void SerialDispatchQueue::AddAsyncTask(const Delegate<void()>& task)
{
    m_taskPool.push_back(task);
}

void SerialDispatchQueue::AddAsyncTask(Delegate<void()>&& task)
{
    m_taskPool.push_back(std::move(task));
}

void SerialDispatchQueue::AddSyncTask(const Delegate<void()>& task)
{
    task();
}
    
void SerialDispatchQueue::Dispatch()
{
    for (auto& task : m_taskPool)
    {
        task();
    }
}

ConcurrentDispatchQueue::ConcurrentDispatchQueue(ConcurrentDispatchQoS qos, int32_t threadPoolCount) :
    m_threadPool(threadPoolCount),
    m_needToDestroy(false)
{
    for (auto& thread : m_threadPool)
    {
        thread = std::thread(&ConcurrentDispatchQueue::DispatchQueueHandler, this);
    }
}

ConcurrentDispatchQueue::~ConcurrentDispatchQueue()
{
    m_needToDestroy = true;
    m_cv.notify_all();
    
    for (auto& thread : m_threadPool)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}
    
void ConcurrentDispatchQueue::AddAsyncTask(const Delegate<void()>& task)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    m_taskPool.push_back(task);
    m_cv.notify_one();
}

void ConcurrentDispatchQueue::AddAsyncTask(Delegate<void()>&& task)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    
    m_taskPool.push_back(std::move(task));
    m_cv.notify_one();
}
    
void ConcurrentDispatchQueue::AddSyncTask(const Delegate<void()>& task)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    
    bool isTaskExecuted = false;
    m_taskPool.push_back([&]()
    {
        task();
        isTaskExecuted = true;
    });
    m_cv.notify_one();
    
    lock.unlock();
    while (isTaskExecuted == false);
}

    void ConcurrentDispatchQueue::DispatchQueueHandler()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    
    while (m_needToDestroy == false)
    {
        m_cv.wait(lock, [this]() {
            return (m_taskPool.size() > 0) || m_needToDestroy;
        });

        if ((m_taskPool.size() <= 0) || m_needToDestroy)
        {
            continue;
        }
        
        auto task = std::move(m_taskPool.front());
        m_taskPool.pop_front();
        
        lock.unlock();
        {
            task();
        }
        lock.lock();
    }
}

} /* namespace tgon */
