#include "PrecompiledHeader.h"

#include "Engine.h"

#include "Core/Platform/WindowType.h"

namespace tgon
{

WindowStyle Engine::GetRootWindowStyle() const noexcept
{
    return {};
}

void Engine::AddModule(const std::shared_ptr<IModule>& module)
{
    m_modules.push_back(module);
    m_modulesToFind.insert({module->GetRTTI()->GetHashCode(), module});
}
    
void Engine::Update()
{
    for (auto& module : m_modules)
    {
        module->Update();
    }
}

} /* namespace tgon */
