#include "PrecompiledHeader.h"

#include "Time/Time.h"

#include "TaskModule.h"

namespace tgon
{

TaskModule::TaskModule()
{
}

void TaskModule::Update()
{
    m_mainDispatchQueue.Dispatch();
}

SerialDispatchQueue& TaskModule::GetMainDispatchQueue() noexcept
{
    return m_mainDispatchQueue;
}

const SerialDispatchQueue& TaskModule::GetMainDispatchQueue() const noexcept
{
    return m_mainDispatchQueue;
}

ConcurrentDispatchQueue& TaskModule::GetGlobalDispatchQueue(ThreadPriority threadPriority)
{
    auto& dispatchQueue = m_globalDispatchQueues[(int)threadPriority];
    if (dispatchQueue == nullptr)
    {
        dispatchQueue = std::make_unique<ConcurrentDispatchQueue>(threadPriority, 2);
    }
    
    return *dispatchQueue;
}
    
const ConcurrentDispatchQueue& TaskModule::GetGlobalDispatchQueue(ThreadPriority threadPriority) const
{
    return const_cast<TaskModule*>(this)->GetGlobalDispatchQueue(threadPriority);
}

}
