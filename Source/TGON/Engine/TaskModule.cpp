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

ConcurrentDispatchQueue& TaskModule::GetGlobalDispatchQueue(ThreadPriority threadPriority) noexcept
{
    return this->GetConcurrentDispatchQueue(threadPriority);
}
    
const SerialDispatchQueue& TaskModule::GetMainDispatchQueue() const noexcept
{
    return m_mainDispatchQueue;
}

const ConcurrentDispatchQueue& TaskModule::GetGlobalDispatchQueue(ThreadPriority threadPriority) const noexcept
{
    return this->GetConcurrentDispatchQueue(threadPriority);
}
    
ConcurrentDispatchQueue& TaskModule::GetConcurrentDispatchQueue(ThreadPriority threadPriority) noexcept
{
    auto& dispatchQueue = m_concurrentDispatchQueues[(int)threadPriority];
    if (dispatchQueue == nullptr)
    {
        dispatchQueue = std::make_unique<ConcurrentDispatchQueue>(threadPriority, 2);
    }
    
    return *dispatchQueue;
}
    
const ConcurrentDispatchQueue& TaskModule::GetConcurrentDispatchQueue(ThreadPriority threadPriority) const noexcept
{
    return const_cast<TaskModule*>(this)->GetConcurrentDispatchQueue(threadPriority);
}

} /* namespace tgon */
