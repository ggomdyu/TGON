#include "PrecompiledHeader.pch"
#include "GameApplication.h"

#include "Graphics/RHI/Base/BaseRHI.h"
#include "Graphics/RHI/Base/BaseRHIType.h"
#include "Graphics/RHI/RHIUtility.h"

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
    m_rhi(rhi::MakeRHI(videoMode))
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
