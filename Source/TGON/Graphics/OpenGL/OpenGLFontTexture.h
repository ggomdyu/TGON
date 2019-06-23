/**
 * @file    OpenGLFontTexture.h
 * @author  ggomdyu
 * @since   06/06/2019
 */

#pragma once
#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include "Drawing/Image.h"

#include "../TextureType.h"

namespace tgon
{

class TGON_API OpenGLFontTexture :
    private boost::noncopyable
{
/**@section Constructor */
public:
    /**@brief   Initializes texture through specified file path and texture property. */
    explicit OpenGLFontTexture(const char* filePath, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap);

/**@section Destructor */
public:
    ~OpenGLFontTexture();

/**@section Method */
public:
    /**@brief   Changes rendering pipeline state to use this texture. */
    void Use();
    
    /**@brief   Changes rendering pipeline state to not use the texture. */
    void Unuse();
    
    /**@brief   Sets the texture filter mode. */
    void SetFilterMode(FilterMode filterMode);
    
    /**@brief   Sets the texture wrap mode. */
    void SetWrapMode(WrapMode wrapMode);
    
    /**@brief   Gets the texture filter mode. */
    FilterMode GetFilterMode() const noexcept;
    
    /**@brief   Gets the texture wrap mode. */
    WrapMode GetWrapMode() const noexcept;
    
    /**@brief   Gets the handle of texture object. */
    GLuint GetTextureHandle() const noexcept;
    
    /**@brief   Checks the image file was loaded successfully. */
    bool IsValid() const noexcept;
    
    /**@brief   Gets the image width. */
    int32_t GetWidth() const noexcept;
    
    /**@brief   Gets the image height. */
    int32_t GetHeight() const noexcept;
    
    /**@brief   Gets the size of image which contains width and height. */
    I32Extent2D GetSize() const noexcept;
    
    /**@brief   Gets the count of color channel. */
    int32_t GetChannels() const noexcept;
    
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
    FilterMode m_filterMode;
    WrapMode m_wrapMode;
    Image m_image;
    int32_t m_width;
    int32_t m_height;
};

using PlatformTexture = OpenGLFontTexture;

} /* namespace tgon */
