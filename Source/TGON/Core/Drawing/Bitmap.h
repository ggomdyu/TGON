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

class Bitmap final
{
public:
    /**
     * @brief                   Read a image data from the given path specified by 'filePath'.
     * @param [in] filePath     The path of image file
     */
    explicit Bitmap(const std::string& filePath);

    /**
     * @brief                   Read a image data from memory.
     * @param [in] imageFormat  The format of image
     * @param [in] srcData      The pointer to image data
     * @param [in] srcDataLen   The bytes of image data
     */
    explicit Bitmap(ImageFormat imageFormat, const uint8_t* srcData, std::size_t srcDataBytes);

public:
    uint8_t& operator[](std::size_t index);
    const uint8_t& operator[](std::size_t index) const;

public:
    std::vector<uint8_t>& GetBits();
    const std::vector<uint8_t>& GetBits() const;
    int32_t GetBitsPerPixel() const;
    PixelFormat GetPixelFormat() const;
    int32_t GetWidth() const;
    int32_t GetHeight() const;
    const std::string& GetFilePath() const;

private:
    std::vector<uint8_t> m_bits;
    int32_t m_bitsPerPixel;
    PixelFormat m_pixelFormat;
    int32_t m_width;
    int32_t m_height;
    std::string m_filePath;
};

} /* namespace core */
} /* namespace tgon */
