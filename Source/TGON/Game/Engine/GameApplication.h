/**
 * @filename    GameApplication.h
 * @author      ggomdyu
 * @since       10/21/2017
 */

#pragma once
#include "Core/Platform/Application.h"

#include "../Object/Module/TimeModule.h"
#include "../Object/Module/GraphicsModule.h"

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

    TimeModule& GetTimeModule() noexcept;
//    InputModule& GetInputModule();
    GraphicsModule& GetGraphicsModule() noexcept;

    const TimeModule& GetTimeModule() const noexcept;
//    const InputModule& GetInputModule() const;
    const GraphicsModule& GetGraphicsModule() const noexcept;

/* @section Private variable */
private:
    TimeModule m_timeModule;
//    InputModule m_inputModule;
    GraphicsModule m_graphicsModule;
    //std::shared_ptr<SceneModule> m_sceneModule;
    //std::shared_ptr<UIModule> m_uiModule;
    //std::shared_ptr<SoundModule> m_soundModule;
    //std::shared_ptr<TaskModule> m_taskModule;
};

} /* namespace tgon */
