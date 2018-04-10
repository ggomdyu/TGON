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
    BMP,
    JPG,
    JPEG = JPG,
    PNG,
    TIFF,
    GIF,
    WEBP,
};

enum class PixelFormat
{
    Unknown = 0,
    R8G8B8A8_UNORM,
    R8G8B8_UNORM,
    PVRTC2,
    PVRTC4,
};

} /* namespace tgon */  