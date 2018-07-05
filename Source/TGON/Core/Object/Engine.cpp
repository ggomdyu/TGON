#include "PrecompiledHeader.h"

#include <algorithm>

#include "Core/Platform/WindowType.h"
#include "Core/Platform/Application.h"

#include "Engine.h"
#include "Module/IModule.h"

namespace tgon
{

Engine::Engine() :
    m_timeModule(std::make_shared<TimeModule>())
{
}

Engine::~Engine() = default;

Engine& Engine::GetInstance() noexcept
{
    return Application::GetInstance().GetEngine();
}
    
void Engine::AddModule(const std::shared_ptr<IModule>& module)
{
    auto predicate = [&](const std::shared_ptr<IModule>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };

    auto iter = std::lower_bound(m_modules.begin(), m_modules.end(), module->GetRTTI()->GetHashCode(), predicate);

    m_modules.emplace(iter, module);
}

std::shared_ptr<IModule> Engine::GetModule(size_t moduleId)
{
    auto predicate = [&](const std::shared_ptr<IModule>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };

    auto iter = std::lower_bound(m_modules.begin(), m_modules.end(), moduleId, predicate);
    if (iter != m_modules.end())
    {
        return *iter;
    }
    else
    {
        return nullptr;
    }
}

bool Engine::RemoveModule(size_t moduleId)
{
    auto predicate = [&](const std::shared_ptr<IModule>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };

    auto iter = std::lower_bound(m_modules.begin(), m_modules.end(), moduleId, predicate);
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
