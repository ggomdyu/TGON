#include "PrecompiledHeader.pch"

#include "GraphicsModule.h"

#include "Core/Math/Color.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphicsType.h"
#if TGON_PLATFORM_WINDOWS
//#   include "Graphics/LowLevelRender/Direct3D11/D3D11Graphics.h"
#else
#endif
#include "Graphics/LowLevelRender/OpenGL/OpenGLGraphics.h"

namespace tgon
{

GraphicsModule::GraphicsModule(const VideoMode& videoMode, const std::shared_ptr<GenericWindow>& window) :
    m_graphics(MakeGraphics(videoMode, window))
{
}

GraphicsModule::~GraphicsModule() = default;

void GraphicsModule::Update()
{
}

const std::shared_ptr<GenericGraphics>& GraphicsModule::GetGraphics() const
{
    return m_graphics;
}

std::shared_ptr<GenericGraphics> GraphicsModule::MakeGraphics(const VideoMode& videoMode, const std::shared_ptr<GenericWindow>& window) const
{
    switch (videoMode.graphicsSDK)
    {
    case GraphicsSDK::Direct3D11:
        //return std::make_shared<D3D11Graphics>(videoMode, window);

    case GraphicsSDK::OpenGL2_1:
    case GraphicsSDK::OpenGL3_0:
    case GraphicsSDK::OpenGL4_0:
    case GraphicsSDK::OpenGL4_6:
        return std::make_shared<OpenGLGraphics>(videoMode, window);

    default:
        return nullptr;
    }
}

} /* namespace tgon */