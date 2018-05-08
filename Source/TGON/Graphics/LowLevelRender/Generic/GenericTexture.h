/**
 * @filename    GenericTexture.h
 * @author      ggomdyu
 * @since       02/20/2018
 * @brief
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Drawing/Image.h"

#include "GenericTextureType.h"

namespace tgon
{

class GenericTexture :
    private Image,
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
    using Image::operator=;
    using Image::operator[];

/* @section Public method */
public:
    virtual void Use() = 0;
    virtual void SetFilterMode(TextureFilterMode filterMode) = 0;
    virtual void SetWrapMode(TextureWrapMode addressMode) = 0;
    virtual TextureFilterMode GetFilterMode() const noexcept = 0;
    virtual TextureWrapMode GetWrapMode() const noexcept = 0;
    virtual bool IsUseMipmap() const noexcept;
    
    using Image::IsValid;
    using Image::GetImageData;
    using Image::GetWidth;
    using Image::GetHeight;
    using Image::GetChannels;
    using Image::GetColorDepth;
    using Image::GetPixelFormat;
    using Image::GetFilePath;

/* Protected variable */
protected:
    bool m_isUseMipmap;
};

inline GenericTexture::~GenericTexture() = default;

} /* namespace tgon */