/**
 * @filename    TaskModule.h
 * @author      ggomdyu
 * @since       05/25/2018
 */

#pragma once
#include <vector>
#include <deque>
#include <cstdint>
#include <thread>

#include "Core/Object/Delegate.h"

#include "IModule.h"

namespace tgon
{

class TGON_API TaskModule :
    public IModule
{
public:
    TGON_RUNTIME_OBJECT(TaskModule);

/* @section Public constructor */
public:
    explicit TaskModule(int32_t taskThreadCount = 2);

/* @section Public destructor */
public:
    virtual ~TaskModule() final override;

/* @section Public method */
public:
    virtual void Update() override;
    
    template <typename _TaskType, typename _TaskCompleteHandlerType>
    void AddTask(_TaskType&& task, _TaskCompleteHandlerType&& taskCompleteHandler);
    
private:    
    std::mutex m_threadPoolMutex;
    std::condition_variable m_threadPoolCv;
    std::vector<std::thread> m_threadPool;
    
    std::deque<std::pair<Delegate<void()>, Delegate<void()>>> m_taskQueue;
    
    std::mutex m_taskCompleteHandlerQueueMutex;
    std::deque<Delegate<void()>> m_taskCompleteHandlerQueue;
};

template <typename _TaskType, typename _TaskCompleteHandlerType>
inline void TaskModule::AddTask(_TaskType&& task, _TaskCompleteHandlerType&& onTaskComplete)
{
    m_taskQueue.push_back({std::forward<_TaskType>(task), std::forward<_TaskCompleteHandlerType>(onTaskComplete)});
}
    
} /* namespace tgon */
