#include "PrecompiledHeader.h"

#include "GameApplication.h"

#include "Core/Platform/Window.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphics.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphicsType.h"

namespace tgon
{

GameApplication::GameApplication(const WindowStyle& windowStyle, const VideoMode& videoMode) :
    Application(windowStyle),
    m_graphicsSystem(videoMode, GetRootWindow())
{
    if (m_rootWindow != nullptr)
    {
        m_rootWindow->OnWindowResize = [&](int32_t width, int32_t height)
        {
            m_graphicsSystem.GetGraphics().SetViewport(0, 0, width, height);
        };
    }
}

void GameApplication::OnUpdate()
{
    m_timeSystem.Update();
    m_graphicsSystem.Update();
}

TimeSystem& GameApplication::GetTimeSystem() noexcept
{
    return m_timeSystem;
}

const TimeSystem& GameApplication::GetTimeSystem() const noexcept
{
    return m_timeSystem;
}

const InputSystem& GameApplication::GetInputSystem() const
{
    return m_inputSystem;
}

GraphicsSystem& GameApplication::GetGraphicsSystem() noexcept
{
    return m_graphicsSystem;
}

const GraphicsSystem& GameApplication::GetGraphicsSystem() const noexcept
{
    return m_graphicsSystem;
}

} /* namespace tgon */