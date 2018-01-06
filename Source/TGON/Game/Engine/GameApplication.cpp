#include "PrecompiledHeader.pch"

#include "GameApplication.h"

#include "Graphics/RHI/RHIType.h"
#include "Game/Module/TimeModule.h"

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

//const std::unique_ptr<render::Renderer>& GameApplication::GetRenderer() const
//{
//    return m_renderer;
//}

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
