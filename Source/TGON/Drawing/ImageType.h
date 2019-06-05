/**
 * @file    ImageType.h
 * @author  ggomdyu
 * @since   04/10/2018
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
    RGBA8888,
    RGB888,
    RGBA4444,
    //AST
    //ETC
    //ETC2
    //PVRTC2
    //PVRTC4
};

} /* namespace tgon */  
