#include "PrecompiledHeader.h"

#include <algorithm>

#include "Core/Platform/Application.h"

#include "Engine.h"

namespace tgon
{
    
extern std::unique_ptr<Engine> MakeEngine();

Engine::Engine() :
    m_timeModule(std::make_unique<TimeModule>())
{
}

Engine::~Engine() = default;

Engine* Engine::GetInstance()
{
    static decltype(auto) instance = MakeEngine();
    return instance.get();
}
    
void Engine::AddModule(std::unique_ptr<IModule> module)
{
    auto iter = std::lower_bound(m_modules.begin(), m_modules.end(), module->GetRTTI()->GetHashCode(), [&](const std::unique_ptr<IModule>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    });

    m_modules.emplace(iter, std::move(module));
}

IModule* Engine::GetModule(size_t moduleId)
{
    auto iter = std::lower_bound(m_modules.begin(), m_modules.end(), moduleId, [&](const std::unique_ptr<IModule>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    });
    if (iter != m_modules.end())
    {
        return (*iter).get();
    }
    else
    {
        return nullptr;
    }
}

bool Engine::RemoveModule(size_t moduleId)
{
    auto iter = std::lower_bound(m_modules.begin(), m_modules.end(), moduleId, [&](const std::unique_ptr<IModule>& lhs, size_t rhs)
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
}

} /* namespace tgon */
