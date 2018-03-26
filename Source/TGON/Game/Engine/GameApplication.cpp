#include "PrecompiledHeader.pch"

#include "GameApplication.h"

#include "Core/Platform/Window.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphics.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphicsType.h"
#include "Game/Module/TimeModule.h"
#include "Game/Module/GraphicsModule.h"

namespace tgon
{

GameApplication::GameApplication(const WindowStyle& windowStyle) :
    Application(windowStyle),
    m_timeModule(std::make_shared<TimeModule>())
{
}

GameApplication::GameApplication(const WindowStyle& windowStyle, const VideoMode& videoMode) :
    Application(windowStyle),
    m_timeModule(std::make_shared<TimeModule>()),
    m_graphicsModule(std::make_shared<GraphicsModule>(videoMode, GetRootWindow()))
{
    if (m_rootWindow != nullptr)
    {
        m_rootWindow->OnWindowResize = [&](int32_t width, int32_t height)
        {
            decltype(auto) graphics = m_graphicsModule->GetGraphics();
            graphics->SetViewport(0, 0, width, height);
        };
    }
}

void GameApplication::OnUpdate()
{
    m_timeModule->Update();

    for (auto& module : m_modulesToIterate)
    {
        module->Update();
    }
}

} /* namespace tgon */