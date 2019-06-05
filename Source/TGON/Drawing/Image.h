/**
 * @file    Image.h
 * @author  ggomdyu
 * @since   01/20/2018
 */

#pragma once
#include <vector>
#include <algorithm>
#include <string>

#include "String/StringHash.h"
#include "Math/Extent.h"

#include "ImageUtility.h"

namespace tgon
{

class TGON_API Image
{
/**@section Constructor */
public:
    Image() noexcept;

    /**
     * @brief   Reads an image data from the specified path.
     * @param [in] filePath     The file path of image
     */
    template <typename _StringType>
    explicit Image(_StringType&& filePath);

    /**
     * @brief   Reads an image data from memory.
     * @param [in] filePath     The file path of image file
     * @param [in] srcData      The pointer to image data
     * @param [in] srcDataBytes The bytes of image data
     */
    template <typename _StringType>
    Image(_StringType&& filePath, const uint8_t* srcData, int32_t srcDataBytes);
    
    Image(Image&& rhs) noexcept;

/**@section Operator */
public:
    Image& operator=(Image&& rhs);

    /**@brief   Gets the raw pointer of image. */
    uint8_t& operator[](std::size_t index);

    /**@brief   Gets the raw pointer of image. */
    const uint8_t operator[](std::size_t index) const;

/**@section Method */
public:
    /**@brief   Checks the image file was loaded successfully. */
    bool IsValid() const noexcept;

    /**@brief   Gets the raw image data. */
    std::unique_ptr<uint8_t>& GetImageData() noexcept;

    /**@brief   Gets the raw image data. */
    const std::unique_ptr<uint8_t>& GetImageData() const noexcept;
    
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

    /**
     * @brief   Gets the file path saved at loading time.
     * @warn    It can be incorrect if the file moved somewhere after image loaded.
     */
    const StringHash& GetFilePath() const noexcept;

    /**
     * @brief   Saves the image as PNG.
     * @param [in] saveFilePath The path to the file where you want to save the image.  
     * @return  Returns true if the save was saved successfully, false otherwise.
     */
    bool SaveAsPng(const char* saveFilePath);

    /**
     * @brief   Saves the image as JPEG.
     * @param [in] saveFilePath The path to the file where you want to save the image.  
     * @param [in] quality      The quality of JPEG image. It has value between 1 and 100.
                                Higher quality is looks better but the file size is also bigger.
     * @return  Returns true if the save was saved successfully, false otherwise.
     */
    bool SaveAsJpeg(const char* saveFilePath, int32_t quality);

    /**
     * @brief   Saves the image as BMP.
     * @param [in] saveFilePath The path to the file where you want to save the image.  
     * @return  Returns true if the save was saved successfully, false otherwise.
     */
    bool SaveAsBmp(const char* saveFilePath);

    /**
     * @brief   Saves the image as TGA.
     * @param [in] saveFilePath The path to the file where you want to save the image.  
     * @return  Returns true if the save was saved successfully, false otherwise.
     */
    bool SaveAsTga(const char* saveFilePath);

private:
  

private:
    void Destroy();

/**@section Variable */
private:
    std::unique_ptr<uint8_t> m_imageData;
    int32_t m_width;
    int32_t m_height;
    int32_t m_channels;
    PixelFormat m_pixelFormat;
    StringHash m_filePath;
};

template<typename _StringType>
inline Image::Image(_StringType&& filePath) :
    m_filePath(filePath),
    m_imageData(),
    m_pixelFormat(m_channels == 4 ? PixelFormat::RGBA8888 : m_channels == 3 ? PixelFormat::RGB888 : PixelFormat::Unknown)
{
}

template<typename _StringType>
inline Image::Image(_StringType&& filePath, const uint8_t* srcData, int32_t srcDataBytes) :
    m_filePath(filePath),
    m_imageData(),
    m_pixelFormat(m_channels == 4 ? PixelFormat::RGBA8888 : m_channels == 3 ? PixelFormat::RGB888 : PixelFormat::Unknown)
{
}

} /* namespace tgon */
