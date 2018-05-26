/**
 * @filename    TaskModule.h
 * @author      ggomdyu
 * @since       05/25/2018
 */

#pragma once
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
    TaskModule() = default;

/* @section Public destructor */
public:
    virtual ~TaskModule() final override = default;

/* @section Public method */
public:
    template <typename _TaskType, typename _TaskCompleteHandlerType>
    void AddTask(_TaskType&& task, _TaskCompleteHandlerType&& onTaskComplete);
    virtual void Update();
};
    
} /* namespace tgon */
