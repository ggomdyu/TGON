#include "PrecompiledHeader.h"

#include <algorithm>
#include <thread>

#include "Engine.h"

namespace tgon
{

Engine::~Engine() = default;

void Engine::OnLaunch()
{
}

void Engine::OnTerminate()
{
}

void Engine::RegisterModule(const std::shared_ptr<Module>& module)
{
    auto iter = std::lower_bound(m_modules.begin(), m_modules.end(), module->GetRTTI()->GetHashCode(), [&](const std::shared_ptr<Module>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    });
    
    m_modules.insert(iter, module);
}

bool Engine::UnregisterModule(size_t moduleId)
{
    auto iter = std::lower_bound(m_modules.begin(), m_modules.end(), moduleId, [&](const std::shared_ptr<Module>& lhs, size_t rhs)
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

std::shared_ptr<Module> Engine::FindModule(size_t moduleId)
{
    auto iter = std::lower_bound(m_modules.begin(), m_modules.end(), moduleId, [&](const std::shared_ptr<Module>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
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

void Engine::Update()
{
    for (auto& module : m_modules)
    {
        module->Update();
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

} /* namespace tgon */
