/**
 * @file    Graphics.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include "Math/Rect.h"
#include "Math/Color.h"

#if TGON_GRAPHICS_OPENGL
#   include "OpenGL/OpenGLGraphics.h"
#endif

namespace tgon
{

enum class PrimitiveType
{
    Points,
    Lines,
    LineStrip,
    Triangles,
    TriangleStrip,
    TriangleFan,
};

enum class FillMode
{
    Point,
    WireFrame,
    Solid,
};

enum class CullMode
{
    CW,
    CCW,
};

enum class BlendMode
{
    Normal,
    Alpha,
    Additive,
    Subtractive,
    Darken,
    Multiply,
    Divide,
    Subtract,
    SoftLight,
    HardLight,
};

class Window;

class Graphics final :
    private PlatformGraphics
{
/**@section Constructor */
public:
    Graphics(const std::shared_ptr<Window>& displayWindow, const VideoMode& videoMode);

/**@section Method */
public:
    PlatformGraphics& GetPlatformDependency() noexcept;
    const PlatformGraphics& GetPlatformDependency() const noexcept;
    void SetScissorRect(const FRect& scissorRect);
    void SetClearColor(const Color4f& color);
    void SetFillMode(FillMode fillMode);
    void SetCullMode(CullMode cullMode);
    void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);
    void SetBlendMode(BlendMode blendMode);
    void EnableCullFace();
    void EnableBlend();
    void EnableDepthTest();
    void EnableScissorTest();
    void DisableCullFace();
    void DisableBlend();
    void DisableDepthTest();
    void DisableScissorTest();
    void ClearColorBuffer();
    void ClearColorDepthBuffer();
    void SwapBuffer();
    void DrawPrimitives(PrimitiveType primitiveType, int32_t vertexStartOffset, int32_t vertexCount);
    void DrawIndexedPrimitives(PrimitiveType primitiveType, int32_t indexCount);
    std::shared_ptr<Window> GetDisplayWindow() noexcept;
    std::shared_ptr<const Window> GetDisplayWindow() const noexcept;

/**@section Variable */
private:
    std::shared_ptr<Window> m_displayWindow;
};

} /* namespace tgon */
