#include "PrecompiledHeader.h"

#include <algorithm>

#include "Core/Platform/WindowType.h"

#include "Engine.h"

namespace tgon
{

WindowStyle Engine::GetRootWindowStyle() const noexcept
{
    return {};
}

void Engine::AddModule(IModule* module)
{
    auto predicate = [&](const std::shared_ptr<IModule>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };

    auto iter = std::lower_bound(m_modules.begin(), m_modules.end(), module->GetRTTI()->GetHashCode(), predicate);

    m_modules.emplace(iter, module);
}

std::shared_ptr<IModule> Engine::GetModule(size_t moduleId) const
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
    for (auto& module : m_modules)
    {
        module->Update();
    }
}

} /* namespace tgon */
