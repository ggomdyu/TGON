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
        return ImageFormat::Bmp;
    case X65599Hash("jpg"):
        return ImageFormat::Jpg;
    case X65599Hash("jpeg"):
        return ImageFormat::Jpeg;
    case X65599Hash("png"):
        return ImageFormat::Png;
    case X65599Hash("tiff"):
        return ImageFormat::Tiff;
    case X65599Hash("gif"):
        return ImageFormat::Gif;
    case X65599Hash("webp"):
        return ImageFormat::WebP;
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