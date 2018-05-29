#include "PrecompiledHeader.h"

#include <mutex>

#include "Core/Debug/Log.h"

#include "TaskModule.h"

namespace tgon
{
namespace
{
    
std::mutex g_mutex;
    
} /* namespace */
    
TaskModule::TaskModule(int32_t taskThreadCount) :
    m_taskThreads(taskThreadCount)
{
    for (auto i = 0; i < taskThreadCount; ++i)
    {
        m_taskThreads[i] = std::thread([&]
        {
//            Log(LogLevel::Warning, "1");
            std::unique_lock<std::mutex> lockGuard(g_mutex);
            
            std::condition_variable cv;
            cv.wait(lockGuard, [&]()
            {
                return !m_tasks.empty();
            });
//            Log(LogLevel::Warning, "2");
            auto& taskPair = m_tasks.front();
            Delegate<void()> task = std::move(taskPair.first);
            Delegate<void()> onTaskComplete = std::move(taskPair.second);
            m_tasks.pop_front();
            
//            Log(LogLevel::Warning, "3");
            lockGuard.unlock();
        });
    }
}

void TaskModule::Update()
{
}

} /* namespace tgon */
