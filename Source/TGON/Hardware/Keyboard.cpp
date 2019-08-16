#include "PrecompiledHeader.h"

#include "Keyboard.h"

namespace tgon
{

PlatformKeyboard& Keyboard::GetPlatformDependency() noexcept
{
    return *this;
}

const PlatformKeyboard& Keyboard::GetPlatformDependency() const noexcept
{
    return *this;
}

} /* namespace tgon */
