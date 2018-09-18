#include "PrecompiledHeader.h"

#include <algorithm>
#include <thread>

#include "Core/Platform/Application.h"

#include "Engine.h"

namespace tgon
{

Engine::Engine() :
    m_timeModule(std::make_shared<TimeModule>())
{
}

Engine::~Engine() = default;

void Engine::OnDidLaunch()
{
}

void Engine::OnWillTerminate()
{
}

void Engine::RegisterModule(const std::shared_ptr<IModule>& module)
{
    m_modules.push_back(module);
}

std::shared_ptr<IModule> Engine::FindModule(size_t moduleId)
{
    auto iter = std::find_if(m_modules.begin(), m_modules.end(), [&](const std::shared_ptr<IModule>& lhs)
    {
        return lhs->GetRTTI()->GetHashCode() == moduleId;
    });
    if (iter != m_modules.end())
    {
        return *iter;
    }
    else
    {
        return nullptr;
    }
}

bool Engine::UnregisterModule(size_t moduleId)
{
    auto iter = std::lower_bound(m_modules.begin(), m_modules.end(), moduleId, [&](const std::shared_ptr<IModule>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    });
    if (iter != m_modules.end())
    {
        m_modules.erase(iter);
        return true;
    }
    else
    {
        return false;
    }
}

void Engine::Update()
{
    m_timeModule->Update();
    
    for (auto& module : m_modules)
    {
        module->Update();
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

} /* namespace tgon */
