#include "PrecompiledHeader.h"

#include "DispatchQueue.h"

namespace tgon
{

DispatchQueue::DispatchQueue(int32_t threadPoolCount) :
    m_threadPool(threadPoolCount),
    m_needToDestroy(false)
{
    for (auto& thread : m_threadPool)
    {
        thread = std::thread(&DispatchQueue::DispatchQueueHandler, this);
    }
}

DispatchQueue::~DispatchQueue()
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
    
void DispatchQueue::AddAsyncTask(const Delegate<void()>& task)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    m_taskPool.push_back(task);
    m_cv.notify_one();
}

void DispatchQueue::DispatchQueueHandler()
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
