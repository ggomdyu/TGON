/**
 * @file    GraphicsType.h
 * @author  ggomdyu
 * @since   06/30/2018
 */

#pragma once
#include "Platform/Config.h"
#include "Math/Color.h"

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
/**@section Variable */
public:
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

} /* namespace tgon */
