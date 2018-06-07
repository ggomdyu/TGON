#include "PrecompiledHeader.h"

#include "Core/Math/Color.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphicsType.h"
#if TGON_PLATFORM_WINDOWS
//#   include "Graphics/LowLevelRender/Direct3D11/D3D11Graphics.h"
#   include "Graphics/LowLevelRender/OpenGL/OpenGLGraphics.h"
#else
#   include "Graphics/LowLevelRender/OpenGL/OpenGLGraphics.h"
#endif

#include "GraphicsModule.h"

namespace tgon
{

GraphicsModule::GraphicsModule(const VideoMode& videoMode, const std::shared_ptr<GenericWindow>& displayTargetWindow) :
    m_graphics(videoMode, displayTargetWindow)
{
}

GraphicsModule::~GraphicsModule() = default;

void GraphicsModule::Update()
{
    this->Draw();
}

void GraphicsModule::Draw()
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
