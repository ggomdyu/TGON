#include "PrecompiledHeader.pch"
#include "RHIUtility.h"
#include "Base/BaseRHIType.h"

#include <boost/predef/os.h>

#include "OpenGL/OpenGLRHI.h"
//#include "OpenGL3_0/OpenGL3_0RHI.h"
//#include "Vulkan/VulkanRHI.h"
//#include "Direct3D9/Direct3D9RHI.h"
//#include "Direct3D11/Direct3D11RHI.h"
//#include "Direct3D12/Direct3D12RHI.h"

namespace tgon
{
namespace rhi
{

std::unique_ptr<BaseRHI> MakeRHI(const std::shared_ptr<platform::Window>& window, const VideoMode& videoMode)
{
    switch (videoMode.graphicsSDK)
    {
    case GraphicsSDK::OpenGL:
        return std::make_unique<OpenGLRHI>(window, videoMode);

#if BOOST_OS_MACOS
    case GraphicsSDK::Metal:
        return nullptr;
#endif

#if BOOST_OS_WINDOWS
    /*case GraphicsSDK::Direct3D9:
        return std::make_unique<Direct3D9RHI>(window, videoMode);

    case GraphicsSDK::Direct3D11:
        return std::make_unique<Direct3D11RHI>(window, videoMode);*/
#endif

    default:
        return nullptr;
    }
}

} /* namespace rhi */
} /* namespace tgon */
