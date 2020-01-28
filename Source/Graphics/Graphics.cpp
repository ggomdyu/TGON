#include "PrecompiledHeader.h"

#include "Platform/Window.h"

#include "Graphics.h"

namespace tgon
{

Graphics::Graphics(const std::shared_ptr<Window>& displayWindow, const VideoMode& videoMode) :
    PlatformGraphics(displayWindow, videoMode),
    m_displayWindow(displayWindow)
{
    this->EnableCullFace();

    auto clientSize = displayWindow->GetClientSize();
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

std::shared_ptr<Window> Graphics::GetDisplayWindow() noexcept
{
    return m_displayWindow;
}

std::shared_ptr<const Window> Graphics::GetDisplayWindow() const noexcept
{
    return m_displayWindow;
}

} /* namespace tgon */
