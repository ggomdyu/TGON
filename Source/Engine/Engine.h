#pragma once

#include <vector>

#include "Platform/WindowStyle.h"
#include "Graphics/VideoMode.h"

#include "Input.h"
#include "Module.h"

#define TGON_ENGINE(className)\
    namespace tg\
    {\
    \
    std::unique_ptr<Engine> CreateEngine()\
    {\
        static_assert(std::is_base_of_v<Engine, className>, "TGON_DECLARE_ENGINE accepts only class that inherited from Engine.");\
        return std::make_unique<className>();\
    }\
    \
    }

namespace tg
{

struct EngineConfiguration final
{
    WindowStyle windowStyle;
    InputMode inputMode;
    VideoMode videoMode;
};

class Engine :
    public RuntimeObject
{
public:
    TGON_RTTI(Engine)

/**@section Constructor */
public:
    explicit Engine(const EngineConfiguration& engineConfig) noexcept;
    Engine(const Engine& rhs) = delete;
    Engine(Engine&& rhs) = delete;

/**@section Destructor */
public:
    ~Engine() override;

/**@section Operator */
public:
    Engine& operator=(const Engine& rhs) = delete;
    Engine& operator=(Engine&& rhs) = delete;

/**@section Method */
public:
    /**
     * @brief   Initialize the object.
     */
    virtual void Initialize();

    /**
     * @brief   Update the frame of the object.
     */
    virtual void Update();

    /**
     * @brief   Adds a module to the object.
     * @param args  Arguments for construct the specified type of module.
     * @return  The added module.
     */
    template <typename _ModuleType, typename... _ArgTypes>
    _ModuleType* AddModule(_ArgTypes&&... args);

    /**
     * @brief   Finds the module of the specified type.
     * @return  The type of module to retrieve or nullptr.
     */
    template <typename _ModuleType>
    [[nodiscard]] _ModuleType* FindModule() noexcept;

    /**
     * @brief   Finds the module of the specified type.
     * @return  The type of module to retrieve or nullptr.
     */
    template <typename _ModuleType>
    [[nodiscard]] const _ModuleType* FindModule() const noexcept;

    /**
     * @brief   Gets the configuration of the engine.
     */
    [[nodiscard]] const EngineConfiguration& GetEngineConfiguration() const noexcept;

private:
    void RemoveAllModule();

/**@section Variable */
private:
    EngineConfiguration m_engineConfig;
    std::vector<std::unique_ptr<Module>> m_modules;
};
    
template <typename _ModuleType, typename... _ArgTypes>
_ModuleType* Engine::AddModule(_ArgTypes&&... args)
{
    auto module = std::make_unique<_ModuleType>(std::forward<_ArgTypes>(args)...);
    auto* rawModule = module.get();
    m_modules.push_back(std::move(module));

    rawModule->Initialize();

    return rawModule;
}

template <typename _ModuleType>
_ModuleType* Engine::FindModule() noexcept
{
    for (auto& module : m_modules)
    {
        if (module->GetRtti() == GetRtti<_ModuleType>())
        {
            return reinterpret_cast<_ModuleType*>(module.get());
        }
    }

    return nullptr;
}

template <typename _ModuleType>
const _ModuleType* Engine::FindModule() const noexcept
{
    return const_cast<Engine*>(this)->FindModule<_ModuleType>();
}

}