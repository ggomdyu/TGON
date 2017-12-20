/**
 * @filename    BaseRHIType.h
 * @author      ggomdyu
 * @since       10/22/2017
 * @brief
 */

#pragma once
#include <cstdint>

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
    CW = 0,
    CCW,
};

enum class ImageFormat
{
    BMP,
    JPG,
    PNG,
    TIFF,
    GIF,
    WEBP,
};

enum class PixelFormat
{
    R8G8B8A8_UNORM = 0,
    R8G8B8A8_UNORM_SRGB,
    R8G8B8A8_UINT,
    R8G8B8_UNORM,
    R8G8B8_UINT,
    PVRTC2,
    PVRTC4,
};

struct VideoMode final
{
/* @section Public variable */
public:
    GraphicsSDK graphicsSDK = GraphicsSDK::OpenGL;

    /* @brief   If false, the application will perform software rendering. */
    bool enableHardwareAccelerate = true;
    bool enableDoubleBuffer = true;
    bool enableTripleBuffer = false;
    bool enableVerticalSync = false;

    bool enableMultiSampling = false;
    uint16_t sampleCount = 16;

    uint16_t colorBits = 32;
    uint16_t depthBits;
    uint16_t stencilBits;
};

} /* namespace rhi */
} /* namespace tgon */