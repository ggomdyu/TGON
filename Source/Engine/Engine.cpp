#include "PrecompiledHeader.h"

#include "Platform/Application.h"
#include "Graphics/Graphics.h"

#include "Engine.h"
#include "AssetModule.h"
#include "Input.h"
#include "Time.h"
#include "TimerModule.h"
#include "TaskModule.h"
#include "Input.h"
#include "Audio.h"
#include "SceneModule.h"

namespace tg
{

Engine::Engine(const EngineConfiguration& engineConfig) noexcept :
    m_engineConfig(engineConfig)
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
    this->AddModule<Audio>();
    this->AddModule<Time>();
    this->AddModule<TimerModule>();
    //this->AddModule<Input>s(m_engineConfig.inputMode);
    this->AddModule<SceneManager>();
}

void Engine::Update()
{
    for (auto& module : m_modules)
    {
        if (module != nullptr)
        {
            module->Update();
        }
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void Engine::RemoveAllModule()
{
    while (m_modules.empty() == false)
    {
        m_modules.pop_back();
    }
}

const EngineConfiguration& Engine::GetEngineConfiguration() const noexcept
{
    return m_engineConfig;
}

}
