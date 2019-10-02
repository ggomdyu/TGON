/**
 * @file    Graphics.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include "Platform/Config.h"
#include "Math/Rect.h"
#include "Math/Color.h"

#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
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

enum class GraphicsSDK
{
    OpenGL2_1 = 0,
    OpenGL3_0,
    OpenGL4_0,
    OpenGL4_6,
    OpenGLES,
    Direct3D9,
    Direct3D11,
    Direct3D12,
    Metal,
    Vulkan,
};

struct VideoMode final
{
    Color4f clearColor = Color4f(0.0f, 0.44313f, 0.75686f, 1.0f);
    bool enableHardwareAccelerate = true;
    bool enableTripleBuffer = false;
    bool enableVerticalSync = false;
    bool enableMultiSampling = false;
    uint16_t sampleCount = 16;
    uint16_t colorBits = 32;
    uint16_t depthBits;
    uint16_t stencilBits;
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

class TGON_API Graphics final :
    private PlatformGraphics
{
/**@section Constructor */
public:
    using PlatformGraphics::PlatformGraphics;
    
/**@section Method */
public:
    PlatformGraphics* GetPlatformDependency() noexcept;
    const PlatformGraphics* GetPlatformDependency() const noexcept;
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
};

} /* namespace tgon */
