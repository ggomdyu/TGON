#include "PrecompiledHeader.h"

#include "Core/Math/Color.h"

#include "GraphicsModule.h"

namespace tgon
{

GraphicsModule::GraphicsModule(const VideoMode& videoMode, Window& displayTargetWindow) :
    m_graphics(videoMode, displayTargetWindow),
    m_graphicsContext(m_graphics)
{
}

GraphicsModule::~GraphicsModule() = default;

void GraphicsModule::Update()
{
    this->Draw(m_graphicsContext);
}

void GraphicsModule::Draw(GraphicsContext& graphicsContext)
{
    m_graphics.ClearColorDepthBuffer();
    {
        m_spriteBatch.FlushBatch(graphicsContext);
    }
    m_graphics.SwapBuffer();
}

SpriteBatch& GraphicsModule::GetSpriteBatch() noexcept
{
    return m_spriteBatch;
}
    
const SpriteBatch& GraphicsModule::GetSpriteBatch() const noexcept
{
    return m_spriteBatch;
}

Graphics& GraphicsModule::GetGraphics() noexcept
{
    return m_graphics;
}

const Graphics& GraphicsModule::GetGraphics() const noexcept
{
    return m_graphics;
}

} /* namespace tgon */
