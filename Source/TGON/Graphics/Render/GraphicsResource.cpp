#include "PrecompiledHeader.h"

#include "GraphicsResource.h"

namespace tgon
{

GraphicsResource::GraphicsResource(const GraphicsContext& graphicsContext) :
    m_graphicsContext(graphicsContext)
{
}

GraphicsResource::~GraphicsResource() = default;

GraphicsContext& GraphicsResource::GetGraphicsContext() noexcept
{
    return m_graphicsContext;
}

GraphicsContext::GraphicsContext(Graphics& graphics) noexcept :
    m_graphics(graphics)
{
}

Graphics& GraphicsContext::GetGraphics() noexcept
{
    return m_graphics;
}

} /* namespace tgon */