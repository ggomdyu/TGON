#include "PrecompiledHeader.h"

#include "ThreadPool.h"

namespace tgon
{

class ThreadPool::ThreadWorker
{
/* @section Public constructor */
public:
    explicit ThreadWorker(ThreadPool& owner);

/* @section Public operator */
public:
    void operator()();

/* @section Private variable */
private:
    ThreadPool& m_owner;
};

ThreadPool::ThreadPool(int32_t allocateThreadCount) :
    m_threads(allocateThreadCount),
    m_isJoinable(true)
{
    for (auto& thread : m_threads)
    {
        thread = std::thread(ThreadWorker(*this));
    }
}

void ThreadPool::Join()
{
    m_isJoinable = false;
    m_conditionLock.notify_all();

    for (auto& thread : m_threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}

bool ThreadPool::IsJoinable() const noexcept
{
    return m_isJoinable;
}

ThreadPool::ThreadWorker::ThreadWorker(ThreadPool& owner) :
    m_owner(owner)
{
}

inline void ThreadPool::ThreadWorker::operator()()
{
    Delegate<void()> task;
    
    while (m_owner.IsJoinable())
    {
        std::unique_lock<std::mutex> uniqueLock(m_owner.m_conditionMutex);

        if (m_owner.m_taskQueue.IsEmpty())
        {
            m_owner.m_conditionLock.wait(uniqueLock);
        }

        task = std::move(m_owner.m_taskQueue.Dequeue());

        task();
    }
}
    
} /* namespace tgon */