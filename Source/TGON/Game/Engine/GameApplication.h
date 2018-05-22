/**
 * @filename    GameApplication.h
 * @author      ggomdyu
 * @since       10/21/2017
 */

#pragma once
#include "Core/Platform/Application.h"

#include "../System/TimeSystem.h"
#include "../System/GraphicsSystem.h"

namespace tgon
{

class TGON_API GameApplication :
    public Application
{
public:
    TGON_RUNTIME_OBJECT(GameApplication)

/* @section Public constructor */
public:
    GameApplication(const WindowStyle& windowStyle, const VideoMode& videoMode);

/* @section Public destructor */
public:
    virtual ~GameApplication() override = default;

/* @section Public method */
public:
    virtual void OnUpdate() override;

    TimeSystem& GetTimeSystem() noexcept;
//    InputSystem& GetInputSystem();
    GraphicsSystem& GetGraphicsSystem() noexcept;

    const TimeSystem& GetTimeSystem() const noexcept;
//    const InputSystem& GetInputSystem() const;
    const GraphicsSystem& GetGraphicsSystem() const noexcept;

/* @section Private variable */
private:
    TimeSystem m_timeSystem;
//    InputSystem m_inputSystem;
    GraphicsSystem m_graphicsSystem;
    //std::shared_ptr<SceneSystem> m_sceneSystem;
    //std::shared_ptr<UISystem> m_uiSystem;
    //std::shared_ptr<SoundSystem> m_soundSystem;
    //std::shared_ptr<TaskSystem> m_taskSystem;
};

} /* namespace tgon */
