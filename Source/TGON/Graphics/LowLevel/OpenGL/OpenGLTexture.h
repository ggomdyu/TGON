/**
 * @file    OpenGLTexture.h
 * @author  ggomdyu
 * @since   02/20/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Drawing/Image.h"

#include "../TextureType.h"

namespace tgon
{

class TGON_API OpenGLTexture final :
    private Image,
    private boost::noncopyable
{
/**@section Public constructor */
public:
    /**@brief   Initializes texture through specified file path and texture property. */
    OpenGLTexture(const std::string& filePath, const TextureProperty& textureProperty);

/**@section Public destructor */
public:
    ~OpenGLTexture();

/**@section Public method */
public:
    /**@brief   Changes rendering pipeline state to use this texture. */
    void Use();
    
    /**@brief   Sets the texture filter mode. */
    void SetFilterMode(TextureFilterMode filterMode);
    
    /**@brief   Sets the texture wrap mode. */
    void SetWrapMode(TextureWrapMode wrapMode);
    
    /**@brief   Gets the texture filter mode. */
    TextureFilterMode GetFilterMode() const noexcept;
    
    /**@brief   Gets the texture wrap mode. */
    TextureWrapMode GetWrapMode() const noexcept;
    
    /**@brief   Checks the image file was loaded successfully. */
    using Image::IsValid;
    
    /**@brief   Gets the raw image data. */
    using Image::GetImageData;
    
    /**@brief   Gets the image width. */
    using Image::GetWidth;
    
    /**@brief   Gets the image height. */
    using Image::GetHeight;
    
    /**@brief   Gets the count of color channel. */
    using Image::GetChannels;
    
    /**@brief   Gets the pixel format of image. */
    using Image::GetPixelFormat;
    
    /**
     * @brief   Gets the file path saved at loading time.
     * @warn    This can be incorrect information if the file moved somewhere after image loaded.
     */
    using Image::GetFilePath;
    
    /**@brief   Gets the handle of texture object. */
    GLuint GetTextureHandle() const noexcept;

private:
    void TransferToVideo();
    
    void UpdateTexParemeters();
    
    GLuint CreateTextureHandle() const;
    
    void CreateMipmap() const;

private:
    bool m_isUseMipmap;
    GLuint m_textureHandle;
    GLint m_filterMode;
    GLint m_wrapMode;
};

using PlatformTexture = OpenGLTexture;

} /* namespace tgon */
