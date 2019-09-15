/**
 * @file    Image.h
 * @author  ggomdyu
 * @since   01/20/2018
 */

#pragma once
#include <vector>
#include <string_view>
#include <algorithm>

#include "Platform/Config.h"
#include "Math/Extent.h"

namespace tgon
{

enum class ImageFormat
{
    Unknown = 0,
    Bmp,
    Jpg,
    Jpeg = Jpg,
    Png,
    Tiff,
    Gif,
    WebP,
};

enum class PixelFormat
{
    Unknown = 0,
    RGBA8888,
    RGB888,
    RGBA4444,
    R8,
};

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
    Image(const std::byte* fileData, int32_t fileDataBytes);
    
    /**
     * @brief   Initializes with the decoded image data.
     * @param [in] imageData    The pointer to the decoded image data.
     * @param [in] size         The size of the image.
     * @param [in] pixelFormat  The type of the pixel encoding.
     */
    Image(std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat);

    Image(Image&& rhs) noexcept;

/**@section Destructor */
public:
    ~Image() = default;

/**@section Operator */
public:
    Image& operator=(Image&& rhs) noexcept;
    std::byte& operator[](std::size_t index);
    std::byte operator[](std::size_t index) const;

/**@section Method */
public:
    bool IsValid() const noexcept;
    void SetImageData(std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat);
    std::unique_ptr<std::byte[]>& GetImageData() noexcept;
    const std::unique_ptr<std::byte[]>& GetImageData() const noexcept;
    const I32Extent2D& GetSize() const noexcept;
    int32_t GetChannels() const noexcept;
    PixelFormat GetPixelFormat() const noexcept;
    bool SaveAsPng(const char* destFilePath) const;
    bool SaveAsJpeg(const char* destFilePath, int32_t quality) const;
    bool SaveAsBmp(const char* destFilePath) const;
    bool SaveAsTga(const char* destFilePath) const;

/**@section Variable */
private:
    std::unique_ptr<std::byte[]> m_imageData;
    I32Extent2D m_size;
    PixelFormat m_pixelFormat;
};

constexpr int32_t ConvertPixelFormatToBytesPerPixel(PixelFormat pixelFormat)
{
    constexpr int32_t bitsPerPixelTable[] = {
        0, // Unknown
        4, // RGBA8888
        3, // RGB888
        2, // RGBA4444
        1, // R8
    };
    
    return bitsPerPixelTable[static_cast<int>(pixelFormat)];
}

constexpr int32_t ConvertPixelFormatToBitsPerPixel(PixelFormat pixelFormat)
{
    return ConvertPixelFormatToBytesPerPixel(pixelFormat) * 8;
}

/*todo: deprecated. Use tgon::Span */
class TGON_API ImageView
{
/**@section Constructor */
public:
    /**
     * @brief   Initializes with the decoded image data.
     * @param [in] imageData    The pointer to the decoded image data.
     * @param [in] size         The size of the image.
     * @param [in] pixelFormat  The type of the pixel encoding.
     */
    ImageView(std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat);

    /**
     * @brief   Initializes with the image.
     * @param [in] image        The reference to the image.
     */
    ImageView(Image& image);
    
/**@section Operator */
public:
    /**@brief   Gets the raw pointer of image. */
    std::byte& operator[](std::size_t index);

    /**@brief   Gets the raw pointer of image. */
    const std::byte operator[](std::size_t index) const;

/**@section Method */
public:
    /**@brief   Gets the decoded raw image data. */
    std::byte* GetImageData() noexcept;

    /**@brief   Gets the decoded raw image data. */
    const std::byte* GetImageData() const noexcept;

    /**@brief   Gets the image size. */
    const I32Extent2D& GetSize() const noexcept;

    /**@brief   Gets the count of color channel. */
    int32_t GetChannels() const noexcept;

    /**@brief   Gets the pixel format of image. */
    PixelFormat GetPixelFormat() const noexcept;

/**@section Variable */
public:
    std::byte* m_imageData;
    I32Extent2D m_size;
    PixelFormat m_pixelFormat;
};

} /* namespace tgon */
