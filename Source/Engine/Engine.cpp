#include "PrecompiledHeader.h"

#include "Platform/Application.h"
#include "Graphics/Graphics.h"

#include "Engine.h"
#include "AssetModule.h"
#include "InputModule.h"
#include "TimeModule.h"
#include "TimerModule.h"
#include "TaskModule.h"
#include "InputModule.h"
#include "AudioModule.h"
#include "SceneModule.h"
#include "RendererModule.h"

namespace tg
{

Engine::Engine(EngineConfiguration engineConfig) noexcept :
    m_engineConfig(std::move(engineConfig))
{
}

Engine::~Engine()
{
    this->RemoveAllModule();
}

void Engine::Initialize()
{
    this->AddModule<TaskModule>();
    this->AddModule<AssetModule>();
    this->AddModule<AudioModule>();
    this->AddModule<TimeModule>();
    this->AddModule<TimerModule>();
    //this->AddModule<Input>s(m_engineConfig.inputMode);
    this->AddModule<SceneModule>();
}

void Engine::Update()
{
    for (auto& modules : m_moduleStage)
    {
        for (auto& module : modules)
        {
            if (module != nullptr)
            {
                module->Update();
            }
        }
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void Engine::RemoveAllModule()
{
    for (auto& modules : m_moduleStage)
    {
        while (modules.empty() == false)
        {
            modules.pop_back();
        }
    }
}

const EngineConfiguration& Engine::GetEngineConfiguration() const noexcept
{
    return m_engineConfig;
}

}
