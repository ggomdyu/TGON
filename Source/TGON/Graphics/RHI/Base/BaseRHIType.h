/**
 * @filename    BaseRHIType.h
 * @author      ggomdyu
 * @since       10/22/2017
 * @brief
 */

#pragma once

namespace tgon
{
namespace rhi
{

enum class GraphicsSDK
{
    OpenGL = 0,
    OpenGL3_0,
    OpenGL4_6,
    OpenGLES,
    Direct3D9,
    Direct3D10,
    Direct3D11,
    Direct3D12,
    Metal,
    Vulkan,
};

enum class PrimitiveType
{
    PointList = 0,
    LineList,
    LineStrip,
    TriangleList,
    TriangleStrip,
    TriangleFan,
};

enum class FillMode
{
    Point = 0,
    WireFrame,
    Solid,
};

enum class CullMode
{
    None = 0,
    CW,
    CCW,
};

enum class TextureFormat
{
    R8G8B8A8_UNORM = 0,
};

struct VideoMode final
{
/* @section Public variable */
public:
    GraphicsSDK graphicsSDK = GraphicsSDK::OpenGL;

    /* @brief   If false, the application will perform software rendering. */
    bool enableHardwareAccelerate = true;
    bool enableDoubleBuffer = true;
    bool enableMultiSampling = true;
    
    uint16_t sampleCount = 16;
    uint16_t colorBits = 32;
    uint16_t depthBits;
    uint16_t stencilBits;

    uint16_t viewWidth = 600;
    uint16_t viewHeight = 600;
};

} /* namespace rhi */
} /* namespace tgon */
