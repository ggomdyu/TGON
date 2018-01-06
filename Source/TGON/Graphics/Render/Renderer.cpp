#include "PrecompiledHeader.pch"

#include "Core/Platform/Window.h"
#include "Graphics/RHI/RHIType.h"
#include "Graphics/RHI/OpenGL/Dynamic/OpenGLDynamicRHI.h"

#include "Renderer.h"


//#include <boost/predef/os.h>
//
//#include "OpenGL/Dynamic/DynamicOpenGLRHI.h"
//
//#include "RHI.h"
//#include "RHIType.h"
//#include "OpenGL3_0/OpenGL3_0RHI.h"
//#include "Vulkan/VulkanRHI.h"
//#include "Direct3D9/Direct3D9RHI.h"
//#include "Direct3D11/Direct3D11RHI.h"
//#include "Direct3D12/Direct3D12RHI.h"


namespace tgon
{
namespace render
{

Renderer::Renderer(const std::shared_ptr<platform::Window>& window, const rhi::VideoMode& videoMode) :
    m_rhi(MakeRHI(window, videoMode))
{
}

const std::unique_ptr<rhi::IDynamicRHI>& Renderer::GetRHI() const noexcept
{
    return m_rhi;
}

std::unique_ptr<rhi::IDynamicRHI> Renderer::MakeRHI(const std::shared_ptr<platform::Window>& window, const rhi::VideoMode & videoMode)
{
    switch (videoMode.graphicsSDK)
    {
#if BOOST_OS_WINDOWS || BOOST_OS_MACOS || BOOST_OS_IOS || BOOST_OS_ANDROID
    case rhi::GraphicsSDK::OpenGL:
        return std::make_unique<rhi::OpenGLDynamicRHI>(window, videoMode);
#endif

#if BOOST_OS_MACOS || BOOST_OS_IOS
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

} /* namespace render */
} /* namespace tgon */