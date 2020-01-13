#include "PrecompiledHeader.h"

#include "Platform/Application.h"

#include "Engine.h"
#include "AssetModule.h"
#include "AudioModule.h"
#include "TimeModule.h"
#include "TimerModule.h"
#include "TaskModule.h"
#include "InputModule.h"
#include "UIRendererModule.h"
#include "SceneModule.h"

namespace tgon
{

Engine::Engine(const EngineConfig& enfingConfig) noexcept :
    m_engineConfig(enfingConfig)
{
}

Engine::~Engine()
{
    this->Destroy();
}

void Engine::Initialize()
{
    this->AddModule<TaskModule>();
    this->AddModule<AssetModule>();
    this->AddModule<AudioModule>();
    this->AddModule<TimeModule>();
    this->AddModule<TimerModule>();
    this->AddModule<InputModule>(m_engineConfig.inputMode);

    auto graphics = std::make_shared<Graphics>(*Application::GetInstance().GetRootWindow(), m_engineConfig.videoMode);
    this->AddModule<UIRendererModule>(graphics);

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
