#include "PrecompiledHeader.h"

#include "Graphics.h"

namespace tgon
{

Graphics::Graphics(const Window& displayTarget, const VideoMode& videoMode) :
    PlatformGraphics(displayTarget, videoMode)
{
    this->EnableCullFace();
}

PlatformGraphics& Graphics::GetPlatformDependency() noexcept
{
    return *this;
}

const PlatformGraphics& Graphics::GetPlatformDependency() const noexcept
{
    return *this;
}

} /* namespace tgon */
