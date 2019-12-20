#include "PrecompiledHeader.h"

#include "InputManager.h"

namespace tgon
{

InputManager::InputManager(const Window& inputTargetWindow) :
    PlatformInputManager(inputTargetWindow)
{
}

PlatformInputManager& InputManager::GetPlatformDependency() noexcept
{
    return *this;
}

const PlatformInputManager& InputManager::GetPlatformDependency() const noexcept
{
    return *this;
}

} /* namespace tgon */
