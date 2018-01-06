/**
 * @filename    GameApplication.h
 * @author      ggomdyu
 * @since       10/21/2017
 */

#pragma once
#include "GameApplicationFwd.h"

#include "Core/Platform/Application.h"

#include <vector>
#include <unordered_map>

namespace tgon
{
namespace game
{

class TGON_API GameApplication :
    public core::Application
{
public:
    TGON_RUNTIME_OBJECT(GameApplication)

/* @section Public constructor */
public:
    GameApplication(const core::WindowStyle& windowStyle);
    GameApplication(const core::WindowStyle& windowStyle, const graphics::VideoMode& videoMode);
    virtual ~GameApplication() = default;

/* @section Public method */
public:
    virtual void OnUpdate() override;

    /**
     * @brief   Adds a module to engine.
     * @detail  Added module will be updated automatically by engine.
     */
    template <typename _ModuleType>
    void AddModule(const std::shared_ptr<_ModuleType>& module);

    /**
     * @brief                   Finds a module.
     * @tparam  _ModuleType     The type of module to find
     * @return                  Returns module if succeeded, nullptr otherwise.
     */
    template <typename _ModuleType>
    const std::shared_ptr<_ModuleType>& FindModule() const;

/* @section Private method */
private:

/* @section Private variable */
private:
    std::vector<std::shared_ptr<IModule>> m_modulesToIterate;
    std::unordered_map<uint32_t, std::shared_ptr<IModule>> m_modulesToFind;

    //std::shared_ptr<SceneModule> m_sceneModule;
    //std::shared_ptr<UIModule> m_uiModule;
    //std::shared_ptr<SoundModule> m_soundModule;
    //std::shared_ptr<InputModule> m_inputModule;
    std::shared_ptr<TimeModule> m_timeModule;
    std::shared_ptr<GraphicsModule> m_graphicsModule;
};

template<typename _ModuleType>
inline void GameApplication::AddModule(const std::shared_ptr<_ModuleType>& module)
{
    m_modulesToIterate.push_back(module);
    m_modulesToFind.insert({module->GetRTTI()->GetHashCode(), module});
}

template<typename _ModuleType>
inline const std::shared_ptr<_ModuleType>& GameApplication::FindModule() const
{
    auto iter = m_modulesToFind.find(core::GetRTTI<_ModuleType>()->GetHashCode());
    if (iter != m_modulesToFind.end())
    {
        return *iter;
    }

    return nullptr;
}

template<>
inline const std::shared_ptr<TimeModule>& GameApplication::FindModule<TimeModule>() const
{
    return m_timeModule;
}

template<>
inline const std::shared_ptr<GraphicsModule>& GameApplication::FindModule<GraphicsModule>() const
{
    return m_graphicsModule;
}

} /* namespace game */
} /* namespace tgon */