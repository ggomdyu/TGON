/**
 * @filename    ImageUtility.h
 * @author      ggomdyu
 * @since       04/10/2018
 */

#pragma once
#include <cstdint>

#include "Core/String/StringTraits.h"

#include "ImageType.h"

namespace tgon
{


inline ImageFormat ConvertStringToImageFormat(const char* imageFormatStr, std::size_t imageFormatStrLen)
{
    char lowercaseStr[32] {};
    StringTraits<char>::ToLower(imageFormatStr, lowercaseStr);

    switch (X65599Hash(lowercaseStr))
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


} /* namespace tgon */  