#pragma once

#include "Threading/DispatchQueue.h"

#include "Module.h"

namespace tg
{

class TaskModule :
	public Module
{
public:
    TGON_DECLARE_RTTI(TaskModule)

/**@section Constructor */
public:
    explicit TaskModule(int32_t threadPoolCount = Thread::GetHardwareConcurrency());

/**@section Method */
public:
    SerialDispatchQueue& GetMainDispatchQueue() noexcept;
    const SerialDispatchQueue& GetMainDispatchQueue() const noexcept;
    ConcurrentDispatchQueue& GetGlobalDispatchQueue();
    const ConcurrentDispatchQueue& GetGlobalDispatchQueue() const;
    void Update() override;
    
/**@section Variable */
private:
    SerialDispatchQueue m_mainDispatchQueue;
    ConcurrentDispatchQueue m_globalDispatchQueue;
};

}
