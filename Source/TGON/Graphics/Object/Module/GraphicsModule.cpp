#include "PrecompiledHeader.h"

#include "Core/Math/Color.h"

#include "GraphicsModule.h"

namespace tgon
{

GraphicsModule::GraphicsModule(const VideoMode& videoMode, Window& displayTargetWindow) :
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
