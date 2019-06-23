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
    /**
     * @brief   Initializes with the specified path of the image.
     * @param [in] filePath     The file path of the image.
     * @param [in] filterMode   The filtering mode of the texture.
     * @param [in] wrapMode     The wrapping mode of the texture.
     */
    OpenGLTexture(const std::string_view& filePath, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage);

    /**
     * @brief   Initializes with the decoded texture data.
     * @param [in] imageData    The pointer to the decoded image data.
     * @param [in] size         The size of the texture.
     * @param [in] pixelFormat  The type of the pixel encoding.
     */
    OpenGLTexture(const uint8_t* imageData, const I32Extent2D& size, PixelFormat pixelFormat, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage);

    OpenGLTexture(Image&& image, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage);

/**@section Destructor */
public:
    ~OpenGLTexture();

/**@section Method */
public:
    /**@brief   Changes rendering pipeline state to use this texture. */
    void Use();
    
    /**@brief   Changes rendering pipeline state to not use the texture. */
    void Unuse();
    
    /**@brief   Sets image data into the buffer. */
    void SetData(const uint8_t* imageData, const I32Extent2D& size, PixelFormat pixelFormat);
    
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
    
    /**@brief   Gets the size of image which contains width and height. */
    const I32Extent2D& GetSize() const noexcept;
    
    /**@brief   Gets the pixel format of image. */
    PixelFormat GetPixelFormat() const noexcept;
    
private:
    void UpdateTexParemeters();
    GLuint CreateTextureHandle() const;
    GLuint CreatePixelBufferHandle(int32_t bufferBytes) const;
    void CreateMipmap() const;

private:
    bool m_isUseMipmap;
    bool m_isDynamicUsage;
    GLuint m_textureHandle;
    GLuint m_pixelBufferHandle;
    PixelFormat m_pixelFormat;
    FilterMode m_filterMode;
    WrapMode m_wrapMode;
    I32Extent2D m_size;
};

using PlatformTexture = OpenGLTexture;

} /* namespace tgon */
