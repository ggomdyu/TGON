/**
 * @file    TaskModule.h
 * @author  ggomdyu
 * @since   05/22/2019
 */

#pragma once
#include <unordered_map>
#include <array>
#include <memory>

#include "Thread/DispatchQueue.h"

#include "IModule.h"

namespace tgon
{
    
//struct TaskModuleProperty
//{
//    int32_t UserInteractiveDispatchQueue
////    ConcurrentDispatchQoS qos, int32_t threadPoolCount)
//};

class TGON_API TaskModule final :
	public IModule
{
public:
    TGON_DECLARE_RTTI(TaskModule);

/**@section Constructor */
public:
    TaskModule();

/**@section Destructor */
public:
    virtual ~TaskModule() override = default;

/**@section Method */
public:
    virtual void Update() override;
    SerialDispatchQueue& GetMainDispatchQueue() noexcept;
    ConcurrentDispatchQueue& GetGlobalDispatchQueue(ThreadPriority threadPriority = ThreadPriority::Normal) noexcept;
    const SerialDispatchQueue& GetMainDispatchQueue() const noexcept;
    const ConcurrentDispatchQueue& GetGlobalDispatchQueue(ThreadPriority threadPriority = ThreadPriority::Normal) const noexcept;
    
private:
    ConcurrentDispatchQueue& GetConcurrentDispatchQueue(ThreadPriority threadPriority) noexcept;
    const ConcurrentDispatchQueue& GetConcurrentDispatchQueue(ThreadPriority threadPriority) const noexcept;
    
/**@section Variable */
private:
    SerialDispatchQueue m_mainDispatchQueue;
    std::array<std::unique_ptr<ConcurrentDispatchQueue>, 5> m_concurrentDispatchQueues;
};

} /* namespace tgon */