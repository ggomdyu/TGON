#include "PrecompiledHeader.h"

#include "GraphicsSystem.h"

#include "Core/Math/Color.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphicsType.h"
#if TGON_PLATFORM_WINDOWS
//#   include "Graphics/LowLevelRender/Direct3D11/D3D11Graphics.h"
#else
#endif
#include "Graphics/LowLevelRender/OpenGL/OpenGLGraphics.h"
#include "GraphicsSystem.h"

namespace tgon
{

GraphicsSystem::GraphicsSystem(const VideoMode& videoMode, const std::shared_ptr<GenericWindow>& window) :
    m_graphics(videoMode, window)
{
}

GraphicsSystem::~GraphicsSystem() = default;

void GraphicsSystem::Update()
{
}

Graphics& GraphicsSystem::GetGraphics()
{
    return m_graphics;
}

const Graphics& GraphicsSystem::GetGraphics() const
{
    return m_graphics;
}

} /* namespace tgon */