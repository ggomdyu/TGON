#include "PrecompiledHeader.h"

#include "InputManager.h"

namespace tgon
{

InputManager::InputManager(std::shared_ptr<Window> inputTarget) :
    m_platformInputManager(inputTarget)
{
}
    
InputManager::~InputManager() = default;

void InputManager::Update()
{
    m_platformInputManager.Update();
}

const PlatformInputManager& InputManager::GetPlatformDependency() const noexcept
{
    return m_platformInputManager;
}

PlatformInputManager& InputManager::GetPlatformDependency() noexcept
{
    return m_platformInputManager;
}

} /* namespace tgon */
