#include "PrecompiledHeader.pch"

#include "GraphicsModule.h"

#include "Core/Math/Color.h"
#include "Graphics/Abstract/Generic/GenericGraphicsType.h"
#if TGON_PLATFORM_WINDOWS
//#   include "Graphics/Abstract/Direct3D11/D3D11Graphics.h"
#else
#endif
#include "Graphics/Abstract/OpenGL/OpenGLGraphics.h"

namespace tgon
{
namespace game
{

GraphicsModule::GraphicsModule(const graphics::VideoMode& videoMode, const std::shared_ptr<core::GenericWindow>& window) :
    m_graphics(MakeGraphics(videoMode, window))
{
}

GraphicsModule::~GraphicsModule() = default;

void GraphicsModule::Update()
{
}

const std::unique_ptr<graphics::GenericGraphics>& GraphicsModule::GetGraphics() const
{
    return m_graphics;
}

std::unique_ptr<graphics::GenericGraphics> GraphicsModule::MakeGraphics(const graphics::VideoMode& videoMode, const std::shared_ptr<core::GenericWindow>& window) const
{
    switch (videoMode.graphicsSDK)
    {
    case graphics::GraphicsSDK::Direct3D11:
        //return std::make_unique<graphics::D3D11Graphics>(videoMode, window);

    case graphics::GraphicsSDK::OpenGL2_1:
    case graphics::GraphicsSDK::OpenGL3_0:
    case graphics::GraphicsSDK::OpenGL4_0:
    case graphics::GraphicsSDK::OpenGL4_6:
        return std::make_unique<graphics::OpenGLGraphics>(videoMode, window);

    default:
        return nullptr;
    }
}

} /* namespace game */
} /* namespace tgon */
