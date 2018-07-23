/**
 * @file    Texture.h
 * @author  ggomdyu
 * @since   02/20/2018
 */

#pragma once
#include <memory>
#include <boost/noncopyable.hpp>

#include "Core/Platform/Config.h"
#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLTexture.h"
#endif

namespace tgon
{
    
struct TextureProperty;
enum class TextureFilterMode;
enum class TextureWrapMode;
enum class PixelFormat;
    
class Texture final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    /* @brief   Initializes texture through specified file path. */
    Texture(const std::string& filePath);
    
    /* @brief   Initializes texture through specified file path and texture property. */
    Texture(const std::string& filePath, const TextureProperty& textureProperty);
    
/* @section Public destructor */
public:
    ~Texture();
    
/* @section Public method */
public:
    /* @brief   Changes rendering pipeline state to use this texture. */
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
    uint8_t* GetImageData() noexcept;
    
    /* @brief   Gets the raw image data. */
    const uint8_t* GetImageData() const noexcept;
    
    /* @brief   Gets the image width. */
    int32_t GetWidth() const noexcept;
    
    /* @brief   Gets the image height. */
    int32_t GetHeight() const noexcept;
    
    /* @brief   Gets the count of color channel. */
    int32_t GetChannels() const noexcept;
    
    /* @brief   Gets the pixel format of image. */
    PixelFormat GetPixelFormat() const noexcept;
    
    /**
     * @brief   Gets the file path saved at loading time.
     * @warn    This can not be correct information if the file moved somewhere after image loaded.
     */
    const std::string& GetFilePath() const noexcept;

    TextureImpl& GetTextureImpl() noexcept;
    
    const TextureImpl& GetTextureImpl() const noexcept;
  
/* @section Private variable */
public:
    TextureImpl m_textureImpl;
};
    
} /* namespace tgon */
