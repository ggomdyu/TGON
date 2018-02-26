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
    Linear,
};

enum class TextureAddressMode
{
    Wrap,
    Border,
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
    virtual void Use() = 0;
    virtual void Unuse() = 0;
    virtual void SetFilterMode(TextureFilterMode filterMode) = 0;
    virtual void SetAddressMode(TextureAddressMode addressMode) = 0;
    TextureFilterMode GetFilterMode() const noexcept;
    TextureAddressMode GetAddressMode() const noexcept;
    
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

/* @section Protected variable */
protected:
    TextureFilterMode m_filterMode;
    TextureAddressMode m_addressMode;
};

inline GenericTexture::~GenericTexture() = default;

} /* namespace graphics */
} /* namespace tgon */
