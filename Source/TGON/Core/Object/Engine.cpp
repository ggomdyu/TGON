#include "PrecompiledHeader.h"

#include "Engine.h"

#include "Core/Platform/WindowType.h"

namespace tgon
{

WindowStyle Engine::GetMainWindowStyle() const noexcept
{
    return {};
}
    
void Engine::Update()
{
    for (auto& module : m_modules)
    {
        module->Update();
    }
}

} /* namespace tgon */
