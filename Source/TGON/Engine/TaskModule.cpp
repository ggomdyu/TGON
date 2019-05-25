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

ConcurrentDispatchQueue& TaskModule::GetGlobalDispatchQueue(ConcurrentDispatchQoS qos) noexcept
{
    return this->GetConcurrentDispatchQueue(qos);
}
    
const SerialDispatchQueue& TaskModule::GetMainDispatchQueue() const noexcept
{
    return m_mainDispatchQueue;
}

const ConcurrentDispatchQueue& TaskModule::GetGlobalDispatchQueue(ConcurrentDispatchQoS qos) const noexcept
{
    return this->GetConcurrentDispatchQueue(qos);
}
    
ConcurrentDispatchQueue& TaskModule::GetConcurrentDispatchQueue(ConcurrentDispatchQoS qos) noexcept
{
    auto& dispatchQueue = m_concurrentDispatchQueues[(int)qos];
    if (dispatchQueue == nullptr)
    {
        dispatchQueue = std::make_unique<ConcurrentDispatchQueue>(qos, 2);
    }
    
    return *dispatchQueue;
}
    
const ConcurrentDispatchQueue& TaskModule::GetConcurrentDispatchQueue(ConcurrentDispatchQoS qos) const noexcept
{
    return const_cast<TaskModule*>(this)->GetConcurrentDispatchQueue(qos);
}

} /* namespace tgon */
