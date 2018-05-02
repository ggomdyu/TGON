/**
 * @filename    ImageType.h
 * @author      ggomdyu
 * @since       04/10/2018
 */

#pragma once

namespace tgon
{

enum class ImageFormat
{
    Unknown = 0,
    Bmp,
    Jpg,
    Jpeg = Jpg,
    Png,
    Tiff,
    Gif,
    WebP,
};

enum class PixelFormat
{
    Unknown = 0,
    R8G8B8A8_Unorm, // A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits per channel including alpha.
    R8G8B8A8_Unorm_Srgb, // A four-component, 32-bit unsigned-normalized integer sRGB format that supports 8 bits per channel including alpha.
    R32G32B32A32_Float, // A four-component, 128-bit floating-point format that supports 32 bits per channel including alpha.
    R32G32B32A32_Uint, // A four-component, 128-bit unsigned-integer format that supports 32 bits per channel including alpha.
    Pvrtc2,
    Pvrtc4,
};

} /* namespace tgon */  