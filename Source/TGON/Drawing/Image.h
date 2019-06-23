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
     * @brief   Initializes with the specified path of the image.
     * @param [in] filePath     The file path of image.
     */
    explicit Image(const std::string_view& filePath);

    /**
     * @brief   Initializes with the encoded image data.
     * @param [in] fileData         The pointer to the encoded file data.
     * @param [in] fileDataBytes    The bytes size of the encoded file data.
     */
    Image(const uint8_t* fileData, int32_t fileDataBytes);
    
    /**
     * @brief   Initializes with the decoded image data.
     * @param [in] imageData    The pointer to the decoded image data.
     * @param [in] size         The size of the image.
     * @param [in] pixelFormat  The type of the pixel encoding.
     */
    Image(uint8_t* imageData, const I32Extent2D& size, PixelFormat pixelFormat);

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

    /**
     * @brief   Sets the decoded raw image data.
     * @param [in] imageData        The pointer to the decoded image data
     * @param [in] imageDataBytes   The bytes size of the decoded image data
     */
    void SetImageData(uint8_t* imageData, const I32Extent2D& size, PixelFormat pixelFormat);

    /**@brief   Gets the decoded raw image data. */
    std::unique_ptr<uint8_t[]>& GetImageData() noexcept;

    /**@brief   Gets the decoded raw image data. */
    const std::unique_ptr<uint8_t[]>& GetImageData() const noexcept;
    
    /**@brief   Gets the image size. */
    const I32Extent2D& GetSize() const noexcept;

    /**@brief   Gets the count of color channel. */
    int32_t GetChannels() const noexcept;

    /**@brief   Gets the pixel format of image. */
    PixelFormat GetPixelFormat() const noexcept;

    /**
     * @brief   Saves the image as PNG.
     * @param [in] destFilePath     The path to save the image.
     * @return  Returns true if the save was successful, false otherwise.
     */
    bool SaveAsPng(const char* destFilePath);

    /**
     * @brief   Saves the image as JPEG.
     * @param [in] destFilePath     The path to save the image.
     * @param [in] quality          The quality of JPEG image. It has value between 1 and 100. Higher quality is looks better but the file size is also bigger.
     * @return  Returns true if the save was successful, false otherwise.
     */
    bool SaveAsJpeg(const char* destFilePath, int32_t quality);

    /**
     * @brief   Saves the image as BMP.
     * @param [in] destFilePath     The path to save the image.
     * @return  Returns true if the save was successful, false otherwise.
     */
    bool SaveAsBmp(const char* saveFilePath);

    /**
     * @brief   Saves the image as TGA.
     * @param [in] destFilePath     The path to save the image.
     * @return  Returns true if the save was successful, false otherwise.
     */
    bool SaveAsTga(const char* destFilePath);

/**@section Variable */
private:
    std::unique_ptr<uint8_t[]> m_imageData;
    I32Extent2D m_size;
    PixelFormat m_pixelFormat;
};

} /* namespace tgon */
