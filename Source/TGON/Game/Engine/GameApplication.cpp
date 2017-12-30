#include "PrecompiledHeader.pch"

#include "Graphics/RHI/RHI.h"
#include "Graphics/RHI/RHIType.h"

#include "GameApplication.h"

namespace tgon
{
namespace engine
{

GameApplication::GameApplication(const platform::WindowStyle& windowStyle) :
    platform::Application(windowStyle)
{
}

GameApplication::GameApplication(const platform::WindowStyle& windowStyle, const rhi::VideoMode& videoMode) :
    platform::Application(windowStyle),
    m_rhi(rhi::MakeRHI(this->GetMainWindow(), videoMode))
{
}

void GameApplication::Update()
{
//    for (auto& module : m_modules)
//    {
//        module->Update();
//    }
}

} /* namespace engine */
} /* namespace tgon */
