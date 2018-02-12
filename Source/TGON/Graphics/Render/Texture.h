/**
 * @filename    Texture.h
 * @author      ggomdyu
 * @since       12/09/2017
 */

#pragma once
#include "Core/Drawing/Bitmap.h"

namespace tgon
{
namespace graphics
{

enum class TextureAddressMode
{
    Wrap,
    Border,
    Clamp,
    Mirror,
};

class Texture2D :
    private core::Bitmap
{
/* @section Public constructor */
public:
    using core::Bitmap::Bitmap;

/* @section Public operator */
public:
    using core::Bitmap::operator=;
    using core::Bitmap::operator[];

/* @section Public method */
public:
    using core::Bitmap::Save;

    /* @brief   Checks the image file was loaded successfully. */
    using core::Bitmap::IsValid;

    /* @brief   Get the raw pointer of image. */
    using core::Bitmap::GetBits;

    /* @brief   Get the width of image. */
    using core::Bitmap::GetWidth;

    /* @brief   Get the height of image. */
    using core::Bitmap::GetHeight;

    using core::Bitmap::GetColorDepth;

    using core::Bitmap::GetBitsPerPixel;
    
    /* @brief   Get the pixel format of image. */
    using core::Bitmap::GetPixelFormat;

    /* @brief   Get the file path saved at loading time. */
    using core::Bitmap::GetFilePath;
};

} /* namespace graphics */
} /* namespace tgon */