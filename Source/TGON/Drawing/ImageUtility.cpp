#include "PrecompiledHeader.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#ifdef _MSC_VER
#   define STBI_MSC_SECURE_CRT
#endif
#include <stb_image.h>

#include "String/StringTraits.h"
#include "String/Hash.h"

#if TGON_USE_LOWLEVEL_IMAGE_IMPORTER
#   include "ImageProcessor/BmpImageProcessor.h"
#   include "ImageProcessor/JpgImageProcessor.h"
#   include "ImageProcessor/PngImageProcessor.h"
#endif
#include "ImageProcessor/WebPImageProcessor.h"

#include "ImageUtility.h"

namespace tgon
{

TGON_API std::unique_ptr<uint8_t[]> LoadImageData(const char* filePath, int32_t* width, int32_t* height, int32_t* channels)
{
#if defined(_MSC_VER) && _MSC_VER >= 1400
    FILE* file = nullptr;
    fopen_s(&file, filePath, "rb");
#else
    FILE* file = fopen(filePath, "rb");
#endif
    if (file == nullptr)
    {
        return nullptr;
    }
    
    fseek(file, 0, SEEK_END);
    int32_t fileSize = static_cast<int32_t>(ftell(file));
    fseek(file, 0, SEEK_SET);

    auto fileData = std::make_unique<uint8_t[]>(fileSize);
    fread(fileData.get(), 1, fileSize, file);
    fclose(file);

    return LoadImageData(fileData.get(), fileSize, width, height, channels);
}

TGON_API std::unique_ptr<uint8_t[]> LoadImageData(const uint8_t* srcData, int32_t srcDataBytes, int32_t* width, int32_t* height, int32_t* channels)
{
#if TGON_USE_LOWLEVEL_IMAGE_IMPORTER
    auto loadImage = [&](auto& imageProcessor)
    {
        *width = imageProcessor.GetWidth();
        *height = imageProcessor.GetHeight();
        *channels = imageProcessor.GetChannels();
        return std::move(imageProcessor.GetImageData());
    };

    if (PngImageProcessor::VerifyFormat(srcData, srcDataBytes))
    {
        return loadImage(PngImageProcessor(srcData, srcDataBytes));
    }
    else if (JpgImageProcessor::VerifyFormat(srcData, srcDataBytes))
    {
        return loadImage(JpgImageProcessor(srcData, srcDataBytes));
    }
    else if (BmpImageProcessor::VerifyFormat(srcData, srcDataBytes))
    {
        return loadImage(BmpImageProcessor(srcData, srcDataBytes));
    }
#endif

    return std::unique_ptr<uint8_t[]>(stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(srcData), srcDataBytes, width, height, channels, 4));
}

TGON_API ImageFormat ConvertStringToImageFormat(const std::string_view& str)
{
    char lowercaseStr[32]{};
    BasicStringTraits<char>::ToLower(str, lowercaseStr, std::extent<decltype(lowercaseStr)>::value);

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