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

template <typename... _Args>
struct AsyncHandler final : 
    public Delegate<_Args...>
{
};

template <typename... _Args>
struct SyncHandler final :
    public Delegate<_Args...>
{
};

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
    virtual ~TaskModule() final override = default;

/* @section Public method */
public:
    virtual void Update() override;
    
    template <typename _Type1, typename _Type2>
    void AddTask(_Type1&& task, _Type2&& onTaskComplete);
//    void RemoveTask();
    
private:
    
private:
    std::vector<std::thread> m_taskThreads;
    std::deque<std::pair<Delegate<void()>, Delegate<void()>>> m_tasks;
};

template <typename _Type1, typename _Type2>
inline void TaskModule::AddTask(_Type1&& task, _Type2&& onTaskComplete)
{
    m_tasks.push_back({std::forward<_Type1>(task), std::forward<_Type2>(onTaskComplete)});
}
    
} /* namespace tgon */
