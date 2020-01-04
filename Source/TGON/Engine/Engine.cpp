#include "PrecompiledHeader.h"

#include "Platform/Application.h"

#include "Engine.h"
#include "AssetModule.h"
#include "AudioModule.h"
#include "TimeModule.h"
#include "TimerModule.h"
#include "TaskModule.h"
#include "InputModule.h"
#include "GraphicsModule.h"
#include "SceneModule.h"

namespace tgon
{

Engine::Engine(const EngineConfig& enfingConfig) noexcept :
    m_engineConfig(enfingConfig)
{
}

Engine::~Engine() = default;

void Engine::Initialize()
{
    this->InitializeModule();

    for (auto& module : m_moduleCache)
    {
        if (module != nullptr)
        {
            module->Initialize();
        }
    }
}

void Engine::InitializeModule()
{
    this->AddModule<AssetModule>();
    this->AddModule<AudioModule>();
    this->AddModule<TimeModule>();
    this->AddModule<TimerModule>();
    this->AddModule<TaskModule>();

    decltype(auto) rootWindow = Application::GetInstance().GetRootWindow();
    this->AddModule<InputModule>(*rootWindow, m_engineConfig.inputMode);
    this->AddModule<GraphicsModule>(*rootWindow, m_engineConfig.videoMode);
    this->AddModule<SceneModule>();
}

void Engine::Destroy()
{
    this->RemoveAllModule();
}

void Engine::Update()
{
    for (auto& module : m_moduleCache)
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
    for (auto iter = m_moduleCache.rbegin(); iter != m_moduleCache.rend(); ++iter)
    {
        (*iter)->Destroy();
    }

    while (m_moduleCache.empty() == false)
    {
        m_moduleCache.pop_back();
    }
}

const EngineConfig& Engine::GetEngineConfig() const noexcept
{
    return m_engineConfig;
}

} /* namespace tgon */
