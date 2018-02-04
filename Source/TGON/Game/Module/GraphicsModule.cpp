#include "PrecompiledHeader.pch"

#include "GraphicsModule.h"

#include "Core/Math/Color.h"
#include "Graphics/RHI/GraphicsType.h"
#if BOOST_OS_WINDOWS
#   include "Graphics/RHI/Direct3D11/D3D11DynamicGraphics.h"
#else
#endif
#include "Graphics/RHI/OpenGL/OpenGLDynamicGraphics.h"

namespace tgon
{
namespace game
{

GraphicsModule::GraphicsModule(const std::shared_ptr<core::Window>& window, const graphics::VideoMode& videoMode) :
    m_graphics(MakeGraphics(window, videoMode))
{
}

GraphicsModule::~GraphicsModule() = default;

void GraphicsModule::Update()
{
}

const std::unique_ptr<graphics::IDynamicGraphics>& GraphicsModule::GetGraphics() const
{
    return m_graphics;
}

std::unique_ptr<graphics::IDynamicGraphics> GraphicsModule::MakeGraphics(const std::shared_ptr<core::Window>& window, const graphics::VideoMode& videoMode) const
{
    switch (videoMode.graphicsSDK)
    {
    case graphics::GraphicsSDK::Direct3D11:
        return std::make_unique<graphics::D3D11DynamicGraphics>(window, videoMode);

    case graphics::GraphicsSDK::OpenGL2_1:
    case graphics::GraphicsSDK::OpenGL3_0:
    case graphics::GraphicsSDK::OpenGL4_0:
    case graphics::GraphicsSDK::OpenGL4_6:
        return std::make_unique<graphics::OpenGLDynamicGraphics>(window, videoMode);

    default:
        return nullptr;
    }
}

} /* namespace game */
} /* namespace tgon */
