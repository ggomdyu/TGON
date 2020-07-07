#include "PrecompiledHeader.h"

#include "Platform/Application.h"
#include "Graphics/Graphics.h"

#include "Engine.h"
#include "AssetModule.h"
#include "Input.h"
#include "Time.h"
#include "Timer.h"
#include "TaskModule.h"
#include "Input.h"
#include "Audio.h"
#include "SceneModule.h"
#include "Renderer.h"

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
    this->AddModule<Audio>();
    this->AddModule<Time>();
    this->AddModule<WorldTimer>();
    //this->AddModule<Input>s(m_engineConfig.inputMode);
    this->AddModule<SceneManager>();
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
