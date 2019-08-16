#include "PrecompiledHeader.h"

#include "InputManager.h"

namespace tgon
{

PlatformInputManager& InputManager::GetPlatformDependency() noexcept
{
    return *this;
}

const PlatformInputManager& InputManager::GetPlatformDependency() const noexcept
{
    return *this;
}

} /* namespace tgon */
