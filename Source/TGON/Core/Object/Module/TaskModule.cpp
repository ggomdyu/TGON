#include "PrecompiledHeader.h"

#include <mutex>

#include "Core/Debug/Log.h"

#include "TaskModule.h"

namespace tgon
{
    
TaskModule::TaskModule(int32_t taskThreadCount) :
    m_threadPool(taskThreadCount)
{
    for (auto i = 0; i < taskThreadCount; ++i)
    {
        m_threadPool[i] = std::thread([&]
        {
            while (true)
            {
                std::pair<Delegate<void()>, Delegate<void()>> taskPair;
                
                std::unique_lock<std::mutex> lockGuard(m_threadPoolMutex);

                // Wait until main thread notify to wake up.
                m_threadPoolCv.wait(lockGuard);
                {
                    // If thread woke up, then pop a task from queue.
                    taskPair = std::move(m_taskQueue.front());
                    m_taskQueue.pop_front();
                }
                // And unlock the mutex for other thread which wait for task.
                lockGuard.unlock();

                // Execute the task.
                taskPair.first();
                
                std::lock_guard<std::mutex> lockGuard2(m_taskCompleteHandlerQueueMutex);
                {
                    m_taskCompleteHandlerQueue.push_back(taskPair.second);
                }
            }
        });
    }
}
    
TaskModule::~TaskModule()
{
    for (auto& thread : m_threadPool)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}

void TaskModule::Update()
{
    if (!m_taskQueue.empty())
    {
        m_threadPoolCv.notify_one();
    }
    
    if (!m_taskCompleteHandlerQueue.empty())
    {
        std::lock_guard<std::mutex> lockGuard(m_taskCompleteHandlerQueueMutex);
        {
            for (auto& taskCompleteHandler : m_taskCompleteHandlerQueue)
            {
                taskCompleteHandler();
            }
            m_taskCompleteHandlerQueue.clear();
        }
    }
}

} /* namespace tgon */
