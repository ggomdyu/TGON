#include "PrecompiledHeader.h"

#include "String/StringTraits.h"
#include "String/Hash.h"

#include "ImageUtility.h"

namespace tgon
{

ImageFormat ImageUtilty::ConvertStringToImageFormat(const char * imageFormatStr, std::size_t imageFormatStrLen)
{
    char lowercaseStr[32]{};
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

} /* namespace tgon */
