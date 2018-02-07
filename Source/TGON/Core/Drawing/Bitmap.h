/**
 * @filename    Bitmap.h
 * @author      ggomdyu
 * @since       01/20/2018
 */

#pragma once
#include "Core/Platform/Config.h"
#include "Core/Hash/Hash.h"

#include <vector>
#include <cstdint>
#include <algorithm>
#include <string>

namespace tgon
{
namespace core
{

enum class ImageFormat
{
    Unknown = 0,
    BMP,
    JPG,
    JPEG = JPG,
    PNG,
    TIFF,
    GIF,
    WEBP,
};

enum class PixelFormat
{
    Unknown = 0,
    R8G8B8A8_UNORM,
    R8G8B8_UNORM,
    PVRTC2,
    PVRTC4,
};

inline ImageFormat ConvertStringToImageFormat(const char* imageFormatStr, std::size_t imageFormatStrLen)
{
    char lowercaseString[32] {};
    std::transform(imageFormatStr, imageFormatStr + imageFormatStrLen + 1, lowercaseString, ::tolower);

    switch (X65599Hash(lowercaseString))
    {
    case X65599Hash("bmp"):
        return ImageFormat::BMP;
    case X65599Hash("jpg"):
        return ImageFormat::JPG;
    case X65599Hash("jpeg"):
        return ImageFormat::JPEG;
    case X65599Hash("png"):
        return ImageFormat::PNG;
    case X65599Hash("tiff"):
        return ImageFormat::TIFF;
    case X65599Hash("gif"):
        return ImageFormat::GIF;
    case X65599Hash("webp"):
        return ImageFormat::WEBP;
    }

    return ImageFormat::Unknown;
}

template <std::size_t ImageFormatStrLen>
inline ImageFormat ConvertStringToImageFormat(const char(&imageFormatStr)[ImageFormatStrLen])
{
    return ConvertStringToImageFormat(imageFormatStr, ImageFormatStrLen - 1);
}

constexpr const char* ConvertImageFormatToString(ImageFormat imageFormat)
{
    constexpr const char* imageFormatStringTable[] =
    {
        "bmp",
        "jpg",
        "jpeg",
        "png",
        "tiff",
        "gif",
        "webp",
    };

    return imageFormatStringTable[(std::size_t)imageFormat];
}

class Bitmap
{
/* @section Public constructor */
public:
    /**
     * @brief                   Reads a image data from the given path specified by 'filePath'.
     * @param [in] filePath     The path of image file
     */
    explicit Bitmap(const std::string& filePath);

    /**
     * @brief                   Reads a image data from memory.
     * @param [in] imageFormat  The format of image
     * @param [in] srcData      The pointer to image data
     * @param [in] srcDataLen   The bytes of image data
     */
    Bitmap(ImageFormat imageFormat, const uint8_t* srcData, std::size_t srcDataBytes);
    
    Bitmap(const Bitmap& rhs) = default;
    Bitmap(Bitmap&& rhs);

/* @section Public operator */
public:
    Bitmap& operator=(const Bitmap& rhs) = default;
    Bitmap& operator=(Bitmap&& rhs);

    /* @brief   Get the raw pointer of image. */
    uint8_t& operator[](std::size_t index);

    /* @brief   Get the raw pointer of image. */
    const uint8_t& operator[](std::size_t index) const;

/* @section Public method */
public:
    void Save(const char* filePath, ImageFormat imageFormat);

    /* @brief   Checks the image file was loaded successfully. */
    bool IsValid() const noexcept;

    /* @brief   Get the raw pointer of image. */
    std::vector<uint8_t>& GetBits() noexcept;

    /* @brief   Get the raw pointer of image. */
    const std::vector<uint8_t>& GetBits() const noexcept;
    
    /* @brief   Get the width of image. */
    int32_t GetWidth() const noexcept;

    /* @brief   Get the height of image. */
    int32_t GetHeight() const noexcept;

    int32_t GetChannels() const noexcept;

    int32_t GetColorDepth() const noexcept;

    int32_t GetBitsPerPixel() const noexcept;

    /* @brief   Get the pixel format of image. */
    PixelFormat GetPixelFormat() const noexcept;

    /* @brief   Get the file path saved at loading time. */
    const std::string& GetFilePath() const noexcept;

/* @section Private variable */
private:
    std::vector<uint8_t> m_bits;
    int32_t m_width;
    int32_t m_height;
    int32_t m_channels;
    int32_t m_colorDepth;
    PixelFormat m_pixelFormat;
    std::string m_filePath;
};

} /* namespace core */
} /* namespace tgon */  