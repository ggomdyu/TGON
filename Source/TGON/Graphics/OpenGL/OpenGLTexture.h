/**
 * @file    OpenGLTexture.h
 * @author  ggomdyu
 * @since   02/20/2018
 */

#pragma once
#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include "Drawing/Image.h"

#include "../TextureType.h"

namespace tgon
{

class TGON_API OpenGLTexture :
    private boost::noncopyable
{
/**@section Constructor */
public:
    OpenGLTexture(const std::string& filePath, TextureFilterMode filterMode, TextureWrapMode wrapMode, bool isUseMipmap);

    OpenGLTexture(Image&& image, TextureFilterMode filterMode, TextureWrapMode wrapMode, bool isUseMipmap);

private:

/**@section Destructor */
public:
    ~OpenGLTexture();

/**@section Method */
public:
    /**@brief   Changes rendering pipeline state to use this texture. */
    void Use();
    
    /**@brief   Changes rendering pipeline state to not use the texture. */
    void Unuse();
    
    /**@brief   Sets the texture filter mode. */
    void SetFilterMode(TextureFilterMode filterMode);
    
    /**@brief   Sets the texture wrap mode. */
    void SetWrapMode(TextureWrapMode wrapMode);
    
    /**@brief   Gets the texture filter mode. */
    TextureFilterMode GetFilterMode() const noexcept;
    
    /**@brief   Gets the texture wrap mode. */
    TextureWrapMode GetWrapMode() const noexcept;
    
    /**@brief   Gets the handle of texture object. */
    GLuint GetTextureHandle() const noexcept;
    
    /**@brief   Gets the image width. */
    int32_t GetWidth() const noexcept;
    
    /**@brief   Gets the image height. */
    int32_t GetHeight() const noexcept;
    
    /**@brief   Gets the size of image which contains width and height. */
    I32Extent2D GetSize() const noexcept;
    
    /**@brief   Gets the pixel format of image. */
    PixelFormat GetPixelFormat() const noexcept;
    
private:
    void TransferToVideo();
    void UpdateTexParemeters();
    GLuint CreateTextureHandle() const;
    void CreateMipmap() const;

private:
    bool m_isUseMipmap;
    GLuint m_textureHandle;
    TextureFilterMode m_filterMode;
    TextureWrapMode m_wrapMode;
    PixelFormat m_pixelFormat;
    int32_t m_width;
    int32_t m_height;
    std::unique_ptr<uint8_t> m_imageData;
};

using PlatformTexture = OpenGLTexture;

} /* namespace tgon */
