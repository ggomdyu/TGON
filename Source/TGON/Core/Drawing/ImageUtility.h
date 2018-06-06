/**
 * @filename    ImageUtility.h
 * @author      ggomdyu
 * @since       04/10/2018
 */

#pragma once
#include <cstdint>

#include "Core/String/StringTraits.h"
#include "Core/Hash/Hash.h"

#include "ImageType.h"

namespace tgon
{

inline ImageFormat ConvertStringToImageFormat(const char* imageFormatStr, std::size_t imageFormatStrLen)
{
    char lowercaseStr[32] {};
    StringTraits<char>::ToLower(imageFormatStr, lowercaseStr, std::extent<decltype(lowercaseStr)>::value);

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
    default:
        return ImageFormat::Unknown;
    }
}

template <std::size_t _ImageFormatStrLen>
inline ImageFormat ConvertStringToImageFormat(const char(&imageFormatStr)[_ImageFormatStrLen])
{
    return ConvertStringToImageFormat(imageFormatStr, _ImageFormatStrLen - 1);
}

constexpr const char* ConvertImageFormatToString(ImageFormat imageFormat)
{
    constexpr const char* imageFormatStringTable[] =
    {
        "",
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
