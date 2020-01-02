#include "PrecompiledHeader.h"

#include <algorithm>
#include <thread>

#include "Engine.h"

namespace tgon
{

Engine::~Engine() = default;

void Engine::Initialize()
{
    for (auto& module : m_moduleCache)
    {
        module->Initialize();
    }
}

void Engine::Destroy()
{
    for (auto iter = m_moduleCache.rbegin(); iter != m_moduleCache.rend(); ++iter)
    {
        (*iter)->Destroy();
    }

    while (m_moduleCache.empty() == false)
    {
        m_moduleCache.back();
    }
}

void Engine::Update()
{
    for (auto& module : m_moduleCache)
    {
        module->Update();
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

} /* namespace tgon */
