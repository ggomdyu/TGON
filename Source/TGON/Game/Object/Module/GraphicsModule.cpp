#include "PrecompiledHeader.h"

#include "GraphicsModule.h"

#include "Core/Math/Color.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphicsType.h"
#if TGON_PLATFORM_WINDOWS
//#   include "Graphics/LowLevelRender/Direct3D11/D3D11Graphics.h"
#else
#endif
#include "Graphics/LowLevelRender/OpenGL/OpenGLGraphics.h"
#include "GraphicsModule.h"

namespace tgon
{

GraphicsModule::GraphicsModule(const VideoMode& videoMode, const std::shared_ptr<GenericWindow>& window) :
    m_graphics(videoMode, window)
{
}

GraphicsModule::~GraphicsModule() = default;

void GraphicsModule::Update()
{
}

Graphics& GraphicsModule::GetGraphics()
{
    return m_graphics;
}

const Graphics& GraphicsModule::GetGraphics() const
{
    return m_graphics;
}

} /* namespace tgon */