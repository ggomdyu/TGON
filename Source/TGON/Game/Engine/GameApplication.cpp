#include "PrecompiledHeader.h"

#include "GameApplication.h"

#include "Core/Platform/Window.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphics.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphicsType.h"

namespace tgon
{

GameApplication::GameApplication(const WindowStyle& windowStyle, const VideoMode& videoMode) :
    Application(windowStyle),
    m_graphicsModule(videoMode, GetRootWindow())
{
    if (m_rootWindow != nullptr)
    {
        m_rootWindow->OnWindowResize = [&](int32_t width, int32_t height)
        {
            m_graphicsModule.GetGraphics().SetViewport(0, 0, width, height);
        };
    }
}

void GameApplication::OnUpdate()
{
    m_timeModule.Update();
    m_graphicsModule.Update();
}

TimeModule& GameApplication::GetTimeModule() noexcept
{
    return m_timeModule;
}

const TimeModule& GameApplication::GetTimeModule() const noexcept
{
    return m_timeModule;
}

GraphicsModule& GameApplication::GetGraphicsModule() noexcept
{
    return m_graphicsModule;
}

const GraphicsModule& GameApplication::GetGraphicsModule() const noexcept
{
    return m_graphicsModule;
}

} /* namespace tgon */
