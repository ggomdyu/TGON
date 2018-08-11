/**
 * @file    Engine.h
 * @author  ggomdyu
 * @since   06/11/2018
 */

#pragma once
#include "Core/Object/CoreObject.h"

#include "TimeModule.h"
#include "InputModule.h"

#define TGON_DECLARE_ENGINE(className)\
    namespace tgon\
    {\
    \
    std::unique_ptr<Engine> MakeEngine()\
    {\
        static_assert(std::is_base_of<Engine, className>::value, "TGON_DECLARE_ENGINE accepts only class that inherited from Engine.");\
        return std::make_unique<className>();\
    }\
    \
    } /* namespace tgon */

namespace tgon
{

class TGON_API Engine :
    public CoreObject
{
public:
    TGON_RUNTIME_OBJECT(Engine);

/* @section Protected constructor */
protected:
    Engine();

/* @section Public destructor */
public:
    virtual ~Engine() = 0;
    
/* @section Public method */
public:
    /* @brief   Gets the global instance of this class. */
    static Engine* GetInstance();
    
    /* @brief               Updates the Engine. */
    virtual void Update();
    
    /**
     * @brief               Inserts a module to manage.
     * @param [in] args     Parameters of the _ModuleType constructor.
     */
    template <typename _ModuleType, typename... _ArgTypes>
    void AddModule(_ArgTypes&&... args);
    
    /**
     * @brief               Removes the managed module.
     * @tparam _ModuleType  The type of module to remove.
     */
    template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>* = nullptr>
    bool RemoveModule();

    /**
     * @brief               Returns a module that managed by Application.
     */
    template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>* = nullptr>
    const _ModuleType* FindModule() const noexcept;

    /* @brief               Returns a module that managed by Application. */
    template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>* = nullptr>
    _ModuleType* FindModule() noexcept;

/* @section Private method */
private:
    /**
     * @brief               Inserts a module to manage.
     * @param [in] module   The module to insert.
     */
    void AddModule(std::unique_ptr<IModule> module);
    
    /**
     * @brief               Returns a module that managed by Application.
     * @param [in] moduleId The unique id of module to get.
     * @return              Returns a pointer to module if successful, nullptr otherwise.
     */
    IModule* FindModule(size_t moduleId);

    /**
     * @brief               Returns a module that managed by Application.
     * @param [in] moduleId The unique id of module to get.
     * @return              Returns a pointer to module if successful, nullptr otherwise.
     */
    bool RemoveModule(size_t moduleId);

/* @section Private variable */
private:
    //std::unique_ptr<AudioModule> m_audioModule;

    std::unique_ptr<TimeModule> m_timeModule;

    std::vector<std::unique_ptr<IModule>> m_modules;
};

template <typename _ModuleType, typename ..._ArgTypes>
inline void Engine::AddModule(_ArgTypes&&... args)
{
    this->AddModule(std::make_unique<_ModuleType>(std::forward<_ArgTypes>(args)...));
}

template <>
inline void Engine::AddModule<TimeModule>()
{
}

template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>*>
inline const _ModuleType* Engine::FindModule() const noexcept
{
    return const_cast<Engine*>(this)->FindModule<_ModuleType>();
}

template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>*>
inline _ModuleType* Engine::FindModule() noexcept
{
    return static_cast<_ModuleType*>(this->FindModule(tgon::GetRTTI<_ModuleType>()->GetHashCode()));
}

template <>
inline const TimeModule* Engine::FindModule<TimeModule>() const noexcept
{
    return m_timeModule.get();
}

template <>
inline TimeModule* Engine::FindModule<TimeModule>() noexcept
{
    return m_timeModule.get();
}

template <typename _ModuleType, std::enable_if_t<std::is_base_of<IModule, _ModuleType>::value>*>
inline bool Engine::RemoveModule()
{
    return this->RemoveModule(tgon::GetRTTI<_ModuleType>()->GetHashCode());
}
    
} /* namespace tgon */
