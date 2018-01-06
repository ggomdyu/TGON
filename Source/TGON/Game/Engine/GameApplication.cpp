#include "PrecompiledHeader.pch"

#include "GameApplication.h"

#include "Graphics/RHI/RHIType.h"
#include "Game/Module/TimeModule.h"
#include "Game/Module/GraphicsModule.h"

namespace tgon
{
namespace game
{

GameApplication::GameApplication(const core::WindowStyle& windowStyle) :
    core::Application(windowStyle),
    m_timeModule(std::make_shared<TimeModule>())
{
}

GameApplication::GameApplication(const core::WindowStyle& windowStyle, const graphics::VideoMode& videoMode) :
    core::Application(windowStyle),
    m_timeModule(std::make_shared<TimeModule>()),
    m_graphicsModule(std::make_shared<GraphicsModule>(GetMainWindow(), videoMode))
{
}

void GameApplication::OnUpdate()
{
    m_timeModule->Update();

    for (auto& module : m_modulesToIterate)
    {
        module->Update();
    }
}

} /* namespace game */
} /* namespace tgon */