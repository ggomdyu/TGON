/**
 * @file    OpenGLTexture.h
 * @author  ggomdyu
 * @since   02/20/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <GL/glew.h>

#include "Core/Drawing/Image.h"

namespace tgon
{
    
struct TextureProperty;
enum class TextureFilterMode;
enum class TextureWrapMode;
    
class TextureImpl final :
    private Image,
    private boost::noncopyable
{
/* @section Public constructor */
public:
    TextureImpl(const std::string& filePath, const TextureProperty& textureProperty);

/* @section Public destructor */
public:
    ~TextureImpl();

/* @section Public method */
public:
    void Use();
    
    /* @brief   Sets the texture filter mode. */
    void SetFilterMode(TextureFilterMode filterMode);
    
    /* @brief   Sets the texture wrap mode. */
    void SetWrapMode(TextureWrapMode wrapMode);
    
    /* @brief   Gets the texture filter mode. */
    TextureFilterMode GetFilterMode() const noexcept;
    
    /* @brief   Gets the texture wrap mode. */
    TextureWrapMode GetWrapMode() const noexcept;
    
    /* @brief   Checks the image file was loaded successfully. */
    bool IsValid() const noexcept;
    
    /* @brief   Gets the raw image data. */
    std::vector<uint8_t>& GetImageData() noexcept;
    
    /* @brief   Gets the raw image data. */
    const std::vector<uint8_t>& GetImageData() const noexcept;
    
    /* @brief   Gets the image width. */
    int32_t GetWidth() const noexcept;
    
    /* @brief   Gets the image height. */
    int32_t GetHeight() const noexcept;
    
    /* @brief   Gets the count of color channel. */
    int32_t GetChannels() const noexcept;
    
    int32_t GetColorDepth() const noexcept;
    
    /* @brief   Gets the pixel format of image. */
    PixelFormat GetPixelFormat() const noexcept;
    
    /**
     * @brief   Gets the file path saved at loading time.
     * @warn    This can not be correct information if the file moved somewhere after image loaded.
     */
    const std::string& GetFilePath() const noexcept;
    
    /* @brief   Gets the handle of texture object. */
    GLuint GetTextureHandle() const noexcept;

private:
    void TransferToVideo();
    void UpdateParemeters();
    GLuint CreateTextureHandle() const;
    void CreateMipmap() const;

private:
    bool m_isUseMipmap;
    GLuint m_textureHandle;
    GLint m_filterMode;
    GLint m_wrapMode;
};

} /* namespace tgon */
