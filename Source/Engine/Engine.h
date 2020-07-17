#pragma once

#include <vector>
#include <array>

#include "Core/Algorithm.h"
#include "Platform/WindowStyle.h"
#include "Graphics/VideoMode.h"

#include "InputModule.h"
#include "TimeModule.h"

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
    explicit Engine(EngineConfiguration engineConfig) noexcept;
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
     * @brief   Initializes the object.
     */
    virtual void Initialize();

    /**
     * @brief   Updates the frame of the object.
     */
    virtual void Update();

    /**
     * @brief   Adds a module to the object.
     * @param args  Arguments for construct the specified type of module.
     * @return  The added module.
     */
    template <Modularizable _ModuleType, typename... _ArgTypes>
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
     * @return  The engine configuration.
     */
    [[nodiscard]] const EngineConfiguration& GetEngineConfiguration() const noexcept;

    /**
     * @brief   Forces the engine to render at a specified frame rate.
     * @param targetFrameRate   The frame rate.
     */
    void SetTargetFrameRate(float targetFrameRate);

    /**
     * @brief   Gets the frame rate of the engine.
     * @return  The frame rate.
     */
    [[nodiscard]] float GetTargetFrameRate() const noexcept;

private:
    void UpdateModule();
    void UpdateModuleStage(ModuleStage moduleStage);
    void RemoveAllModule();

/**@section Variable */
private:
    EngineConfiguration m_engineConfig;
    std::array<std::vector<std::unique_ptr<Module>>, 3> m_moduleStage;
    int64_t m_prevFrameTime = 0;
    float m_frameTime = 0.0f;
    float m_targetSecondPerFrame = -1.0f;
};
    
template <Modularizable _ModuleType, typename... _ArgTypes>
_ModuleType* Engine::AddModule(_ArgTypes&&... args)
{
    auto module = std::make_unique<_ModuleType>(std::forward<_ArgTypes>(args)...);
    auto* rawModule = module.get();
    m_moduleStage[UnderlyingCast(_ModuleType::ModuleStage)].push_back(std::move(module));

    rawModule->Initialize();

    return rawModule;
}

template <typename _ModuleType>
_ModuleType* Engine::FindModule() noexcept
{
    for (auto& modules : m_moduleStage)
    {
        for (auto& module : modules)
        {
            if (module->GetRtti() == GetRtti<_ModuleType>())
            {
                return reinterpret_cast<_ModuleType*>(module.get());
            }
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