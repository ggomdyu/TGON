#include "PrecompiledHeader.h"

#include "Core/Platform/WindowType.h"

#include "Engine.h"

namespace tgon
{

WindowStyle Engine::GetRootWindowStyle() const noexcept
{
    return {};
}

void Engine::AddModule(const std::shared_ptr<IModule>& module)
{
    m_modulesToIter.push_back(module);
    m_modulesToFind.insert({module->GetRTTI()->GetHashCode(), module});
}
    
void Engine::Update()
{
    for (auto& module : m_modulesToIter)
    {
        module->Update();
    }
}

} /* namespace tgon */
