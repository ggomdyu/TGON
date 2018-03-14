/**
 * @filename    GenericTexture.h
 * @author      ggomdyu
 * @since       02/20/2018
 * @brief
 */

#pragma once
#include "Core/Drawing/Bitmap.h"

#include <boost/noncopyable.hpp>

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

struct TextureCreateDesc
{
    TextureFilterMode filterMode = TextureFilterMode::Bilinear;
    TextureWrapMode wrapMode = TextureWrapMode::Repeat;
    bool isUseMipmap = true;
};

class GenericTexture :
    private core::Bitmap,
    private boost::noncopyable
{
/* @section Public constructor */
public:
    GenericTexture(const std::string& imagePath, const TextureCreateDesc& textureCreateDesc);

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
    virtual bool IsUseMipmap() const noexcept;
    
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

/* Protected variable */
protected:
    bool m_isUseMipmap;
};

inline GenericTexture::~GenericTexture() = default;

} /* namespace graphics */
} /* namespace tgon */
