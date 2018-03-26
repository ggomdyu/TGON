/**
 * @filename    GenericTexture.h
 * @author      ggomdyu
 * @since       02/20/2018
 * @brief
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Drawing/Bitmap.h"

#include "GenericTextureType.h"

namespace tgon
{

class GenericTexture :
    private Bitmap,
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
    using Bitmap::operator=;
    using Bitmap::operator[];

/* @section Public method */
public:
    virtual void TransferToVideo() = 0;
    virtual void UpdateParemeters() = 0;

    virtual void SetFilterMode(TextureFilterMode filterMode) = 0;
    virtual void SetWrapMode(TextureWrapMode addressMode) = 0;
    virtual TextureFilterMode GetFilterMode() const noexcept = 0;
    virtual TextureWrapMode GetWrapMode() const noexcept = 0;
    virtual bool IsUseMipmap() const noexcept;
    
    using Bitmap::Save;
    using Bitmap::IsValid;
    using Bitmap::GetBits;
    using Bitmap::GetWidth;
    using Bitmap::GetHeight;
    using Bitmap::GetChannels;
    using Bitmap::GetColorDepth;
    using Bitmap::GetBitsPerPixel;
    using Bitmap::GetPixelFormat;
    using Bitmap::GetFilePath;

/* Protected variable */
protected:
    bool m_isUseMipmap;
};

inline GenericTexture::~GenericTexture() = default;

} /* namespace tgon */