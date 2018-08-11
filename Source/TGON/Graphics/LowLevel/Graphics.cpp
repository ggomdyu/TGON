#include "PrecompiledHeader.h"

#include "Graphics.h"

namespace tgon
{

Graphics::Graphics(const Window& displayTarget, const VideoMode& videoMode) :
    m_graphicsImpl(displayTarget, videoMode)
{
}

void Graphics::SetClearColor(const Color4f& color)
{
    m_graphicsImpl.SetClearColor(color);
}

void Graphics::SetFillMode(FillMode fillMode)
{
    m_graphicsImpl.SetFillMode(fillMode);
}

void Graphics::SetCullMode(CullMode cullMode)
{
    m_graphicsImpl.SetCullMode(cullMode);
}

void Graphics::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
    m_graphicsImpl.SetViewport(x, y, width, height);
}
    
void Graphics::SetBlendMode(BlendMode blendMode)
{
    m_graphicsImpl.SetBlendMode(blendMode);
}

void Graphics::EnableBlend()
{
    m_graphicsImpl.EnableBlend();
}

void Graphics::EnableDepthTest()
{
    m_graphicsImpl.EnableDepthTest();
}

void Graphics::DisableBlend()
{
    m_graphicsImpl.DisableBlend();
}

void Graphics::DisableDepthTest()
{
    m_graphicsImpl.DisableDepthTest();
}

void Graphics::ClearColorBuffer()
{
    m_graphicsImpl.ClearColorBuffer();
}

void Graphics::ClearColorDepthBuffer()
{
    m_graphicsImpl.ClearColorDepthBuffer();
}

void Graphics::SwapBuffer()
{
    m_graphicsImpl.SwapBuffer();
}

void Graphics::DrawPrimitives(PrimitiveType primitiveType, int32_t primitiveCount)
{
    m_graphicsImpl.DrawPrimitives(primitiveType, primitiveCount);
}

void Graphics::DrawIndexedPrimitives(PrimitiveType primitiveType, int32_t primitiveCount)
{
    m_graphicsImpl.DrawIndexedPrimitives(primitiveType, primitiveCount);
}

} /* namespace tgon */
