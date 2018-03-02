/**
 * @filename    GenericTexture.h
 * @author      ggomdyu
 * @since       02/20/2018
 * @brief
 */

#pragma once
#include "Core/Drawing/Bitmap.h"

namespace tgon
{
namespace graphics
{

enum class TextureFilterMode
{
    Point = 0,
    Bilinear,
};

enum class TextureWrapMode
{
    Repeat,
    Clamp,
    Mirror,
};

class GenericTexture :
    private core::Bitmap
{
/* @section Public constructor */
public:
    using core::Bitmap::Bitmap;

/* @section Public destructor */
public:
    virtual ~GenericTexture() = 0;

/* @section Public operator */
public:
    using core::Bitmap::operator=;
    using core::Bitmap::operator[];

/* @section Public method */
public:
    virtual void TransferToVideo() = 0;
    virtual void UpdateParemeters() = 0;

    virtual void SetFilterMode(TextureFilterMode filterMode) = 0;
    virtual void SetWrapMode(TextureWrapMode addressMode) = 0;
    virtual TextureFilterMode GetFilterMode() const noexcept = 0;
    virtual TextureWrapMode GetWrapMode() const noexcept = 0;
    
    using core::Bitmap::Save;
    using core::Bitmap::IsValid;
    using core::Bitmap::GetBits;
    using core::Bitmap::GetWidth;
    using core::Bitmap::GetHeight;
    using core::Bitmap::GetChannels;
    using core::Bitmap::GetColorDepth;
    using core::Bitmap::GetBitsPerPixel;
    using core::Bitmap::GetPixelFormat;
    using core::Bitmap::GetFilePath;
};

inline GenericTexture::~GenericTexture() = default;

} /* namespace graphics */
} /* namespace tgon */
