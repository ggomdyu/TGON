/**
 * @file    Bitmap.h
 * @author  ggomdyu
 * @since   01/20/2018
 */

#pragma once
#include <vector>
#include <cstdint>
#include <algorithm>
#include <string>

#include "Core/Platform/Config.h"

#include "ImageType.h"

namespace tgon
{

class Image
{
/* @section Public constructor */
public:
    Image();

    /**
     * @brief                   Reads a image data from the specified path.
     * @param [in] filePath     The file path of image
     */
    explicit Image(const std::string& filePath);

    /**
     * @brief                   Reads a image data from memory.
     * @param [in] filePath     The file path of image file
     * @param [in] srcData      The pointer to image data
     * @param [in] srcDataBytes The bytes of image data
     * @param [in] imageFormat  The format of image
     */
    Image(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes, ImageFormat imageFormat);
    
    /**
     * @brief                   Reads a image data from memory.
     * @param [in] filePath     The file path of image source
     * @param [in] srcData      The pointer to image data
     * @param [in] srcDataBytes The bytes of image data
     */
    Image(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes);
    
    Image(const Image& rhs) = default;
    Image(Image&& rhs);
    
/* @section Public operator */
public:
    Image& operator=(const Image& rhs) = default;
    Image& operator=(Image&& rhs);

    /* @brief   Gets the raw pointer of image. */
    uint8_t& operator[](std::size_t index);

    /* @brief   Gets the raw pointer of image. */
    const uint8_t& operator[](std::size_t index) const;

/* @section Public method */
public:
    /**
     * @brief                   Reads a image data from the path specified by filePath.
     * @param [in] filePath     The file path of image
     */
    bool Initialize(const std::string& filePath);

    /**
     * @brief                   Reads a image file data from memory.
     * @param [in] filePath     The file path of image source
     * @param [in] srcData      The pointer to image data
     * @param [in] srcDataBytes The bytes of image data
     */
    bool Initialize(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes);
    
    /* @brief   Checks the image file was loaded successfully. */
    bool IsValid() const noexcept;

    /* @brief   Gets the raw image data. */
    std::unique_ptr<uint8_t[]>& GetImageData() noexcept;

    /* @brief   Gets the raw image data. */
    const std::unique_ptr<uint8_t[]>& GetImageData() const noexcept;
    
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

    void SaveAsPng(const char* saveFilePath);
    void SaveAsJpg(const char* saveFilePath);
    void SaveAsWebP(const char* saveFilePath);

/* @section Private variable */
private:
    std::unique_ptr<uint8_t[]> m_imageData;
    int32_t m_width;
    int32_t m_height;
    int32_t m_channels;
    int32_t m_colorDepth;
    PixelFormat m_pixelFormat;
    std::string m_filePath;
};

class AnimatedImage
{
};

} /* namespace tgon */  
