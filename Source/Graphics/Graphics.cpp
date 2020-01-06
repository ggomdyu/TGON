#include "PrecompiledHeader.h"

#include "Graphics.h"

namespace tgon
{

Graphics::Graphics(const Window& displayTarget, const VideoMode& videoMode) :
    PlatformGraphics(displayTarget, videoMode)
{
    this->EnableCullFace();

    auto clientSize = displayTarget.GetClientSize();
    this->SetViewport(0, 0, clientSize.width, clientSize.height);
    this->SetClearColor(videoMode.clearColor);
    this->SetCullMode(CullMode::CW);
    this->EnableDepthTest();
    this->EnableBlend();
    this->SetBlendMode(BlendMode::Alpha);
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
