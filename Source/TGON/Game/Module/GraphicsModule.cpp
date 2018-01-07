#include "PrecompiledHeader.pch"

#include "GraphicsModule.h"

#include "Core/Math/Color.h"
#include "Graphics/RHI/RHIType.h"
#include "Graphics/RHI/OpenGL/OpenGLDynamicRHI.h"

namespace tgon
{
namespace game
{

GraphicsModule::GraphicsModule(const std::shared_ptr<core::Window>& window, const graphics::VideoMode& videoMode) :
    m_rhi(MakeRHI(window, videoMode))
{
    m_rhi->SetClearColor({1.0f, 0.0f, 0.0f, 1.0f});
}

GraphicsModule::~GraphicsModule() = default;

void GraphicsModule::Update()
{
}

const std::unique_ptr<graphics::IDynamicRHI>& GraphicsModule::GetRHI() const
{
    return m_rhi;
}

std::unique_ptr<graphics::IDynamicRHI> GraphicsModule::MakeRHI(const std::shared_ptr<core::Window>& window, const graphics::VideoMode& videoMode) const
{
    switch (videoMode.graphicsSDK)
    {
    case graphics::GraphicsSDK::OpenGL2_1:
    case graphics::GraphicsSDK::OpenGL3_0:
    case graphics::GraphicsSDK::OpenGL4_0:
    case graphics::GraphicsSDK::OpenGL4_6:
        return std::make_unique<graphics::OpenGLDynamicRHI>(window, videoMode);

    default:
        return nullptr;
    }
}

} /* namespace game */
} /* namespace tgon */
