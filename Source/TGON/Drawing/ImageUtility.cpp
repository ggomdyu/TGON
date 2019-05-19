#include "PrecompiledHeader.h"

#include "String/StringTraits.h"
#include "String/Hash.h"

#include "ImageUtility.h"

namespace tgon
{

ImageFormat ImageUtilty::ConvertStringToImageFormat(const char * imageFormatStr, std::size_t imageFormatStrLen)
{
    char lowercaseStr[32]{};
    BasicStringTraits<char>::ToLower(imageFormatStr, lowercaseStr, std::extent<decltype(lowercaseStr)>::value);

    switch (X65599Hash(lowercaseStr))
    {
    case TGON_X65599("bmp"):
        return ImageFormat::Bmp;
    case TGON_X65599("jpg"):
        return ImageFormat::Jpg;
    case TGON_X65599("jpeg"):
        return ImageFormat::Jpeg;
    case TGON_X65599("png"):
        return ImageFormat::Png;
    case TGON_X65599("tiff"):
        return ImageFormat::Tiff;
    case TGON_X65599("gif"):
        return ImageFormat::Gif;
    case TGON_X65599("webp"):
        return ImageFormat::WebP;
    default:
        return ImageFormat::Unknown;
    }
}

} /* namespace tgon */
