#include "PrecompiledHeader.pch"
#include "RHIUtility.h"

#include "OpenGL/OpenGLRHI.h"

namespace tgon
{
namespace rhi
{

std::unique_ptr<rhi::BaseRHI> MakeRHI(const rhi::VideoMode& videoMode)
{
    switch (videoMode.graphicsSDK)
    {
        case rhi::GraphicsSDK::OpenGL:
            return std::make_unique<rhi::gl::OpenGLRHI>(videoMode);

        case rhi::GraphicsSDK::Metal:
            return nullptr;

        case rhi::GraphicsSDK::Direct3D9:
            return nullptr;
    }
    return nullptr;
}

} /* namespace rhi */
} /* namespace tgon */
