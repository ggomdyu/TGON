#include "PrecompiledHeader.h"

#include "Graphics.h"

namespace tgon
{

PlatformGraphics& Graphics::GetPlatformDependency() noexcept
{
    return *this;
}

const PlatformGraphics& Graphics::GetPlatformDependency() const noexcept
{
    return *this;
}

} /* namespace tgon */
