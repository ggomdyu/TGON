/**
 * @filename    Bitmap.h
 * @author      ggomdyu
 * @since       01/20/2018
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
    /**
     * @brief                   Reads a image data from the given path specified by filePath.
     * @param [in] filePath     The path of image file
     */
    explicit Image(const std::string& filePath);

    /**
     * @brief                   Reads a image data from memory.
     * @param [in] imageFormat  The format of image
     * @param [in] srcData      The pointer to image data
     * @param [in] srcDataBytes The bytes of image data
     */
    Image(ImageFormat imageFormat, const uint8_t* srcData, std::size_t srcDataBytes);
    
    Image(const Image& rhs) = default;
    Image(Image&& rhs);
    
/* @section Private constructor */
private:
    Image();

/* @section Public operator */
public:
    Image& operator=(const Image& rhs) = default;
    Image& operator=(Image&& rhs);

    /* @brief   Returns the raw pointer of image. */
    uint8_t& operator[](std::size_t index);

    /* @brief   Returns the raw pointer of image. */
    const uint8_t& operator[](std::size_t index) const;

/* @section Public method */
public:
    /* @brief   Checks the image file was loaded successfully. */
    bool IsValid() const noexcept;

    /* @brief   Returns the raw pointer of image. */
    std::vector<uint8_t>& GetBits() noexcept;

    /* @brief   Returns the raw pointer of image. */
    const std::vector<uint8_t>& GetBits() const noexcept;
    
    /* @brief   Returns the width of image. */
    int32_t GetWidth() const noexcept;

    /* @brief   Returns the height of image. */
    int32_t GetHeight() const noexcept;

    /* @brief   Returns the count of color channel. */
    int32_t GetChannels() const noexcept;

    int32_t GetColorDepth() const noexcept;

    /* @brief   Returns the pixel format of image. */
    PixelFormat GetPixelFormat() const noexcept;

    /* @brief   Returns the file path saved at loading time. */
    const std::string& GetFilePath() const noexcept;

/* @section Private variable */
private:
    std::vector<uint8_t> m_imageBits;
    int32_t m_width;
    int32_t m_height;
    int32_t m_channels;
    int32_t m_colorDepth;
    PixelFormat m_pixelFormat;
    std::string m_filePath;
};

} /* namespace tgon */  