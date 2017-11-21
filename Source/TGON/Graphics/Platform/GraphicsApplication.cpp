#include "PrecompiledHeader.pch"
#include "GraphicsApplication.h"

#include "Graphics/RHI/Base/BaseRHIType.h"
#include "Graphics/RHI/OpenGL/OpenGLRHI.h"

namespace tgon
{
namespace platform
{

GraphicsApplication::GraphicsApplication(const WindowStyle& windowStyle, const rhi::VideoMode& videoMode) :
    Application(windowStyle),
    m_rhi(MakeRHI(videoMode))
{
}

void GraphicsApplication::OnDraw()
{
}

std::shared_ptr<rhi::BaseRHI> GraphicsApplication::MakeRHI(const rhi::VideoMode& videoMode) const
{
    switch (videoMode.graphicsSDK)
    {
    case rhi::GraphicsSDK::OpenGL:
        return std::make_shared<rhi::gl::OpenGLRHI>(videoMode);

    case rhi::GraphicsSDK::Metal:
        return nullptr;

    case rhi::GraphicsSDK::Direct3D9:
        return nullptr;
    }
    return nullptr;
}

} /* namespace platform */
} /* namespace tgon */
