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

namespace tgon
{

enum class PixelFormat;

class TGON_API Image
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
    Image(const std::string& filePath, const uint8_t* srcData, int32_t srcDataBytes);
    
    Image(const Image& rhs) = default;

    Image(Image&& rhs);
    
/* @section Public destructor */
public:
    ~Image();
    
/* @section Public operator */
public:
    Image& operator=(const Image& rhs) = default;

    Image& operator=(Image&& rhs);

    /* @brief                   Gets the raw pointer of image. */
    uint8_t& operator[](std::size_t index);

    /* @brief                   Gets the raw pointer of image. */
    const uint8_t operator[](std::size_t index) const;

/* @section Public method */
public:
    /* @brief                   Checks the image file was loaded successfully. */
    bool IsValid() const noexcept;

    /* @brief                   Gets the raw image data. */
    uint8_t* GetImageData() noexcept;

    /* @brief                   Gets the raw image data. */
    const uint8_t* GetImageData() const noexcept;
    
    /* @brief                   Gets the image width. */
    int32_t GetWidth() const noexcept;

    /* @brief                   Gets the image height. */
    int32_t GetHeight() const noexcept;

    /* @brief                   Gets the count of color channel. */
    int32_t GetChannels() const noexcept;

    /* @brief                   Gets the pixel format of image. */
    PixelFormat GetPixelFormat() const noexcept;

    /**
     * @brief                   Gets the file path saved at loading time.
     * @warn                    This can be incorrect information if the file moved somewhere after image loaded.
     */
    const std::string& GetFilePath() const noexcept;

    /**
     * @brief                   Saves the image as PNG.
     * @param [in] saveFilePath The path to the file where you want to save the image.  
     * @return                  Returns true if the save was saved successfully, false otherwise.
     */
    bool SaveAsPng(const char* saveFilePath);

    /**
     * @brief                   Saves the image as JPEG.
     * @param [in] saveFilePath The path to the file where you want to save the image.  
     * @param [in] quality      The quality of JPEG image. It has value between 1 and 100.
                                Higher quality is looks better but the file size is also bigger.
     * @return                  Returns true if the save was saved successfully, false otherwise.
     */
    bool SaveAsJpeg(const char* saveFilePath, int32_t quality);

    /**
     * @brief                   Saves the image as BMP.
     * @param [in] saveFilePath The path to the file where you want to save the image.  
     * @return                  Returns true if the save was saved successfully, false otherwise.
     */
    bool SaveAsBmp(const char* saveFilePath);

    /**
     * @brief                   Saves the image as TGA.
     * @param [in] saveFilePath The path to the file where you want to save the image.  
     * @return                  Returns true if the save was saved successfully, false otherwise.
     */
    bool SaveAsTga(const char* saveFilePath);

/* @section Private variable */
private:
    uint8_t* m_imageData;
    int32_t m_width;
    int32_t m_height;
    int32_t m_channels;
    std::string m_filePath;
};

} /* namespace tgon */  
